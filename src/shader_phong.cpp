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

    // Light
    _light_pos_location =          get_uni_loc("light_pos");
    _light_color_location =        get_uni_loc("light_color");
    
    // Material
    _mat_diffuse_color_location =  get_uni_loc("mat_diff_color");
    _mat_diffuse_location =        get_uni_loc("mat_diff");
    _mat_specular_color_location = get_uni_loc("mat_spec_color");
    _mat_specular_location =       get_uni_loc("mat_spec");
    _mat_shininess_location =      get_uni_loc("mat_shininess");

    // Projection and modelview matrix
    _proj_matrix_location =        get_uni_loc("proj_matrix");
    _view_matrix_location =        get_uni_loc("view_matrix");
    _model_matrix_location =       get_uni_loc("model_matrix");

    // Textures
    _tex_skin_location =           get_uni_loc("tex_skin");

    set_light_pos(PHONG_LIGHT_POS_DEFAULT);
    set_light_color(PHONG_LIGHT_COLOR_DEFAULT);

    set_mat_diffuse_color(PHONG_MAT_DIFF_COLOR_DEFAULT);
    set_mat_diffuse(PHONG_MAT_DIFF_DEFAULT);
    set_mat_specular_color(PHONG_MAT_SPEC_COLOR_DEFAULT);
    set_mat_specular(PHONG_MAT_SPEC_DEFAULT);
    set_mat_shininess(PHONG_MAT_SHININESS_DEFAULT);

    set_tex_skin(0);

    unbind();
}

////////////////////////////////////////////////////////////////////////////////////////
 
void ShaderPhong::set_light_pos (const Vec3f& light_pos)
{
    glUniform3f(_light_pos_location, light_pos[X], light_pos[Y], light_pos[Z]);
}

////////////////////////////////////////////////////////////////////////////////////////
 
void ShaderPhong::set_light_color (const Vec4f& light_color)
{
    glUniform4f(_light_color_location, light_color[X], light_color[Y], light_color[Z], 
            light_color[W]);
}

////////////////////////////////////////////////////////////////////////////////////////

void ShaderPhong::set_mat_diffuse_color (const Vec4f& mat_diff_color)
{
    glUniform4f(_mat_diffuse_color_location, mat_diff_color[X], mat_diff_color[Y], 
            mat_diff_color[Z], mat_diff_color[W]);
}

////////////////////////////////////////////////////////////////////////////////////////

void ShaderPhong::set_mat_diffuse (float s)
{
    glUniform1f(_mat_diffuse_location, s);
}

////////////////////////////////////////////////////////////////////////////////////////

void ShaderPhong::set_mat_specular_color (const Vec4f& mat_spec_color)
{
    glUniform4f(_mat_specular_color_location, mat_spec_color[X], mat_spec_color[Y], 
            mat_spec_color[Z], mat_spec_color[W]);
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

void ShaderPhong::set_tex_skin(int i)
{
    glUniform1i(_tex_skin_location, i);
}

////////////////////////////////////////////////////////////////////////////////////////
