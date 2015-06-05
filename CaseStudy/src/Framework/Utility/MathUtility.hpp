//==============================================================================
//
// 数学用汎用関数 [MathUtility.h]
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
// 2点間の距離の2乗を返す
//------------------------------------------------
template<typename T>
T LengthSq( const T& x1, const T& y1, const T& x2, const T& y2 );


template<typename T>
T LengthSq( const T& x1, const T& y1, const T& z1, const T& x2, const T& y2, const T& z2 );


//------------------------------------------------
// 2点間の距離を返す
//------------------------------------------------
template<typename T>
T Length( const T& x1, const T& y1, const T& x2, const T& y2 );


template<typename T>
T Length( const T& x1, const T& y1, const T& z1, const T& x2, const T& y2, const T& z2 );


//------------------------------------------------
// 循環クランプ的な(値を循環させる)
// x <= | 閾値 |
// となるような値を返す
// ただし循環させる
//------------------------------------------------
template<typename T>
T CirculateClamp( T x, T value );


template<typename T>
inline T CirculateClamp( T* p, T value );


//------------------------------------------------
// 循環クランプ的な(値を循環させる)
// 最小値 <= x <= 最大値
// となるような値を返す
// ただし循環させる
//------------------------------------------------
template<typename T>
T CirculateClamp( T x, T min, T max );


template<typename T>
inline T CirculateClamp( T* p, T min, T max );


//------------------------------------------------
// クランプ(値の丸め込み的な)
// x <= | 閾値 |
// となるような値を返す
//------------------------------------------------
template<typename T>
T Clamp( T x, T value );


template<typename T>
inline T Clamp( T* p, T value );


//------------------------------------------------
// クランプ(値の丸め込み的な)
// 最小値 <= x <= 最大値
// となるような値を返す
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