/*
 * =====================================================================================
 *       Filename:  camera_device.hpp
 *    Description:  
 *        Created:  2015-02-16 19:44
 *         Author:  Tiago Lobato Gimenes        (tlgimenes@gmail.com)
 * =====================================================================================
 */

////////////////////////////////////////////////////////////////////////////////////////

#ifndef CAMERA_DEVICE_HPP
#define CAMERA_DEVICE_HPP

////////////////////////////////////////////////////////////////////////////////////////

#include <memory>
#include <glm/mat4x4.hpp>
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr

////////////////////////////////////////////////////////////////////////////////////////

namespace sgl
{
    namespace device
    {
        class camera 
        {
            private:
                GLuint _proj, _view, _model;
                std::shared_ptr<glm::mat4> _proj_mat, _view_mat, _model_mat;

            protected:
                void update_projection();
                void update_view();
                void update_model();

            public:
                camera(std::shared_ptr<glm::mat4>& proj_mat, 
                       std::shared_ptr<glm::mat4>& view_mat,
                       std::shared_ptr<glm::mat4>& model_mat,
                       GLuint proj = 0, GLuint view = 0, GLuint model = 0);

                inline void bind(){update_projection(); update_view(); update_model();}
                inline void unbind(){}

                /**
                 * Sets
                 * */ 
                inline GLuint& proj() {return _proj;}
                inline GLuint& view() {return _view;}
                inline GLuint& model() {return _model;}
        };
    }
}

////////////////////////////////////////////////////////////////////////////////////////

inline sgl::device::camera::camera(std::shared_ptr<glm::mat4>& proj_mat, 
        std::shared_ptr<glm::mat4>& view_mat, std::shared_ptr<glm::mat4>& model_mat, 
        GLuint proj, GLuint view, GLuint model) :
    _proj_mat(proj_mat),
    _model_mat(model_mat),
    _view_mat(view_mat),
    _proj(proj),
    _view(view),
    _model(model)
{
    /* Nothing to do here */
}

////////////////////////////////////////////////////////////////////////////////////////

inline void sgl::device::camera::update_projection()
{
    glUniformMatrix4fv(_proj, 1, GL_FALSE, glm::value_ptr(*_proj_mat));
    gl_check_for_errors();
}

////////////////////////////////////////////////////////////////////////////////////////

inline void sgl::device::camera::update_view()
{
    glUniformMatrix4fv(_view, 1, GL_FALSE, glm::value_ptr(*_view_mat));
    gl_check_for_errors();
}

////////////////////////////////////////////////////////////////////////////////////////

inline void sgl::device::camera::update_model()
{
    glUniformMatrix4fv(_model, 1, GL_FALSE, glm::value_ptr(*_model_mat));
    gl_check_for_errors();
}

////////////////////////////////////////////////////////////////////////////////////////

#endif /* !CAMERA_DEVICE_HPP */

////////////////////////////////////////////////////////////////////////////////////////

