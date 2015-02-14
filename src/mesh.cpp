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

#ifndef X
#define X 0
#endif
#ifndef Y
#define Y 1
#endif
#ifndef Z
#define Z 2
#endif

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

template <typename T>
void Mesh<T>::recomputeNormals () 
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

template <typename T>
void Mesh<T>::centerAndScaleToUnit () 
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
/**
 *  Generates a vertex index array from the _triangles array 
 * */
template <typename T>
uint* Mesh<T>::triangle_to_vertex_index_array() const
{
    uint* array = new uint[_triangles.size()*3];
    uint j;

    for(uint i=0; i < _triangles.size(); i++)
    {
        j = i*3;
        array[j  ] = _triangles[i].v()[X];
        array[j+1] = _triangles[i].v()[Y];
        array[j+2] = _triangles[i].v()[Z];
    }

    return array;
}

////////////////////////////////////////////////////////////////////////////////////////

template <typename T>
void Mesh<T>::correct_tex_uv()
{
    std::vector<Vec2f> new_tex_uv(_vertex_coord.size());

    for(uint i=0; i < _triangles.size(); i++)
    {
        new_tex_uv[_triangles[i].v()[0]] = _tex_uv[_triangles[i].tex()[0]];
        new_tex_uv[_triangles[i].v()[1]] = _tex_uv[_triangles[i].tex()[1]];
        new_tex_uv[_triangles[i].v()[2]] = _tex_uv[_triangles[i].tex()[2]];
    }

    _tex_uv.assign(new_tex_uv.begin(), new_tex_uv.end());
}

////////////////////////////////////////////////////////////////////////////////////////

template <typename T>
std::vector<Texture<T>*>& Mesh<T>::texture_vec() const 
{
    std::vector<Texture<T>*>& tex = *(new std::vector<Texture<T>*>());

    for(auto i = _textures.begin(); i != _textures.end(); i++)
    {
        tex.push_back(i->second);
    }

    return tex;
}

////////////////////////////////////////////////////////////////////////////////////////
