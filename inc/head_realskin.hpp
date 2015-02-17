/*
 * =====================================================================================
 *       Filename:  head_realskin.hpp
 *    Description:  
 *        Created:  2015-02-17 15:19
 *         Author:  Tiago Lobato Gimenes        (tlgimenes@gmail.com)
 * =====================================================================================
 */

////////////////////////////////////////////////////////////////////////////////////////

#ifndef HEAD_REALSKIN_HPP
#define HEAD_REALSKIN_HPP

////////////////////////////////////////////////////////////////////////////////////////

#include "sgl/renderable.hpp"

#include "shader_realskin.hpp"

////////////////////////////////////////////////////////////////////////////////////////

class head_realskin: public sgl::device::renderable
{
    public:
        head_realskin(std::shared_ptr<sgl::device::mesh> m,
             std::shared_ptr<sgl::device::camera> c,
             std::shared_ptr<shader_realskin> s,
             std::vector<std::shared_ptr<sgl::device::texture2D>>& t) : 
            sgl::device::renderable(m, c, s, t)
    {
        c->proj() = s->proj_matrix_location();
        c->view() = s->view_matrix_location();
        c->model() = s->model_matrix_location();
    }
};

////////////////////////////////////////////////////////////////////////////////////////

#endif /* !HEAD_REALSKIN_HPP */

////////////////////////////////////////////////////////////////////////////////////////

