/*
 * =====================================================================================
 *       Filename:  camera_host.hpp
 *    Description:  
 *        Created:  2015-02-16 16:42
 *         Author:  Tiago Lobato Gimenes        (tlgimenes@gmail.com)
 * =====================================================================================
 */

////////////////////////////////////////////////////////////////////////////////////////

#ifndef CAMERA_HOST_HPP
#define CAMERA_HOST_HPP

////////////////////////////////////////////////////////////////////////////////////////

// ---------------------------------------------
// BEGIN : Code from SGI
// ---------------------------------------------

/*
 * Pass the x and y coordinates of the last and current positions of
 * the mouse, scaled so they are from (-1.0 ... 1.0).
 *
 * The resulting rotation is returned as a quaternion rotation in the
 * first paramater.
 */
void
trackball(float q[4], float p1x, float p1y, float p2x, float p2y);

void
negate_quat(float *q, float *qn);

/*
 * Given two quaternions, add them together to get a third quaternion.
 * Adding quaternions to get a compound rotation is analagous to adding
 * translations to get a compound translation.  when incrementally
 * adding rotations, the first argument here should be the new
 * rotation, the second and third the total rotation (which will be
 * over-written with the resulting new total rotation).
 */
void
add_quats(float *q1, float *q2, float *dest);

/*
 * A useful function, builds a rotation matrix in Matrix based on
 * given quaternion.
 */
void
build_rotmatrix(float m[4][4], float q[4]);

/*
 * This function computes a quaternion based on an axis (defined by
 * the given vector) and an angle about which to rotate.  The angle is
 * expressed in radians.  The result is put into the third argument.
 */
void
axis_to_quat(float a[3], float phi, float q[4]);

// ---------------------------------------------
// END : Code from SGI
// ---------------------------------------------

////////////////////////////////////////////////////////////////////////////////////////

#include <memory>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp> // glm::value_ptr

#include "camera_device.hpp"

////////////////////////////////////////////////////////////////////////////////////////

namespace sgl
{
    namespace host
    {
        class camera 
        {
            private:
                float _fov;             // field of view
                int _width, _height;    // width and height in pixels
                float _z_near, _z_far;  // plane near and plane far

                glm::vec3 _pos; // camera position

                float _zoom; // camera zoom

                std::shared_ptr<glm::mat4> _proj, _view, _model; // Projection, view and model matrices

                float _curquat[4];
                float _lastquat[4];

                int _spinning, _moving;
                int _beginu, _beginv;

            protected:
                inline void update_projection() {
                    *_proj = glm::perspective(_fov, (float)_width/ (float)_height, _z_near, _z_far);
                }

                inline void update_view() {
                    *_view = glm::translate(glm::mat4(1.0), glm::vec3(_pos[0], 
                                _pos[1], -_pos[2]));
                }

                inline void update_model() {
                    *_model = glm::scale(glm::mat4(1.0), glm::vec3(_zoom));
                }

            public:
                camera(int width = 800, int height = 600, float fov = 45, float z_near = 0.1, 
                        float z_far = 10000.0, float zoom = 0.5, 
                        glm::vec3 pos = glm::vec3(0.0, 0.0, 2.0));
                inline virtual ~camera() {}

                /**
                 * Creates a camera with matrices on the device
                 * */
                std::shared_ptr<sgl::device::camera> to_device();

                /**
                 * Resize camera
                 * */
                void resize(int width, int height);

                /**
                 * Move camera
                 * */
                void move(float dx, float dy, float dz);

                /**
                 * Starts rotation
                 * */
                void begin_rotate(int u, int v);

                /**
                 * Rotates the view  
                 * */
                void rotate(int u, int v);

                /**
                 * Zoom
                 * */
                void zoom(float zoom);

                /**
                 * Apply transformations 
                 * */
                void apply();

                /**
                 * Return the camera's positions
                 * */
                glm::vec3 pos();
        };
    }
}

