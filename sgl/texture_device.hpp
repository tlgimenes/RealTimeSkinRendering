/*
 * =====================================================================================
 *       Filename:  texture_device.hpp
 *    Description:  
 *        Created:  2015-02-16 18:04
 *         Author:  Tiago Lobato Gimenes        (tlgimenes@gmail.com)
 * =====================================================================================
 */

////////////////////////////////////////////////////////////////////////////////////////

#ifndef TEXTURE_DEVICE_HPP
#define TEXTURE_DEVICE_HPP

////////////////////////////////////////////////////////////////////////////////////////

#include <memory>
#include <vector>

#include <glm/vec4.hpp>

#include "error.hpp"

////////////////////////////////////////////////////////////////////////////////////////

namespace sgl
{
    namespace device
    {
        class texture2D 
        {
            private:
                GLuint _id;

            protected:
                GLuint new_texture(unsigned char* data, int height, int width);

            public:
                texture2D(std::shared_ptr<std::vector<unsigned char>> pixels, int height, int width);
                texture2D(const texture2D& texture);

                /**
                 * Binds texture 
                 * */
                inline void bind() {glBindTexture (GL_TEXTURE_2D, _id); gl_check_for_errors();}

                /**
                 * Unbinds texture 
                 * */
                inline void unbind() {glBindTexture (GL_TEXTURE_2D, 0); gl_check_for_errors();}

                /**
                 * Gets the OpenGL ID of this texture 
                 * */
                inline GLuint id() const {return _id;}
        };
    }
}

////////////////////////////////////////////////////////////////////////////////////////

sgl::device::texture2D::texture2D(std::shared_ptr<std::vector<unsigned char>> pixels, 
        int height, int width)
{
    _id = new_texture(pixels->data(), height, width);
}

////////////////////////////////////////////////////////////////////////////////////////

sgl::device::texture2D::texture2D(const texture2D& texture)
{
    _id = texture.id();
}

////////////////////////////////////////////////////////////////////////////////////////

GLuint sgl::device::texture2D::new_texture(unsigned char* data, int height, int width)
{
    GLuint id;

    // Creates new texture
    glGenTextures (1, &id); gl_check_for_errors();   // Creates texture
    glBindTexture (GL_TEXTURE_2D, id); gl_check_for_errors(); // Assigns the texture
    
    // Sets texture parameters
    glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); gl_check_for_errors();
    glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR); gl_check_for_errors();
    glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); gl_check_for_errors();
    glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); gl_check_for_errors();
    
    // Sets texture data
    gluBuild2DMipmaps (GL_TEXTURE_2D, GL_RGB, width, height, GL_RGB, GL_UNSIGNED_BYTE, 
            data); gl_check_for_errors();
    
    // Unbinds texture
    glBindTexture(GL_TEXTURE_2D, 0);

    return id;
}

////////////////////////////////////////////////////////////////////////////////////////

#endif /* !TEXTURE_DEVICE_HPP */

////////////////////////////////////////////////////////////////////////////////////////

