/*
 * =====================================================================================
 *       Filename:  vec4.hpp
 *    Description:  
 *        Created:  2015-02-12 11:33
 *         Author:  Tiago Lobato Gimenes        (tlgimenes@gmail.com)
 * =====================================================================================
 */

////////////////////////////////////////////////////////////////////////////////////////

#ifndef VEC4_HPP
#define VEC4_HPP

////////////////////////////////////////////////////////////////////////////////////////

#include "vec.hpp"

////////////////////////////////////////////////////////////////////////////////////////

#ifndef X
#define X 0
#endif
#ifndef Y
#define Y 1
#endif
#ifndef Z
#define Z 2
#endif
#ifndef W
#define W 3
#endif
#ifndef R
#define R 0
#endif
#ifndef G
#define G 1
#endif
#ifndef B
#define B 2
#endif
#ifndef A
#define A 3
#endif

////////////////////////////////////////////////////////////////////////////////////////

template <class T>
class Vec4 : public Vec<4, T>
{
    public:
        inline Vec4(T x = 0.0, T y = 0.0, T z = 0.0, T w = 0.0);
        inline Vec4(const Vec<4, T>& v);
        inline Vec4(T* );

        inline void operator() (T x, T y, T z, T w);
        inline Vec4<T> operator= (const Vec<4, T> &P);
};

////////////////////////////////////////////////////////////////////////////////////////

template <class T>
inline Vec4<T>::Vec4(T x, T y, T z, T w) {
    this->_p[X] = x;
    this->_p[Y] = y;
    this->_p[Z] = z;
    this->_p[W] = w;
}

////////////////////////////////////////////////////////////////////////////////////////
template <class T>
inline Vec4<T>::Vec4(const Vec<4, T>& v) {
    this->_p[X] = v[X];
    this->_p[Y] = v[Y];
    this->_p[Z] = v[Z];
    this->_p[W] = v[W];
}

////////////////////////////////////////////////////////////////////////////////////////

template <class T>
inline Vec4<T>::Vec4(T* P) {
    this->_p[X] = P[X];
    this->_p[Y] = P[Y];
    this->_p[Z] = P[Z];
    this->_p[W] = P[W];
}

////////////////////////////////////////////////////////////////////////////////////////

template <class T>
inline void Vec4<T>::operator() (T x, T y, T z, T w) {
    this->_p[X] = x;
    this->_p[Y] = y;
    this->_p[Z] = z;
    this->_p[W] = w;
}

////////////////////////////////////////////////////////////////////////////////////////

template <class T>
inline Vec4<T> Vec4<T>::operator= (const Vec<4, T>& P) {
    this->_p[X] = P[X];
    this->_p[Y] = P[Y];
    this->_p[Z] = P[Z];
    this->_p[W] = P[W];
    return *(this);
}

////////////////////////////////////////////////////////////////////////////////////////

typedef Vec4<float>  Vec4f;
typedef Vec4<double> Vec4d;
typedef Vec4<uint>   Vec4u;

////////////////////////////////////////////////////////////////////////////////////////

#endif /* !VEC4_HPP */

////////////////////////////////////////////////////////////////////////////////////////

