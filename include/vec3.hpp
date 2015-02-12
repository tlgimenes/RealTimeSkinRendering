/*
 * =====================================================================================
 *       Filename:  vec3.hpp
 *    Description:  
 *        Created:  2015-01-29 19:25
 *         Author:  Tiago Lobato Gimenes        (tlgimenes@gmail.com)
 * =====================================================================================
 */

////////////////////////////////////////////////////////////////////////////////////////

#ifndef VEC3_HPP
#define VEC3_HPP

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

////////////////////////////////////////////////////////////////////////////////////////

template <class T>
class Vec3 : public Vec<3, T>
{
    public:
        inline Vec3(T x = 0.0, T y = 0.0, T z = 0.0);
        inline Vec3(const Vec<3, T>& v);
        inline Vec3(T* );

        inline void operator() (T x, T y, T z);
        inline Vec3<T> operator= (const Vec<3, T> &P);

        inline Vec3<T> cross (const Vec3<T>& b) const;
};

////////////////////////////////////////////////////////////////////////////////////////

template <class T>
inline Vec3<T>::Vec3(T x, T y, T z) {
    this->_p[0] = x;
    this->_p[1] = y;
    this->_p[2] = z;
}

template <class T>
inline Vec3<T>::Vec3(const Vec<3, T>& v) {
    this->_p[0] = v[0];
    this->_p[1] = v[1];
    this->_p[2] = v[2];
}

template <class T> 
inline Vec3<T>::Vec3(T * P)  {
    this->_p[0] = P[0];
    this->_p[1] = P[1];
    this->_p[2] = P[2];
}
 
////////////////////////////////////////////////////////////////////////////////////////

template <class T>
inline void Vec3<T>::operator() (T x, T y, T z) {
    this->_p[0] = x;
    this->_p[1] = y;
    this->_p[2] = z;
}

template <class T>
inline Vec3<T> Vec3<T>::operator= (const Vec<3, T>& P) {
    this->_p[0] = P[0];
    this->_p[1] = P[1];
    this->_p[2] = P[2];
    return (*this);
}

////////////////////////////////////////////////////////////////////////////////////////

template <class T>
inline Vec3<T> Vec3<T>::cross (const Vec3<T>& b) const {
    Vec3<T> r;
    r[0] = this->_p[1] * b[2] - this->_p[2] * b[1];
    r[1] = this->_p[2] * b[0] - this->_p[0] * b[2];
    r[2] = this->_p[0] * b[1] - this->_p[1] * b[0];
    return r;
}

////////////////////////////////////////////////////////////////////////////////////////

typedef Vec3<float>  Vec3f;
typedef Vec3<double> Vec3d;
typedef Vec3<uint>   Vec3u;

////////////////////////////////////////////////////////////////////////////////////////

#endif /* !VEC3_HPP */

////////////////////////////////////////////////////////////////////////////////////////

