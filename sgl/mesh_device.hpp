/*
 * =====================================================================================
 *       Filename:  mesh_device.hpp
 *    Description:  
 *        Created:  2015-02-16 18:40
 *         Author:  Tiago Lobato Gimenes        (tlgimenes@gmail.com)
 * =====================================================================================
 */

////////////////////////////////////////////////////////////////////////////////////////

#ifndef MESH_DEVICE_HPP
#define MESH_DEVICE_HPP

////////////////////////////////////////////////////////////////////////////////////////

#include <memory>
#include <vector>
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>

#include "error.hpp"

////////////////////////////////////////////////////////////////////////////////////////

namespace sgl
{
    namespace device
    {
        enum mesh_t {
            VERTEX,
            NORMAL,
            TEX_UV
        };

        class mesh 
        {
            private:
                GLuint _vertex; // vertex
                GLuint _normal; // normals
                GLuint _tex_uv; // textures uv

                GLuint _faces;  // index buffer

                GLuint _vao;    // vao 

                int _faces_count; // Number of elements in the index buffer

            protected:
                
                GLuint new_vbo(std::vector<float>& data);

                GLuint new_index(std::vector<int>& faces);

                GLuint new_vao();

            public:
                mesh(std::shared_ptr<std::vector<glm::vec3>> vertex,
                     std::shared_ptr<std::vector<glm::vec3>> normal,
                     std::shared_ptr<std::vector<glm::vec2>> tex_uv,
                     std::shared_ptr<std::vector<int>> faces);
                mesh(const mesh& m);

                /**
                 * Binds VAO  
                 * */
                inline void bind() {
                    glBindVertexArray (_vao); gl_check_for_errors();
                    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _faces); gl_check_for_errors();
                }

                /**
                 * Unbinds VAO 
                 * */
                inline void unbind() {
                    glBindVertexArray (0); gl_check_for_errors();
                    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); gl_check_for_errors();
                }

                /**
                 * Gets
                 * */
                inline GLuint vertex() const {return _vertex;}  // vertex
                inline GLuint normal() const {return _normal;}  // normals
                inline GLuint tex_uv() const {return _tex_uv;}  // textures uv

                inline GLuint faces() const {return _faces;}  // index buffer

                inline GLuint index_count() const {return _faces_count;} // 3 * faces->size()

                inline GLuint vao() const {return _vao;}    // vao 
        };
    }
}

////////////////////////////////////////////////////////////////////////////////////////

sgl::device::mesh::mesh(std::shared_ptr<std::vector<glm::vec3>> vertex,
                        std::shared_ptr<std::vector<glm::vec3>> normal,
                        std::shared_ptr<std::vector<glm::vec2>> tex_uv,
                        std::shared_ptr<std::vector<int>> faces) :
    _vertex(0),
    _normal(0),
    _tex_uv(0),
    _faces(0),
    _vao(0)
{
    std::vector<float> vertex_array(vertex->size() * 3);
    std::vector<float> normal_array(normal->size() * 3);
    std::vector<float> tex_uv_array(tex_uv->size() * 2);

    for(int i=0; i < vertex->size(); i++)
    {
        vertex_array[3*i  ] = vertex->at(i)[0];
        vertex_array[3*i+1] = vertex->at(i)[1];
        vertex_array[3*i+2] = vertex->at(i)[2];

        normal_array[3*i  ] = normal->at(i)[0];
        normal_array[3*i+1] = normal->at(i)[1];
        normal_array[3*i+2] = normal->at(i)[2];

        tex_uv_array[2*i  ] = tex_uv->at(i)[0];
        tex_uv_array[2*i+1] = tex_uv->at(i)[1];
    }

    _vertex = new_vbo(vertex_array);
    _normal = new_vbo(normal_array);
    _tex_uv = new_vbo(tex_uv_array);

    _faces  = new_index(*faces);
    _faces_count = faces->size();

    _vao = new_vao();
}

////////////////////////////////////////////////////////////////////////////////////////

sgl::device::mesh::mesh(const mesh& m) :
    _vertex(m.vertex()),
    _normal(m.normal()),
    _tex_uv(m.tex_uv()),
    _faces(m.faces()),
    _vao(m.vao()),
    _faces_count(m.index_count())
{
    /* Nothing to do here */
}

////////////////////////////////////////////////////////////////////////////////////////

GLuint sgl::device::mesh::new_vbo(std::vector<float>& data)
{
    GLuint vbo;

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float), data.data(), GL_STATIC_DRAW);

    gl_check_for_errors();

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    return vbo;
}

////////////////////////////////////////////////////////////////////////////////////////

GLuint sgl::device::mesh::new_index(std::vector<int>& faces)
{
    GLuint index;

    glGenBuffers(1, &index);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, faces.size() * sizeof(int), faces.data(), GL_STATIC_DRAW);

    gl_check_for_errors();
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    
    return index;
}

////////////////////////////////////////////////////////////////////////////////////////

GLuint sgl::device::mesh::new_vao()
{
    GLuint vao;

    /* Generate VAO */
    glGenVertexArrays (1, &vao);
    glBindVertexArray (vao);

    // Set VERTEX VBO to position 0 of VAO
    glBindBuffer (GL_ARRAY_BUFFER, _vertex);
    glVertexAttribPointer (VERTEX, 3, GL_FLOAT, GL_FALSE, 0, NULL);

    // Set NORMAL VBO to position 1 of VAO
    glBindBuffer (GL_ARRAY_BUFFER, _normal);
    glVertexAttribPointer (NORMAL, 3, GL_FLOAT, GL_FALSE, 0, NULL);

     // Set TEXTURE VBO to position 2 of VAO
    glBindBuffer (GL_ARRAY_BUFFER, _tex_uv);
    glVertexAttribPointer (TEX_UV, 2, GL_FLOAT, GL_FALSE, 0, NULL);

    glEnableVertexAttribArray (VERTEX);
    glEnableVertexAttribArray (NORMAL);
    glEnableVertexAttribArray (TEX_UV);

    gl_check_for_errors();

    glBindVertexArray (0);

    return vao;
}

////////////////////////////////////////////////////////////////////////////////////////

#endif /* !MESH_DEVICE_HPP */

////////////////////////////////////////////////////////////////////////////////////////

