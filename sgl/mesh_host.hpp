/*
 * =====================================================================================
 *       Filename:  mesh_host.hpp
 *    Description:  
 *        Created:  2015-02-16 15:05
 *         Author:  Tiago Lobato Gimenes        (tlgimenes@gmail.com)
 * =====================================================================================
 */

////////////////////////////////////////////////////////////////////////////////////////

#ifndef MESH_HPP
#define MESH_HPP

////////////////////////////////////////////////////////////////////////////////////////

#include <memory>
#include <vector>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/geometric.hpp>
#include <glm/gtx/norm.hpp>

#include "mesh_device.hpp"

////////////////////////////////////////////////////////////////////////////////////////

namespace sgl
{
    namespace host
    {
        class mesh 
        {
            private:
                std::shared_ptr<std::vector<glm::vec3>> _vertex; // Vertex coordinates
                std::shared_ptr<std::vector<glm::vec3>> _normal; // Normal coordinates
                std::shared_ptr<std::vector<glm::vec2>> _tex_uv; // Texture UV coordinates
                std::shared_ptr<std::vector<int>> _faces; // Indice vector, each three indices define a triangle

            public:
                inline mesh(std::shared_ptr<std::vector<glm::vec3>> vertex, 
                        std::shared_ptr<std::vector<glm::vec3>> normal,
                        std::shared_ptr<std::vector<glm::vec2>> tex_uv, 
                        std::shared_ptr<std::vector<int>> faces) :
                    _vertex(vertex), _normal(normal), _tex_uv(tex_uv), _faces(faces) {}

                /**
                 * Loads mesh in host to device 
                 * */
                inline std::shared_ptr<sgl::device::mesh> to_device();

                /**
                 * Recompute normals. One normal per vertex
                 * */
                void recompute_normals();

                /**
                 * Center vertex to origin
                 * */
                inline void center();

                /**
                 * Scale mesh to unit
                 * */
                inline void scale_to_unit();

                /**
                 * Gets
                 * */
                inline const std::shared_ptr<std::vector<glm::vec3>>& vertex() const {return _vertex;}
                inline const std::shared_ptr<std::vector<glm::vec3>>& normal() const {return _normal;}
                inline const std::shared_ptr<std::vector<glm::vec2>>& tex_uv() const {return _tex_uv;}
                inline const std::shared_ptr<std::vector<int>>&       faces()  const {return _faces;}

                /**
                 * Sets
                 * */
                inline std::shared_ptr<std::vector<glm::vec3>>& vertex() {return _vertex;}
                inline std::shared_ptr<std::vector<glm::vec3>>& normal() {return _normal;}
                inline std::shared_ptr<std::vector<glm::vec2>>& tex_uv() {return _tex_uv;}
                inline std::shared_ptr<std::vector<int>>&       faces()  {return _faces;}
        };
    }
}

////////////////////////////////////////////////////////////////////////////////////////

inline std::shared_ptr<sgl::device::mesh> sgl::host::mesh::to_device()
{
    return std::shared_ptr<sgl::device::mesh>(new sgl::device::mesh(_vertex, _normal, 
                _tex_uv, _faces));
}

////////////////////////////////////////////////////////////////////////////////////////

void sgl::host::mesh::recompute_normals()
{
    _normal->resize(_vertex->size());

    for(int i = 0; i < _vertex->size (); i++)
        _normal->at(i) = glm::vec3(0.0, 0.0, 0.0);

    for(int i=0; i < _faces->size(); i+=3)
    {
        glm::vec3 e01 = _vertex->at(_faces->at(i+1)) - _vertex->at(_faces->at(i));
        glm::vec3 e02 = _vertex->at(_faces->at(i+2)) - _vertex->at(_faces->at(i));
        glm::vec3 n   = glm::cross(e01, e02);

        glm::normalize(n);

        _normal->at(_faces->at(i)  ) += n;
        _normal->at(_faces->at(i+1)) += n;
        _normal->at(_faces->at(i+2)) += n;
    }

    for (unsigned int i = 0; i < _normal->size (); i++) {
        glm::normalize(_normal->at(i));
    }
}

////////////////////////////////////////////////////////////////////////////////////////

inline void sgl::host::mesh::center()
{
    glm::vec3 c(0.0, 0.0, 0.0);

    for(int i=0; i < _vertex->size(); i++)
        c += _vertex->at(i);
    
    c /= _vertex->size();
    for(int i=0; i < _vertex->size(); i++)
        _vertex->at(i) -= c;
}

////////////////////////////////////////////////////////////////////////////////////////

inline void sgl::host::mesh::scale_to_unit()
{
    float maxD = glm::l2Norm(_vertex->at(0));
    float currD = 0;

    for(int i=0; i < _vertex->size(); i++)
    {
        currD = glm::l2Norm(_vertex->at(0));
        if(currD > maxD)
            maxD = currD;
    }

    for(int i=0; i < _vertex->size(); i++)
        _vertex->at(i) = _vertex->at(i) / maxD;
}

////////////////////////////////////////////////////////////////////////////////////////

#endif /* !MESH_HPP */

////////////////////////////////////////////////////////////////////////////////////////

