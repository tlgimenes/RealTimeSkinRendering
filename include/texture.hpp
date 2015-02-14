/*
 * =====================================================================================
 *       Filename:  Texture.hpp
 *    Description:  
 *        Created:  2015-01-14 16:37
 *         Author:  Tiago Lobato Gimenes        (tlgimenes@gmail.com)
 * =====================================================================================
 */

////////////////////////////////////////////////////////////////////////////////////////

#ifndef TEXTURE_HPP
#define TEXTURE_HPP

////////////////////////////////////////////////////////////////////////////////////////

#include <vector>
#include <string>

#include "error.hpp"
#include "utils.hpp"

#include <GL/gl.h>
#include <GL/glu.h>

////////////////////////////////////////////////////////////////////////////////////////

template <typename T>
class Texture
{
    private:
        std::vector<T> _data; // texture data
        uint _width, _height; // window width and height

        GLuint _gl_tex_id; // OpenGL texture id

    protected:
        /**
         * Creates a new OpenGL texture based on the data in _data, _width and _height 
         * variables. This method also sets the _gl_tex_id field;
         * */
        void gl_new_texture();

    public:
        /**
         *  Constructs a NEW OpenGL Texture 
         * */
        Texture(const Texture& tex); 
        Texture(const std::vector<T>& data, uint height, uint width);
        ~Texture();

        /**
         * Binds the OpenGL texture associated to the object
         * */
        inline void bind() const {glBindTexture(GL_TEXTURE_2D, _gl_tex_id);}
 
        /**
         * UnBinds the OpenGL texture associated to the object
         * */
        inline void unbind() const {glBindTexture(GL_TEXTURE_2D, 0);}

        /**
         * Gets and sets 
         * */
        inline const std::vector<T>& data() const {return _data;}
        inline uint height() const {return _height;}
        inline uint width() const {return _width;}
        inline GLuint gl_tex_id() const {return _gl_tex_id;}
};

////////////////////////////////////////////////////////////////////////////////////////

template class Texture<uchar>;
template class Texture<float>;
template class Texture<uint>;

////////////////////////////////////////////////////////////////////////////////////////

#endif /* !TEXTURE_HPP */

////////////////////////////////////////////////////////////////////////////////////////

