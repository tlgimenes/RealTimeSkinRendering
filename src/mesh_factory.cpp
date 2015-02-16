/*
 * =====================================================================================
 *       Filename:  mesh_factory.cpp
 *    Description:  
 *        Created:  2015-02-12 22:07
 *         Author:  Tiago Lobato Gimenes        (tlgimenes@gmail.com)
 * =====================================================================================
 */

////////////////////////////////////////////////////////////////////////////////////////

#include "mesh_factory.hpp"

#include "mesh_loader_obj.hpp"
#include "mesh_loader_off.hpp"

#include "texture_loader_jpeg.hpp"

////////////////////////////////////////////////////////////////////////////////////////

template <typename T>
Mesh<T>& MeshFactory<T>::load(const std::string& filename)
{
    Mesh<T>* mesh = new Mesh<T>();

    if(filename.compare(filename.size()-4, 4, ".obj") == 0) { // if .obj
        MeshLoaderObj<T>::load(filename, *mesh);
    }
    else if(filename.compare(filename.size()-4, 4, ".off") == 0) { // if .off
        //MeshLoaderOff<T>::load(filename, *mesh);
        FATAL_ERROR("Sorry, .off files are no longer supported");
    }
    else {
        FATAL_ERROR("File format valid");
    }

    TextureLoaderJPEG<T> tex_loader;
    char* blurs[] = {"../../models/blondGirl/Blur0.jpg",
                     "../../models/blondGirl/Blur1.jpg",
                     "../../models/blondGirl/Blur2.jpg",
                     "../../models/blondGirl/Blur3.jpg",
                     "../../models/blondGirl/Blur4.jpg",
                     "../../models/blondGirl/Blur5.jpg"};

    for(uint i=0; i < 6; i++)
    {
        mesh->_blured_textures.push_back(&tex_loader.load_texture(blurs[i]));
    }

    return *mesh;
}

////////////////////////////////////////////////////////////////////////////////////////

