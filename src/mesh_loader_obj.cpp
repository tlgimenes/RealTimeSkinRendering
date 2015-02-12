/*
 * =====================================================================================
 *       Filename:  mesh_loader_obj.cpp
 *    Description:  
 *        Created:  2015-01-29 15:28
 *         Author:  Tiago Lobato Gimenes        (tlgimenes@gmail.com)
 * =====================================================================================
 */

////////////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <tuple>

#include "mesh_loader_obj.hpp"

#include "vec3.hpp"
#include "error.hpp"

////////////////////////////////////////////////////////////////////////////////////////

Mesh* MeshLoaderObj::curr_mesh = NULL;

////////////////////////////////////////////////////////////////////////////////////////

void MeshLoaderObj::load(const std::string& filename, Mesh& mesh)
{
    obj::obj_parser parser;

    // Uploads current mesh
    MeshLoaderObj::curr_mesh = &mesh;

    // Connect callbacks
    parser.geometric_vertex_callback(&MeshLoaderObj::geometric_vertex_cb);
    parser.texture_vertex_callback(&MeshLoaderObj::texture_vertex_cb);
    parser.vertex_normal_callback(&MeshLoaderObj::vertex_normal_cb);
    parser.face_callbacks(
            &MeshLoaderObj::triangular_face_geometric_vertices_cb,
            &MeshLoaderObj::triangular_face_geometric_vertices_texture_vertices_cb,
            &MeshLoaderObj::triangular_face_geometric_vertices_vertex_normals_cb,
            &MeshLoaderObj::triangular_face_geometric_vertices_texture_vertices_vertex_normals_cb,
            &MeshLoaderObj::quadrilateral_face_geometric_vertices_cb,
            &MeshLoaderObj::quadrilateral_face_geometric_vertices_texture_vertices_cb,
            &MeshLoaderObj::quadrilateral_face_geometric_vertices_vertex_normals_cb,
            &MeshLoaderObj::quadrilateral_face_geometric_vertices_texture_vertices_vertex_normals_cb,
            &MeshLoaderObj::polygonal_face_geometric_vertices_begin_cb,
            &MeshLoaderObj::polygonal_face_geometric_vertices_vertex_cb,
            &MeshLoaderObj::polygonal_face_geometric_vertices_end_cb,
            &MeshLoaderObj::polygonal_face_geometric_vertices_texture_vertices_begin_cb,
            &MeshLoaderObj::polygonal_face_geometric_vertices_texture_vertices_vertex_cb,
            &MeshLoaderObj::polygonal_face_geometric_vertices_texture_vertices_end_cb,
            &MeshLoaderObj::polygonal_face_geometric_vertices_vertex_normals_begin_cb,
            &MeshLoaderObj::polygonal_face_geometric_vertices_vertex_normals_vertex_cb,
            &MeshLoaderObj::polygonal_face_geometric_vertices_vertex_normals_end_cb,
            &MeshLoaderObj::polygonal_face_geometric_vertices_texture_vertices_vertex_normals_begin_cb,
            &MeshLoaderObj::polygonal_face_geometric_vertices_texture_vertices_vertex_normals_vertex_cb,
            &MeshLoaderObj::polygonal_face_geometric_vertices_texture_vertices_vertex_normals_end_cb);

    parser.group_name_callback(&MeshLoaderObj::group_name_cb);

    parser.warning_callback(&MeshLoaderObj::warning_cb);
    parser.error_callback(&MeshLoaderObj::error_cb);

    // Parse file
    parser.parse(filename);

    mesh.centerAndScaleToUnit();
    mesh.recomputeNormals();
}

////////////////////////////////////////////////////////////////////////////////////////

void MeshLoaderObj::geometric_vertex_cb(const obj::float_type& x, const obj::float_type& y, 
        const obj::float_type& z)
{
    MeshLoaderObj::curr_mesh->vertex().push_back(Vec3f(x,y,z));
}

////////////////////////////////////////////////////////////////////////////////////////

