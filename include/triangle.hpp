/*
 * =====================================================================================
 *       Filename:  triangle.hpp
 *    Description:  A Triangle class expressed as a triplet of indices (over an external vertex list)
 *        Created:  2015-01-15 23:10
 *         Author:  Tiago Lobato Gimenes        (tlgimenes@gmail.com)
 * =====================================================================================
 */

////////////////////////////////////////////////////////////////////////////////////////

#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP

////////////////////////////////////////////////////////////////////////////////////////

#include <cassert>

#include "vec3.hpp"
#include "vec2.hpp"

////////////////////////////////////////////////////////////////////////////////////////

class Triangle {
    private:
        Vec3u _v; // Vertices indices
        Vec3u _n; // Normal indices
        Vec3u _tex; // Texture indices

    public:
        /**
         * Constructs triangles based on indices  
         * */
        Triangle(const Vec3u& v = Vec3u(0,0,0), const Vec3u& n = Vec3u(0,0,0), 
                const Vec3u& tex = Vec3u(0,0,0));
        
        /**
         * Gets
         */
        inline const Vec3u& v() const {return _v;}
        inline const Vec3u& n() const {return _n;}
        inline const Vec3u& tex() const {return _tex;}

        /**
         * Sets
         */
        inline Vec3u& v() {return _v;}
        inline Vec3u& n() {return _n;}
        inline Vec3u& tex() {return _tex;}

        /**
         * Operators  
         * */
        inline Triangle& operator= (const Triangle& t);
};

////////////////////////////////////////////////////////////////////////////////////////

#endif /* !TRIANGLE_HPP */

////////////////////////////////////////////////////////////////////////////////////////

