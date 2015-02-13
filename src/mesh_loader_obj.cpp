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

#include "texture_factory.hpp"
#include "vec3.hpp"
#include "error.hpp"

////////////////////////////////////////////////////////////////////////////////////////

template <typename T>
Mesh<T>* MeshLoaderObj<T>::_curr_mesh = NULL;

template <typename T>
Texture<T>* MeshLoaderObj<T>::_curr_tex = NULL;

template <typename T>
std::map<std::string, GLuint> MeshLoaderObj<T>::_map_tex_id;

////////////////////////////////////////////////////////////////////////////////////////

template <typename T>
void MeshLoaderObj<T>::load(const std::string& filename, Mesh<T>& mesh)
{
    obj::obj_parser parser;

    // Uploads current Mesh 
    MeshLoaderObj<T>::_curr_mesh = &mesh;

    // Connect callbacks
    parser.geometric_vertex_callback(&MeshLoaderObj<T>::geometric_vertex_cb);
    parser.texture_vertex_callback(&MeshLoaderObj<T>::texture_vertex_cb);
    parser.vertex_normal_callback(&MeshLoaderObj<T>::vertex_normal_cb);
    parser.face_callbacks(
            &MeshLoaderObj<T>::triangular_face_geometric_vertices_cb,
            &MeshLoaderObj<T>::triangular_face_geometric_vertices_texture_vertices_cb,
            &MeshLoaderObj<T>::triangular_face_geometric_vertices_vertex_normals_cb,
            &MeshLoaderObj<T>::triangular_face_geometric_vertices_texture_vertices_vertex_normals_cb,
            &MeshLoaderObj<T>::quadrilateral_face_geometric_vertices_cb,
            &MeshLoaderObj<T>::quadrilateral_face_geometric_vertices_texture_vertices_cb,
            &MeshLoaderObj<T>::quadrilateral_face_geometric_vertices_vertex_normals_cb,
            &MeshLoaderObj<T>::quadrilateral_face_geometric_vertices_texture_vertices_vertex_normals_cb,
            &MeshLoaderObj<T>::polygonal_face_geometric_vertices_begin_cb,
            &MeshLoaderObj<T>::polygonal_face_geometric_vertices_vertex_cb,
            &MeshLoaderObj<T>::polygonal_face_geometric_vertices_end_cb,
            &MeshLoaderObj<T>::polygonal_face_geometric_vertices_texture_vertices_begin_cb,
            &MeshLoaderObj<T>::polygonal_face_geometric_vertices_texture_vertices_vertex_cb,
            &MeshLoaderObj<T>::polygonal_face_geometric_vertices_texture_vertices_end_cb,
            &MeshLoaderObj<T>::polygonal_face_geometric_vertices_vertex_normals_begin_cb,
            &MeshLoaderObj<T>::polygonal_face_geometric_vertices_vertex_normals_vertex_cb,
            &MeshLoaderObj<T>::polygonal_face_geometric_vertices_vertex_normals_end_cb,
            &MeshLoaderObj<T>::polygonal_face_geometric_vertices_texture_vertices_vertex_normals_begin_cb,
            &MeshLoaderObj<T>::polygonal_face_geometric_vertices_texture_vertices_vertex_normals_vertex_cb,
            &MeshLoaderObj<T>::polygonal_face_geometric_vertices_texture_vertices_vertex_normals_end_cb);
    parser.group_name_callback(&MeshLoaderObj<T>::group_name_cb);
    parser.info_callback(&MeshLoaderObj<T>::info_cb);
    parser.comment_callback(&MeshLoaderObj<T>::comment_cb);
    parser.object_name_callback(&MeshLoaderObj<T>::object_name_cb);
    parser.material_library_callback(&MeshLoaderObj<T>::material_library_cb);
    parser.material_name_callback(&MeshLoaderObj<T>::material_name_cb);
    parser.warning_callback(&MeshLoaderObj<T>::warning_cb);
    parser.error_callback(&MeshLoaderObj<T>::error_cb);

    // Parse file
    parser.parse(filename);

    mesh.centerAndScaleToUnit();
    mesh.recomputeNormals();
}

