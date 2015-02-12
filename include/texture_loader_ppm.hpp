/*
 * =====================================================================================
 *       Filename:  TextureLoaderPPM.hpp
 *    Description:  
 *        Created:  2015-01-14 16:54
 *         Author:  Tiago Lobato Gimenes        (tlgimenes@gmail.com)
 * =====================================================================================
 */

////////////////////////////////////////////////////////////////////////////////////////

#ifndef TEXTURELOADERPPM_HPP
#define TEXTURELOADERPPM_HPP

////////////////////////////////////////////////////////////////////////////////////////

#include <vector>

#include "texture.hpp"
#include "texture_loader.hpp"
#include "utils.hpp"

////////////////////////////////////////////////////////////////////////////////////////

template <typename T>
class TextureLoaderPPM: public TextureLoader<T>
{
    public:
        /**
         * Loads a PPM P3 texture type with each value of RGB being
         * unsigned byte and creates a texture object.
         * */
        Texture<T>& load_texture(const std::string& file_name) const;
};

////////////////////////////////////////////////////////////////////////////////////////

template class TextureLoaderPPM<uchar>;
template class TextureLoaderPPM<float>;
template class TextureLoaderPPM<uint>;

////////////////////////////////////////////////////////////////////////////////////////

#endif /* !TEXTURELOADERPPM_HPP */

////////////////////////////////////////////////////////////////////////////////////////

