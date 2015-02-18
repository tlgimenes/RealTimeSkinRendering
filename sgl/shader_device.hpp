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
                GLuint _shader_id;

                GLenum _type;

            protected:
                void compile(const std::string& source);

            public:
                shader (const std::string& shader_path, GLenum type);
                shader (const shader& s) : _shader_id(s.id()), _type(s.type()) {}
                virtual ~shader ();

                /**
                 * Gets
                 * */
                inline const GLuint& id() const {return _shader_id;}
                inline const GLenum& type() const {return _type;}

                /**
                 * Sets
                 * */
                inline GLuint& id() {return _shader_id;}
                inline GLenum& type() {return _type;}
        };
    }
}

////////////////////////////////////////////////////////////////////////////////////////

inline sgl::device::shader::shader(const std::string& shader_path, GLenum type) :
    _shader_id(0),
    _type(type)
{
    std::ifstream shader_file(shader_path);
    std::stringstream shader_source;

    // Checks if shader file exists
    if(!shader_file) fatal_error(std::string("Shader file not found: ")+shader_path);

    shader_source << shader_file.rdbuf();

    compile(shader_source.str()); gl_check_for_errors();
}

////////////////////////////////////////////////////////////////////////////////////////

inline sgl::device::shader::~shader () 
{
    //glDeleteShader (_vertex_shader);
    //glDeleteShader (_fragment_shader);
}

////////////////////////////////////////////////////////////////////////////////////////

inline void sgl::device::shader::compile(const std::string& source)
{
    GLint shaderCompiled;
    const GLchar * src = source.c_str();

    _shader_id = glCreateShader (_type);
    glShaderSource (_shader_id, 1, &src, NULL);
    glCompileShader (_shader_id);
    gl_check_for_errors();

    glGetShaderiv (_shader_id, GL_COMPILE_STATUS, &shaderCompiled);
    gl_check_for_errors();

    if (!shaderCompiled) {
        warning_error(source);
        print_shader_info_log (_shader_id);
     }
}

////////////////////////////////////////////////////////////////////////////////////////

#endif /* !SHADER_DEVICE_HPP */

////////////////////////////////////////////////////////////////////////////////////////

