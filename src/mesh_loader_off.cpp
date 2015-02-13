/*
 * =====================================================================================
 *       Filename:  mesh_loader_off.cpp
 *    Description:  
 *        Created:  2015-01-29 15:10
 *         Author:  Tiago Lobato Gimenes        (tlgimenes@gmail.com)
 * =====================================================================================
 */

////////////////////////////////////////////////////////////////////////////////////////

#include <fstream>

#include "mesh_loader_off.hpp"

#include "error.hpp"

////////////////////////////////////////////////////////////////////////////////////////

template <typename T>
void MeshLoaderOff<T>::load(const std::string& filename, Mesh<T>& mesh)
{
    std::ifstream in (filename, std::ios_base::in);

    ASSERT_FATAL_ERROR(in, "File not found");
    std::string offString;
    unsigned int sizeV, sizeT, tmp;
    in >> offString >> sizeV >> sizeT >> tmp;
    mesh.vertex().resize (sizeV);
    mesh.triangle().resize (sizeT);
    for (unsigned int i = 0; i < sizeV; i++) 
        in >> mesh.vertex()[i];
    int s;
    for (unsigned int i = 0; i < sizeT; i++) {
        in >> s;
        for (unsigned int j = 0; j < 3; j++) {
            in >> s; 
            mesh.triangle()[i].n()[j] = mesh.triangle()[i].v()[j] = s;
        }
    }
    in.close ();

    mesh.centerAndScaleToUnit ();
    mesh.recomputeNormals ();
}

////////////////////////////////////////////////////////////////////////////////////////

