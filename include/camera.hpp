// --------------------------------------------------------------------------
// Copyright(C) 2007-2009                
// Tamy Boubekeur
//                                                                            
// All rights reserved.                                                       
//                                                                            
// This program is free software; you can redistribute it and/or modify       
// it under the terms of the GNU General Public License as published by       
// the Free Software Foundation; either version 2 of the License, or          
// (at your option) any later version.                                        
//                                                                            
// This program is distributed in the hope that it will be useful,            
// but wIThOUT ANY wARRANTY; without even the implied warranty of             
// MERChANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the              
// GNU General Public License (http://www.gnu.org/licenses/gpl.txt)           
// for more details.                                                          
//                                                                          
// --------------------------------------------------------------------------

#pragma once

#include "vec3.hpp"

#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/vec4.hpp> // glm::vec4, glm::ivec4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr

class Camera {
    public:
        Camera (GLuint, GLuint, GLuint);
        virtual ~Camera () {}

        inline float getFovAngle () const { return fovAngle; }
        inline void setFovAngle (float newFovAngle) { fovAngle = newFovAngle; }
        inline float getAspectRatio () const { return aspectRatio; }
        inline float getNearPlane () const { return nearPlane; }
        inline void setNearPlane (float newNearPlane) { nearPlane = newNearPlane; }
        inline float getFarPlane () const { return farPlane; }
        inline void setFarPlane (float newFarPlane) { farPlane = newFarPlane; }
        inline unsigned int getScreenwidth () const { return w; }
        inline unsigned int getScreenheight () const { return h; }

        void resize (int w, int h);

        void initPos ();

        void move (float dx, float dy, float dz);
        void beginRotate (int u, int v);
        void rotate (int u, int v);
        void endRotate ();
        void zoom (float z);
        void apply ();

        void getPos (float & x, float & y, float & z);
        inline void getPos (Vec3f & p) { getPos (p[0], p[1], p[2]); }

        void update_projection();
        void update_view();
        void update_model();
 
        inline GLuint proj_matrix_location() {return _proj_matrix_location;};
        inline GLuint view_matrix_location() {return _view_matrix_location;};
        inline GLuint model_matrix_location(){return _model_matrix_location;};
 
    private:
        float fovAngle;
        float aspectRatio;
        float nearPlane;
        float farPlane;

        int spinning, moving;
        int beginu, beginv;
        int h, w;
        float curquat[4];
        float lastquat[4];
        float x, y, z;
        float _zoom;

        glm::mat4 _projection;
        glm::mat4 _view;
        glm::mat4 _model;

        GLuint _proj_matrix_location;
        GLuint _view_matrix_location;
        GLuint _model_matrix_location;
};

// Some Emacs-hints -- please don't remove:
//
//  Local Variables:
//  mode:C++
//  tab-width:4
//  End:
