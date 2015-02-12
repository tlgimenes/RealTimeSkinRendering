/*
 * =====================================================================================
 *       Filename:  TextureLoaderPPM.cpp
 *    Description:  
 *        Created:  2015-01-14 16:56
 *         Author:  Tiago Lobato Gimenes        (tlgimenes@gmail.com)
 * =====================================================================================
 */

////////////////////////////////////////////////////////////////////////////////////////

#include <fstream>
#include <iostream>

#include "texture_loader_ppm.hpp"
#include "error.hpp"

////////////////////////////////////////////////////////////////////////////////////////

template <typename T>
Texture<T>& TextureLoaderPPM<T>::load_texture(const std::string& file_name) const
{
    std::ifstream file(file_name, std::ifstream::in); // Opens texture file 
    std::string garbage;    // variable for sending useless format variables like commentaries
    uint R,G,B;             // Texture's RGB
    uint size;              // size, must be 255
    uint width=0, height=0; // width and height of the texture
    std::vector<T> data;    // texture's data vector

    if(!file.is_open()) FATAL_ERROR("File not found");

    file >> garbage >> garbage;  // P3
    file.ignore(999, '\n');      // # -- comments --
    file >> width >> height;     // width heigth
    file >> size;                // size must be equals to 255

    // Size must be equal to 255 and file extension must be ppm
    if(size != 255 || this->file_extension(file_name).compare("ppm")) 
        FATAL_ERROR("Filetype/format not supported");

    // file to data vector
    while(!file.eof())
    {
        file >> R >> G >> B;
        data.push_back(R);
        data.push_back(G);
        data.push_back(B);
    }
    // returns the new texture
    return *(new Texture<T>(data, height, width)); 
}

////////////////////////////////////////////////////////////////////////////////////////

