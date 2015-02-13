// --------------------------------------------------------------------------
// Simple fragment shader to fill.
//
// Copyright(C) 2007-2009                
// Tamy Boubekeur
//                                                                            
// All rights reserved.                                                       
// --------------------------------------------------------------------------

// Light properties
uniform vec3 light_pos;
uniform vec4 light_color;

// Material properties
uniform vec4 mat_diff_color;
uniform float mat_diff;
uniform vec4 mat_spec_color;
uniform float mat_spec;
uniform float mat_shininess;

// 3D point properties
varying vec4 P;
varying vec3 N;

void main (void) {
    gl_FragColor = vec4 (0.0, 0.0, 0.0, 1);
   
    vec3 p = vec3 (gl_ModelViewMatrix * P);
    vec3 n = normalize (gl_NormalMatrix * N);
    vec3 l = normalize (light_pos - p);
    
    vec3 r = reflect (-l, n);
    vec3 v = normalize (-p);
    
    // ---------- Code à modifier -------------
    float diffuse = 0.5;
    float spec = 0.5; 
 
    vec3 h = normalize (l+v);
    diffuse = max (0.0, dot(n, l));
    spec = pow ( max (0.0, dot(n, h)), mat_shininess);
    // ----------------------------------------
    
    gl_FragColor += (mat_diff * diffuse * mat_diff_color + mat_spec * spec * mat_spec_color) * light_color;
}
 