void MeshLoaderObj::vertex_normal_cb(const obj::float_type& x, const obj::float_type& y, 
        const obj::float_type& z)
{
    MeshLoaderObj::curr_mesh->normal().push_back(Vec3f(x,y,z));
}

////////////////////////////////////////////////////////////////////////////////////////
void MeshLoaderObj::texture_vertex_cb(const obj::float_type& u, const obj::float_type& v)
{
    MeshLoaderObj::curr_mesh->tex_uv().push_back(Vec2f(u,v));
}

////////////////////////////////////////////////////////////////////////////////////////

void MeshLoaderObj::triangular_face_geometric_vertices_cb(obj::index_type, 
        obj::index_type, obj::index_type)
{
    FATAL_ERROR("Function not implemented");
}

////////////////////////////////////////////////////////////////////////////////////////

void MeshLoaderObj::triangular_face_geometric_vertices_texture_vertices_cb(
        const obj::index_2_tuple_type& v0, const obj::index_2_tuple_type& v1, 
        const obj::index_2_tuple_type& v2)
{
    MeshLoaderObj::curr_mesh->triangle().push_back(Triangle(
                Vec3u(std::tr1::get<0>(v0)-1, std::tr1::get<0>(v1)-1, std::tr1::get<0>(v2)-1),
                Vec3u(0,0,0),
                Vec3u(std::tr1::get<1>(v0)-1, std::tr1::get<1>(v1)-1, std::tr1::get<1>(v2)-1)));
}

////////////////////////////////////////////////////////////////////////////////////////

void MeshLoaderObj::triangular_face_geometric_vertices_vertex_normals_cb(
        const obj::index_2_tuple_type&, const obj::index_2_tuple_type&, 
        const obj::index_2_tuple_type&)
{
    FATAL_ERROR("Function not implemented");
}

////////////////////////////////////////////////////////////////////////////////////////

void MeshLoaderObj::triangular_face_geometric_vertices_texture_vertices_vertex_normals_cb(
        const obj::index_3_tuple_type&, const obj::index_3_tuple_type&, 
        const obj::index_3_tuple_type&)
{
    FATAL_ERROR("Function not implemented");
}

////////////////////////////////////////////////////////////////////////////////////////

void MeshLoaderObj::quadrilateral_face_geometric_vertices_cb(
        obj::index_type, obj::index_type, obj::index_type, obj::index_type)
{
    FATAL_ERROR("Function not implemented");
}

////////////////////////////////////////////////////////////////////////////////////////

void MeshLoaderObj::quadrilateral_face_geometric_vertices_texture_vertices_cb(
        const obj::index_2_tuple_type& v0, const obj::index_2_tuple_type& v1, 
        const obj::index_2_tuple_type& v2, const obj::index_2_tuple_type& v3)
{
    MeshLoaderObj::curr_mesh->triangle().push_back(Triangle(
                Vec3u(std::tr1::get<0>(v0)-1, std::tr1::get<0>(v1)-1, std::tr1::get<0>(v2)-1),
                Vec3u(0,0,0),
                Vec3u(std::tr1::get<1>(v0)-1, std::tr1::get<1>(v1)-1, std::tr1::get<1>(v2)-1)));

    MeshLoaderObj::curr_mesh->triangle().push_back(Triangle(
                Vec3u(std::tr1::get<0>(v2)-1, std::tr1::get<0>(v3)-1, std::tr1::get<0>(v0)-1),
                Vec3u(0,0,0),
                Vec3u(std::tr1::get<1>(v2)-1, std::tr1::get<1>(v3)-1, std::tr1::get<1>(v0)-1)));
}

////////////////////////////////////////////////////////////////////////////////////////

void MeshLoaderObj::quadrilateral_face_geometric_vertices_vertex_normals_cb(
        const obj::index_2_tuple_type&, const obj::index_2_tuple_type&, 
        const obj::index_2_tuple_type&, const obj::index_2_tuple_type&)
{
    FATAL_ERROR("Function not implemented");
}

////////////////////////////////////////////////////////////////////////////////////////

