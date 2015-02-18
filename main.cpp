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
#include <glm/vec3.hpp>

#include "sgl/error.hpp"
#include "sgl/mesh_host.hpp"
#include "sgl/mesh_device.hpp"
#include "sgl/camera_host.hpp"
#include "sgl/camera_device.hpp"
#include "sgl/texture_host.hpp"
#include "sgl/texture_device.hpp"
#include "sgl/mesh_loader_obj.hpp"
#include "sgl/texture_loader_jpeg.hpp"
#include "sgl/renderable.hpp"

#include "parser.hpp"
#include "program_phong.hpp"
#include "program_realskin.hpp"
#include "head_phong.hpp"
#include "head_realskin.hpp"

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
static std::vector<std::shared_ptr<sgl::host::mesh>> mesh_vec;
static head_phong* phong_head = NULL;
static head_realskin* realskin_head = NULL;
static sgl::device::renderable* curr_head = NULL;
static sgl::host::camera* camera = NULL;
static glm::vec3 background_color(0,0,0);

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

//src///////////////////////////////////////////////////////////////////////////////////

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
        sgl::fatal_error("Driver does not support OpenGL Shading Language");
    }

    /* Init global variables */
    // load meshes
    mesh_vec = sgl::mesh_loader_obj::load(file_name);

    // load camera
    camera = new sgl::host::camera();
    camera->resize(SCREENWIDTH, SCREENHEIGHT);

    // load shaders
    std::shared_ptr<program_phong> phong = std::make_shared<program_phong>(program_phong());
    std::shared_ptr<program_realskin> realskin = std::make_shared<program_realskin>(program_realskin());

    // load textures 
    std::shared_ptr<sgl::host::texture2D> skin = sgl::texture_loader_jpeg::load("../../../models/blondGirl/ModelsFace_skin_hi.jpg");
    std::vector<std::shared_ptr<sgl::device::texture2D>> textures;
    textures.push_back(skin->to_device());

    // create a renderable object
    curr_head = phong_head = new head_phong(mesh_vec[2]->to_device(), camera->to_device(), phong, textures);
    textures.push_back(sgl::texture_loader_jpeg::load("../../models/blondGirl/Blur0.jpg")->to_device());
    textures.push_back(sgl::texture_loader_jpeg::load("../../models/blondGirl/Blur1.jpg")->to_device());
    textures.push_back(sgl::texture_loader_jpeg::load("../../models/blondGirl/Blur2.jpg")->to_device());
    textures.push_back(sgl::texture_loader_jpeg::load("../../models/blondGirl/Blur3.jpg")->to_device());
    textures.push_back(sgl::texture_loader_jpeg::load("../../models/blondGirl/Blur4.jpg")->to_device());
    textures.push_back(sgl::texture_loader_jpeg::load("../../models/blondGirl/Blur5.jpg")->to_device());

    realskin_head = new head_realskin(mesh_vec[2]->to_device(), camera->to_device(), realskin, textures);

    gl_check_for_errors();

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
        unsigned int numOfTriangles = mesh_vec[0]->faces()->size()/3;
        if(curr_head == phong_head)
            sprintf (winTitle, "Shader: Phong - Number Of Triangles: %d - FPS: %d", numOfTriangles, FPS);
        else if(curr_head == realskin_head)
            sprintf (winTitle, "Shader: Realskin - Number Of Triangles: %d - FPS: %d", numOfTriangles, FPS);
        else
            sprintf (winTitle, "BUG ! :(");
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
    camera->apply();

    curr_head->bind();

    curr_head->draw();

    curr_head->unbind();
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
            curr_head = phong_head;
            break;
        case '2': // Realskin's shader 
            curr_head = realskin_head;
            break;
        case '+': // Zoom +
            camera->zoom(1.05);
            break;
        case '-': // Zoom -
            camera->zoom(0.95);
            break;
        case 'q': // Quit
            exit(EXIT_SUCCESS);
            break;

    }
}

////////////////////////////////////////////////////////////////////////////////////////
void reshape(int w, int h)
{
    camera->resize(w, h);
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
            camera->begin_rotate (x, y);
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
