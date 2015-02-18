/*
 * =====================================================================================
 *       Filename:  texture_host.hpp
 *    Description:  
 *        Created:  2015-02-16 17:48
 *         Author:  Tiago Lobato Gimenes        (tlgimenes@gmail.com)
 * =====================================================================================
 */

////////////////////////////////////////////////////////////////////////////////////////

#ifndef TEXTURE_HOST_HPP
#define TEXTURE_HOST_HPP

////////////////////////////////////////////////////////////////////////////////////////

#include <memory>
#include <glm/vec4.hpp>

#include "texture_device.hpp"

////////////////////////////////////////////////////////////////////////////////////////

namespace sgl
{
    namespace host
    {
        class texture2D
        {
            private:
                std::shared_ptr<std::vector<unsigned char>> _pixels;
                int _height, _width;

            public:
                texture2D(const std::shared_ptr<std::vector<unsigned char>>& pixels, 
                        int height, int width);
                inline ~texture2D() {}

                /**
                 * Creates a new texture in device based on this object
                 * */
                std::shared_ptr<sgl::device::texture2D> to_device();

                /**
                 * Gets
                 * */
                inline std::shared_ptr<std::vector<unsigned char>> pixels();
                inline int height() const {return _height;}
                inline int width() const {return _width;}

                /**
                 * Sets 
                 *  */
                inline int& height() {return _height;}
                inline int& width() {return _width;}
        };
    }
}

////////////////////////////////////////////////////////////////////////////////////////

inline sgl::host::texture2D::texture2D(const std::shared_ptr<std::vector<unsigned char>>&
        pixels, int height, int width) :
    _pixels(pixels),
    _height(height),
    _width(width)
{
    /* Nothing to do here */
}

////////////////////////////////////////////////////////////////////////////////////////

inline std::shared_ptr<sgl::device::texture2D> sgl::host::texture2D::to_device()
{
    return std::shared_ptr<sgl::device::texture2D>(new sgl::device::texture2D(_pixels, 
                _height, _width));
}

////////////////////////////////////////////////////////////////////////////////////////

#endif /* !TEXTURE_HOST_HPP */

////////////////////////////////////////////////////////////////////////////////////////