////////////////////////////////////////////////////////////////////////////////////////

inline sgl::host::camera::camera(int width, int height, float fov, float z_near, float z_far, 
        float zoom, glm::vec3 pos) :
    _width(width),
    _height(height),
    _fov(fov),
    _z_near(z_near),
    _z_far(z_far),
    _zoom(zoom),
    _pos(pos),
    _proj(new glm::mat4()),
    _view(new glm::mat4()),
    _model(new glm::mat4())
{
    _spinning = 0;
    _moving = 0;
    _beginu = 0;
    _beginv = 0;

    trackball (_curquat, 0.0, 0.0, 0.0, 0.0);

    update_projection();
    update_view();
    update_model();
}

////////////////////////////////////////////////////////////////////////////////////////

inline std::shared_ptr<sgl::device::camera> sgl::host::camera::to_device()
{
    return std::shared_ptr<sgl::device::camera>(new sgl::device::camera(_proj, _view, _model));
}

////////////////////////////////////////////////////////////////////////////////////////

inline void sgl::host::camera::resize(int width, int height)
{
    _height = height;
    _width = width;

    glViewport(0, 0, _width, _height);
    update_projection();
}

////////////////////////////////////////////////////////////////////////////////////////

inline void sgl::host::camera::move(float dx, float dy, float dz)
{
    _pos[0] += dx;
    _pos[1] += dy;
    _pos[2] += dz;
}

////////////////////////////////////////////////////////////////////////////////////////

inline void sgl::host::camera::begin_rotate(int u, int v) {
    _beginu = u;
    _beginv = v;
    _moving = 1;
    _spinning = 0;
}

////////////////////////////////////////////////////////////////////////////////////////

inline void sgl::host::camera::rotate(int u, int v)
{
    if (_moving) {
        trackball(_lastquat,
                (2.0 * _beginu - _width) / _width,
                (_height - 2.0 * _beginv) / _height,
                (2.0 * u - _width) / _width,
                (_height - 2.0 * v) / _height);
        _beginu = u;
        _beginv = v;
        _spinning = 1;
        add_quats (_lastquat, _curquat, _curquat);
    }
}

////////////////////////////////////////////////////////////////////////////////////////

inline void sgl::host::camera::zoom(float zoom)
{
    _zoom *= zoom;
}

////////////////////////////////////////////////////////////////////////////////////////

inline void sgl::host::camera::apply()
{
    update_model();
    update_view();
    
    GLfloat m[4][4];
    build_rotmatrix(m, _curquat);
 
    glm::mat4 rot = glm::mat4(glm::vec4(glm::make_vec4(m[0])),
            glm::vec4(glm::make_vec4(m[1])),
            glm::vec4(glm::make_vec4(m[2])),
            glm::vec4(glm::make_vec4(m[3])));

    *_view = *_view * rot;
}

////////////////////////////////////////////////////////////////////////////////////////

inline glm::vec3 sgl::host::camera::pos()
{
    glm::vec3 p;
    GLfloat m[4][4]; 

    build_rotmatrix(m, _curquat);

    float _x = -_pos[0];
    float _y = -_pos[1];
    float _z = -_pos[2] + _zoom;

    p[0] = m[0][0] * _x +  m[0][1] * _y +  m[0][2] * _z;
    p[1] = m[1][0] * _x +  m[1][1] * _y +  m[1][2] * _z;
    p[2] = m[2][0] * _x +  m[2][1] * _y +  m[2][2] * _z;
}

////////////////////////////////////////////////////////////////////////////////////////

// ---------------------------------------------
// BEGIN : Code from SGI
// ---------------------------------------------

