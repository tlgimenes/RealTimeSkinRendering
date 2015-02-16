/*
 * =====================================================================================
 *       Filename:  main.cpp
 *    Description:  File containning calls and GLUT callbacks
 *        Created:  2015-02-11 19:45 
 *         Author:  Tiago Lobato Gimenes        (tlgimenes@gmail.com)
 * =====================================================================================
 */

////////////////////////////////////////////////////////////////////////////////////////

#include <cstdlib>

#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include "shader.hpp"
#include "shader_phong.hpp"
#include "shader_realskin.hpp"
#include "shader_blur.hpp"
#include "mesh.hpp"
#include "mesh_factory.hpp"
#include "mesh_gl.hpp"
#include "parser.hpp"
#include "camera.hpp"
#include "error.hpp"

////////////////////////////////////////////////////////////////////////////////////////
// GLUT variables
static GLint window;
static int SCREENWIDTH = 800;
static int SCREENHEIGHT = 600;
static bool mouseRotatePressed = false;
static bool mouseMovePressed = false;
static bool mouseZoomPressed = false;
static int lastX=0, lastY=0, lastZoom=0;
static unsigned int FPS = 0;
static bool full_screen = false;
static bool wireframe = false;
static bool shader = true;

////////////////////////////////////////////////////////////////////////////////////////
// Global variables
static Mesh<uchar>* meshs = NULL;
static MeshGL<uchar> *mesh_gl = NULL;
static ShaderRealskin* shader_realskin = NULL;
static ShaderPhong* shader_phong = NULL;
static ShaderBlur* shader_blur = NULL;
static Shader* curr_shader = NULL;
static Camera* camera = NULL;
static Camera* camera_phong = NULL;
static Camera* camera_realskin = NULL;
static std::vector<Texture<uchar>*>* textures = NULL;
static std::vector<GLuint> textures_ids;
static Vec3f background_color(0,0,0);

////////////////////////////////////////////////////////////////////////////////////////
// Init function. This function initializes the global variables as well as
// some OpenGL functionalities
void init (const std::string& file_name);

////////////////////////////////////////////////////////////////////////////////////////
// Callback functions declarations
void idle(); // Updates FPS model size and ask for Rendering
void display(); // Draw's
void key(unsigned char key, int x, int y); // key_pressed callbacks
void reshape(int w, int h);
void motion(int x, int y);
void mouse(int button, int state, int x, int y);

void drawGL4();

////////////////////////////////////////////////////////////////////////////////////////

/* ======= Function ==================================================
 *   Name: main
 *   Description: main entry Function
 * =================================================================== 
 */
int main(int argc, char *argv[])
{
    std::string file_path;      // path to the 3D model
    Parser parser(argc, argv);  // CLI parser

    parser.get_options(file_path); // Get program's options

    /* GLUT initialization */
    glutInit (&argc, argv);
    glutInitDisplayMode (GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
    glutInitWindowSize (SCREENWIDTH, SCREENHEIGHT);
    window = glutCreateWindow ("Rendering");

    /* Connect GLUT callbacks */
    glutIdleFunc (idle);
    glutDisplayFunc (display);
    glutKeyboardFunc (key);
    glutReshapeFunc (reshape);
    glutMotionFunc (motion);
    glutMouseFunc (mouse);

    /* Initialize Global variables */
    init (file_path);

    /* Main loop -> Should never return */
    glutMainLoop ();

    return EXIT_SUCCESS;
}

////////////////////////////////////////////////////////////////////////////////////////
// Init function. This function initializes the global variables as well as
// some OpenGL functionalities
void init (const std::string& file_name) {
    /* Init GLEW */
    glewInit();
    if (glewGetExtension ("GL_ARB_vertex_shader")        != GL_TRUE ||
        glewGetExtension ("GL_ARB_shader_objects")       != GL_TRUE ||
        glewGetExtension ("GL_ARB_shading_language_100") != GL_TRUE) {
        FATAL_ERROR("Driver does not support OpenGL Shading Language");
    }
    
    /* Init global variables */
    meshs = &MeshFactory<uchar>::load(file_name);
    mesh_gl = new MeshGL<uchar>(*meshs);
    textures = &meshs->texture_vec(); 
    textures_ids.push_back(textures->at(2)->gl_tex_id());
    for(uint i=0; i < meshs->_blured_textures.size(); i++)
        textures_ids.push_back(meshs->_blured_textures[i]->gl_tex_id());

    mesh_gl->bind();

    shader_phong = new ShaderPhong();
    shader_realskin = new ShaderRealskin();
 
    curr_shader = shader_phong;
    curr_shader->bind();

    camera = new Camera(curr_shader->proj_matrix_location(),
                        curr_shader->view_matrix_location(),
                        curr_shader->model_matrix_location());

    camera->resize(SCREENWIDTH, SCREENHEIGHT);

    // Specifies the faces to cull (here the ones pointing away from the camera)
    glCullFace (GL_BACK); 

    // Enables face culling (based on the orientation defined by the CW/CCW enumeration).
    glEnable (GL_CULL_FACE);
    
    // Specify the depth test for the z-buffer
    glDepthFunc (GL_LESS);
    
    // Enable the z-buffer in the rasterization)
    glEnable (GL_DEPTH_TEST); 

    // Background color
    glClearColor (background_color[0], background_color[1], background_color[2], 0.0f);

    // Enable Textures !!r
    glEnable(GL_TEXTURE_2D);
}


////////////////////////////////////////////////////////////////////////////////////////
// Updates FPS model size and ask for Rendering
void idle()
{
    static float lastTime = glutGet ((GLenum)GLUT_ELAPSED_TIME);
    static unsigned int counter = 0;
    counter++;
    float currentTime = glutGet ((GLenum)GLUT_ELAPSED_TIME);
    if (currentTime - lastTime >= 1000.0f) {
        FPS = counter;
        counter = 0;
        static char winTitle [128];
        unsigned int numOfTriangles = meshs->triangle().size ();
        if(curr_shader == shader_realskin)
            sprintf (winTitle, "Shader: Real Skin - Number Of Triangles: %d - FPS: %d", numOfTriangles, FPS);
        else if(curr_shader == shader_phong)
            sprintf (winTitle, "Shader: Phong - Number Of Triangles: %d - FPS: %d", numOfTriangles, FPS);
        else if(curr_shader == shader_blur)
            sprintf (winTitle, "Shader: Blur - Number Of Triangles: %d - FPS: %d", numOfTriangles, FPS);
        glutSetWindowTitle (winTitle);
        lastTime = currentTime;
    }

    // calls the display function
    glutPostRedisplay (); 
}

////////////////////////////////////////////////////////////////////////////////////////
// Draw using OpenGL 4.5
inline void drawGL4()
{
    //textures->at(2)->bind();
    //mesh_gl->bind();

    // Applies blur
    //curr_shader->unbind();
    //shader_blur->bind();

    //camera->reset_matrices(shader_blur->proj_matrix_location(), shader_blur->view_matrix_location(), shader_blur->model_matrix_location());

    //camera->apply();
    //shader_blur->apply();
    //shader_blur->unbind();

    //shader_blur->apply();

    glBindTextures(0, textures_ids.size(), textures_ids.data());
   
    // Applies normal shader
    curr_shader->bind();

    camera->reset_matrices(curr_shader->proj_matrix_location(),
                           curr_shader->view_matrix_location(),
                           curr_shader->model_matrix_location());

    camera->apply();

    glDrawElements(GL_TRIANGLES, mesh_gl->vertex_index_size(), GL_UNSIGNED_INT, NULL);
 
    curr_shader->unbind();
    //textures->at(2)->unbind();
    //mesh_gl->unbind();
}

////////////////////////////////////////////////////////////////////////////////////////
// Draw's
void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Set up the modelview matrix and the projection matrix from the camera
    drawGL4();

    // Ensures any previous OpenGL call has been executed
    glFlush ();

    // swap the render buffer and the displayed (screen) one
    glutSwapBuffers (); 
}

