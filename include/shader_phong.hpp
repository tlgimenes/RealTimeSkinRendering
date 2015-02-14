/*
 * =====================================================================================
 *       Filename:  shader_phong.hpp
 *    Description:  
 *        Created:  2015-02-12 11:08
 *         Author:  Tiago Lobato Gimenes        (tlgimenes@gmail.com)
 * =====================================================================================
 */

////////////////////////////////////////////////////////////////////////////////////////

#ifndef SHADER_PHONG_HPP
#define SHADER_PHONG_HPP

////////////////////////////////////////////////////////////////////////////////////////

#include "shader.hpp"
#include "vec3.hpp"
#include "vec4.hpp"

////////////////////////////////////////////////////////////////////////////////////////

#define PHONG_FRAG_SHADER_PATH "../shaders/shader_phong.frag"
#define PHONG_VERT_SHADER_PATH "../shaders/shader_phong.vert"

#define PHONG_LIGHT_POS_DEFAULT Vec3f(5.0, 5.0, 5.0)
#define PHONG_LIGHT_COLOR_DEFAULT Vec4f(1.0, 1.0, 1.0, 1.0)
#define PHONG_MAT_DIFF_COLOR_DEFAULT Vec4f(1.0, 1.0, 1.0, 1.0)
#define PHONG_MAT_DIFF_DEFAULT 0.5
#define PHONG_MAT_SPEC_COLOR_DEFAULT Vec4f(1.0, 1.0, 1.0, 1.0)
#define PHONG_MAT_SPEC_DEFAULT 0.5
#define PHONG_MAT_SHININESS_DEFAULT 0.5

////////////////////////////////////////////////////////////////////////////////////////

class ShaderPhong : public Shader
{
    public:
        ShaderPhong();
        inline virtual ~ShaderPhong() {}

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

#endif /* !SHADER_PHONG_HPP */

////////////////////////////////////////////////////////////////////////////////////////

