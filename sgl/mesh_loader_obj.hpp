/*
 * =====================================================================================
 *       Filename:  mesh_loader_obj.hpp
 *    Description:  
 *        Created:  2015-02-16 22:03
 *         Author:  Tiago Lobato Gimenes        (tlgimenes@gmail.com)
 * =====================================================================================
 */

////////////////////////////////////////////////////////////////////////////////////////

#ifndef MESH_LOADER_OBJ_HPP
#define MESH_LOADER_OBJ_HPP

////////////////////////////////////////////////////////////////////////////////////////

#include <memory>
#include <vector>
#include <obj.hpp>
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>

#include "mesh_host.hpp"
#include "error.hpp"

////////////////////////////////////////////////////////////////////////////////////////

namespace sgl
{
    class mesh_loader_obj 
    {
        public:
            /**
             * Load obj file 
             * @arg0: file path 
             * @returns: vector of meshes - each mesh correspond to a different
             * group in the obj Filename
             * */
            static std::vector<std::shared_ptr<sgl::host::mesh>>& load(const std::string& path);

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

            static void info_cb(size_t, const std::string& );

            static void comment_cb(const std::string&);

            static void object_name_cb(const std::string&);

            static void material_library_cb(const std::string&);

            static void material_name_cb(const std::string&);

            static void warning_cb(std::size_t, const std::string&);

            static void error_cb(std::size_t, const std::string&);

            
            static std::vector<std::shared_ptr<sgl::host::mesh>>* _mesh_vec;

            static std::shared_ptr<std::vector<glm::vec3>> _vertex;
            static std::shared_ptr<std::vector<glm::vec3>> _normal;
            static std::shared_ptr<std::vector<glm::vec2>> _tex_uv;

            static std::shared_ptr<std::vector<std::pair<int, int>>> _index;
    };
}

////////////////////////////////////////////////////////////////////////////////////////

std::vector<std::shared_ptr<sgl::host::mesh>>* sgl::mesh_loader_obj::_mesh_vec = NULL;
            
std::shared_ptr<std::vector<glm::vec3>> sgl::mesh_loader_obj::_vertex;

std::shared_ptr<std::vector<glm::vec3>> sgl::mesh_loader_obj::_normal;
std::shared_ptr<std::vector<glm::vec2>> sgl::mesh_loader_obj::_tex_uv;

std::shared_ptr<std::vector<std::pair<int, int>>> sgl::mesh_loader_obj::_index;

////////////////////////////////////////////////////////////////////////////////////////

template <typename B>
std::pair<std::shared_ptr<std::vector<B>>, std::shared_ptr<std::vector<int>>> merge_indices( 
        std::shared_ptr<std::vector<B>>& change, 
        std::shared_ptr<std::vector<std::pair<int, int>>>& index)
{
    std::shared_ptr<std::vector<B>> new_change = std::make_shared<std::vector<B>>
        (std::vector<B>(sgl::mesh_loader_obj::_vertex->size()));

    std::shared_ptr<std::vector<int>> new_index = std::make_shared<std::vector<int>>
        (std::vector<int>(index->size()));

    for(int i=0; i < index->size(); i++)
    {
        new_change->at(index->at(i).first) = change->at(index->at(i).second);
        new_index->at(i) = index->at(i).first;
    }

    return std::pair<std::shared_ptr<std::vector<B>>, std::shared_ptr<std::vector<int>>>
        (new_change, new_index);
}

////////////////////////////////////////////////////////////////////////////////////////