////////////////////////////////////////////////////////////////////////////////////////
// key_pressed callbacks
void key(unsigned char key, int x, int y)
{
    switch(key)
    {
        case 'f': // Fullscreen
            (full_screen ? glutReshapeWindow(SCREENWIDTH, SCREENHEIGHT) : glutFullScreen());
            full_screen = !full_screen;
            break;
        case 'w': // Wireframe
            glPolygonMode( GL_FRONT_AND_BACK, wireframe ? GL_FILL : GL_LINE);
            wireframe = !wireframe;
            break;
        case '1': // Phong's shader 
            shader_phong->bind();
            camera->reset_matrices(shader_phong->proj_matrix_location(), 
                                   shader_phong->view_matrix_location(),
                                   shader_phong->model_matrix_location());
            curr_shader = shader_phong;
            curr_shader->unbind();
            break;
        case '2': // Realskin's shader
            shader_realskin->bind();
            camera->reset_matrices(shader_realskin->proj_matrix_location(),
                                   shader_realskin->view_matrix_location(),
                                   shader_realskin->model_matrix_location());
            curr_shader = shader_realskin;
            curr_shader->unbind();
            break;
        /*case '3': // Realskin's shader
            shader_blur->bind();
            camera->reset_matrices(shader_blur->proj_matrix_location(),
                                   shader_blur->view_matrix_location(),
                                   shader_blur->model_matrix_location());
            curr_shader = shader_blur;
            curr_shader->unbind();
            break;*/
        case '+': // Zoom +
            camera->zoom(0.2);
            break;
        case '-': // Zoom -
            camera->zoom(-0.2);
            break;
        case 'q': // Quit
            exit(EXIT_SUCCESS);
            break;

    }
}

////////////////////////////////////////////////////////////////////////////////////////
void reshape(int w, int h)
{
    curr_shader->bind();
    camera->resize(w, h);
    curr_shader->unbind();
}

////////////////////////////////////////////////////////////////////////////////////////

void motion(int x, int y)
{
    if (mouseRotatePressed == true) {
        camera->rotate (x, y);
    }
    else if (mouseMovePressed == true) {
        camera->move ((x-lastX)/static_cast<float>(SCREENWIDTH), (lastY-y)/static_cast<float>(SCREENHEIGHT), 0.0);
        lastX = x;
        lastY = y;
    }
    else if (mouseZoomPressed == true) {
        camera->zoom (float (y-lastZoom)/SCREENHEIGHT);
        lastZoom = y;
    }
}

////////////////////////////////////////////////////////////////////////////////////////

void mouse(int button, int state, int x, int y)
{
    if (state == GLUT_UP) {
        mouseMovePressed = false;
        mouseRotatePressed = false;
        mouseZoomPressed = false;
    } else {
        if (button == GLUT_LEFT_BUTTON) {
            camera->beginRotate (x, y);
            mouseMovePressed = false;
            mouseRotatePressed = true;
            mouseZoomPressed = false;
        } else if (button == GLUT_RIGHT_BUTTON) {
            lastX = x;
            lastY = y;
            mouseMovePressed = true;
            mouseRotatePressed = false;
            mouseZoomPressed = false;
        } else if (button == GLUT_MIDDLE_BUTTON) {
            if (mouseZoomPressed == false) {
                lastZoom = y;
                mouseMovePressed = false;
                mouseRotatePressed = false;
                mouseZoomPressed = true;
            }
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////