#include <cstdio>
/*
 * (c) Copyright 1993, 1994, Silicon Graphics, Inc.
 * ALL RIGhTS RESERVED
 * Permission to use, copy, modify, and distribute this software for
 * any purpose and without fee is hereby granted, provided that the above
 * copyright notice appear in all copies and that both the copyright notice
 * and this permission notice appear in supporting documentation, and that
 * the name of Silicon Graphics, Inc. not be used in advertising
 * or publicity pertaining to distribution of the software without specific,
 * written prior permission.
 *
 * ThE MATERIAL EMBODIED ON ThIS SOFTwARE IS PROVIDED TO YOU "AS-IS"
 * AND wIThOUT wARRANTY OF ANY KIND, EXPRESS, IMPLIED OR OThERwISE,
 * INCLUDING wIThOUT LIMITATION, ANY wARRANTY OF MERChANTABILITY OR
 * FITNESS FOR A PARTICULAR PURPOSE.  IN NO EVENT ShALL SILICON
 * GRAPhICS, INC.  BE LIABLE TO YOU OR ANYONE ELSE FOR ANY DIRECT,
 * SPECIAL, INCIDENTAL, INDIRECT OR CONSEQUENTIAL DAMAGES OF ANY
 * KIND, OR ANY DAMAGES whATSOEVER, INCLUDING wIThOUT LIMITATION,
 * LOSS OF PROFIT, LOSS OF USE, SAVINGS OR REVENUE, OR ThE CLAIMS OF
 * ThIRD PARTIES, whEThER OR NOT SILICON GRAPhICS, INC.  hAS BEEN
 * ADVISED OF ThE POSSIBILITY OF SUCh LOSS, hOwEVER CAUSED AND ON
 * ANY ThEORY OF LIABILITY, ARISING OUT OF OR IN CONNECTION wITh ThE
 * POSSESSION, USE OR PERFORMANCE OF ThIS SOFTwARE.
 *
 * US Government Users Restricted Rights
 * Use, duplication, or disclosure by the Government is subject to
 * restrictions set forth in FAR 52.227.19(c)(2) or subparagraph
 * (c)(1)(ii) of the Rights in Technical Data and Computer Software
 * clause at DFARS 252.227-7013 and/or in similar or successor
 * clauses in the FAR or the DOD or NASA FAR Supplement.
 * Unpublished-- rights reserved under the copyright laws of the
 * United States.  Contractor/manufacturer is Silicon Graphics,
 * Inc., 2011 N.  Shoreline Blvd., Mountain View, CA 94039-7311.
 *
 * OpenGL(TM) is a trademark of Silicon Graphics, Inc.
 */
/*
 * Trackball code:
 *
 * Implementation of a virtual trackball.
 * Implemented by Gavin Bell, lots of ideas from Thant Tessman and
 *   the August '88 issue of Siggraph's "Computer Graphics," pp. 121-129.
 *
 * Vector manip code:
 *
 * Original code from:
 * David M. Ciemiewicz, Mark Grossman, henry Moreton, and Paul haeberli
 *
 * Much mucking with by:
 * Gavin Bell
 */
#if defined(_WIN32)
#pragma warning (disable:4244)          /* disable bogus conversion warnings */
#endif
#include <cmath>

/*
 * This size should really be based on the distance from the center of
 * rotation to the point on the object underneath the mouse.  That
 * point would then track the mouse as closely as possible.  This is a
 * simple example, though, so that is left as an Exercise for the
 * Programmer.
 */
#define TRACKBALLSIZE  (0.8f)

/*
 * Local function prototypes (not defined in trackball.h)
 */
static float tb_project_to_sphere(float, float, float);
static void normalize_quat(float [4]);

    void
vzero(float *v)
{
    v[0] = 0.0;
    v[1] = 0.0;
    v[2] = 0.0;
}

    void
vset(float *v, float x, float y, float z)
{
    v[0] = x;
    v[1] = y;
    v[2] = z;
}

    void
vsub(const float *src1, const float *src2, float *dst)
{
    dst[0] = src1[0] - src2[0];
    dst[1] = src1[1] - src2[1];
    dst[2] = src1[2] - src2[2];
}

    void
