/*
 * =====================================================================================
 *       Filename:  renderable.hpp
 *    Description:  
 *        Created:  2015-02-16 20:55
 *         Author:  Tiago Lobato Gimenes        (tlgimenes@gmail.com)
 * =====================================================================================
 */

////////////////////////////////////////////////////////////////////////////////////////

#ifndef RENDERABLE_HPP
#define RENDERABLE_HPP

////////////////////////////////////////////////////////////////////////////////////////

#include <vector>

#include "pipeline_device.hpp"
#include "texture_device.hpp"
#include "camera_device.hpp"
#include "mesh_device.hpp"

#include "error.hpp"

////////////////////////////////////////////////////////////////////////////////////////

namespace sgl
{
    namespace device
    {
        class renderable 
        {
            protected:
                std::shared_ptr<mesh> _mesh;    // Mesh
                std::shared_ptr<camera> _camera; // Camera
                std::shared_ptr<pipeline> _shader; // Shader 
                std::vector<GLuint> _textures; // Textures
 
            public:
                renderable(const std::shared_ptr<mesh>& _mesh,    // Mesh
                           const std::shared_ptr<camera>& _camera, // Camera
                           const std::shared_ptr<pipeline>& _shader, // Shader 
                           const std::vector<std::shared_ptr<texture2D>>& _textures); // Textures

                virtual void draw();

                virtual void bind();

                virtual void unbind();
        };
    }
}

////////////////////////////////////////////////////////////////////////////////////////

inline sgl::device::renderable::renderable(
        const std::shared_ptr<mesh>& mesh,    // Mesh
        const std::shared_ptr<camera>& camera, // Camera
        const std::shared_ptr<pipeline>& shader, // Shader 
        const std::vector<std::shared_ptr<texture2D>>& textures) :
    _mesh(mesh),
    _camera(camera),
    _shader(shader),
    _textures(0)
{
    gl_check_for_errors();
    
    for(int i=0; i < textures.size(); i++)
        _textures.push_back(textures[i]->id());
}

////////////////////////////////////////////////////////////////////////////////////////

inline void sgl::device::renderable::draw()
{
    glDrawElements(GL_TRIANGLES, _mesh->index_count(), GL_UNSIGNED_INT, NULL);

    glFlush();
}

////////////////////////////////////////////////////////////////////////////////////////

inline void sgl::device::renderable::bind()
{
    _mesh->bind();
    _shader->bind();
    _camera->bind();

    glBindTextures(0, _textures.size(), _textures.data());
}

////////////////////////////////////////////////////////////////////////////////////////

inline void sgl::device::renderable::unbind()
{
    _shader->unbind();
    _camera->unbind();
    _mesh->unbind();

    glBindTexture(GL_TEXTURE_2D, 0);
}

////////////////////////////////////////////////////////////////////////////////////////

#endif /* !RENDERABLE_HPP */

////////////////////////////////////////////////////////////////////////////////////////