std::vector<std::shared_ptr<sgl::host::mesh>>& sgl::mesh_loader_obj::load(const std::string& path)
{
    obj::obj_parser parser(obj::obj_parser::triangulate_faces);

    // Sets vector of meshes
    sgl::mesh_loader_obj::_mesh_vec = new std::vector<std::shared_ptr<sgl::host::mesh>>();
    sgl::mesh_loader_obj::_vertex = std::make_shared<std::vector<glm::vec3>>(std::vector<glm::vec3>());
    sgl::mesh_loader_obj::_normal = std::make_shared<std::vector<glm::vec3>>(std::vector<glm::vec3>());
    sgl::mesh_loader_obj::_tex_uv = std::make_shared<std::vector<glm::vec2>>(std::vector<glm::vec2>());

    sgl::mesh_loader_obj::_index = std::make_shared<std::vector<std::pair<int, int>>>(std::vector<std::pair<int, int>>());

    // Connect callbacks
    parser.geometric_vertex_callback(&sgl::mesh_loader_obj::geometric_vertex_cb);
    parser.texture_vertex_callback(&sgl::mesh_loader_obj::texture_vertex_cb);
    parser.vertex_normal_callback(&sgl::mesh_loader_obj::vertex_normal_cb);
    parser.face_callbacks(
            &sgl::mesh_loader_obj::triangular_face_geometric_vertices_cb,
            &sgl::mesh_loader_obj::triangular_face_geometric_vertices_texture_vertices_cb,
            &sgl::mesh_loader_obj::triangular_face_geometric_vertices_vertex_normals_cb,
            &sgl::mesh_loader_obj::triangular_face_geometric_vertices_texture_vertices_vertex_normals_cb,
            &sgl::mesh_loader_obj::quadrilateral_face_geometric_vertices_cb,
            &sgl::mesh_loader_obj::quadrilateral_face_geometric_vertices_texture_vertices_cb,
            &sgl::mesh_loader_obj::quadrilateral_face_geometric_vertices_vertex_normals_cb,
            &sgl::mesh_loader_obj::quadrilateral_face_geometric_vertices_texture_vertices_vertex_normals_cb,
            &sgl::mesh_loader_obj::polygonal_face_geometric_vertices_begin_cb,
            &sgl::mesh_loader_obj::polygonal_face_geometric_vertices_vertex_cb,
            &sgl::mesh_loader_obj::polygonal_face_geometric_vertices_end_cb,
            &sgl::mesh_loader_obj::polygonal_face_geometric_vertices_texture_vertices_begin_cb,
            &sgl::mesh_loader_obj::polygonal_face_geometric_vertices_texture_vertices_vertex_cb,
            &sgl::mesh_loader_obj::polygonal_face_geometric_vertices_texture_vertices_end_cb,
            &sgl::mesh_loader_obj::polygonal_face_geometric_vertices_vertex_normals_begin_cb,
            &sgl::mesh_loader_obj::polygonal_face_geometric_vertices_vertex_normals_vertex_cb,
            &sgl::mesh_loader_obj::polygonal_face_geometric_vertices_vertex_normals_end_cb,
            &sgl::mesh_loader_obj::polygonal_face_geometric_vertices_texture_vertices_vertex_normals_begin_cb,
            &sgl::mesh_loader_obj::polygonal_face_geometric_vertices_texture_vertices_vertex_normals_vertex_cb,
            &sgl::mesh_loader_obj::polygonal_face_geometric_vertices_texture_vertices_vertex_normals_end_cb);
    parser.group_name_callback(&sgl::mesh_loader_obj::group_name_cb);
    parser.info_callback(&sgl::mesh_loader_obj::info_cb);
    parser.comment_callback(&sgl::mesh_loader_obj::comment_cb);
    parser.object_name_callback(&sgl::mesh_loader_obj::object_name_cb);
    parser.material_library_callback(&sgl::mesh_loader_obj::material_library_cb);
    parser.material_name_callback(&sgl::mesh_loader_obj::material_name_cb);
    parser.warning_callback(&sgl::mesh_loader_obj::warning_cb);
    parser.error_callback(&sgl::mesh_loader_obj::error_cb);

    // Parse file
    parser.parse(path);

    std::pair<std::shared_ptr<std::vector<glm::vec2>>, std::shared_ptr<std::vector<int>>>
        res = merge_indices<glm::vec2>(sgl::mesh_loader_obj::_tex_uv, 
                sgl::mesh_loader_obj::_index);

    sgl::mesh_loader_obj::_mesh_vec->push_back(std::make_shared<sgl::host::mesh>(
                sgl::host::mesh(
                sgl::mesh_loader_obj::_vertex, 
                sgl::mesh_loader_obj::_normal, 
                res.first, 
                res.second)));

    for(int i=0; i < _mesh_vec->size(); i++)
    {
        _mesh_vec->at(i)->center();
        _mesh_vec->at(i)->scale_to_unit();
        _mesh_vec->at(i)->recompute_normals();
    }

    return *_mesh_vec;
}

////////////////////////////////////////////////////////////////////////////////////////

void sgl::mesh_loader_obj::geometric_vertex_cb(const obj::float_type& x, const obj::float_type& y, 
        const obj::float_type& z)
{
    sgl::mesh_loader_obj::_vertex->push_back(glm::vec3(x,y,z));
}

