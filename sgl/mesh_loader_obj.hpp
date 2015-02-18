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
            inline static std::vector<std::shared_ptr<sgl::host::mesh>>& load(const std::string& path);

            /**
             * callbacks for libobj  
             * */
            static inline void texture_vertex_cb(const obj::float_type&, const obj::float_type&);

            static inline void geometric_vertex_cb(const obj::float_type&, const obj::float_type&, 
                    const obj::float_type&);

            static inline void vertex_normal_cb(const obj::float_type&, const obj::float_type&, 
                    const obj::float_type&);

            static inline void triangular_face_geometric_vertices_cb(obj::index_type, 
                    obj::index_type, obj::index_type);

            static inline void triangular_face_geometric_vertices_texture_vertices_cb(
                    const obj::index_2_tuple_type&, const obj::index_2_tuple_type&, 
                    const obj::index_2_tuple_type&);

            static inline void triangular_face_geometric_vertices_vertex_normals_cb(
                    const obj::index_2_tuple_type&, const obj::index_2_tuple_type&, 
                    const obj::index_2_tuple_type&);

            static inline void triangular_face_geometric_vertices_texture_vertices_vertex_normals_cb(
                    const obj::index_3_tuple_type&, const obj::index_3_tuple_type&, 
                    const obj::index_3_tuple_type&);

            static inline void quadrilateral_face_geometric_vertices_cb(
                    obj::index_type, obj::index_type, obj::index_type, obj::index_type);

            static inline void quadrilateral_face_geometric_vertices_texture_vertices_cb(
                    const obj::index_2_tuple_type&, const obj::index_2_tuple_type&, 
                    const obj::index_2_tuple_type&, const obj::index_2_tuple_type&);

            static inline void quadrilateral_face_geometric_vertices_vertex_normals_cb(
                    const obj::index_2_tuple_type&, const obj::index_2_tuple_type&, 
                    const obj::index_2_tuple_type&, const obj::index_2_tuple_type&);

            static inline void quadrilateral_face_geometric_vertices_texture_vertices_vertex_normals_cb(
                    const obj::index_3_tuple_type&, const obj::index_3_tuple_type&, 
                    const obj::index_3_tuple_type&, const obj::index_3_tuple_type&);

            static inline void polygonal_face_geometric_vertices_begin_cb(
                    obj::index_type, obj::index_type, obj::index_type);

            static inline void polygonal_face_geometric_vertices_vertex_cb(obj::index_type);

            static inline void polygonal_face_geometric_vertices_end_cb();

            static inline void  polygonal_face_geometric_vertices_texture_vertices_begin_cb(
                    const obj::index_2_tuple_type&, const obj::index_2_tuple_type&, 
                    const obj::index_2_tuple_type&);

            static inline void polygonal_face_geometric_vertices_texture_vertices_vertex_cb(
                    const obj::index_2_tuple_type&);

            static inline void polygonal_face_geometric_vertices_texture_vertices_end_cb();

            static inline void polygonal_face_geometric_vertices_vertex_normals_begin_cb(
                    const obj::index_2_tuple_type&, const obj::index_2_tuple_type&, 
                    const obj::index_2_tuple_type&);

            static inline void polygonal_face_geometric_vertices_vertex_normals_vertex_cb(
                    const obj::index_2_tuple_type&);

            static inline void polygonal_face_geometric_vertices_vertex_normals_end_cb();

            static inline void polygonal_face_geometric_vertices_texture_vertices_vertex_normals_begin_cb(
                    const obj::index_3_tuple_type&, const obj::index_3_tuple_type&,
                    const obj::index_3_tuple_type&);

            static inline void polygonal_face_geometric_vertices_texture_vertices_vertex_normals_vertex_cb(
                    const obj::index_3_tuple_type&);

            static inline void polygonal_face_geometric_vertices_texture_vertices_vertex_normals_end_cb();

            static inline void group_name_cb(const std::string&);

            static inline void info_cb(size_t, const std::string& );

            static inline void comment_cb(const std::string&);

            static inline void object_name_cb(const std::string&);

            static inline void material_library_cb(const std::string&);

            static inline void material_name_cb(const std::string&);

            static inline void warning_cb(std::size_t, const std::string&);

            static inline void error_cb(std::size_t, const std::string&);

            
            static std::shared_ptr<std::vector<glm::vec3>> _vertex;
            static std::shared_ptr<std::vector<glm::vec3>> _normal;
            static std::shared_ptr<std::vector<glm::vec2>> _tex_uv;

            static std::shared_ptr<std::vector<std::pair<int, int>>> _index;

            static std::vector<int> vertex_counter_index;
            static std::vector<int> tex_uv_counter_index;
            static std::vector<int> index_counter_index;
    };
}

