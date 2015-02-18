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
                camera(const std::shared_ptr<glm::mat4>& proj_mat, 
                       const std::shared_ptr<glm::mat4>& view_mat,
                       const std::shared_ptr<glm::mat4>& model_mat,
                       GLuint proj = 0, GLuint view = 0, GLuint model = 0);

                camera(const camera& m) : _proj_mat(m.proj_mat()), _view_mat(m.view_mat()),
                    _model_mat(m.model_mat()), _proj(m.proj()), _view(m.view()), _model(m.model()) {}

                inline void bind(){update_projection(); update_view(); update_model();}
                inline void unbind(){}

                /**
                 * Gets
                 * */
                inline const GLuint& proj() const {return _proj;}
                inline const GLuint& view() const {return _view;}
                inline const GLuint& model() const {return _model;}

                inline const std::shared_ptr<glm::mat4>& proj_mat() const {return _proj_mat;}
                inline const std::shared_ptr<glm::mat4>& view_mat() const {return _view_mat;}
                inline const std::shared_ptr<glm::mat4>& model_mat() const {return _model_mat;}

                /**
                 * Sets
                 * */ 
                inline GLuint& proj() {return _proj;}
                inline GLuint& view() {return _view;}
                inline GLuint& model() {return _model;}
 
                inline std::shared_ptr<glm::mat4>& proj_mat() {return _proj_mat;}
                inline std::shared_ptr<glm::mat4>& view_mat() {return _view_mat;}
                inline std::shared_ptr<glm::mat4>& model_mat() {return _model_mat;}
        };
    }
}

////////////////////////////////////////////////////////////////////////////////////////

inline sgl::device::camera::camera(
        const std::shared_ptr<glm::mat4>& proj_mat, 
        const std::shared_ptr<glm::mat4>& view_mat, 
        const std::shared_ptr<glm::mat4>& model_mat, 
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

