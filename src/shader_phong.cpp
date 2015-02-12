/*
 * =====================================================================================
 *       Filename:  shader_phong.cpp
 *    Description:  
 *        Created:  2015-02-12 11:18
 *         Author:  Tiago Lobato Gimenes        (tlgimenes@gmail.com)
 * =====================================================================================
 */

////////////////////////////////////////////////////////////////////////////////////////

#include "shader_phong.hpp"

////////////////////////////////////////////////////////////////////////////////////////

ShaderPhong::ShaderPhong() : Shader()
{
    load_from_file(PHONG_VERT_SHADER_PATH, PHONG_FRAG_SHADER_PATH);
    bind();

    _light_pos_location =          get_uni_loc("light_pos");
    _light_color_location =        get_uni_loc("light_color");
    _mat_diffuse_color_location =  get_uni_loc("mat_diff_color");
    _mat_diffuse_location =        get_uni_loc("mat_diff");
    _mat_specular_color_location = get_uni_loc("mat_spec_color");
    _mat_specular_location =       get_uni_loc("mat_spec");
    _mat_shininess_location =      get_uni_loc("mat_shininess");

    set_light_pos(LIGHT_POS_DEFAULT);
    set_light_color(LIGHT_COLOR_DEFAULT);

    set_mat_diffuse_color(MAT_DIFF_COLOR_DEFAULT);
    set_mat_diffuse(MAT_DIFF_DEFAULT);
    set_mat_specular_color(MAT_SPEC_COLOR_DEFAULT);
    set_mat_specular(MAT_SPEC_DEFAULT);
    set_mat_shininess(MAT_SHININESS_DEFAULT);
}

////////////////////////////////////////////////////////////////////////////////////////
 
void ShaderPhong::set_light_pos (const Vec3f& light_pos)
{
    glUniform3f(_light_pos_location, light_pos[X], light_pos[Y], light_pos[Z]);
}

////////////////////////////////////////////////////////////////////////////////////////
 
void ShaderPhong::set_light_color (const Vec4f& light_color)
{
    glUniform4f(_light_color_location, light_color[R], light_color[G], light_color[B], 
            light_color[A]);
}

////////////////////////////////////////////////////////////////////////////////////////

void ShaderPhong::set_mat_diffuse_color (const Vec4f& mat_diff_color)
{
    glUniform4f(_mat_diffuse_color_location, mat_diff_color[R], mat_diff_color[G], 
            mat_diff_color[B], mat_diff_color[A]);
}

////////////////////////////////////////////////////////////////////////////////////////

void ShaderPhong::set_mat_diffuse (float s)
{
    glUniform1f(_mat_diffuse_location, s);
}

////////////////////////////////////////////////////////////////////////////////////////

void ShaderPhong::set_mat_specular_color (const Vec4f& mat_spec_color)
{
    glUniform4f(_mat_specular_color_location, mat_spec_color[R], mat_spec_color[G], 
            mat_spec_color[B], mat_spec_color[A]);
}

////////////////////////////////////////////////////////////////////////////////////////

void ShaderPhong::set_mat_specular(float s)
{
    glUniform1f(_mat_specular_location, s);
}

////////////////////////////////////////////////////////////////////////////////////////

void ShaderPhong::set_mat_shininess (float s)
{
    glUniform1f(_mat_shininess_location, s);
}

////////////////////////////////////////////////////////////////////////////////////////
