/*
 * =====================================================================================
 *       Filename:  pipeline_device.hpp
 *    Description:  
 *        Created:  2015-02-18 10:24
 *         Author:  Tiago Lobato Gimenes        (tlgimenes@gmail.com)
 * =====================================================================================
 */

////////////////////////////////////////////////////////////////////////////////////////

#ifndef PIPELINE_DEVICE_HPP
#define PIPELINE_DEVICE_HPP

////////////////////////////////////////////////////////////////////////////////////////

#include "shader_device.hpp"
#include "error.hpp"

////////////////////////////////////////////////////////////////////////////////////////

namespace sgl
{
    namespace device
    {
        class pipeline 
        {
            private:
                GLuint _shader_program; // Shader's program ID

                bool _is_bindable;
    
            public:
                pipeline();
                pipeline(const pipeline& pipe) :
                    _shader_program(pipe.program()), _is_bindable(pipe.is_bindable()) {}

                ~pipeline() {};

                /**
                 * Attachs shader to this pipeline 
                 * */
                void attach(const sgl::device::shader& shader);

                /**
                 * Links shaders and makes pipeline bindable
                 * */
                void link();

                /**
                 * Binds pipeline
                 * */
                void bind();

                /**
                 * Unbinds pipeline 
                 * */
                void unbind ();

                /**
                 * Returns the unique location  
                 * */
                GLint get_uni_loc (const GLchar *name, GLuint program);
                inline GLint get_uni_loc(const GLchar *name) {return get_uni_loc(name, _shader_program);}

                /**
                 * Gets  
                 * */
                inline const GLuint& program() const {return _shader_program;}
                inline const bool& is_bindable() const {return _is_bindable;}
        };
    }
}

////////////////////////////////////////////////////////////////////////////////////////

inline sgl::device::pipeline::pipeline() :
    _shader_program(0),
    _is_bindable(false)
{
    _shader_program = glCreateProgram(); 
    gl_check_for_errors();
}

////////////////////////////////////////////////////////////////////////////////////////

inline void sgl::device::pipeline::attach(const sgl::device::shader& shader)
{
    glAttachShader(_shader_program, shader.id());
    gl_check_for_errors();
}

////////////////////////////////////////////////////////////////////////////////////////

inline void sgl::device::pipeline::link()
{
    glLinkProgram(_shader_program);

    gl_check_for_link_errors(_shader_program);

    _is_bindable = true;
}

////////////////////////////////////////////////////////////////////////////////////////

inline void sgl::device::pipeline::bind () 
{
    assert_fatal_error(_is_bindable, "Pipeline is not bindable");

    glUseProgram (_shader_program); 

    gl_check_for_errors();
}

////////////////////////////////////////////////////////////////////////////////////////

inline void sgl::device::pipeline::unbind()
{
    assert_fatal_error(_is_bindable, "Pipeline is not unbindable");

    glUseProgram(0);

    gl_check_for_errors();
}

////////////////////////////////////////////////////////////////////////////////////////

inline GLint sgl::device::pipeline::get_uni_loc(const GLchar* name, GLuint program)
{
    GLint loc = glGetUniformLocation (program, name);
    gl_check_for_errors();

    if(loc == -1)
        fatal_error("No such uniform named " + std::string(name));

    return loc;
}

////////////////////////////////////////////////////////////////////////////////////////

#endif /* !PIPELINE_DEVICE_HPP */

////////////////////////////////////////////////////////////////////////////////////////

