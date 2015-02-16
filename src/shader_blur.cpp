/*
 * =====================================================================================
 *       Filename:  shader_blur.cpp
 *    Description:  
 *        Created:  2015-02-15 13:59
 *         Author:  Tiago Lobato Gimenes        (tlgimenes@gmail.com)
 * =====================================================================================
 */

////////////////////////////////////////////////////////////////////////////////////////

#include "shader_blur.hpp"

#include "error.hpp"

////////////////////////////////////////////////////////////////////////////////////////

ShaderBlur::ShaderBlur(const Texture<uchar>& base, uint count) : 
    Shader(),
    _tex_base(base)
{
    gen_tex_blur(count);
    gen_frame_buff();

    load_from_file(BLUR_VERT_SHADER_PATH, BLUR_FRAG_SHADER_PATH);
    bind();

    // Projection and modelview matrix
    _proj_matrix_location =        get_uni_loc("proj_matrix");
    _view_matrix_location =        get_uni_loc("view_matrix");
    _model_matrix_location =       get_uni_loc("model_matrix");

    // Textures
    _tex_skin_location =           get_uni_loc("tex_skin");

    set_tex_skin(0);

    unbind();
}

////////////////////////////////////////////////////////////////////////////////////////

void ShaderBlur::gen_tex_blur(uint count)
{
    for(uint i=0; i < count; i++)
    {
        _tex_blur.push_back(new Texture<uchar>(_tex_base));
    }
}

////////////////////////////////////////////////////////////////////////////////////////

void ShaderBlur::gen_frame_buff()
{
    glGenFramebuffers(1, &_frame_buff);
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, _frame_buff);

    WARNING_ERROR("IS IT CORRECT ?");
    //glFramebufferParameteri(GL_DRAW_FRAMEBUFFER, GL_FRAMEBUFFER_DEFAULT_WIDTH, _tex_base.width());
    //glFramebufferParameteri(GL_DRAW_FRAMEBUFFER, GL_FRAMEBUFFER_DEFAULT_HEIGHT, _tex_base.height());
    glFramebufferParameteri(GL_DRAW_FRAMEBUFFER, GL_FRAMEBUFFER_DEFAULT_SAMPLES, _tex_blur.size());

    for(int i=0; i < _tex_blur.size(); i++)
    {
        _tex_blur[i]->bind();
        glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D,
                _tex_blur[i]->gl_tex_id(), 0);
        _tex_blur[i]->unbind();

        //glFramebufferTexture(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i,
        //        _tex_blur[i]->gl_tex_id(), 0);
    }

    if (glCheckFramebufferStatus(GL_DRAW_FRAMEBUFFER)!= GL_FRAMEBUFFER_COMPLETE)
    {
        FATAL_ERROR("Problem with the FBO ! :(");
    }

    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
}

////////////////////////////////////////////////////////////////////////////////////////

void ShaderBlur::apply()
{
    std::vector<GLenum> draw_buffers;

    // Erase the color and z buffers.
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    _tex_base.bind();
    bind(); // binds shader
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, _frame_buff);

    // sets draw_buffers variable
    for(uint i=0; i < _tex_blur.size(); i++)
    {
        draw_buffers.push_back(GL_COLOR_ATTACHMENT0 + i);
    }

    // Draw in buffers
    glDrawBuffers(draw_buffers.size(), draw_buffers.data());

    if (glCheckFramebufferStatus(GL_DRAW_FRAMEBUFFER)!= GL_FRAMEBUFFER_COMPLETE)
    {
        FATAL_ERROR("Problem with the FBO ! :(");
    }
    GL_CHECK_FOR_ERRORS();

    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
    _tex_base.unbind();
    unbind(); // unbinds Shader

    // Ensures any previous OpenGL call has been executed
    glFlush ();
}

////////////////////////////////////////////////////////////////////////////////////////
 
void ShaderBlur::set_light_pos (const Vec3f& light_pos)
{
    glUniform3f(_light_pos_location, light_pos[X], light_pos[Y], light_pos[Z]);
}

////////////////////////////////////////////////////////////////////////////////////////
 
void ShaderBlur::set_light_color (const Vec4f& light_color)
{
    glUniform4f(_light_color_location, light_color[X], light_color[Y], light_color[Z], 
            light_color[W]);
}

////////////////////////////////////////////////////////////////////////////////////////

void ShaderBlur::set_mat_diffuse_color (const Vec4f& mat_diff_color)
{
    glUniform4f(_mat_diffuse_color_location, mat_diff_color[X], mat_diff_color[Y], 
            mat_diff_color[Z], mat_diff_color[W]);
}

////////////////////////////////////////////////////////////////////////////////////////

void ShaderBlur::set_mat_diffuse (float s)
{
    glUniform1f(_mat_diffuse_location, s);
}

////////////////////////////////////////////////////////////////////////////////////////

void ShaderBlur::set_mat_specular_color (const Vec4f& mat_spec_color)
{
    glUniform4f(_mat_specular_color_location, mat_spec_color[X], mat_spec_color[Y], 
            mat_spec_color[Z], mat_spec_color[W]);
}

////////////////////////////////////////////////////////////////////////////////////////

void ShaderBlur::set_mat_specular(float s)
{
    glUniform1f(_mat_specular_location, s);
}

////////////////////////////////////////////////////////////////////////////////////////
 
void ShaderBlur::set_mat_roughness(float m)
{
    glUniform1f(_mat_roughness_location, m);
}

////////////////////////////////////////////////////////////////////////////////////////
 
void ShaderBlur::set_mat_reflect_normal(float F0)
{
    glUniform1f(_mat_roughness_location, F0);
}

////////////////////////////////////////////////////////////////////////////////////////

void ShaderBlur::set_tex_skin(int i)
{
    glUniform1i(_tex_skin_location, i);
}

////////////////////////////////////////////////////////////////////////////////////////
