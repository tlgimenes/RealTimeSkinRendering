/*
 * =====================================================================================
 *       Filename:  vec.hpp
 *    Description:  
 *        Created:  2015-01-29 17:14
 *         Author:  Tiago Lobato Gimenes        (tlgimenes@gmail.com)
 * =====================================================================================
 */

////////////////////////////////////////////////////////////////////////////////////////

#ifndef VEC_HPP
#define VEC_HPP

////////////////////////////////////////////////////////////////////////////////////////

#pragma GCC push_options
#pragma GCC optimize ("unroll-loops")

////////////////////////////////////////////////////////////////////////////////////////

#include <fstream>
#include <cmath>

#include "utils.hpp"
#include "error.hpp"

////////////////////////////////////////////////////////////////////////////////////////

template <int dim, class T>
class Vec 
{
    public:
        inline Vec();
        inline Vec(const Vec& v);
        inline Vec(T *);

        /**
         * Operators
         * */
        virtual inline T& operator[] (int index);
        virtual inline const T& operator[] (int index) const; 
        inline Vec<dim,T>& operator= (const Vec<dim,T> & P);
        virtual inline Vec<dim,T>& operator+= (const Vec<dim,T> & P);
        virtual inline Vec<dim,T>& operator-= (const Vec<dim,T> & P);
        virtual inline Vec<dim,T>& operator*= (T s);
        virtual inline Vec<dim,T>& operator/= (T s);
        virtual inline Vec<dim,T> operator+ (const Vec<dim,T> & P) const;
        virtual inline Vec<dim,T> operator- (const Vec<dim,T> & P) const;
        virtual inline Vec<dim,T> operator- () const;
        virtual inline Vec<dim,T> operator* (T s) const;
        virtual inline Vec<dim,T> operator/ (T s) const;
        virtual inline bool operator== (const Vec<dim,T>& a) const; 
        virtual inline bool operator!= (const Vec<dim,T> & a) const;
        virtual inline bool operator< (const Vec<dim,T> & a) const; 
        virtual inline bool operator>= (const Vec<dim,T> &a) const;

        /**
         * Geometric operations  
         * */
        virtual inline T dot(const Vec<dim, T>& b) const;
        virtual inline T squared_norm2() const;
        virtual inline T norm2() const;
        virtual inline T dist(const Vec<dim, T>& b) const;
        virtual inline T normalize(); // return length before normalization

    protected:
        T _p[dim];
};

////////////////////////////////////////////////////////////////////////////////////////
// Constructors
template <int dim, typename T>
inline Vec<dim, T>::Vec() {
    for(uint i=0; i < dim; i++) {
        _p[i] = 0.0f;
    }
}

template <int dim, typename T>
inline Vec<dim, T>::Vec(const Vec<dim, T>& v) {
    for(uint i=0; i < dim; i++) {
        _p[i] = v[i];
    }
}

template <int dim, typename T>
inline Vec<dim, T>::Vec(T * P) {
    for(uint i=0; i < dim; i++) {
        _p[i] = P[i];
    }
}

////////////////////////////////////////////////////////////////////////////////////////

template <int dim, typename T>
inline T& Vec<dim,T>::operator[] (int index) {
    ASSERT_FATAL_ERROR(index < dim, "Index out of bounds");
    return (_p[index]);
}

template <int dim, typename T>
inline const T& Vec<dim,T>::operator[] (int index) const {
    ASSERT_FATAL_ERROR(index < dim, "Index out of bounds");
    return (_p[index]);
}

template <int dim, typename T>
inline Vec<dim,T>& Vec<dim,T>::operator= (const Vec<dim,T> & P) {
    for(uint i=0; i < dim; i++) {
        _p[i] = P[i];
    }
    return (*this);
}

template <int dim, typename T>
inline Vec<dim,T>& Vec<dim,T>::operator+= (const Vec<dim,T> & P) {
    for(uint i=0; i < dim; i++) {
        _p[i] += P[i];
    }
    return (*this);
}

template <int dim, typename T>
inline Vec<dim,T>& Vec<dim,T>::operator-= (const Vec<dim,T> & P) {
    for(uint i=0; i < dim; i++) {
        _p[i] -= P[i];
    }
    return (*this);
}

template <int dim, typename T>
inline Vec<dim,T>& Vec<dim,T>::operator*= (T s) {
    for(uint i=0; i < dim; i++) {
        _p[i] *= s;
    }
    return (*this);
}

