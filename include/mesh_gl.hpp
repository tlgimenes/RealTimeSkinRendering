/*
 * =====================================================================================
 *       Filename:  mesh_gl.hpp
 *    Description:  
 *        Created:  2015-02-13 16:15
 *         Author:  Tiago Lobato Gimenes        (tlgimenes@gmail.com)
 * =====================================================================================
 */

////////////////////////////////////////////////////////////////////////////////////////

#ifndef MESH_GL_HPP
#define MESH_GL_HPP

////////////////////////////////////////////////////////////////////////////////////////

#include "mesh.hpp"
#include "error.hpp"

////////////////////////////////////////////////////////////////////////////////////////

#define VERTEX 0
#define NORMAL 1
#define TEX_UV 2

////////////////////////////////////////////////////////////////////////////////////////
// Class for loading Mesh data into GPU using OpenGL's VAOs, VBOs, etc
template <typename T>
class MeshGL
{
    private:
        GLuint _vao; // VAO buffer
        
        GLuint _v_vbo; // Vertex vbo
        GLuint _n_vbo; // Normal vbo
        GLuint _t_vbo; // Texture UV VBOs

        GLuint _i_tex_vbo; // Index texture VBO
    
        GLuint _i_vbo; // Index vbo for _v_vbo and _n_vbo VBO

        size_t _i_vbo_size; // Size of _i_vbo

    protected:
        void load_vbos(Mesh<T>& mesh);
 
        void load_index_buffer(Mesh<T>& mesh);

        void load_vao(Mesh<T>& mesh);
 
        void load_textures(Mesh<T>& mesh);

    public:
        MeshGL(Mesh<T>& mesh);

        /**
         * Binds VAO  
         * */
        inline void bind() {
            glBindVertexArray (_vao); GL_CHECK_FOR_ERRORS();
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _i_vbo); GL_CHECK_FOR_ERRORS();
        }

        /**
         * Unbinds VAO 
         * */
        inline void unbind() {
            glBindVertexArray (0); GL_CHECK_FOR_ERRORS();
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); GL_CHECK_FOR_ERRORS();
        }

        /**
         * Gets
         * */
        inline size_t vertex_index_size() {return _i_vbo_size;}
};

////////////////////////////////////////////////////////////////////////////////////////

template class MeshGL<uchar>;
template class MeshGL<float>;
template class MeshGL<uint>;

////////////////////////////////////////////////////////////////////////////////////////

#endif /* !MESH_GL_HPP */

////////////////////////////////////////////////////////////////////////////////////////

