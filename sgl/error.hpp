/*
 * =====================================================================================
 *       Filename:  error.hpp
 *    Description:  
 *        Created:  2015-01-15 20:34
 *         Author:  Tiago Lobato Gimenes        (tlgimenes@gmail.com)
 * =====================================================================================
 */

////////////////////////////////////////////////////////////////////////////////////////

#ifndef ERROR_HPP
#define ERROR_HPP

////////////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <string>
#include <chrono>
#include <sstream>
#include <cstring>

#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>

////////////////////////////////////////////////////////////////////////////////////////

namespace sgl
{

////////////////////////////////////////////////////////////////////////////////////////

inline void __error(const std::string& error_code, const std::string& file, int line)
{
    auto now = std::chrono::system_clock::now();
    std::time_t now_c = std::chrono::system_clock::to_time_t(now);
    struct tm *tm = std::localtime(&now_c);

    std::cout << "FATAL ERROR ! " << file << ":" << line; 
    std::cout << " ["<< tm->tm_mday << "/" << (tm->tm_mon+1) << "/" << (tm->tm_year+1900);
    std::cout << "]:" << tm->tm_hour << ":" << tm->tm_min << ":" << tm->tm_sec << std::endl;
    std::cout << "'" << error_code << "'" << std::endl << std::endl;

    exit(EXIT_FAILURE);

    return;
}

////////////////////////////////////////////////////////////////////////////////////////

inline void __warning(const std::string& error_code, const std::string& file, int line)
{
    auto now = std::chrono::system_clock::now();
    std::time_t now_c = std::chrono::system_clock::to_time_t(now);
    struct tm *tm = std::localtime(&now_c);

    std::cout << "WARNING ! " << file << ":" << line; 
    std::cout << " ["<< tm->tm_mday << "/" << (tm->tm_mon+1) << "/" << (tm->tm_year+1900);
    std::cout << "]:" << tm->tm_hour << ":" << tm->tm_min << ":" << tm->tm_sec << std::endl;
    std::cout << "'" << error_code << "'" << std::endl << std::endl;

    return;
}

////////////////////////////////////////////////////////////////////////////////////////

#ifdef NDEBUG
#define assert_fatal_error(boolean, str)
#define assert_warning_error(boolean, str)
#define gl_safe(code)
#else
#define assert_fatal_error(boolean, str)  (void)(boolean || (__error(str, __FILE__, __LINE__),0))
#define assert_warning_error(boolean, str) (void)(boolean || (__warning(str, __FILE__, __LINE__), 0))
#define gl_safe(code) (void)(code == GL_NO_ERROR || (__error(gluErrorString(glGetError()), __FILE__, __LINE__),0))
#endif

#define fatal_error(str) __error(str, __FILE__, __LINE__)
#define warning_error(str) __warning(str, __FILE__, __LINE__)
#define gl_check_for_errors() (void) (glGetError() == GL_NO_ERROR || (sgl::__error(std::string((char*)gluErrorString(glGetError())), __FILE__, __LINE__), 0))
#define gl_check_for_link_errors(program) sgl::__gl_check_for_link_errors(program, __FILE__, __LINE__)

////////////////////////////////////////////////////////////////////////////////////////

inline void __gl_check_for_errors(const std::string& file, int line)
{
    GLenum gl_error_check = glGetError();

    if(gl_error_check != GL_NO_ERROR)
    {
        std::stringstream sstream("OpenGL error ");
        sstream << gluErrorString(gl_error_check);
        __error(sstream.str(), file, line);
    }

    return ;
}

////////////////////////////////////////////////////////////////////////////////////////

inline void print_shader_info_log (GLuint shader) {
    int infologLength = 0;
    int charsWritten  = 0;
    GLchar *infoLog;

    gl_check_for_errors();
    glGetShaderiv (shader, GL_INFO_LOG_LENGTH, &infologLength);
    gl_check_for_errors();

    if (infologLength > 0) {
        infoLog = new GLchar[infologLength];
        if (infoLog == NULL) {
            __error("Could not allocate InfoLog buffer", __FILE__, __LINE__);
        }
        glGetShaderInfoLog (shader, infologLength, &charsWritten, infoLog);
        if (infologLength > 8)
            __error("InfoLog: " + std::string(infoLog), __FILE__, __LINE__);
        delete [] infoLog;
    }
    gl_check_for_errors();
}

////////////////////////////////////////////////////////////////////////////////////////

inline void print_program_info_log (GLuint program) 
{
    int infologLength = 0;
    int charsWritten  = 0;
    GLchar *infoLog;

    gl_check_for_errors();
    glGetProgramiv (program, GL_INFO_LOG_LENGTH, &infologLength);
    gl_check_for_errors();

    if (infologLength > 0) {
        infoLog = new GLchar[infologLength];
        if (infoLog == NULL) {
            __error("Could not allocate InfoLog buffer", __FILE__, __LINE__);
        }
        glGetProgramInfoLog (program, infologLength, &charsWritten, infoLog);
        if (infologLength > 8)
            __error("InfoLog: " + std::string(infoLog), __FILE__, __LINE__);
        delete [] infoLog;
    }
    gl_check_for_errors();
}

////////////////////////////////////////////////////////////////////////////////////////

inline void __gl_check_for_link_errors(GLuint program, const std::string& file, int line)
{
    GLint linked;

    glGetProgramiv (program, GL_LINK_STATUS, &linked);
    print_program_info_log(program);

    if (!linked) 
        __error("Shader not linked", file, line);
}

////////////////////////////////////////////////////////////////////////////////////////

}

////////////////////////////////////////////////////////////////////////////////////////

#endif /* !ERROR_HPP */

///////////////////////////////////////////////////////////////////////////////////////deriv header/
