/*
 * =====================================================================================
 *       Filename:  shader_realskin.vert
 *    Description:  
 *        Created:  2015-02-13 22:02
 *         Author:  Tiago Lobato Gimenes        (tlgimenes@gmail.com)
 * =====================================================================================
 */

////////////////////////////////////////////////////////////////////////////////////////
// OpenGL 4.5
#version 450

////////////////////////////////////////////////////////////////////////////////////////
// Location definitions
#define VERTEX 0
#define NORMAL 1
#define TEX_UV 2

////////////////////////////////////////////////////////////////////////////////////////
// Projetion and modelview matrices
uniform mat4 proj_matrix;
uniform mat4 view_matrix;
uniform mat4 model_matrix;

////////////////////////////////////////////////////////////////////////////////////////
// Shader Parameters
layout(location = VERTEX) in vec3 vertex;
layout(location = NORMAL) in vec3 normal;
layout(location = TEX_UV) in vec2 tex_uv;

////////////////////////////////////////////////////////////////////////////////////////
// Returns:
out vec3 vertex_interp;
out vec3 normal_interp;
out vec2 tex_uv_interp;
 
////////////////////////////////////////////////////////////////////////////////////////

void main(void)
{
    mat4 model_view_matrix = view_matrix * model_matrix;
    mat4 normal_matrix = transpose(inverse(model_view_matrix));

    vec4 vertex_aux = model_view_matrix * vec4(vertex, 1.0f);

    vertex_interp = vec3(vertex_aux) / vertex_aux.w;
    normal_interp = vec3(normal_matrix * vec4(normal, 0.0f));

    tex_uv_interp = vec2(tex_uv.x, 1-tex_uv.y);

    gl_Position = proj_matrix * model_view_matrix * vec4(vertex, 1.0f);
}

////////////////////////////////////////////////////////////////////////////////////////
