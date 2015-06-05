//==============================================================================
//
// ���w�p�ėp�֐� [MathUtility.h]
// Created : Shimizu Shoji
//
//==============================================================================
#pragma once
#ifndef __H_LIZAMATHMATHUTILITY_H__
#define __H_LIZAMATHMATHUTILITY_H__
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// include
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include <assert.h>
#include <math.h>

#include "MathConst.h"


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// prototype declaration
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
namespace liza {
	namespace math {

//------------------------------------------------
// 2�_�Ԃ̋�����2���Ԃ�
//------------------------------------------------
template<typename T>
T LengthSq( const T& x1, const T& y1, const T& x2, const T& y2 );


template<typename T>
T LengthSq( const T& x1, const T& y1, const T& z1, const T& x2, const T& y2, const T& z2 );


//------------------------------------------------
// 2�_�Ԃ̋�����Ԃ�
//------------------------------------------------
template<typename T>
T Length( const T& x1, const T& y1, const T& x2, const T& y2 );


template<typename T>
T Length( const T& x1, const T& y1, const T& z1, const T& x2, const T& y2, const T& z2 );


//------------------------------------------------
// �z�N�����v�I��(�l���z������)
// x <= | 臒l |
// �ƂȂ�悤�Ȓl��Ԃ�
// �������z������
//------------------------------------------------
template<typename T>
T CirculateClamp( T x, T value );


template<typename T>
inline T CirculateClamp( T* p, T value );


//------------------------------------------------
// �z�N�����v�I��(�l���z������)
// �ŏ��l <= x <= �ő�l
// �ƂȂ�悤�Ȓl��Ԃ�
// �������z������
//------------------------------------------------
template<typename T>
T CirculateClamp( T x, T min, T max );


template<typename T>
inline T CirculateClamp( T* p, T min, T max );


//------------------------------------------------
// �N�����v(�l�̊ۂߍ��ݓI��)
// x <= | 臒l |
// �ƂȂ�悤�Ȓl��Ԃ�
//------------------------------------------------
template<typename T>
T Clamp( T x, T value );


template<typename T>
inline T Clamp( T* p, T value );


//------------------------------------------------
// �N�����v(�l�̊ۂߍ��ݓI��)
// �ŏ��l <= x <= �ő�l
// �ƂȂ�悤�Ȓl��Ԃ�
//------------------------------------------------
template<typename T>
T Clamp( T x, T min, T max );


template<typename T>
inline T Clamp( T* p, T min, T max );


//------------------------------------------------
// co-secant
//------------------------------------------------
template<typename T>
inline T csc( T x );


//------------------------------------------------
// co-tangent
//------------------------------------------------
template<typename T>
inline T cot( T x );


//------------------------------------------------
// lerp(linear-interpolation)
//------------------------------------------------
template<typename T>
T Lerp( T a, T b, T t );


template<typename T, typename U>
T Lerp( T a, T b, U t );


//------------------------------------------------
// secant
//------------------------------------------------
template<typename T>
inline T sec( T x );


//------------------------------------------------
// To degree
//------------------------------------------------
template<typename T>
inline T ToDegree( T radian );


//------------------------------------------------
// To radian
//------------------------------------------------
template<typename T>
inline T ToRadian( T degree );


#include "MathUtility.inl"

	} // namespace math
} // namespace liza


#endif // __H_LIZAMATHMATHUTILITY_H__