////////////////////////////////////////////////////////////////////////////////////////

void sgl::mesh_loader_obj::vertex_normal_cb(const obj::float_type& x, const obj::float_type& y, 
        const obj::float_type& z)
{
    sgl::mesh_loader_obj::_normal->push_back(glm::vec3(x,y,z));
}

////////////////////////////////////////////////////////////////////////////////////////

void sgl::mesh_loader_obj::texture_vertex_cb(const obj::float_type& u, const obj::float_type& v)
{
    sgl::mesh_loader_obj::_tex_uv->push_back(glm::vec2(u,v));
}

////////////////////////////////////////////////////////////////////////////////////////

void sgl::mesh_loader_obj::triangular_face_geometric_vertices_cb(obj::index_type, 
        obj::index_type, obj::index_type)
{
    fatal_error("Function not implemented");
}

////////////////////////////////////////////////////////////////////////////////////////

void sgl::mesh_loader_obj::triangular_face_geometric_vertices_texture_vertices_cb(
        const obj::index_2_tuple_type& v0, const obj::index_2_tuple_type& v1, 
        const obj::index_2_tuple_type& v2)
{
    sgl::mesh_loader_obj::_index->push_back(std::make_pair<int, int>(std::tr1::get<0>(v0)-1, std::tr1::get<1>(v0)-1));
    sgl::mesh_loader_obj::_index->push_back(std::make_pair<int, int>(std::tr1::get<0>(v1)-1, std::tr1::get<1>(v1)-1));
    sgl::mesh_loader_obj::_index->push_back(std::make_pair<int, int>(std::tr1::get<0>(v2)-1, std::tr1::get<1>(v2)-1));
}

////////////////////////////////////////////////////////////////////////////////////////

void sgl::mesh_loader_obj::triangular_face_geometric_vertices_vertex_normals_cb(
        const obj::index_2_tuple_type&, const obj::index_2_tuple_type&, 
        const obj::index_2_tuple_type&)
{
    fatal_error("Function not implemented");
}

////////////////////////////////////////////////////////////////////////////////////////

void sgl::mesh_loader_obj::triangular_face_geometric_vertices_texture_vertices_vertex_normals_cb(
        const obj::index_3_tuple_type&, const obj::index_3_tuple_type&, 
        const obj::index_3_tuple_type&)
{
    fatal_error("Function not implemented");
}

////////////////////////////////////////////////////////////////////////////////////////
 
void sgl::mesh_loader_obj::quadrilateral_face_geometric_vertices_cb(
        obj::index_type, obj::index_type, obj::index_type, obj::index_type)
{
    fatal_error("Function not implemented");
}

////////////////////////////////////////////////////////////////////////////////////////
 
void sgl::mesh_loader_obj::quadrilateral_face_geometric_vertices_texture_vertices_cb(
        const obj::index_2_tuple_type& v0, const obj::index_2_tuple_type& v1, 
        const obj::index_2_tuple_type& v2, const obj::index_2_tuple_type& v3)
{
    fatal_error("Function not implemented");
}

////////////////////////////////////////////////////////////////////////////////////////

void sgl::mesh_loader_obj::quadrilateral_face_geometric_vertices_vertex_normals_cb(
        const obj::index_2_tuple_type&, const obj::index_2_tuple_type&, 
        const obj::index_2_tuple_type&, const obj::index_2_tuple_type&)
{
    fatal_error("Function not implemented");
}

////////////////////////////////////////////////////////////////////////////////////////

void sgl::mesh_loader_obj::quadrilateral_face_geometric_vertices_texture_vertices_vertex_normals_cb(
        const obj::index_3_tuple_type&, const obj::index_3_tuple_type&, 
        const obj::index_3_tuple_type&, const obj::index_3_tuple_type&)
{
    fatal_error("Function not implemented");
}

////////////////////////////////////////////////////////////////////////////////////////

void sgl::mesh_loader_obj::polygonal_face_geometric_vertices_begin_cb(
        obj::index_type, obj::index_type, obj::index_type)
{
    fatal_error("Function not implemented");
}

////////////////////////////////////////////////////////////////////////////////////////
 
void sgl::mesh_loader_obj::polygonal_face_geometric_vertices_vertex_cb(obj::index_type)
{
    fatal_error("Function not implemented");
}

////////////////////////////////////////////////////////////////////////////////////////
 
void sgl::mesh_loader_obj::polygonal_face_geometric_vertices_end_cb()
{
    fatal_error("Function not implemented");
}