////////////////////////////////////////////////////////////////////////////////////////

std::shared_ptr<std::vector<glm::vec3>> sgl::mesh_loader_obj::_vertex;

std::shared_ptr<std::vector<glm::vec3>> sgl::mesh_loader_obj::_normal;
std::shared_ptr<std::vector<glm::vec2>> sgl::mesh_loader_obj::_tex_uv;

std::shared_ptr<std::vector<std::pair<int, int>>> sgl::mesh_loader_obj::_index;

std::vector<int> sgl::mesh_loader_obj::vertex_counter_index;
std::vector<int> sgl::mesh_loader_obj::tex_uv_counter_index;
std::vector<int> sgl::mesh_loader_obj::index_counter_index;

////////////////////////////////////////////////////////////////////////////////////////

void center_mesh(std::vector<glm::vec3>& vertex)
{
    glm::vec3 c(0.0, 0.0, 0.0);
    
    for(int i=0; i < vertex.size(); i++)
        c += vertex[i];
    
    c /= vertex.size();
    for(int i=0; i < vertex.size(); i++)
        vertex[i] -= c;
}

////////////////////////////////////////////////////////////////////////////////////////

void scale_to_unit(std::vector<glm::vec3>& vertex)
{
    float maxD = glm::l2Norm(vertex[0]);
    float currD = 0;

    for(int i=0; i < vertex.size(); i++)
    {
        currD = glm::l2Norm(vertex[0]);
        if(currD > maxD)
            maxD = currD;
    }

    for(int i=0; i < vertex.size(); i++)
        vertex[i] = vertex[i] / maxD;

}

////////////////////////////////////////////////////////////////////////////////////////

template <typename B>
inline std::pair<std::shared_ptr<std::vector<B>>, std::shared_ptr<std::vector<int>>> merge_indices( 
        std::vector<B>& change, 
        std::vector<std::pair<int, int>>& index,
        int vertex_counter, int tex_uv_counter, int vertex_num)
{
    std::vector<B>* new_change = new std::vector<B>(vertex_num);

    std::vector<int>* new_index = new std::vector<int>(index.size());

    for(int i=0; i < index.size(); i++)
    {
        (*new_change)[index[i].first -vertex_counter] = change[index[i].second - tex_uv_counter];
        (*new_index)[i] = index[i].first - vertex_counter;
    }

    return std::pair<std::shared_ptr<std::vector<B>>, std::shared_ptr<std::vector<int>>>
        (std::shared_ptr<std::vector<B>>(new_change), std::shared_ptr<std::vector<int>>(new_index));
}



////////////////////////////////////////////////////////////////////////////////////////

std::vector<std::shared_ptr<sgl::host::mesh>>* spread_meshes(
        std::vector<int>& vertex_counter_index,
        std::vector<int>& tex_uv_counter_index,
        std::vector<int>& index_counter_index,
        std::shared_ptr<std::vector<glm::vec3>>& _vertex,
        std::shared_ptr<std::vector<glm::vec2>>& _tex_uv,
        std::shared_ptr<std::vector<std::pair<int, int>>>& _index)
{
    std::vector<std::shared_ptr<sgl::host::mesh>>* mesh_vec = new std::vector<std::shared_ptr<sgl::host::mesh>>();
    std::pair<std::shared_ptr<std::vector<glm::vec2>>, std::shared_ptr<std::vector<int>>> res;
    std::vector<glm::vec3> vertex;
    std::vector<glm::vec3> normal;
    std::vector<glm::vec2> tex_uv;
    std::vector<std::pair<int, int>> index;
    int zero, zero_uv, zero_id;

    for(int i=0; i < index_counter_index.size(); i++)
    {
        vertex.clear();
        tex_uv.clear();
        index.clear();

        zero = (i > 0 ? vertex_counter_index[i-1]: 0);
        zero_uv = (i > 0 ? tex_uv_counter_index[i-1]: 0);
        zero_id = (i > 0 ? index_counter_index[i-1]: 0);
        vertex.insert(vertex.begin(), _vertex->data()+zero, _vertex->data()+vertex_counter_index[i]);
        tex_uv.insert(tex_uv.begin(), _tex_uv->data()+zero_uv, _tex_uv->data()+tex_uv_counter_index[i]);
        index.insert(index.begin(), _index->data()+zero_id, _index->data()+index_counter_index[i]);
        res = merge_indices<glm::vec2>(tex_uv, index, zero, zero_uv, vertex_counter_index[i]-zero);

        mesh_vec->push_back(std::make_shared<sgl::host::mesh>(
                    std::make_shared<std::vector<glm::vec3>>(vertex), 
                    std::make_shared<std::vector<glm::vec3>>(normal), 
                    res.first, res.second));
    }

    return mesh_vec;
}

