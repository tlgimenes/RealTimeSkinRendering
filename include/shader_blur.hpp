/*
 * =====================================================================================
 *       Filename:  shader_blur.hpp
 *    Description:  
 *        Created:  2015-02-15 13:52
 *         Author:  Tiago Lobato Gimenes        (tlgimenes@gmail.com)
 * =====================================================================================
 */

////////////////////////////////////////////////////////////////////////////////////////

#ifndef SHADER_BLUR_HPP
#define SHADER_BLUR_HPP

////////////////////////////////////////////////////////////////////////////////////////

#include "shader.hpp"
#include "texture.hpp"

#include "vec4.hpp"
#include "vec3.hpp"

////////////////////////////////////////////////////////////////////////////////////////

#define BLUR_VERT_SHADER_PATH "../shaders/shader_blur.vert"
#define BLUR_FRAG_SHADER_PATH "../shaders/shader_blur.frag"

#define BLUR_LIGHT_POS_DEFAULT Vec3f(5.0, 5.0, 5.0)
#define BLUR_LIGHT_COLOR_DEFAULT Vec4f(1.0, 1.0, 1.0, 1.0)
#define BLUR_MAT_DIFF_COLOR_DEFAULT Vec4f(1.0, 1.0, 1.0, 1.0)
#define BLUR_MAT_DIFF_DEFAULT 0.5
#define BLUR_MAT_SPEC_COLOR_DEFAULT Vec4f(1.0, 1.0, 1.0, 1.0)
#define BLUR_MAT_SPEC_DEFAULT 0.000004
#define BLUR_MAT_ROUGHNESS_DEFAULT 0.00001
#define BLUR_MAT_REFLECT_NORMAL_DEFAULT 0.028

////////////////////////////////////////////////////////////////////////////////////////

class ShaderBlur: public Shader
{
    public:
        ShaderBlur(const Texture<uchar>& base, uint count);
        inline virtual ~ShaderBlur() {}

        /**
         * Applies the blur to all generated textures
         * */
        void apply();

        /**
         * Gets
         * */
        inline const std::vector<Texture<uchar>*>& tex_blur() const {return _tex_blur;}
        inline GLuint proj_matrix_location () const { return _proj_matrix_location; }
        inline GLuint view_matrix_location () const { return _view_matrix_location; }
        inline GLuint model_matrix_location() const { return _model_matrix_location;}
       
        /**
         * Sets
         * */
        inline std::vector<Texture<uchar>*>& tex_blur() {return _tex_blur;}

        void set_light_pos (const Vec3f& ligth_pos);
        void set_light_color (const Vec4f& ligth_color);
        void set_mat_diffuse_color (const Vec4f& mat_diff_color);
        void set_mat_diffuse (float s);
        void set_mat_specular_color (const Vec4f& mat_spec_color);
        void set_mat_specular(float s);
        void set_mat_roughness(float m);
        void set_mat_reflect_normal(float F0);

        void set_tex_skin(int i);

    protected:
        /**
         * Creates count textures that will be blured
         * */
         void gen_tex_blur(uint count);

         /**
          * Generates a multi-texture frame buffer
          * */
         void gen_frame_buff();

    private: 
        std::vector<Texture<uchar>*> _tex_blur; // Blured textures

        const Texture<uchar>& _tex_base;        // Base texture
            
        GLuint _frame_buff;                      // Multi-texture frame buffer

        // Light
        GLint _light_pos_location;
        GLint _light_color_location;

        // Material
        GLint _mat_diffuse_color_location;
        GLint _mat_diffuse_location;
        GLint _mat_specular_color_location;
        GLint _mat_specular_location;
        GLint _mat_roughness_location;
        GLint _mat_reflect_normal_locaiton;

        // Projection and modelview matrices
        GLuint _proj_matrix_location;
        GLuint _view_matrix_location;
        GLuint _model_matrix_location;

        GLuint _tex_skin_location; // Texture location in shader
};

////////////////////////////////////////////////////////////////////////////////////////

#endif /* !SHADER_BLUR_HPP */

////////////////////////////////////////////////////////////////////////////////////////

