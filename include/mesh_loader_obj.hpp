/*
 * =====================================================================================
 *       Filename:  mesh_loader_obj.hpp
 *    Description:  
 *        Created:  2015-01-29 15:06
 *         Author:  Tiago Lobato Gimenes        (tlgimenes@gmail.com)
 * =====================================================================================
 */

////////////////////////////////////////////////////////////////////////////////////////

#ifndef MESH_LOADER_OBJ_HPP
#define MESH_LOADER_OBJ_HPP

////////////////////////////////////////////////////////////////////////////////////////

#include <obj.hpp>
#include <functional>

#include "mesh.hpp"

////////////////////////////////////////////////////////////////////////////////////////

class MeshLoaderObj 
{
    public:
        /**
         * Loads an obj file  
         * */
        static void load(const std::string& filename, Mesh& mesh);

        /**
         * callbacks for libobj  
         * */
        static void texture_vertex_cb(const obj::float_type&, const obj::float_type&);
        
        static void geometric_vertex_cb(const obj::float_type&, const obj::float_type&, 
                const obj::float_type&);
        
        static void vertex_normal_cb(const obj::float_type&, const obj::float_type&, 
                const obj::float_type&);

        static void triangular_face_geometric_vertices_cb(obj::index_type, 
                obj::index_type, obj::index_type);

        static void triangular_face_geometric_vertices_texture_vertices_cb(
                const obj::index_2_tuple_type&, const obj::index_2_tuple_type&, 
                const obj::index_2_tuple_type&);

        static void triangular_face_geometric_vertices_vertex_normals_cb(
                const obj::index_2_tuple_type&, const obj::index_2_tuple_type&, 
                const obj::index_2_tuple_type&);

        static void triangular_face_geometric_vertices_texture_vertices_vertex_normals_cb(
                const obj::index_3_tuple_type&, const obj::index_3_tuple_type&, 
                const obj::index_3_tuple_type&);

        static void quadrilateral_face_geometric_vertices_cb(
                obj::index_type, obj::index_type, obj::index_type, obj::index_type);

        static void quadrilateral_face_geometric_vertices_texture_vertices_cb(
                const obj::index_2_tuple_type&, const obj::index_2_tuple_type&, 
                const obj::index_2_tuple_type&, const obj::index_2_tuple_type&);

        static void quadrilateral_face_geometric_vertices_vertex_normals_cb(
                const obj::index_2_tuple_type&, const obj::index_2_tuple_type&, 
                const obj::index_2_tuple_type&, const obj::index_2_tuple_type&);

        static void quadrilateral_face_geometric_vertices_texture_vertices_vertex_normals_cb(
                const obj::index_3_tuple_type&, const obj::index_3_tuple_type&, 
                const obj::index_3_tuple_type&, const obj::index_3_tuple_type&);

        static void polygonal_face_geometric_vertices_begin_cb(
                obj::index_type, obj::index_type, obj::index_type);

        static void polygonal_face_geometric_vertices_vertex_cb(obj::index_type);

        static void polygonal_face_geometric_vertices_end_cb();
        
        static void  polygonal_face_geometric_vertices_texture_vertices_begin_cb(
                const obj::index_2_tuple_type&, const obj::index_2_tuple_type&, 
                const obj::index_2_tuple_type&);

        static void polygonal_face_geometric_vertices_texture_vertices_vertex_cb(
                const obj::index_2_tuple_type&);

        static void polygonal_face_geometric_vertices_texture_vertices_end_cb();

        static void polygonal_face_geometric_vertices_vertex_normals_begin_cb(
                const obj::index_2_tuple_type&, const obj::index_2_tuple_type&, 
                const obj::index_2_tuple_type&);

        static void polygonal_face_geometric_vertices_vertex_normals_vertex_cb(
                const obj::index_2_tuple_type&);

        static void polygonal_face_geometric_vertices_vertex_normals_end_cb();

        static void polygonal_face_geometric_vertices_texture_vertices_vertex_normals_begin_cb(
                const obj::index_3_tuple_type&, const obj::index_3_tuple_type&,
                const obj::index_3_tuple_type&);
    
        static void polygonal_face_geometric_vertices_texture_vertices_vertex_normals_vertex_cb(
                const obj::index_3_tuple_type&);

        static void polygonal_face_geometric_vertices_texture_vertices_vertex_normals_end_cb();

        static void group_name_cb(const std::string&);

        static void warning_cb(std::size_t, const std::string&);

        static void error_cb(std::size_t, const std::string&);

    private:
        // Current mesh beeing loaded
        static Mesh* curr_mesh;
};

////////////////////////////////////////////////////////////////////////////////////////

#endif /* !MESH_LOADER_OBJ_HPP */

////////////////////////////////////////////////////////////////////////////////////////

