/*
 * =====================================================================================
 *       Filename:  Texture.cpp
 *    Description:  
 *        Created:  2015-01-14 16:46
 *         Author:  Tiago Lobato Gimenes        (tlgimenes@gmail.com)
 * =====================================================================================
 */

////////////////////////////////////////////////////////////////////////////////////////

#include <sstream>

#include "texture.hpp"
#include "error.hpp"
#include "texture_loader.hpp"
#include "texture_loader_ppm.hpp"

////////////////////////////////////////////////////////////////////////////////////////
// Constructors

template <typename T>
Texture<T>::Texture(const Texture& tex) :
    _data(tex.data()),
    _width(tex.width()),
    _height(tex.height())
{
    // Creates new OpenGL texture
    gl_new_texture();
}

////////////////////////////////////////////////////////////////////////////////////////

template <typename T>
Texture<T>::Texture(const std::vector<T>& data, uint height, uint width):
    _data(data),
    _width(width),
    _height(height)
{
    // Creates new OpenGL texture
    gl_new_texture();
}

////////////////////////////////////////////////////////////////////////////////////////
// Destructors
template <typename T>
Texture<T>::~Texture()
{
    glDeleteTextures(1, &_gl_tex_id);
    _data.std::vector<T>::~vector();
}

////////////////////////////////////////////////////////////////////////////////////////

template <typename T> 
void Texture<T>::gl_new_texture()
{
    // Creates new texture
    glGenTextures (1, &_gl_tex_id); GL_CHECK_FOR_ERRORS();   // Creates texture
    glBindTexture (GL_TEXTURE_2D, _gl_tex_id); GL_CHECK_FOR_ERRORS(); // Assigns the texture
    
    // Sets texture parameters
    glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); GL_CHECK_FOR_ERRORS();
    glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR); GL_CHECK_FOR_ERRORS();
    glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); GL_CHECK_FOR_ERRORS();
    glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); GL_CHECK_FOR_ERRORS();
    
    // Sets texture data
    gluBuild2DMipmaps (GL_TEXTURE_2D, GL_RGB, _width, _height, GL_RGB, 
            GL_UNSIGNED_BYTE, _data.data()); GL_CHECK_FOR_ERRORS();
    
    // Unbinds texture
    glBindTexture(GL_TEXTURE_2D, 0);
}

////////////////////////////////////////////////////////////////////////////////////////
