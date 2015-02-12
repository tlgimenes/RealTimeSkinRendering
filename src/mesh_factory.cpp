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

////////////////////////////////////////////////////////////////////////////////////////

Mesh& MeshFactory::load(const std::string& filename)
{
    Mesh* mesh = new Mesh();

    if(filename.compare(filename.size()-4, 4, ".obj") == 0) { // if .obj
        MeshLoaderObj::load(filename, *mesh);
    }
    else if(filename.compare(filename.size()-4, 4, ".off") == 0) { // if .off
        MeshLoaderOff::load(filename, *mesh);
    }
    else {
        FATAL_ERROR("File format valid");
    }

    return *mesh;
}

////////////////////////////////////////////////////////////////////////////////////////