////////////////////////////////////////////////////////////////////////////////////////

void  sgl::mesh_loader_obj::polygonal_face_geometric_vertices_texture_vertices_begin_cb(
        const obj::index_2_tuple_type&, const obj::index_2_tuple_type&, 
        const obj::index_2_tuple_type&)
{
    fatal_error("Function not implemented");
}

////////////////////////////////////////////////////////////////////////////////////////

void sgl::mesh_loader_obj::polygonal_face_geometric_vertices_texture_vertices_vertex_cb(
        const obj::index_2_tuple_type&)
{
    fatal_error("Function not implemented");
}

////////////////////////////////////////////////////////////////////////////////////////

void sgl::mesh_loader_obj::polygonal_face_geometric_vertices_texture_vertices_end_cb()
{
    fatal_error("Function not implemented");
}

////////////////////////////////////////////////////////////////////////////////////////

void sgl::mesh_loader_obj::polygonal_face_geometric_vertices_vertex_normals_begin_cb(
        const obj::index_2_tuple_type&, const obj::index_2_tuple_type&, 
        const obj::index_2_tuple_type&)
{
    fatal_error("Function not implemented");
}

////////////////////////////////////////////////////////////////////////////////////////

void sgl::mesh_loader_obj::polygonal_face_geometric_vertices_vertex_normals_vertex_cb(
        const obj::index_2_tuple_type&)
{
    fatal_error("Function not implemented");
}

////////////////////////////////////////////////////////////////////////////////////////
 
void sgl::mesh_loader_obj::polygonal_face_geometric_vertices_vertex_normals_end_cb()
{
    fatal_error("Function not implemented");
}

////////////////////////////////////////////////////////////////////////////////////////

void sgl::mesh_loader_obj::polygonal_face_geometric_vertices_texture_vertices_vertex_normals_begin_cb(
        const obj::index_3_tuple_type&, const obj::index_3_tuple_type&, 
        const obj::index_3_tuple_type&)
{
    fatal_error("Function not implemented");
}

////////////////////////////////////////////////////////////////////////////////////////
 
void sgl::mesh_loader_obj::polygonal_face_geometric_vertices_texture_vertices_vertex_normals_vertex_cb(
        const obj::index_3_tuple_type&)
{
    fatal_error("Function not implemented");
}

////////////////////////////////////////////////////////////////////////////////////////
 
void sgl::mesh_loader_obj::polygonal_face_geometric_vertices_texture_vertices_vertex_normals_end_cb()
{
    fatal_error("Function not implemented");
}

////////////////////////////////////////////////////////////////////////////////////////

void sgl::mesh_loader_obj::group_name_cb(const std::string& name)
{
    warning_error(name + std::string(" I need of some imeplementation"));
}

////////////////////////////////////////////////////////////////////////////////////////
 
void sgl::mesh_loader_obj::info_cb(size_t a, const std::string& str)
{
    warning_error(str + std::string(" I need of some imeplementation"));
}

////////////////////////////////////////////////////////////////////////////////////////
 
void sgl::mesh_loader_obj::comment_cb(const std::string& comment)
{
    assert_warning_error(false, std::string("Comment found in file: \n") + comment);
}

////////////////////////////////////////////////////////////////////////////////////////

void sgl::mesh_loader_obj::object_name_cb(const std::string& name)
{
    warning_error(name + std::string(" I need of some imeplementation"));
}

////////////////////////////////////////////////////////////////////////////////////////
 
void sgl::mesh_loader_obj::material_library_cb(const std::string& material)
{
    warning_error(material + std::string(" I need of some imeplementation"));
}

////////////////////////////////////////////////////////////////////////////////////////
 
void sgl::mesh_loader_obj::material_name_cb(const std::string& material)
{
    warning_error(material + std::string(" I need of some imeplementation"));
}

////////////////////////////////////////////////////////////////////////////////////////

void sgl::mesh_loader_obj::error_cb(std::size_t size, const std::string& error_str)
{
    fatal_error(error_str);
}

////////////////////////////////////////////////////////////////////////////////////////

void sgl::mesh_loader_obj::warning_cb(std::size_t size, const std::string& warning_str)
{
    warning_error(warning_str);
}

////////////////////////////////////////////////////////////////////////////////////////

#endif /* !MESH_LOADER_OBJ_HPP */

////////////////////////////////////////////////////////////////////////////////////////

