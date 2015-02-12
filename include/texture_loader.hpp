/*
 * =====================================================================================
 *       Filename:  TextureLoader.hpp
 *    Description:  
 *        Created:  2015-01-14 16:51
 *         Author:  Tiago Lobato Gimenes        (tlgimenes@gmail.com)
 * =====================================================================================
 */

////////////////////////////////////////////////////////////////////////////////////////

#ifndef TEXTURELOADER_HPP
#define TEXTURELOADER_HPP

////////////////////////////////////////////////////////////////////////////////////////

#include <vector>
#include <sstream>
#include <string>
#include <algorithm>

#include "utils.hpp"
#include "texture.hpp"
#include "error.hpp"

////////////////////////////////////////////////////////////////////////////////////////

template <typename T>
class TextureLoader
{
    protected:
        /**
         * Gets the 3 last caracters of the file name, i.e. the file extension 
         * */
        const std::string file_extension(const std::string& file_name) const;

    public:
        /**
         * Interface for the implementation of loading a texture from a file 
         * */
        virtual Texture<T>& load_texture(const std::string& file_name) const;
};

////////////////////////////////////////////////////////////////////////////////////////

template <typename T>
const std::string TextureLoader<T>::file_extension(const std::string& file_name) const
{
    std::string extension(file_name, file_name.size()-3, 3);

    return extension;
}

////////////////////////////////////////////////////////////////////////////////////////

template <typename T>
Texture<T>& TextureLoader<T>::load_texture(const std::string& file_name) const
{
    FATAL_ERROR("Not implemented function");

    return *(new Texture<T>(std::vector<T>(), 0, 0));
}

////////////////////////////////////////////////////////////////////////////////////////

#endif /* !TEXTURELOADER_HPP */

////////////////////////////////////////////////////////////////////////////////////////

