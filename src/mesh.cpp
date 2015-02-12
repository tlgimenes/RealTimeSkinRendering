/*
 * =====================================================================================
 *       Filename:  mesh.cpp
 *    Description:  
 *        Created:  2015-01-15 23:33
 *         Author:  Tiago Lobato Gimenes        (tlgimenes@gmail.com)
 * =====================================================================================
 */

////////////////////////////////////////////////////////////////////////////////////////

#include "mesh.hpp"

#include "mesh_loader_obj.hpp"
#include "mesh_loader_off.hpp"
#include "error.hpp"

////////////////////////////////////////////////////////////////////////////////////////

bool is_mesh_correct(const std::vector<Vec3f>& _vertex_coord, const std::vector<Triangle>& _triangles)
{
    for(uint i=0; i < _triangles.size(); i++)
    {
        for(uint j=0; j < 3; j++)
        {
            if(_triangles[i].v()[j] >= _vertex_coord.size() || _triangles[i].v()[j] < 0) {
                std::cout << _vertex_coord.size() << " " << _triangles[i].v()[j] << std::endl;
                FATAL_ERROR("Mesh is not correct !");
            }
        }
    }
    return false;
}

////////////////////////////////////////////////////////////////////////////////////////

void Mesh::recomputeNormals () 
{
    is_mesh_correct(_vertex_coord, _triangles);
     _normals.resize(_vertex_coord.size());
    for (unsigned int i = 0; i < _vertex_coord.size (); i++)
        _normals[i] = Vec3f(0.0, 0.0, 0.0);
    for (unsigned int i = 0; i < _triangles.size (); i++) {
        Vec3f e01 = _vertex_coord[_triangles[i].v()[1]] -  _vertex_coord[_triangles[i].v()[0]];
        Vec3f e02 = _vertex_coord[_triangles[i].v()[2]] -  _vertex_coord[_triangles[i].v()[0]];
        Vec3f n = e01.cross (e02);
        n.normalize ();
        for (unsigned int j = 0; j < 3; j++) {
            _normals[_triangles[i].n()[j]] += n;
        }
    }
    for (unsigned int i = 0; i < _vertex_coord.size (); i++) {
        _normals[i].normalize ();    
    }
}

////////////////////////////////////////////////////////////////////////////////////////

void Mesh::centerAndScaleToUnit () 
{
    Vec3f c;
    for  (unsigned int i = 0; i < _vertex_coord.size (); i++)
        c += _vertex_coord[i];
    c /= _vertex_coord.size ();
    float maxD = _vertex_coord[0].dist(c);
    for (unsigned int i = 0; i < _vertex_coord.size (); i++){
        float m = _vertex_coord[i].dist(c);
        if (m > maxD)
            maxD = m;
    }
    for  (unsigned int i = 0; i < _vertex_coord.size (); i++)
        _vertex_coord[i] = (_vertex_coord[i] - c) / maxD;
}

////////////////////////////////////////////////////////////////////////////////////////

