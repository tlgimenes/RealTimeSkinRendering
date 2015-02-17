/*
 * =====================================================================================
 *       Filename:  shader_realskin.cpp
 *    Description:  
 *        Created:  2015-02-17 16:34
 *         Author:  Tiago Lobato Gimenes        (tlgimenes@gmail.com)
 * =====================================================================================
 */

////////////////////////////////////////////////////////////////////////////////////////

#include "shader_realskin.hpp"

////////////////////////////////////////////////////////////////////////////////////////

shader_realskin::shader_realskin() :
    sgl::device::shader(REALSKIN_VERT_SHADER_PATH, REALSKIN_FRAG_SHADER_PATH)
{
    bind();

    // Light
    _light_pos_location =          get_uni_loc("light_pos");
    _light_color_location =        get_uni_loc("light_color");
    
    // Material
    ////_mat_diffuse_color_location =  get_uni_loc("mat_diff_color");
    _mat_diffuse_location =        get_uni_loc("mat_diff");
    _mat_specular_color_location = get_uni_loc("mat_spec_color");
    _mat_specular_location =       get_uni_loc("mat_spec");
    _mat_roughness_location =      get_uni_loc("mat_roughness");
    _mat_reflect_normal_locaiton = get_uni_loc("mat_reflect_normal");

    // Projection and modelview matrix
    _proj_matrix_location =        get_uni_loc("proj_matrix");
    _view_matrix_location =        get_uni_loc("view_matrix");
    _model_matrix_location =       get_uni_loc("model_matrix");

    // Textures
    _tex_skin_location =           get_uni_loc("tex_skin");
    _tex_blurs_location.push_back(get_uni_loc("tex_blur0"));
    _tex_blurs_location.push_back(get_uni_loc("tex_blur1"));
    _tex_blurs_location.push_back(get_uni_loc("tex_blur2"));
    _tex_blurs_location.push_back(get_uni_loc("tex_blur3"));
    _tex_blurs_location.push_back(get_uni_loc("tex_blur4"));
    _tex_blurs_location.push_back(get_uni_loc("tex_blur5"));

    _coeffs_location.push_back(get_uni_loc("coeff0"));
    _coeffs_location.push_back(get_uni_loc("coeff1"));
    _coeffs_location.push_back(get_uni_loc("coeff2"));
    _coeffs_location.push_back(get_uni_loc("coeff3"));
    _coeffs_location.push_back(get_uni_loc("coeff4"));
    _coeffs_location.push_back(get_uni_loc("coeff5"));

    set_light_pos(REALSKIN_LIGHT_POS_DEFAULT); gl_check_for_errors();
    set_light_color(REALSKIN_LIGHT_COLOR_DEFAULT); gl_check_for_errors();

    ////set_mat_diffuse_color(REALSKIN_MAT_DIFF_COLOR_DEFAULT);gl_check_for_errors();
    set_mat_diffuse(REALSKIN_MAT_DIFF_DEFAULT);gl_check_for_errors();
    set_mat_specular_color(REALSKIN_MAT_SPEC_COLOR_DEFAULT);gl_check_for_errors();
    set_mat_specular(REALSKIN_MAT_SPEC_DEFAULT);gl_check_for_errors();
    set_mat_roughness(REALSKIN_MAT_ROUGHNESS_DEFAULT);gl_check_for_errors();
    set_mat_reflect_normal(REALSKIN_MAT_REFLECT_NORMAL_DEFAULT);gl_check_for_errors();
    
    set_tex_skin(0);gl_check_for_errors();
    set_tex_blur(1, _tex_blurs_location[0]);gl_check_for_errors();
    set_tex_blur(2, _tex_blurs_location[1]);gl_check_for_errors();
    set_tex_blur(3, _tex_blurs_location[2]);gl_check_for_errors();
    set_tex_blur(4, _tex_blurs_location[3]);gl_check_for_errors();
    set_tex_blur(5, _tex_blurs_location[4]);gl_check_for_errors();
    set_tex_blur(6, _tex_blurs_location[5]);gl_check_for_errors();
    
    set_coeffs(COEFF0_DEFAULT, _coeffs_location[0]);gl_check_for_errors();
    set_coeffs(COEFF1_DEFAULT, _coeffs_location[1]);gl_check_for_errors();
    set_coeffs(COEFF2_DEFAULT, _coeffs_location[2]);gl_check_for_errors();
    set_coeffs(COEFF3_DEFAULT, _coeffs_location[3]);gl_check_for_errors();
    set_coeffs(COEFF4_DEFAULT, _coeffs_location[4]);gl_check_for_errors();
    set_coeffs(COEFF5_DEFAULT, _coeffs_location[5]);gl_check_for_errors();

    unbind();
}

////////////////////////////////////////////////////////////////////////////////////////

void shader_realskin::set_light_pos (const glm::vec3& light_pos)
{
    glUniform3f(_light_pos_location, light_pos[0], light_pos[1], light_pos[2]);
}

////////////////////////////////////////////////////////////////////////////////////////
 
void shader_realskin::set_light_color (const glm::vec4& light_color)
{
    glUniform4f(_light_color_location, light_color[0], light_color[1], light_color[2], 
            light_color[3]);
}

////////////////////////////////////////////////////////////////////////////////////////

void shader_realskin::set_mat_diffuse_color (const glm::vec4& mat_diff_color)
{
    glUniform4f(_mat_diffuse_color_location, mat_diff_color[0], mat_diff_color[1], 
            mat_diff_color[2], mat_diff_color[3]);
}

////////////////////////////////////////////////////////////////////////////////////////

void shader_realskin::set_mat_diffuse (float s)
{
    glUniform1f(_mat_diffuse_location, s);
}

////////////////////////////////////////////////////////////////////////////////////////

void shader_realskin::set_mat_specular_color (const glm::vec4& mat_spec_color)
{
    glUniform4f(_mat_specular_color_location, mat_spec_color[0], mat_spec_color[1], 
            mat_spec_color[2], mat_spec_color[3]);
}

////////////////////////////////////////////////////////////////////////////////////////

void shader_realskin::set_mat_specular(float s)
{
    glUniform1f(_mat_specular_location, s);
}

////////////////////////////////////////////////////////////////////////////////////////
 
void shader_realskin::set_mat_roughness(float m)
{
    glUniform1f(_mat_roughness_location, m);
}

////////////////////////////////////////////////////////////////////////////////////////
 
void shader_realskin::set_mat_reflect_normal(float F0)
{
    glUniform1f(_mat_roughness_location, F0);
}

////////////////////////////////////////////////////////////////////////////////////////

void shader_realskin::set_tex_skin(int i)
{
    glUniform1i(_tex_skin_location, i);
}

////////////////////////////////////////////////////////////////////////////////////////

void shader_realskin::set_tex_blur(int i, GLuint blur_id_location)
{
    glUniform1i(blur_id_location, i);
}

////////////////////////////////////////////////////////////////////////////////////////

void shader_realskin::set_coeffs(const glm::vec4& coeff, GLuint blur_id)
{
    glUniform4f(blur_id, coeff[0], coeff[1], coeff[2], coeff[3]);
}

////////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////////////

