/*
 * =====================================================================================
 *       Filename:  mesh_gl.cpp
 *    Description:  
 *        Created:  2015-02-13 16:22
 *         Author:  Tiago Lobato Gimenes        (tlgimenes@gmail.com)
 * =====================================================================================
 */

////////////////////////////////////////////////////////////////////////////////////////

#include "mesh_gl.hpp"

#include <GL/gl.h>

////////////////////////////////////////////////////////////////////////////////////////

template <int dim, typename retArray, typename VecIn>
retArray* to_array(const std::vector<VecIn>& vector)
{
    retArray* array = new retArray[vector.size() * dim];
    
    for(uint i=0; i < vector.size(); i++)
    {
        for(uint j=dim*i; j < dim*i+dim; j++)
        {
            array[j] = vector[i][j-dim*i];
        }
    }
    return array;
}

////////////////////////////////////////////////////////////////////////////////////////

template <typename T>
MeshGL<T>::MeshGL(Mesh<T>& mesh) :
    _vao(0),
    _v_vbo(0),
    _n_vbo(0),
    _t_vbo(0),
    _i_vbo(0),
    _t_fbo(0),
    _i_vbo_size(0)
{
    load_vbos(mesh);

    load_index_buffer(mesh);

    load_vao(mesh);

    load_fbos(mesh);

    glBindVertexArray (0);
    glBindBuffer (GL_ARRAY_BUFFER, 0);
}

////////////////////////////////////////////////////////////////////////////////////////

template <typename T>
void MeshGL<T>::load_vbos(Mesh<T>& mesh)
{
    /* Creates Vertex VBO */
    float* vertex_array = to_array<3, float, Vec3f>(mesh.vertex());
    glGenBuffers (1, &_v_vbo);
    glBindBuffer (GL_ARRAY_BUFFER, _v_vbo);
    glBufferData (GL_ARRAY_BUFFER, mesh.vertex().size() * sizeof(float) * 3, 
            vertex_array, GL_STATIC_DRAW);

    /* Creates normal VBO */
    float* normal_array = to_array<3, float, Vec3f>(mesh.normal());
    glGenBuffers (1, &_n_vbo);
    glBindBuffer (GL_ARRAY_BUFFER, _n_vbo);
    glBufferData (GL_ARRAY_BUFFER, mesh.normal().size() * sizeof(float) * 3, 
            normal_array, GL_STATIC_DRAW);
 
    /* Creates texture UV VBO */
    float* tex_uv_array = to_array<2, float, Vec2f>(mesh.tex_uv());
    glGenBuffers (1, &_t_vbo);
    glBindBuffer (GL_ARRAY_BUFFER, _t_vbo);
    glBufferData (GL_ARRAY_BUFFER, mesh.tex_uv().size() * sizeof(float) * 2, 
            tex_uv_array, GL_STATIC_DRAW);
}

////////////////////////////////////////////////////////////////////////////////////////

template <typename T>
void MeshGL<T>::load_index_buffer(Mesh<T>& mesh)
{
    /* Generates Vertex and Normal Index VBO */
    uint* vertex_index = mesh.triangle_to_vertex_index_array();
    _i_vbo_size = mesh.triangle().size() * 3;
    glGenBuffers (1, &_i_vbo);
    glBindBuffer (GL_ELEMENT_ARRAY_BUFFER, _i_vbo);
    glBufferData (GL_ELEMENT_ARRAY_BUFFER, _i_vbo_size * sizeof(uint), vertex_index, 
            GL_STATIC_DRAW);
}

////////////////////////////////////////////////////////////////////////////////////////

template <typename T>
void MeshGL<T>::load_vao(Mesh<T>& mesh)
{
    /* Generate VAO */
    glGenVertexArrays (1, &_vao);
    glBindVertexArray (_vao);
    // Set VERTEX VBO to position 0 of VAO
    glBindBuffer (GL_ARRAY_BUFFER, _v_vbo);
    glVertexAttribPointer (VERTEX, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    // Set NORMAL VBO to position 1 of VAO
    glBindBuffer (GL_ARRAY_BUFFER, _n_vbo);
    glVertexAttribPointer (NORMAL, 3, GL_FLOAT, GL_FALSE, 0, NULL);
     // Set TEXTURE VBO to position 2 of VAO
    glBindBuffer (GL_ARRAY_BUFFER, _t_vbo);
    glVertexAttribPointer (TEX_UV, 2, GL_FLOAT, GL_FALSE, 0, NULL);

    glEnableVertexAttribArray (VERTEX);
    glEnableVertexAttribArray (NORMAL);
    glEnableVertexAttribArray (TEX_UV);

}

////////////////////////////////////////////////////////////////////////////////////////

template <typename T>
void MeshGL<T>::load_textures(Mesh<T>& mesh)
{

}

////////////////////////////////////////////////////////////////////////////////////////

template <typename T>
void MeshGL<T>::load_fbos(Mesh<T>& mesh)
{
}

////////////////////////////////////////////////////////////////////////////////////////