////////////////////////////////////////////////////////////////////////////////////////

template <typename T>
void MeshLoaderObj<T>::geometric_vertex_cb(const obj::float_type& x, const obj::float_type& y, 
        const obj::float_type& z)
{
    MeshLoaderObj<T>::_curr_mesh->vertex().push_back(Vec3f(x,y,z));
}

////////////////////////////////////////////////////////////////////////////////////////

template <typename T>
void MeshLoaderObj<T>::vertex_normal_cb(const obj::float_type& x, const obj::float_type& y, 
        const obj::float_type& z)
{
    MeshLoaderObj<T>::_curr_mesh->normal().push_back(Vec3f(x,y,z));
}

////////////////////////////////////////////////////////////////////////////////////////

template <typename T>
void MeshLoaderObj<T>::texture_vertex_cb(const obj::float_type& u, const obj::float_type& v)
{
    MeshLoaderObj<T>::_curr_mesh->tex_uv().push_back(Vec2f(u,v));
}

////////////////////////////////////////////////////////////////////////////////////////

template <typename T>
void MeshLoaderObj<T>::triangular_face_geometric_vertices_cb(obj::index_type, 
        obj::index_type, obj::index_type)
{
    FATAL_ERROR("Function not implemented");
}

////////////////////////////////////////////////////////////////////////////////////////

template <typename T>
void MeshLoaderObj<T>::triangular_face_geometric_vertices_texture_vertices_cb(
        const obj::index_2_tuple_type& v0, const obj::index_2_tuple_type& v1, 
        const obj::index_2_tuple_type& v2)
{
    MeshLoaderObj<T>::_curr_mesh->triangle().push_back(Triangle(
                Vec3u(std::tr1::get<0>(v0)-1, std::tr1::get<0>(v1)-1, std::tr1::get<0>(v2)-1),
                Vec3u(std::tr1::get<0>(v0)-1, std::tr1::get<0>(v1)-1, std::tr1::get<0>(v2)-1),
                Vec3u(std::tr1::get<1>(v0)-1, std::tr1::get<1>(v1)-1, std::tr1::get<1>(v2)-1),
                MeshLoaderObj::_curr_tex->gl_tex_id()));
}

////////////////////////////////////////////////////////////////////////////////////////

template <typename T>
void MeshLoaderObj<T>::triangular_face_geometric_vertices_vertex_normals_cb(
        const obj::index_2_tuple_type&, const obj::index_2_tuple_type&, 
        const obj::index_2_tuple_type&)
{
    FATAL_ERROR("Function not implemented");
}

////////////////////////////////////////////////////////////////////////////////////////

template <typename T>
void MeshLoaderObj<T>::triangular_face_geometric_vertices_texture_vertices_vertex_normals_cb(
        const obj::index_3_tuple_type&, const obj::index_3_tuple_type&, 
        const obj::index_3_tuple_type&)
{
    FATAL_ERROR("Function not implemented");
}

////////////////////////////////////////////////////////////////////////////////////////

template <typename T> 
void MeshLoaderObj<T>::quadrilateral_face_geometric_vertices_cb(
        obj::index_type, obj::index_type, obj::index_type, obj::index_type)
{
    FATAL_ERROR("Function not implemented");
}

////////////////////////////////////////////////////////////////////////////////////////