////////////////////////////////////////////////////////////////////////////////////////

inline std::vector<std::shared_ptr<sgl::host::mesh>>& sgl::mesh_loader_obj::load(const std::string& path)
{
    obj::obj_parser parser(obj::obj_parser::triangulate_faces | obj::obj_parser::translate_negative_indices);

    // Sets vector of meshes
    sgl::mesh_loader_obj::_vertex = std::make_shared<std::vector<glm::vec3>>(std::vector<glm::vec3>());
    sgl::mesh_loader_obj::_normal = std::make_shared<std::vector<glm::vec3>>(std::vector<glm::vec3>());
    sgl::mesh_loader_obj::_tex_uv = std::make_shared<std::vector<glm::vec2>>(std::vector<glm::vec2>());

    sgl::mesh_loader_obj::_index = std::make_shared<std::vector<std::pair<int, int>>>(std::vector<std::pair<int, int>>());

    sgl::mesh_loader_obj::vertex_counter_index.clear();
    sgl::mesh_loader_obj::tex_uv_counter_index.clear();
    sgl::mesh_loader_obj::index_counter_index.clear();

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

    center_mesh(*sgl::mesh_loader_obj::_vertex);
    scale_to_unit(*sgl::mesh_loader_obj::_vertex);
    std::vector<std::shared_ptr<sgl::host::mesh>> *mesh_vec = spread_meshes(
            sgl::mesh_loader_obj::vertex_counter_index, 
            sgl::mesh_loader_obj::tex_uv_counter_index,
            sgl::mesh_loader_obj::index_counter_index,
            sgl::mesh_loader_obj::_vertex,
            sgl::mesh_loader_obj::_tex_uv,
            sgl::mesh_loader_obj::_index);

    for(int i=0; i < mesh_vec->size(); i++)
    {
         mesh_vec->at(i)->recompute_normals();
    }

    return *mesh_vec;
}

////////////////////////////////////////////////////////////////////////////////////////

inline void sgl::mesh_loader_obj::geometric_vertex_cb(const obj::float_type& x, const obj::float_type& y, 
        const obj::float_type& z)
{
    sgl::mesh_loader_obj::_vertex->push_back(glm::vec3(x,y,z));
}

////////////////////////////////////////////////////////////////////////////////////////

inline void sgl::mesh_loader_obj::vertex_normal_cb(const obj::float_type& x, const obj::float_type& y, 
        const obj::float_type& z)
{
    sgl::mesh_loader_obj::_normal->push_back(glm::vec3(x,y,z));
}

////////////////////////////////////////////////////////////////////////////////////////

inline void sgl::mesh_loader_obj::texture_vertex_cb(const obj::float_type& u, const obj::float_type& v)
{
    sgl::mesh_loader_obj::_tex_uv->push_back(glm::vec2(u,v));
}

////////////////////////////////////////////////////////////////////////////////////////

inline void sgl::mesh_loader_obj::triangular_face_geometric_vertices_cb(obj::index_type, 
        obj::index_type, obj::index_type)
{
    fatal_error("Function not implemented");
}

////////////////////////////////////////////////////////////////////////////////////////

inline void sgl::mesh_loader_obj::triangular_face_geometric_vertices_texture_vertices_cb(
        const obj::index_2_tuple_type& v0, const obj::index_2_tuple_type& v1, 
        const obj::index_2_tuple_type& v2)
{
    sgl::mesh_loader_obj::_index->push_back(std::make_pair<int, int>(std::tr1::get<0>(v0)-1, std::tr1::get<1>(v0)-1));
    sgl::mesh_loader_obj::_index->push_back(std::make_pair<int, int>(std::tr1::get<0>(v1)-1, std::tr1::get<1>(v1)-1));
    sgl::mesh_loader_obj::_index->push_back(std::make_pair<int, int>(std::tr1::get<0>(v2)-1, std::tr1::get<1>(v2)-1));

//    std::cout << "added: " << std::endl;
//    std::cout << sgl::mesh_loader_obj::_index->at(sgl::mesh_loader_obj::_index->size()-3).first << ", " << sgl::mesh_loader_obj::_index->at(sgl::mesh_loader_obj::_index->size()-3).second << std::endl;
//    std::cout << sgl::mesh_loader_obj::_index->at(sgl::mesh_loader_obj::_index->size()-2).first << ", " << sgl::mesh_loader_obj::_index->at(sgl::mesh_loader_obj::_index->size()-2).second << std::endl;
//    std::cout << sgl::mesh_loader_obj::_index->at(sgl::mesh_loader_obj::_index->size()-1).first << ", " << sgl::mesh_loader_obj::_index->at(sgl::mesh_loader_obj::_index->size()-1).second << std::endl;
}

