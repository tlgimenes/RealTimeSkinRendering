/*
 * =====================================================================================
 *       Filename:  program_phong.hpp
 *    Description:  
 *        Created:  2015-02-17 08:53
 *         Author:  Tiago Lobato Gimenes        (tlgimenes@gmail.com)
 * =====================================================================================
 */

////////////////////////////////////////////////////////////////////////////////////////

#ifndef PROGRAM_PHONG_HPP
#define PROGRAM_PHONG_HPP

////////////////////////////////////////////////////////////////////////////////////////

#include "sgl/pipeline_device.hpp"

#include <GL/glew.h>
#include <GL/gl.h>

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>

#include <string>

////////////////////////////////////////////////////////////////////////////////////////

#define PHONG_FRAG_PROGRAM_PATH "../shaders/shader_phong.frag"
#define PHONG_VERT_PROGRAM_PATH "../shaders/shader_phong.vert"

#define PHONG_LIGHT_POS_DEFAULT glm::vec3(5.0, 5.0, 5.0)
#define PHONG_LIGHT_COLOR_DEFAULT glm::vec4(1.5, 1.5, 1.5, 1.0)
#define PHONG_MAT_DIFF_COLOR_DEFAULT glm::vec4(1.0, 1.0, 1.0, 1.0)
#define PHONG_MAT_DIFF_DEFAULT 0.5
#define PHONG_MAT_SPEC_COLOR_DEFAULT glm::vec4(1.0, 1.0, 1.0, 1.0)
#define PHONG_MAT_SPEC_DEFAULT 0.000004
#define PHONG_MAT_SHININESS_DEFAULT 0.5

////////////////////////////////////////////////////////////////////////////////////////

class program_phong : public sgl::device::pipeline
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
        GLint _mat_shininess_location;

        // Projection and modelview matrices
        GLuint _proj_matrix_location;
        GLuint _view_matrix_location;
        GLuint _model_matrix_location;

        // Textures
        GLuint _tex_skin_location;

    public:
        program_phong();
        ~program_phong() {}

        /**
         * Sets
         * */
        void set_light_pos (const glm::vec3& ligth_pos);
        void set_light_color (const glm::vec4& ligth_color);
        void set_mat_diffuse_color (const glm::vec4& mat_diff_color);
        void set_mat_diffuse (float s);
        void set_mat_specular_color (const glm::vec4& mat_spec_color);
        void set_mat_specular(float s);
        void set_mat_shininess (float s);
        void set_tex_skin(int i);

        /**
         * Gets
         * */
        inline GLuint proj_matrix_location () const { return _proj_matrix_location; }
        inline GLuint view_matrix_location () const { return _view_matrix_location; }
        inline GLuint model_matrix_location() const { return _model_matrix_location;}
};

////////////////////////////////////////////////////////////////////////////////////////

#endif /* !PROGRAM_PHONG_HPP */

////////////////////////////////////////////////////////////////////////////////////////

