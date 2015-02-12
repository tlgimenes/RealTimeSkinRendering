/*
 * =====================================================================================
 *       Filename:  vec2.hpp
 *    Description:  
 *        Created:  2015-01-29 18:59
 *         Author:  Tiago Lobato Gimenes        (tlgimenes@gmail.com)
 * =====================================================================================
 */

////////////////////////////////////////////////////////////////////////////////////////

#ifndef VEC2_HPP
#define VEC2_HPP

////////////////////////////////////////////////////////////////////////////////////////

#include "vec.hpp"
#include "utils.hpp"

////////////////////////////////////////////////////////////////////////////////////////

#ifndef X
#define X 0
#endif
#ifndef Y 
#define Y 1
#endif

////////////////////////////////////////////////////////////////////////////////////////

template <class T>
class Vec2 : public Vec<2, T>
{
    public:
        inline Vec2(T x = 0, T y = 0);
        inline Vec2(const Vec<2, T>& v);
        inline Vec2(T* );

        inline void operator() (T x, T y);
        inline Vec2<T> operator= (const Vec<2, T> &P);
};

////////////////////////////////////////////////////////////////////////////////////////

template <class T>
inline Vec2<T>::Vec2(T x, T y) {
    this->_p[0] = x;
    this->_p[1] = y;
}

template <class T>
inline Vec2<T>::Vec2(const Vec<2, T>& v) {
    this->_p[0] = v[0];
    this->_p[1] = v[1];
}

template <class T>
inline Vec2<T>::Vec2(T * P) {
    this->_p[0] = P[0];
    this->_p[1] = P[1];
}

////////////////////////////////////////////////////////////////////////////////////////

template <class T>
inline void Vec2<T>::operator() (T x, T y) {
    this->_p[0] = x;
    this->_p[1] = y;
}

template <class T>
inline Vec2<T> Vec2<T>::operator= (const Vec<2, T>& P) {
    this->_p[0] = P[0];
    this->_p[1] = P[1];
    return (*this);
}

////////////////////////////////////////////////////////////////////////////////////////

typedef Vec2<float>  Vec2f;
typedef Vec2<double> Vec2d;
typedef Vec2<uint>   Vec2u;

////////////////////////////////////////////////////////////////////////////////////////

#endif /* !VEC2_HPP */

////////////////////////////////////////////////////////////////////////////////////////