////////////////////////////////////////////////////////////////////////////////////////

inline void sgl::mesh_loader_obj::triangular_face_geometric_vertices_vertex_normals_cb(
        const obj::index_2_tuple_type&, const obj::index_2_tuple_type&, 
        const obj::index_2_tuple_type&)
{
    fatal_error("Function not implemented");
}

////////////////////////////////////////////////////////////////////////////////////////

inline void sgl::mesh_loader_obj::triangular_face_geometric_vertices_texture_vertices_vertex_normals_cb(
        const obj::index_3_tuple_type&, const obj::index_3_tuple_type&, 
        const obj::index_3_tuple_type&)
{
    fatal_error("Function not implemented");
}

////////////////////////////////////////////////////////////////////////////////////////
 
inline void sgl::mesh_loader_obj::quadrilateral_face_geometric_vertices_cb(
        obj::index_type, obj::index_type, obj::index_type, obj::index_type)
{
    fatal_error("Function not implemented");
}

////////////////////////////////////////////////////////////////////////////////////////
 
inline void sgl::mesh_loader_obj::quadrilateral_face_geometric_vertices_texture_vertices_cb(
        const obj::index_2_tuple_type& v0, const obj::index_2_tuple_type& v1, 
        const obj::index_2_tuple_type& v2, const obj::index_2_tuple_type& v3)
{
    sgl::mesh_loader_obj::_index->push_back(std::make_pair<int, int>(std::tr1::get<0>(v0)-1, std::tr1::get<1>(v0)-1));
    sgl::mesh_loader_obj::_index->push_back(std::make_pair<int, int>(std::tr1::get<0>(v1)-1, std::tr1::get<1>(v1)-1));
    sgl::mesh_loader_obj::_index->push_back(std::make_pair<int, int>(std::tr1::get<0>(v2)-1, std::tr1::get<1>(v2)-1));
 
    sgl::mesh_loader_obj::_index->push_back(std::make_pair<int, int>(std::tr1::get<0>(v2)-1, std::tr1::get<1>(v2)-1));
    sgl::mesh_loader_obj::_index->push_back(std::make_pair<int, int>(std::tr1::get<0>(v3)-1, std::tr1::get<1>(v3)-1));
    sgl::mesh_loader_obj::_index->push_back(std::make_pair<int, int>(std::tr1::get<0>(v0)-1, std::tr1::get<1>(v0)-1));
}

////////////////////////////////////////////////////////////////////////////////////////

inline void sgl::mesh_loader_obj::quadrilateral_face_geometric_vertices_vertex_normals_cb(
        const obj::index_2_tuple_type&, const obj::index_2_tuple_type&, 
        const obj::index_2_tuple_type&, const obj::index_2_tuple_type&)
{
    fatal_error("Function not implemented");
}

////////////////////////////////////////////////////////////////////////////////////////

inline void sgl::mesh_loader_obj::quadrilateral_face_geometric_vertices_texture_vertices_vertex_normals_cb(
        const obj::index_3_tuple_type&, const obj::index_3_tuple_type&, 
        const obj::index_3_tuple_type&, const obj::index_3_tuple_type&)
{
    fatal_error("Function not implemented");
}

////////////////////////////////////////////////////////////////////////////////////////

inline void sgl::mesh_loader_obj::polygonal_face_geometric_vertices_begin_cb(
        obj::index_type, obj::index_type, obj::index_type)
{
    fatal_error("Function not implemented");
}

////////////////////////////////////////////////////////////////////////////////////////
 
inline void sgl::mesh_loader_obj::polygonal_face_geometric_vertices_vertex_cb(obj::index_type)
{
    fatal_error("Function not implemented");
}

////////////////////////////////////////////////////////////////////////////////////////
 
inline void sgl::mesh_loader_obj::polygonal_face_geometric_vertices_end_cb()
{
    fatal_error("Function not implemented");
}

////////////////////////////////////////////////////////////////////////////////////////

inline void  sgl::mesh_loader_obj::polygonal_face_geometric_vertices_texture_vertices_begin_cb(
        const obj::index_2_tuple_type&, const obj::index_2_tuple_type&, 
        const obj::index_2_tuple_type&)
{
    fatal_error("Function not implemented");
}