template <int dim, typename T>
inline Vec<dim,T>& Vec<dim,T>::operator/= (T s) {
    for(uint i=0; i < dim; i++) {
        _p[i] /= s;
    }
    return (*this);
}

template <int dim, typename T>
inline Vec<dim,T> Vec<dim,T>::operator+ (const Vec<dim,T> & P) const {
    Vec<dim,T> res;
    for(uint i=0; i < dim; i++) {
        res[i] = _p[i] + P[i];
    }
    return (res); 
}

template <int dim, typename T>
inline Vec<dim,T> Vec<dim,T>::operator- (const Vec<dim,T> & P) const {
    Vec<dim,T> res;
    for(uint i=0; i < dim; i++) {
        res[i] = _p[i] - P[i];
    }
    return (res); 
}

template <int dim, typename T>
inline Vec<dim,T> Vec<dim,T>::operator- () const {
    Vec<dim,T> res;
    for(uint i=0; i < dim; i++) {
        res[i] = -_p[i];
    }
    return (res); 
}

template <int dim, typename T>
inline Vec<dim,T> Vec<dim,T>::operator* (T s) const {
    Vec<dim,T> res;
    for(uint i=0; i < dim; i++) {
        res[i] = _p[i] * s;
    }
    return (res);
}

template <int dim, typename T>
inline Vec<dim,T> Vec<dim,T>::operator/ (T s) const {
    Vec<dim,T> res;
    for(uint i=0; i < dim; i++) {
        res[i] = _p[i] / s;
    }
    return (res);
}

template <int dim, typename T>
inline bool Vec<dim,T>::operator== (const Vec<dim,T>& a) const {
    bool res = true;
    for(uint i=0; i < dim; i++) {
        res = res && (_p[i] == a[i]);
    }
    return res;
}

template <int dim, typename T>
inline bool Vec<dim,T>::operator != (const Vec<dim,T> & a) const {
    bool res = false;
    for(uint i=0; i < dim; i++) {
        res = res || (_p[i] != a[i]);
    }
    return res;
}

template <int dim, typename T>
inline bool Vec<dim,T>::operator < (const Vec<dim,T> & a) const {
    bool res = true;
    for(uint i=0; i < dim; i++) {
        res = res && (_p[i] < a[i]);
    }
    return res;
}

template <int dim, typename T>
inline bool Vec<dim,T>::operator >= (const Vec<dim,T> &a) const {
    bool res = true;
    for(uint i=0; i < dim; i++) {
        res = res && (_p[i] >= a[i]);
    }
    return res;
}

////////////////////////////////////////////////////////////////////////////////////////
// Geometric operations
template <int dim, typename T>
inline T Vec<dim,T>::dot(const Vec<dim, T>& b) const {
    ASSERT_FATAL_ERROR(dim > 0, "index out of bounds");

    T ac = _p[0] * b[0];
    for(uint i=1; i < dim; i++) {
        ac += _p[i] * b[i];
    }
    return ac;
}

template <int dim, typename T>
inline T Vec<dim,T>::squared_norm2() const {
    return dot(*this);
}

template <int dim, typename T>
inline T Vec<dim,T>::norm2() const {
    return (T) sqrt(squared_norm2());
}

template <int dim, typename T>
inline T Vec<dim,T>::dist(const Vec<dim, T>& b) const {
    return (*this - b).norm2();
}

template <int dim, typename T>
inline T Vec<dim,T>::normalize() { // returns the length before normalization
    T l = norm2();
    if(l < 0.0f + EPSILON && l > 0.0f + EPSILON)
        return 0;
    T invL = 1.0f / l;
    *this *= invL;
    return l;
}

////////////////////////////////////////////////////////////////////////////////////////
// (I/O)stream Operators
template <int dim, typename T>
std::ostream & operator<< (std::ostream & output, const Vec<dim, T> & v) {
    output << "(";
    for(uint i=0; i < dim; i++) {
        output << v[i] << ",";
    }
    output << ")";

    return output;
}

template <int dim, typename T>
std::istream & operator>> (std::istream & input, Vec<dim, T> & v) {
    for(uint i=0; i < dim; i++) {
        input >> v[i];
    }
    return input;
}

////////////////////////////////////////////////////////////////////////////////////////

#pragma GCC pop_options

////////////////////////////////////////////////////////////////////////////////////////

#endif /* !VEC_HPP */

////////////////////////////////////////////////////////////////////////////////////////