void MeshLoaderObj::quadrilateral_face_geometric_vertices_texture_vertices_vertex_normals_cb(
        const obj::index_3_tuple_type&, const obj::index_3_tuple_type&, 
        const obj::index_3_tuple_type&, const obj::index_3_tuple_type&)
{
    FATAL_ERROR("Function not implemented");
}

////////////////////////////////////////////////////////////////////////////////////////

void MeshLoaderObj::polygonal_face_geometric_vertices_begin_cb(
        obj::index_type, obj::index_type, obj::index_type)
{
    FATAL_ERROR("Function not implemented");
}

////////////////////////////////////////////////////////////////////////////////////////

void MeshLoaderObj::polygonal_face_geometric_vertices_vertex_cb(obj::index_type)
{
    FATAL_ERROR("Function not implemented");
}

////////////////////////////////////////////////////////////////////////////////////////

void MeshLoaderObj::polygonal_face_geometric_vertices_end_cb()
{
    FATAL_ERROR("Function not implemented");
}

////////////////////////////////////////////////////////////////////////////////////////

void  MeshLoaderObj::polygonal_face_geometric_vertices_texture_vertices_begin_cb(
        const obj::index_2_tuple_type&, const obj::index_2_tuple_type&, 
        const obj::index_2_tuple_type&)
{
    FATAL_ERROR("Function not implemented");
}

////////////////////////////////////////////////////////////////////////////////////////

void MeshLoaderObj::polygonal_face_geometric_vertices_texture_vertices_vertex_cb(
        const obj::index_2_tuple_type&)
{
    FATAL_ERROR("Function not implemented");
}

////////////////////////////////////////////////////////////////////////////////////////

void MeshLoaderObj::polygonal_face_geometric_vertices_texture_vertices_end_cb()
{
    FATAL_ERROR("Function not implemented");
}

////////////////////////////////////////////////////////////////////////////////////////

void MeshLoaderObj::polygonal_face_geometric_vertices_vertex_normals_begin_cb(
        const obj::index_2_tuple_type&, const obj::index_2_tuple_type&, 
        const obj::index_2_tuple_type&)
{
    FATAL_ERROR("Function not implemented");
}

////////////////////////////////////////////////////////////////////////////////////////

void MeshLoaderObj::polygonal_face_geometric_vertices_vertex_normals_vertex_cb(
        const obj::index_2_tuple_type&)
{
    FATAL_ERROR("Function not implemented");
}

////////////////////////////////////////////////////////////////////////////////////////

void MeshLoaderObj::polygonal_face_geometric_vertices_vertex_normals_end_cb()
{
    FATAL_ERROR("Function not implemented");
}

////////////////////////////////////////////////////////////////////////////////////////

void MeshLoaderObj::polygonal_face_geometric_vertices_texture_vertices_vertex_normals_begin_cb(
        const obj::index_3_tuple_type&, const obj::index_3_tuple_type&, 
        const obj::index_3_tuple_type&)
{
    FATAL_ERROR("Function not implemented");
}

////////////////////////////////////////////////////////////////////////////////////////

void MeshLoaderObj::polygonal_face_geometric_vertices_texture_vertices_vertex_normals_vertex_cb(
        const obj::index_3_tuple_type&)
{
    FATAL_ERROR("Function not implemented");
}

////////////////////////////////////////////////////////////////////////////////////////

void MeshLoaderObj::polygonal_face_geometric_vertices_texture_vertices_vertex_normals_end_cb()
{
    FATAL_ERROR("Function not implemented");
}

////////////////////////////////////////////////////////////////////////////////////////

void MeshLoaderObj::group_name_cb(const std::string& name)
{
    WARNING_ERROR(name);
}

////////////////////////////////////////////////////////////////////////////////////////

void MeshLoaderObj::error_cb(std::size_t size, const std::string& error_str)
{
    FATAL_ERROR(error_str);
}

////////////////////////////////////////////////////////////////////////////////////////

void MeshLoaderObj::warning_cb(std::size_t size, const std::string& warning_str)
{
    WARNING_ERROR(warning_str);
}

////////////////////////////////////////////////////////////////////////////////////////

