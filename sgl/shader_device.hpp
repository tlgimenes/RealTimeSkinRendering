/*
 * =====================================================================================
 *       Filename:  shader_device.hpp
 *    Description:  
 *        Created:  2015-02-16 19:19
 *         Author:  Tiago Lobato Gimenes        (tlgimenes@gmail.com)
 * =====================================================================================
 */

////////////////////////////////////////////////////////////////////////////////////////

#ifndef SHADER_DEVICE_HPP
#define SHADER_DEVICE_HPP

////////////////////////////////////////////////////////////////////////////////////////

#include <GL/glew.h>
#include <GL/gl.h>

#include <string>
#include <fstream>
#include <sstream>

#include "error.hpp"

////////////////////////////////////////////////////////////////////////////////////////

namespace sgl
{
    namespace device
    {
        class shader 
        {
            private:
                GLuint _shader_program;

                GLuint _vertex_shader;
                GLuint _fragment_shader;

            protected:
                void compile_attach(GLuint & shader, GLenum type, const std::string& source);

                GLint get_uni_loc (const GLchar *name, GLuint program);
                inline GLint get_uni_loc(const GLchar *name) {return get_uni_loc(name, _shader_program);}

            public:
                shader (const std::string& vert_path, const std::string& frag_path);
                virtual ~shader ();

                /**
                 * Binds shader
                 * */
                inline void bind () {glUseProgram (_shader_program); gl_check_for_errors();}

                /**
                 * Unbinds shader 
                 * */
                inline void unbind () {glUseProgram (0); gl_check_for_errors();}

                /**
                 * Gets
                 * */
                inline GLuint shader_program  () const {return _shader_program;}
                inline GLuint vertex_shader   () const {return _vertex_shader;}
                inline GLuint fragment_shader () const {return _fragment_shader;}
        };
    }
}

////////////////////////////////////////////////////////////////////////////////////////

inline sgl::device::shader::shader(const std::string& vert_path, const std::string& frag_path) :
    _shader_program      (0),
    _vertex_shader       (0),
    _fragment_shader     (0)
{
    std::ifstream vert(vert_path), frag(frag_path);
    std::stringstream vert_source, frag_source;

    vert_source << vert.rdbuf();
    frag_source << frag.rdbuf();

    _shader_program = glCreateProgram(); gl_check_for_errors();

    compile_attach(_vertex_shader, GL_VERTEX_SHADER, vert_source.str()); gl_check_for_errors();
    compile_attach(_fragment_shader, GL_FRAGMENT_SHADER, frag_source.str()); gl_check_for_errors();

    glLinkProgram(_shader_program);

    gl_check_for_link_errors(_shader_program);
}

////////////////////////////////////////////////////////////////////////////////////////

inline sgl::device::shader::~shader () 
{
    //glDeleteShader (_vertex_shader);
    //glDeleteShader (_fragment_shader);
    //glDeleteProgram (_shader_program);
}

////////////////////////////////////////////////////////////////////////////////////////

inline void sgl::device::shader::compile_attach(GLuint& shader, GLenum type, const std::string& source)
{
    GLint shaderCompiled;
    const GLchar * src = source.c_str();

    shader = glCreateShader (type);
    glShaderSource (shader, 1, &src, NULL);
    glCompileShader (shader);
    gl_check_for_errors();

    glGetShaderiv (shader, GL_COMPILE_STATUS, &shaderCompiled);
    gl_check_for_errors();

    if (!shaderCompiled) {
        __warning(source, __FILE__, __LINE__);
        print_shader_info_log (shader);
     }
    glAttachShader (_shader_program, shader);
}

////////////////////////////////////////////////////////////////////////////////////////

inline GLint sgl::device::shader::get_uni_loc(const GLchar* name, GLuint program)
{
    GLint loc = glGetUniformLocation (program, name);

    if(loc == -1)
        fatal_error("No such uniform named " + std::string(name));
    
    gl_check_for_errors();

    return loc;
}

////////////////////////////////////////////////////////////////////////////////////////

#endif /* !SHADER_DEVICE_HPP */

////////////////////////////////////////////////////////////////////////////////////////

