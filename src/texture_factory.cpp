/*
 * =====================================================================================
 *       file_path:  texture_factory.cpp
 *    Description:  
 *        Created:  2015-02-13 14:44
 *         Author:  Tiago Lobato Gimenes        (tlgimenes@gmail.com)
 * =====================================================================================
 */

////////////////////////////////////////////////////////////////////////////////////////

#include "texture_factory.hpp"

#include "texture_loader_jpeg.hpp"
#include "texture_loader_ppm.hpp"

////////////////////////////////////////////////////////////////////////////////////////

template <typename T>
Texture<T>& TextureFactory<T>::load(const std::string& file_path)
{
    if(file_path.compare(file_path.size()-5, 5, ".jpeg") == 0 ||
       file_path.compare(file_path.size()-4, 4, ".jpg") == 0) { // if .jpeg || jpg
        TextureLoaderJPEG<T> loader;
        return loader.load_texture(file_path);
    }
    else if(file_path.compare(file_path.size()-4, 4, ".ppm") == 0) { // if .ppm
        TextureLoaderPPM<T> loader;
        return loader.load_texture(file_path);
    }
    else {
        FATAL_ERROR("File format valid");
    }
}

////////////////////////////////////////////////////////////////////////////////////////

