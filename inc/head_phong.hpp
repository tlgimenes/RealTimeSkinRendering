/*
 * =====================================================================================
 *       Filename:  head_phong.hpp
 *    Description:  
 *        Created:  2015-02-17 09:23
 *         Author:  Tiago Lobato Gimenes        (tlgimenes@gmail.com)
 * =====================================================================================
 */

////////////////////////////////////////////////////////////////////////////////////////

#ifndef HEAD_PHONG_HPP
#define HEAD_PHONG_HPP

////////////////////////////////////////////////////////////////////////////////////////

#include "sgl/renderable.hpp"

#include "program_phong.hpp"

////////////////////////////////////////////////////////////////////////////////////////

class head_phong : public sgl::device::renderable
{
    private:
        
    public:
        head_phong(std::shared_ptr<sgl::device::mesh> m,
                std::shared_ptr<sgl::device::camera> c,
                std::shared_ptr<program_phong> s,
                std::vector<std::shared_ptr<sgl::device::texture2D>>& t) :
            sgl::device::renderable(m, c, s, t) 
    {
        c->proj() = s->proj_matrix_location();
        c->view() = s->view_matrix_location();
        c->model() = s->model_matrix_location();
    }
};

////////////////////////////////////////////////////////////////////////////////////////

#endif /* !head_phong_HPP */

////////////////////////////////////////////////////////////////////////////////////////

