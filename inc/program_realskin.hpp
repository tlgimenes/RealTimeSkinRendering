/*
 * =====================================================================================
 *       Filename:  program_realskin.hpp
 *    Description:  
 *        Created:  2015-02-17 14:57
 *         Author:  Tiago Lobato Gimenes        (tlgimenes@gmail.com)
 * =====================================================================================
 */

////////////////////////////////////////////////////////////////////////////////////////

#ifndef program_REALSKIN_HPP
#define program_REALSKIN_HPP

////////////////////////////////////////////////////////////////////////////////////////

#include "sgl/pipeline_device.hpp"

#include <glm/vec4.hpp>
#include <glm/vec3.hpp>

#include <vector>

////////////////////////////////////////////////////////////////////////////////////////

#define REALSKIN_VERT_PROGRAM_PATH "../shaders/shader_realskin.vert"
#define REALSKIN_FRAG_PROGRAM_PATH "../shaders/shader_realskin.frag"

#define REALSKIN_LIGHT_POS_DEFAULT glm::vec3(5.0, 5.0, 5.0)
#define REALSKIN_LIGHT_COLOR_DEFAULT glm::vec4(1.5, 1.5, 1.5, 1.0)
#define REALSKIN_MAT_DIFF_COLOR_DEFAULT glm::vec4(1.0, 1.0, 1.0, 1.0)
#define REALSKIN_MAT_DIFF_DEFAULT 0.5
#define REALSKIN_MAT_SPEC_COLOR_DEFAULT glm::vec4(1.0, 1.0, 1.0, 1.0)
#define REALSKIN_MAT_SPEC_DEFAULT 0.00000012
#define REALSKIN_MAT_ROUGHNESS_DEFAULT 0.00001
#define REALSKIN_MAT_REFLECT_NORMAL_DEFAULT 0.028

#define COEFF0_DEFAULT glm::vec4(0.233, 0.455, 0.649, 1.0)
#define COEFF1_DEFAULT glm::vec4(0.100, 0.336, 0.344, 1.0)
#define COEFF2_DEFAULT glm::vec4(0.118, 0.198, 0.000, 1.0)
#define COEFF3_DEFAULT glm::vec4(0.113, 0.007, 0.007, 1.0)
#define COEFF4_DEFAULT glm::vec4(0.358, 0.004, 0.000, 1.0)
#define COEFF5_DEFAULT glm::vec4(0.078, 0.000, 0.000, 1.0)

////////////////////////////////////////////////////////////////////////////////////////

class program_realskin : public sgl::device::pipeline
{
    private:
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

        // Textures
        GLuint _tex_skin_location;
        std::vector<GLuint> _tex_blurs_location;

        // Coefficients
        std::vector<GLuint> _coeffs_location;
    
    public:
        program_realskin();
        inline virtual ~program_realskin() {}

        /**
         * Sets
         * */
        void set_light_pos (const glm::vec3& ligth_pos);
        void set_light_color (const glm::vec4& ligth_color);
        void set_mat_diffuse_color (const glm::vec4& mat_diff_color);
        void set_mat_diffuse (float s);
        void set_mat_specular_color (const glm::vec4& mat_spec_color);
        void set_mat_specular(float s);
        void set_mat_roughness(float m);
        void set_mat_reflect_normal(float F0);
        void set_tex_skin(int i);
        void set_tex_blur(int i, GLuint blur_id);
        void set_coeffs(const glm::vec4& coeff, GLuint coeff_id);
 
        /**
         * Gets
         * */
        inline GLuint proj_matrix_location () const { return _proj_matrix_location; }
        inline GLuint view_matrix_location () const { return _view_matrix_location; }
        inline GLuint model_matrix_location() const { return _model_matrix_location;}

};

////////////////////////////////////////////////////////////////////////////////////////

#endif /* !program_REALSKIN_HPP */

////////////////////////////////////////////////////////////////////////////////////////

