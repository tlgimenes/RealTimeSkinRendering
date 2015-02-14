/*
 * =====================================================================================
 *       Filename:  shader_realskin.hpp
 *    Description:  
 *        Created:  2015-02-13 15:48
 *         Author:  Tiago Lobato Gimenes        (tlgimenes@gmail.com)
 * =====================================================================================
 */

////////////////////////////////////////////////////////////////////////////////////////

#ifndef SHADER_REALSKIN_HPP
#define SHADER_REALSKIN_HPP

////////////////////////////////////////////////////////////////////////////////////////

#include "shader.hpp"
#include "texture.hpp"
#include "vec3.hpp"
#include "vec4.hpp"

#include <vector>

////////////////////////////////////////////////////////////////////////////////////////

#define REALSKIN_VERT_SHADER_PATH "../shaders/shader_realskin.vert"
#define REALSKIN_FRAG_SHADER_PATH "../shaders/shader_realskin.frag"

#define REALSKIN_LIGHT_POS_DEFAULT Vec3f(5.0, 5.0, 5.0)
#define REALSKIN_LIGHT_COLOR_DEFAULT Vec4f(1.0, 1.0, 1.0, 1.0)
#define REALSKIN_MAT_DIFF_COLOR_DEFAULT Vec4f(1.0, 1.0, 1.0, 1.0)
#define REALSKIN_MAT_DIFF_DEFAULT 0.5
#define REALSKIN_MAT_SPEC_COLOR_DEFAULT Vec4f(1.0, 1.0, 1.0, 1.0)
#define REALSKIN_MAT_SPEC_DEFAULT 0.5
#define REALSKIN_MAT_SHININESS_DEFAULT 0.5

////////////////////////////////////////////////////////////////////////////////////////

class ShaderRealskin : public Shader
{
    public:
        ShaderRealskin();
        inline virtual ~ShaderRealskin() {}

        /**
         * Sets
         * */
        void set_light_pos (const Vec3f& ligth_pos);
        void set_light_color (const Vec4f& ligth_color);
        void set_mat_diffuse_color (const Vec4f& mat_diff_color);
        void set_mat_diffuse (float s);
        void set_mat_specular_color (const Vec4f& mat_spec_color);
        void set_mat_specular(float s);
        void set_mat_shininess (float s);
        void set_tex_skin(int i);

        /**
         * Gets
         * */
        inline GLuint proj_matrix_location () const { return _proj_matrix_location; }
        inline GLuint view_matrix_location () const { return _view_matrix_location; }
        inline GLuint model_matrix_location() const { return _model_matrix_location;}

    private:
        // Light
        GLint _light_pos_location;
        GLint _light_color_location;

        // Material
        GLint _mat_diffuse_color_location;
        GLint _mat_diffuse_location;
        GLint _mat_specular_color_location;
        GLint _mat_specular_location;
        GLint _mat_shininess_location;

        // Projection and modelview matrices
        GLuint _proj_matrix_location;
        GLuint _view_matrix_location;
        GLuint _model_matrix_location;

        // Textures
        GLuint _tex_skin_location;
};

////////////////////////////////////////////////////////////////////////////////////////

#endif /* !SHADER_REALSKIN_HPP */

////////////////////////////////////////////////////////////////////////////////////////

