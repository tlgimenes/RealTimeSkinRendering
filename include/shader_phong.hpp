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

#define LIGHT_POS_DEFAULT Vec3f(3.0, 3.0, 3.0)
#define LIGHT_COLOR_DEFAULT Vec4f(1.0, 1.0, 1.0, 1.0)
#define MAT_DIFF_COLOR_DEFAULT Vec4f(1.0, 1.0, 1.0, 1.0)
#define MAT_DIFF_DEFAULT 0.5
#define MAT_SPEC_COLOR_DEFAULT Vec4f(1.0, 1.0, 1.0, 1.0)
#define MAT_SPEC_DEFAULT 0.5
#define MAT_SHININESS_DEFAULT 0.5

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

    private:
        GLint _light_pos_location;
        GLint _light_color_location;
        GLint _mat_diffuse_color_location;
        GLint _mat_diffuse_location;
        GLint _mat_specular_color_location;
        GLint _mat_specular_location;
        GLint _mat_shininess_location;
};

////////////////////////////////////////////////////////////////////////////////////////

#endif /* !SHADER_PHONG_HPP */

////////////////////////////////////////////////////////////////////////////////////////