template <typename T> 
void MeshLoaderObj<T>::quadrilateral_face_geometric_vertices_texture_vertices_cb(
        const obj::index_2_tuple_type& v0, const obj::index_2_tuple_type& v1, 
        const obj::index_2_tuple_type& v2, const obj::index_2_tuple_type& v3)
{
    MeshLoaderObj<T>::_curr_mesh->triangle().push_back(Triangle(
                Vec3u(std::tr1::get<0>(v0)-1, std::tr1::get<0>(v1)-1, std::tr1::get<0>(v2)-1),
                Vec3u(std::tr1::get<0>(v0)-1, std::tr1::get<0>(v1)-1, std::tr1::get<0>(v2)-1),
                Vec3u(std::tr1::get<1>(v0)-1, std::tr1::get<1>(v1)-1, std::tr1::get<1>(v2)-1),
                MeshLoaderObj::_curr_tex->gl_tex_id()));

    MeshLoaderObj<T>::_curr_mesh->triangle().push_back(Triangle(
                Vec3u(std::tr1::get<0>(v2)-1, std::tr1::get<0>(v3)-1, std::tr1::get<0>(v0)-1),
                Vec3u(std::tr1::get<0>(v2)-1, std::tr1::get<0>(v3)-1, std::tr1::get<0>(v0)-1),
                Vec3u(std::tr1::get<1>(v2)-1, std::tr1::get<1>(v3)-1, std::tr1::get<1>(v0)-1),
                MeshLoaderObj::_curr_tex->gl_tex_id()));
}

////////////////////////////////////////////////////////////////////////////////////////

template <typename T> 
void MeshLoaderObj<T>::quadrilateral_face_geometric_vertices_vertex_normals_cb(
        const obj::index_2_tuple_type&, const obj::index_2_tuple_type&, 
        const obj::index_2_tuple_type&, const obj::index_2_tuple_type&)
{
    FATAL_ERROR("Function not implemented");
}

////////////////////////////////////////////////////////////////////////////////////////

template <typename T> 
void MeshLoaderObj<T>::quadrilateral_face_geometric_vertices_texture_vertices_vertex_normals_cb(
        const obj::index_3_tuple_type&, const obj::index_3_tuple_type&, 
        const obj::index_3_tuple_type&, const obj::index_3_tuple_type&)
{
    FATAL_ERROR("Function not implemented");
}

////////////////////////////////////////////////////////////////////////////////////////

template <typename T> 
void MeshLoaderObj<T>::polygonal_face_geometric_vertices_begin_cb(
        obj::index_type, obj::index_type, obj::index_type)
{
    FATAL_ERROR("Function not implemented");
}

////////////////////////////////////////////////////////////////////////////////////////

template <typename T> 
void MeshLoaderObj<T>::polygonal_face_geometric_vertices_vertex_cb(obj::index_type)
{
    FATAL_ERROR("Function not implemented");
}

////////////////////////////////////////////////////////////////////////////////////////

template <typename T> 
void MeshLoaderObj<T>::polygonal_face_geometric_vertices_end_cb()
{
    FATAL_ERROR("Function not implemented");
}

////////////////////////////////////////////////////////////////////////////////////////

template <typename T> 
void  MeshLoaderObj<T>::polygonal_face_geometric_vertices_texture_vertices_begin_cb(
        const obj::index_2_tuple_type&, const obj::index_2_tuple_type&, 
        const obj::index_2_tuple_type&)
{
    FATAL_ERROR("Function not implemented");
}

////////////////////////////////////////////////////////////////////////////////////////

template <typename T>
void MeshLoaderObj<T>::polygonal_face_geometric_vertices_texture_vertices_vertex_cb(
        const obj::index_2_tuple_type&)
{
    FATAL_ERROR("Function not implemented");
}

////////////////////////////////////////////////////////////////////////////////////////

template <typename T>
void MeshLoaderObj<T>::polygonal_face_geometric_vertices_texture_vertices_end_cb()
{
    FATAL_ERROR("Function not implemented");
}

////////////////////////////////////////////////////////////////////////////////////////

template <typename T> 
void MeshLoaderObj<T>::polygonal_face_geometric_vertices_vertex_normals_begin_cb(
        const obj::index_2_tuple_type&, const obj::index_2_tuple_type&, 
        const obj::index_2_tuple_type&)
{
    FATAL_ERROR("Function not implemented");
}

////////////////////////////////////////////////////////////////////////////////////////

template <typename T> 
void MeshLoaderObj<T>::polygonal_face_geometric_vertices_vertex_normals_vertex_cb(
        const obj::index_2_tuple_type&)
{
    FATAL_ERROR("Function not implemented");
}

