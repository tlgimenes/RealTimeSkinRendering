/*
 * =====================================================================================
 *       Filename:  shader_phong.cpp
 *    Description:  
 *        Created:  2015-02-17 16:32
 *         Author:  Tiago Lobato Gimenes        (tlgimenes@gmail.com)
 * =====================================================================================
 */

////////////////////////////////////////////////////////////////////////////////////////

#include "shader_phong.hpp"

////////////////////////////////////////////////////////////////////////////////////////

shader_phong::shader_phong() : 
    sgl::device::shader(PHONG_VERT_SHADER_PATH, PHONG_FRAG_SHADER_PATH)
{
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

void shader_phong::set_light_pos (const glm::vec3& light_pos)
{
    glUniform3f(_light_pos_location, light_pos[0], light_pos[1], light_pos[2]);
}

////////////////////////////////////////////////////////////////////////////////////////
 
void shader_phong::set_light_color (const glm::vec4& light_color)
{
    glUniform4f(_light_color_location, light_color[0], light_color[1], light_color[2], 
            light_color[3]);
}

////////////////////////////////////////////////////////////////////////////////////////

void shader_phong::set_mat_diffuse_color (const glm::vec4& mat_diff_color)
{
    glUniform4f(_mat_diffuse_color_location, mat_diff_color[0], mat_diff_color[1], 
            mat_diff_color[2], mat_diff_color[3]);
}

////////////////////////////////////////////////////////////////////////////////////////

void shader_phong::set_mat_diffuse (float s)
{
    glUniform1f(_mat_diffuse_location, s);
}

////////////////////////////////////////////////////////////////////////////////////////

void shader_phong::set_mat_specular_color (const glm::vec4& mat_spec_color)
{
    glUniform4f(_mat_specular_color_location, mat_spec_color[0], mat_spec_color[1], 
            mat_spec_color[2], mat_spec_color[3]);
}

////////////////////////////////////////////////////////////////////////////////////////

void shader_phong::set_mat_specular(float s)
{
    glUniform1f(_mat_specular_location, s);
}

////////////////////////////////////////////////////////////////////////////////////////

void shader_phong::set_mat_shininess (float s)
{
    glUniform1f(_mat_shininess_location, s);
}

////////////////////////////////////////////////////////////////////////////////////////

void shader_phong::set_tex_skin(int i)
{
    glUniform1i(_tex_skin_location, i);
}



////////////////////////////////////////////////////////////////////////////////////////

