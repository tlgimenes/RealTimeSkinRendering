/*
 * =====================================================================================
 *       Filename:  mesh.hpp
 *    Description:  A Mesh class, storing a list of vertices and a list of triangles 
 *    indexed over it.
 *        Created:  2015-01-15 23:30
 *         Author:  Tiago Lobato Gimenes        (tlgimenes@gmail.com)
 * =====================================================================================
 */

////////////////////////////////////////////////////////////////////////////////////////

#ifndef MESH_HPP
#define MESH_HPP

////////////////////////////////////////////////////////////////////////////////////////

#include <vector>
#include <map>

#include "triangle.hpp"
#include "texture.hpp"
#include "vec2.hpp"

////////////////////////////////////////////////////////////////////////////////////////

template <typename T>
class Mesh {
    private:
        std::vector<Triangle> _triangles; // Vector of triangles
        std::vector<Vec2f> _tex_uv; // UV texture coordinates
        std::vector<Vec3f> _vertex_coord; // vertex coordinates
        std::vector<Vec3f> _normals;      // normals

        std::map<GLuint, Texture<T>*> _textures; // Map between Texture and it's GL id

    public:
        /// Compute smooth per-vertex normals
        void recomputeNormals ();

        /// scale to the unit cube and center at original
        void centerAndScaleToUnit ();

        /**
         *  Generates a vertex index array from the _triangles array 
         * */
        uint* triangle_to_vertex_index_array() const;

        /**
         * tex_uv vector isn't indexed using the same criterea as
         * the _vertex or normals vector, we need to correct it
         * */
        void correct_tex_uv();

        /**
         * Sets  
         * */
        inline std::vector<Triangle>& triangle() {return _triangles;}
        inline std::vector<Vec2f>& tex_uv() {return _tex_uv;}
        inline std::vector<Vec3f>& vertex() {return _vertex_coord;}
        inline std::vector<Vec3f>& normal() {return _normals;}
        inline std::map<GLuint, Texture<T>*>& textures() {return _textures;}

        /**
         * Gets
         * */
        inline const std::vector<Triangle>& triangle() const {return _triangles;}
        inline const std::vector<Vec2f>& tex_uv() const {return _tex_uv;}
        inline const std::vector<Vec3f>& vertex() const {return _vertex_coord;}
        inline const std::vector<Vec3f>& normal() const {return _normals;}
        inline const std::map<GLuint, Texture<T>*>& textures() const {return _textures;}
        std::vector<Texture<T>*>& texture_vec() const;
};

////////////////////////////////////////////////////////////////////////////////////////

template class Mesh<uchar>;
template class Mesh<float>;
template class Mesh<uint>;

////////////////////////////////////////////////////////////////////////////////////////

#endif /* !MESH_HPP */

////////////////////////////////////////////////////////////////////////////////////////