////////////////////////////////////////////////////////////////////////////////////////

template <typename T> 
void MeshLoaderObj<T>::polygonal_face_geometric_vertices_vertex_normals_end_cb()
{
    FATAL_ERROR("Function not implemented");
}

////////////////////////////////////////////////////////////////////////////////////////

template <typename T> 
void MeshLoaderObj<T>::polygonal_face_geometric_vertices_texture_vertices_vertex_normals_begin_cb(
        const obj::index_3_tuple_type&, const obj::index_3_tuple_type&, 
        const obj::index_3_tuple_type&)
{
    FATAL_ERROR("Function not implemented");
}

////////////////////////////////////////////////////////////////////////////////////////

template <typename T> 
void MeshLoaderObj<T>::polygonal_face_geometric_vertices_texture_vertices_vertex_normals_vertex_cb(
        const obj::index_3_tuple_type&)
{
    FATAL_ERROR("Function not implemented");
}

////////////////////////////////////////////////////////////////////////////////////////

template <typename T> 
void MeshLoaderObj<T>::polygonal_face_geometric_vertices_texture_vertices_vertex_normals_end_cb()
{
    FATAL_ERROR("Function not implemented");
}

////////////////////////////////////////////////////////////////////////////////////////

template <typename T> 
void MeshLoaderObj<T>::group_name_cb(const std::string& name)
{
    GLuint curr_id;

    if(MeshLoaderObj<T>::_map_tex_id.count(name) > 0)
    {
        curr_id = MeshLoaderObj<T>::_map_tex_id[name];
        MeshLoaderObj<T>::_curr_tex = MeshLoaderObj<T>::_curr_mesh->textures()[curr_id];
    }
    else {
        std::string path = std::string("../../models/blondGirl/ModelsFace_") + name +
            std::string(".jpg");
        MeshLoaderObj<T>::_curr_tex = &TextureFactory<T>::load(path);
        curr_id = MeshLoaderObj<T>::_curr_tex->gl_tex_id();
        MeshLoaderObj<T>::_map_tex_id.insert(std::pair<std::string, GLuint>(name, curr_id));
        MeshLoaderObj<T>::_curr_mesh->textures().insert(std::pair<GLuint, Texture<T>*>(curr_id, 
                    MeshLoaderObj<T>::_curr_tex));
    }
}

////////////////////////////////////////////////////////////////////////////////////////

template <typename T> 
void MeshLoaderObj<T>::info_cb(size_t a, const std::string& str)
{
    WARNING_ERROR(str + std::string(" I need of some imeplementation"));
}

////////////////////////////////////////////////////////////////////////////////////////

template <typename T> 
void MeshLoaderObj<T>::comment_cb(const std::string& comment)
{
    ASSERT_WARNING_ERROR(false, std::string("Comment found in file: \n") + comment);
}

////////////////////////////////////////////////////////////////////////////////////////

template <typename T> 
void MeshLoaderObj<T>::object_name_cb(const std::string& name)
{
    WARNING_ERROR(name + std::string(" I need of some imeplementation"));
}

////////////////////////////////////////////////////////////////////////////////////////

template <typename T> 
void MeshLoaderObj<T>::material_library_cb(const std::string& material)
{
    WARNING_ERROR(material + std::string(" I need of some imeplementation"));
}

////////////////////////////////////////////////////////////////////////////////////////

template <typename T> 
void MeshLoaderObj<T>::material_name_cb(const std::string& material)
{
    WARNING_ERROR(material + std::string(" I need of some imeplementation"));
}

////////////////////////////////////////////////////////////////////////////////////////

template <typename T> 
void MeshLoaderObj<T>::error_cb(std::size_t size, const std::string& error_str)
{
    FATAL_ERROR(error_str);
}

////////////////////////////////////////////////////////////////////////////////////////

template <typename T> 
void MeshLoaderObj<T>::warning_cb(std::size_t size, const std::string& warning_str)
{
    WARNING_ERROR(warning_str);
}

////////////////////////////////////////////////////////////////////////////////////////
