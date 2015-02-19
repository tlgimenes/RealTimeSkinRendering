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
                
                template <typename T>
                GLuint new_vbo(std::vector<T>& data);

                GLuint new_index(std::vector<int>& faces);

                GLuint new_vao();

            public:
                mesh(const std::shared_ptr<std::vector<glm::vec3>>& vertex,
                     const std::shared_ptr<std::vector<glm::vec3>>& normal,
                     const std::shared_ptr<std::vector<glm::vec2>>& tex_uv,
                     const std::shared_ptr<std::vector<int>>& faces);
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

inline sgl::device::mesh::mesh(const std::shared_ptr<std::vector<glm::vec3>>& vertex,
                        const std::shared_ptr<std::vector<glm::vec3>>& normal,
                        const std::shared_ptr<std::vector<glm::vec2>>& tex_uv,
                        const std::shared_ptr<std::vector<int>>& faces) :
    _vertex(0),
    _normal(0),
    _tex_uv(0),
    _faces(0),
    _vao(0)
{
    _vertex = new_vbo<glm::vec3>(*vertex);
    _normal = new_vbo<glm::vec3>(*normal);
    _tex_uv = new_vbo<glm::vec2>(*tex_uv);

    _faces  = new_index(*faces);
    _faces_count = faces->size();

    _vao = new_vao();
}

////////////////////////////////////////////////////////////////////////////////////////

inline sgl::device::mesh::mesh(const mesh& m) :
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

template <typename T>
inline GLuint sgl::device::mesh::new_vbo(std::vector<T>& data)
{
    GLuint vbo;

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(T), data.data(), GL_STATIC_DRAW);

    gl_check_for_errors();

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    return vbo;
}

////////////////////////////////////////////////////////////////////////////////////////

inline GLuint sgl::device::mesh::new_index(std::vector<int>& faces)
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

inline GLuint sgl::device::mesh::new_vao()
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

