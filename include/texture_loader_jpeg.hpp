/*
 * =====================================================================================
 *       Filename:  texture_loader_jpeg.hpp
 *    Description:  
 *        Created:  2015-02-01 22:07
 *         Author:  Tiago Lobato Gimenes        (tlgimenes@gmail.com)
 * =====================================================================================
 */

////////////////////////////////////////////////////////////////////////////////////////

#ifndef TEXTURE_LOADER_JPEG_HPP
#define TEXTURE_LOADER_JPEG_HPP

////////////////////////////////////////////////////////////////////////////////////////

#include "texture_loader.hpp"
#include "utils.hpp"

////////////////////////////////////////////////////////////////////////////////////////

template <typename T> 
class TextureLoaderJPEG : public TextureLoader<T>
{
    public:
        /**
         * Loads a JPEG file and creates a texture for it 
         * */
        Texture<T>& load_texture(const std::string& file_name) const;
};

////////////////////////////////////////////////////////////////////////////////////////

template class TextureLoaderJPEG<uchar>;
template class TextureLoaderJPEG<float>;
template class TextureLoaderJPEG<uint>;

////////////////////////////////////////////////////////////////////////////////////////

#endif /* !TEXTURE_LOADER_JPEG_HPP */

////////////////////////////////////////////////////////////////////////////////////////