vcopy(const float *v1, float *v2)
{
    register int i;
    for (i = 0 ; i < 3 ; i++)
        v2[i] = v1[i];
}

    void
vcross(const float *v1, const float *v2, float *cross)
{
    float temp[3];

    temp[0] = (v1[1] * v2[2]) - (v1[2] * v2[1]);
    temp[1] = (v1[2] * v2[0]) - (v1[0] * v2[2]);
    temp[2] = (v1[0] * v2[1]) - (v1[1] * v2[0]);
    vcopy(temp, cross);
}

    float
vlength(const float *v)
{
    return sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
}

    void
vscale(float *v, float div)
{
    v[0] *= div;
    v[1] *= div;
    v[2] *= div;
}

    void
vnormal(float *v)
{
    vscale(v,1.0/vlength(v));
}

    float
vdot(const float *v1, const float *v2)
{
    return v1[0]*v2[0] + v1[1]*v2[1] + v1[2]*v2[2];
}

    void
vadd(const float *src1, const float *src2, float *dst)
{
    dst[0] = src1[0] + src2[0];
    dst[1] = src1[1] + src2[1];
    dst[2] = src1[2] + src2[2];
}

/*
 * Ok, simulate a track-ball.  Project the points onto the virtual
 * trackball, then figure out the axis of rotation, which is the cross
 * product of P1 P2 and O P1 (O is the center of the ball, 0,0,0)
 * Note:  This is a deformed trackball-- is a trackball in the center,
 * but is deformed into a hyperbolic sheet of rotation away from the
 * center.  This particular function was chosen after trying out
 * several variations.
 *
 * It is assumed that the arguments to this routine are in the range
 * (-1.0 ... 1.0)
 */
    void
trackball(float q[4], float p1x, float p1y, float p2x, float p2y)
{
    float a[3]; /* Axis of rotation */
    float phi;  /* how much to rotate about axis */
    float p1[3], p2[3], d[3];
    float t;

    if (p1x == p2x && p1y == p2y) {
        /* Zero rotation */
        vzero(q);
        q[3] = 1.0;
        return;
    }

    /*
     * First, figure out z-coordinates for projection of P1 and P2 to
     * deformed sphere
     */
    vset(p1,p1x,p1y,tb_project_to_sphere(TRACKBALLSIZE,p1x,p1y));
    vset(p2,p2x,p2y,tb_project_to_sphere(TRACKBALLSIZE,p2x,p2y));

    /*
     *  Now, we want the cross product of P1 and P2
     */
    vcross(p2,p1,a);

    /*
     *  Figure out how much to rotate around that axis.
     */
    vsub(p1,p2,d);
    t = vlength(d) / (2.0*TRACKBALLSIZE);

    /*
     * Avoid problems with out-of-control values...
     */
    if (t > 1.0) t = 1.0;
    if (t < -1.0) t = -1.0;
    phi = 2.0 * asin(t);

    axis_to_quat(a,phi,q);
}

/*
 *  Given an axis and angle, compute quaternion.
 */
    void
axis_to_quat(float a[3], float phi, float q[4])
{
    vnormal(a);
    vcopy(a,q);
    vscale(q,sin(phi/2.0));
    q[3] = cos(phi/2.0);
}

/*
 * Project an x,y pair onto a sphere of radius r OR a hyperbolic sheet
 * if we are away from the center of the sphere.
 */
    static float
tb_project_to_sphere(float r, float x, float y)
{
    float d, t, z;

    d = sqrt(x*x + y*y);
    if (d < r * 0.70710678118654752440) {    /* Inside sphere */
        z = sqrt(r*r - d*d);
    } else {           /* On hyperbola */
        t = r / 1.41421356237309504880;
        z = t*t / d;
    }
    return z;
}

