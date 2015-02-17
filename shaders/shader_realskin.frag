/*
 * =====================================================================================
 *       Filename:  shader_realskin.frag
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
uniform float mat_roughness;
uniform float mat_reflect_normal;

////////////////////////////////////////////////////////////////////////////////////////
// Camera properties
uniform mat4 view_matrix;
uniform mat4 model_matrix;
uniform mat4 proj_matrix;

////////////////////////////////////////////////////////////////////////////////////////
// Textures
layout(location=0) uniform sampler2D tex_skin;

layout(location=1) uniform sampler2D tex_blur0;
layout(location=2) uniform sampler2D tex_blur1;
layout(location=3) uniform sampler2D tex_blur2;
layout(location=4) uniform sampler2D tex_blur3;
layout(location=5) uniform sampler2D tex_blur4;
layout(location=6) uniform sampler2D tex_blur5;

////////////////////////////////////////////////////////////////////////////////////////
// Gaussian coefficients
uniform vec4 coeff0;
uniform vec4 coeff1;
uniform vec4 coeff2;
uniform vec4 coeff3;
uniform vec4 coeff4;
uniform vec4 coeff5;

////////////////////////////////////////////////////////////////////////////////////////
// Parameters
in vec3 vertex_interp;
in vec3 normal_interp;
in vec2 tex_uv_interp;

////////////////////////////////////////////////////////////////////////////////////////
// Return: color
out vec4 frag_color;
out vec4 whatever;

////////////////////////////////////////////////////////////////////////////////////////
// Computes the Beckmann's PH term 
float PHBeckmann (float ndoth, float m)  
{  
    float alpha = acos( ndoth );  
    float ta = tan( alpha );  
    float val = 1.0/(m*m*pow(ndoth,4.0))*exp(-(ta*ta)/(m*m));  
    return val;  
}

float geometric (vec3 v, vec3 l) 
{
    vec3 h = v + l;
    
    return dot (h, h);
}

float fresnelReflectance( vec3 H, vec3 V, float F0 )
{
    float base = 1.0 - dot( V, H );  
    float exponential = pow( base, 5.0 );  

    return exponential + F0 * ( 1.0 - exponential );  
}

float specular(vec3 vertex, vec3 normal, vec3 halfway, vec3 light, float m, float F0)
{
    return PHBeckmann( dot(normal, halfway), m) * geometric (vertex, light) * fresnelReflectance (halfway, vertex, F0);
}

////////////////////////////////////////////////////////////////////////////////////////
// Computes the diffuse term based on the gaussian textures
vec4 mat_light_color(vec2 tex_coord)
{
    vec4 final_interp = coeff0 * texture (tex_blur0, tex_uv_interp);
    final_interp += coeff1 * texture (tex_blur1, tex_uv_interp);
    final_interp += coeff2 * texture (tex_blur2, tex_uv_interp); 
    final_interp += coeff3 * texture (tex_blur3, tex_uv_interp); 
    final_interp += coeff4 * texture (tex_blur4, tex_uv_interp); 
    final_interp += coeff5 * texture (tex_blur5, tex_uv_interp);

    final_interp /= (coeff0 + coeff1 + coeff2 + coeff3 + coeff4 + coeff5);

    return final_interp;
}

////////////////////////////////////////////////////////////////////////////////////////

void main (void) {
    frag_color = vec4(0.0, 0.0, 0.0, 1.0);
    
    vec3 p = vertex_interp;
    vec3 n = normalize (normal_interp);
    vec3 l = normalize (light_pos - p);
    
    vec3 r = reflect (-l, n);
    vec3 v = normalize (-p);
    
    // ---------- Phong's BRDF -------------
    float diff = max(0, dot(n, l));
    float spec = 0.5; 
 
    vec3 h = normalize (l+v);
    spec =  specular(p, n, h, l, mat_roughness, mat_reflect_normal);
    // ----------------------------------------
    
    // ---------- Texture -------------
    vec4 tex = texture (tex_skin, tex_uv_interp);
    // ----------------------------------------

    frag_color = (mat_diff * diff * mat_light_color(tex_uv_interp) + mat_spec * spec * mat_spec_color) * light_color;
    //frag_color = diff *  tex;
    whatever = tex * texture(tex_skin, tex_uv_interp) * (mat_diff * diff * mat_light_color(tex_uv_interp) + mat_spec * spec * mat_spec_color) * light_color; 
    frag_color *= tex;
}

////////////////////////////////////////////////////////////////////////////////////////
