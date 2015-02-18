/*
 * =====================================================================================
 *       Filename:  shader_phong.frag
 *    Description:  
 *        Created:  2015-02-13 22:02
 *         Author:  Tiago Lobato Gimenes        (tlgimenes@gmail.com)
 * =====================================================================================
 */

////////////////////////////////////////////////////////////////////////////////////////
// OpenGL 4.5 
#version 450

////////////////////////////////////////////////////////////////////////////////////////
// Light properties
uniform vec3 light_pos;
uniform vec4 light_color;

////////////////////////////////////////////////////////////////////////////////////////
// Material properties
uniform vec4 mat_diff_color;
uniform float mat_diff;
uniform vec4 mat_spec_color;
uniform float mat_spec;
uniform float mat_shininess;

////////////////////////////////////////////////////////////////////////////////////////
// Camera properties
uniform mat4 inv_model_view_matrix;
uniform mat4 view_matrix;
uniform mat4 model_matrix;
uniform mat4 proj_matrix;

////////////////////////////////////////////////////////////////////////////////////////
// Textures
layout(location=0) uniform sampler2D tex_skin;

////////////////////////////////////////////////////////////////////////////////////////
// Parameters
in vec3 vertex_interp;
in vec3 normal_interp;
in vec2 tex_uv_interp;

////////////////////////////////////////////////////////////////////////////////////////
// Return: color
out vec4 frag_color;
out vec3 whathever;

////////////////////////////////////////////////////////////////////////////////////////

void main (void) {
    frag_color = vec4(0.0, 0.0, 0.0, 1.0);
    
    vec3 p = vertex_interp;
    vec3 n = normalize (normal_interp);
    vec3 l = normalize (light_pos - p);
    
    vec3 r = reflect (-l, n);
    vec3 v = normalize (-p);
    
    // ---------- Phong's BRDF -------------
    float diffuse = 0.5;
    float spec = 0.5; 
 
    vec3 h = normalize (l+v);
    diffuse = max (0.0, dot(n, l));
    spec = pow ( max (0.0, dot(n, h)), mat_shininess);
    // ----------------------------------------
    
    // ---------- Texture -------------
    vec4 tex = texture (tex_skin, tex_uv_interp);
    // ----------------------------------------

    frag_color += (mat_diff * diffuse * mat_diff_color  + mat_spec * spec * mat_spec_color) * light_color;
    frag_color *= tex;
    whathever = light_pos;
}

////////////////////////////////////////////////////////////////////////////////////////