/*
 * Given two rotations, e1 and e2, expressed as quaternion rotations,
 * figure out the equivalent single rotation and stuff it into dest.
 *
 * This routine also normalizes the result every RENORMCOUNT times it is
 * called, to keep error from creeping in.
 *
 * NOTE: This routine is written so that q1 or q2 may be the same
 * as dest (or each other).
 */

#define RENORMCOUNT 97

    void
negate_quat(float q[4], float nq[4])
{
    nq[0] = -q[0];
    nq[1] = -q[1];
    nq[2] = -q[2];
    nq[3] = q[3];
}

    void
add_quats(float q1[4], float q2[4], float dest[4])
{
    static int count=0;
    float t1[4], t2[4], t3[4];
    float tf[4];

#if 0
    printf("q1 = %f %f %f %f\n", q1[0], q1[1], q1[2], q1[3]);
    printf("q2 = %f %f %f %f\n", q2[0], q2[1], q2[2], q2[3]);
#endif

    vcopy(q1,t1);
    vscale(t1,q2[3]);

    vcopy(q2,t2);
    vscale(t2,q1[3]);

    vcross(q2,q1,t3);
    vadd(t1,t2,tf);
    vadd(t3,tf,tf);
    tf[3] = q1[3] * q2[3] - vdot(q1,q2);

#if 0
    printf("tf = %f %f %f %f\n", tf[0], tf[1], tf[2], tf[3]);
#endif

    dest[0] = tf[0];
    dest[1] = tf[1];
    dest[2] = tf[2];
    dest[3] = tf[3];

    if (++count > RENORMCOUNT) {
        count = 0;
        normalize_quat(dest);
    }
}

/*
 * Quaternions always obey:  a^2 + b^2 + c^2 + d^2 = 1.0
 * If they don't add up to 1.0, dividing by their magnitued will
 * renormalize them.
 *
 * Note: See the following for more information on quaternions:
 *
 * - Shoemake, K., Animating rotation with quaternion curves, Computer
 *   Graphics 19, No 3 (Proc. SIGGRAPh'85), 245-254, 1985.
 * - Pletinckx, D., Quaternion calculus as a basic tool in computer
 *   graphics, The Visual Computer 5, 2-13, 1989.
 */
    static void
normalize_quat(float q[4])
{
    int i;
    float mag;

    mag = sqrt(q[0]*q[0] + q[1]*q[1] + q[2]*q[2] + q[3]*q[3]);
    for (i = 0; i < 4; i++) q[i] /= mag;
}

/*
 * Build a rotation matrix, given a quaternion rotation.
 *
 */
    void
build_rotmatrix(float m[4][4], float q[4])
{
    m[0][0] = 1.0 - 2.0 * (q[1] * q[1] + q[2] * q[2]);
    m[0][1] = 2.0 * (q[0] * q[1] - q[2] * q[3]);
    m[0][2] = 2.0 * (q[2] * q[0] + q[1] * q[3]);
    m[0][3] = 0.0;

    m[1][0] = 2.0 * (q[0] * q[1] + q[2] * q[3]);
    m[1][1]= 1.0 - 2.0 * (q[2] * q[2] + q[0] * q[0]);
    m[1][2] = 2.0 * (q[1] * q[2] - q[0] * q[3]);
    m[1][3] = 0.0;

    m[2][0] = 2.0 * (q[2] * q[0] - q[1] * q[3]);
    m[2][1] = 2.0 * (q[1] * q[2] + q[0] * q[3]);
    m[2][2] = 1.0 - 2.0 * (q[1] * q[1] + q[0] * q[0]);
    m[2][3] = 0.0;

    m[3][0] = 0.0;
    m[3][1] = 0.0;
    m[3][2] = 0.0;
    m[3][3] = 1.0;
}

// ---------------------------------------------
// BEGIN : Code from SGI
// ---------------------------------------------

////////////////////////////////////////////////////////////////////////////////////////

#endif /* !CAMERA_HOST_HPP */

////////////////////////////////////////////////////////////////////////////////////////

