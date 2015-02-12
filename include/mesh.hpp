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

#include <string>
#include <vector>
#include <memory>

#include "triangle.hpp"
#include "texture.hpp"
#include "vec2.hpp"

////////////////////////////////////////////////////////////////////////////////////////

class Mesh {
    private:
        std::vector<Triangle> _triangles; // Vector of triangles
        std::vector<Vec2f> _tex_uv; // UV texture coordinates
        std::vector<Vec3f> _vertex_coord; // vertex coordinates
        std::vector<Vec3f> _normals;      // normals

    public:
        // Loads a mesh from a file.
        // File formats supported: .off, .obj
        //void load(const std::string& filename);

        /// Compute smooth per-vertex normals
        void recomputeNormals ();

        /// scale to the unit cube and center at original
        void centerAndScaleToUnit ();

        /**
         * Sets  
         * */
        inline std::vector<Triangle>& triangle() {return _triangles;}
        inline std::vector<Vec2f>& tex_uv() {return _tex_uv;}
        inline std::vector<Vec3f>& vertex() {return _vertex_coord;}
        inline std::vector<Vec3f>& normal() {return _normals;}

        /**
         * Gets
         * */
        inline const std::vector<Triangle>& triangle() const {return _triangles;}
        inline const std::vector<Vec2f>& tex_uv() const {return _tex_uv;}
        inline const std::vector<Vec3f>& vertex() const {return _vertex_coord;}
        inline const std::vector<Vec3f>& normal() const {return _normals;}
};

////////////////////////////////////////////////////////////////////////////////////////

#endif /* !MESH_HPP */

////////////////////////////////////////////////////////////////////////////////////////