////////////////////////////////////////////////////////////////////////////////////////

inline void sgl::mesh_loader_obj::polygonal_face_geometric_vertices_texture_vertices_vertex_cb(
        const obj::index_2_tuple_type&)
{
    fatal_error("Function not implemented");
}

////////////////////////////////////////////////////////////////////////////////////////

inline void sgl::mesh_loader_obj::polygonal_face_geometric_vertices_texture_vertices_end_cb()
{
    fatal_error("Function not implemented");
}

////////////////////////////////////////////////////////////////////////////////////////

inline void sgl::mesh_loader_obj::polygonal_face_geometric_vertices_vertex_normals_begin_cb(
        const obj::index_2_tuple_type&, const obj::index_2_tuple_type&, 
        const obj::index_2_tuple_type&)
{
    fatal_error("Function not implemented");
}

////////////////////////////////////////////////////////////////////////////////////////

inline void sgl::mesh_loader_obj::polygonal_face_geometric_vertices_vertex_normals_vertex_cb(
        const obj::index_2_tuple_type&)
{
    fatal_error("Function not implemented");
}

////////////////////////////////////////////////////////////////////////////////////////
 
inline void sgl::mesh_loader_obj::polygonal_face_geometric_vertices_vertex_normals_end_cb()
{
    fatal_error("Function not implemented");
}

////////////////////////////////////////////////////////////////////////////////////////

inline void sgl::mesh_loader_obj::polygonal_face_geometric_vertices_texture_vertices_vertex_normals_begin_cb(
        const obj::index_3_tuple_type&, const obj::index_3_tuple_type&, 
        const obj::index_3_tuple_type&)
{
    fatal_error("Function not implemented");
}

////////////////////////////////////////////////////////////////////////////////////////
 
inline void sgl::mesh_loader_obj::polygonal_face_geometric_vertices_texture_vertices_vertex_normals_vertex_cb(
        const obj::index_3_tuple_type&)
{
    fatal_error("Function not implemented");
}

////////////////////////////////////////////////////////////////////////////////////////
 
inline void sgl::mesh_loader_obj::polygonal_face_geometric_vertices_texture_vertices_vertex_normals_end_cb()
{
    fatal_error("Function not implemented");
}

////////////////////////////////////////////////////////////////////////////////////////

inline void sgl::mesh_loader_obj::group_name_cb(const std::string& name)
{
    int aux1 = 0, aux2 = 0, aux3 = 0;
 
    if(sgl::mesh_loader_obj::_vertex->size() > 0)
    {
        sgl::mesh_loader_obj::vertex_counter_index.push_back(sgl::mesh_loader_obj::_vertex->size());
        sgl::mesh_loader_obj::tex_uv_counter_index.push_back(sgl::mesh_loader_obj::_tex_uv->size());
        sgl::mesh_loader_obj::index_counter_index .push_back(sgl::mesh_loader_obj::_index->size() );
    }
}

////////////////////////////////////////////////////////////////////////////////////////
 
inline void sgl::mesh_loader_obj::info_cb(size_t a, const std::string& str)
{
    warning_error(str + std::string(" I need of some imeplementation"));
}

////////////////////////////////////////////////////////////////////////////////////////
 
inline void sgl::mesh_loader_obj::comment_cb(const std::string& comment)
{
    warning_error(std::string("Comment found in file: \n") + comment);
}

////////////////////////////////////////////////////////////////////////////////////////

inline void sgl::mesh_loader_obj::object_name_cb(const std::string& name)
{
    warning_error(name + std::string(" I need of some imeplementation"));
}

////////////////////////////////////////////////////////////////////////////////////////
 
inline void sgl::mesh_loader_obj::material_library_cb(const std::string& material)
{
    warning_error(material + std::string(" I need of some imeplementation"));
}

////////////////////////////////////////////////////////////////////////////////////////
 
inline void sgl::mesh_loader_obj::material_name_cb(const std::string& material)
{
    warning_error(material + std::string(" I need of some imeplementation"));
}

////////////////////////////////////////////////////////////////////////////////////////

inline void sgl::mesh_loader_obj::error_cb(std::size_t size, const std::string& error_str)
{
    fatal_error(error_str);
}

////////////////////////////////////////////////////////////////////////////////////////

inline void sgl::mesh_loader_obj::warning_cb(std::size_t size, const std::string& warning_str)
{
    warning_error(warning_str);
}

////////////////////////////////////////////////////////////////////////////////////////

#endif /* !MESH_LOADER_OBJ_HPP */

////////////////////////////////////////////////////////////////////////////////////////

