/*
 * =====================================================================================
 *       Filename:  shader.cpp
 *    Description:  
 *        Created:  2015-02-11 16:54
 *         Author:  Tiago Lobato Gimenes        (tlgimenes@gmail.com)
 * =====================================================================================
 */

////////////////////////////////////////////////////////////////////////////////////////

#include "shader.hpp"

#include <GL/gl.h>
#include <fstream>
#include <sstream>

#include "error.hpp"

////////////////////////////////////////////////////////////////////////////////////////

Shader::Shader() :
    _shader_program      (0),
    _vertex_shader       (0),
    _fragment_shader     (0),
    _vertex_shader_size  (0),
    _fragment_shader_size(0)
{
    /* Nothing to do here */
}

////////////////////////////////////////////////////////////////////////////////////////

Shader::~Shader () {
    if (has_vertex_shader())
        glDeleteShader (_vertex_shader);
    if (has_fragment_shader())
        glDeleteShader (_fragment_shader_size);
    glDeleteProgram (_shader_program);
}


////////////////////////////////////////////////////////////////////////////////////////

void Shader::load_from_file(const std::string& vertex_shader_filename, 
        const std::string& fragment_shader_filename)
{
    std::string vertex_shader_source;
    std::string fragment_shader_source;

    if(vertex_shader_filename != "")
        read_shader_source(vertex_shader_filename, vertex_shader_source);
    if(fragment_shader_filename != "")
        read_shader_source(fragment_shader_filename, fragment_shader_source);

    _vertex_shader_size = vertex_shader_source.size();
    _fragment_shader_size = fragment_shader_source.size();

    _shader_program = glCreateProgram();
    if (has_vertex_shader ()) {
        compile_attach (_vertex_shader, GL_VERTEX_SHADER, vertex_shader_source);
    }
    if (has_fragment_shader ()) {
        compile_attach (_fragment_shader, GL_FRAGMENT_SHADER, fragment_shader_source);
    }

    glLinkProgram (_shader_program);
    GL_CHECK_FOR_ERRORS();

    GLint linked;
    glGetProgramiv (_shader_program, GL_LINK_STATUS, &linked);
    print_program_info_log(_shader_program);

    if (!linked) 
        FATAL_ERROR("Shader not linked");
}

////////////////////////////////////////////////////////////////////////////////////////

void Shader::read_shader_source (const std::string& shader_filename, std::string& shader_src)
{
    std::ifstream file (shader_filename);
    std::stringstream str;

    if(!file)
        __error("Bad shader file name: " + shader_filename, __FILE__, __LINE__);

    str << file.rdbuf();
    file.close();

    shader_src = str.str();
}

////////////////////////////////////////////////////////////////////////////////////////

void Shader::compile_attach(GLuint& shader, GLenum type, const std::string& source)
{
    GLint shaderCompiled;
    const GLchar * src = source.c_str();

    shader = glCreateShader (type);
    glShaderSource (shader, 1, &src, NULL);
    glCompileShader (shader);
    GL_CHECK_FOR_ERRORS();

    glGetShaderiv (shader, GL_COMPILE_STATUS, &shaderCompiled);
    GL_CHECK_FOR_ERRORS();

    if (!shaderCompiled) {
        __warning(source, __FILE__, __LINE__);
        print_shader_info_log (shader);
     }
    glAttachShader (_shader_program, shader);
}

////////////////////////////////////////////////////////////////////////////////////////

GLint Shader::get_uni_loc (const GLchar *name, GLuint program)
{
    GLint loc = glGetUniformLocation (program, name);

    if(loc == -1) {
        FATAL_ERROR("No such uniform named " + std::string(name));
    }
    GL_CHECK_FOR_ERRORS();

    return loc;
}

////////////////////////////////////////////////////////////////////////////////////////
