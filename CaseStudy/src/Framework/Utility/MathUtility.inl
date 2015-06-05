//==============================================================================
//
// 数学用汎用関数インラインヘッダ [MathUtility.inl]
// Created : Shimizu Shoji
// MEMO:
// もっとうまいやり方がある気がする
// 与えられた数値をテンプレート時に定数展開してくれるやつないの？
// constexprとかどうなんだろ
//
//==============================================================================
#pragma once
#ifndef __INL_LIZAMATHMATHUTILITY_INL__
#define __INL_LIZAMATHMATHUTILITY_INL__
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// include
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "MathUtility.hpp"


//==============================================================================
// function implementation
//==============================================================================
//------------------------------------------------
// 2点間の距離の二乗を返す
//------------------------------------------------
template<typename T>
T LengthSq( const T& x1, const T& y1, const T& x2, const T& y2 ) {
	return ( x1 - x2 ) * ( x1 - x2 ) + ( y1 - y2 ) * ( y1 - y2 );
}


template<typename T>
T LengthSq( const T& x1, const T& y1, const T& z1, const T& x2, const T& y2, const T& z2 ) {
	return ( x1 - x2 ) * ( x1 - x2 ) + ( y1 - y2 ) * ( y1 - y2 ) + ( z1 - z2 ) * ( z1 - z2 );
}


//------------------------------------------------
// 2点間の距離を返す
//------------------------------------------------
template<typename T>
T Length( const T& x1, const T& y1, const T& x2, const T& y2 ) {
	return sqrt( LengthSq( x1, y1, x2, y2 ) );
}


template<typename T>
T Length( const T& x1, const T& y1, const T& z1, const T& x2, const T& y2, const T& z2 ) {
	return sqrt( LengthSq( x1, y1, z1, x2, y2, z2 ) );
}


//------------------------------------------------
// 循環クランプ的な(値を循環させる)
// x <= | 閾値 |
// となるような値を返す
// ただし循環させる
//------------------------------------------------
template<typename T>
T CirculateClamp( const T x, const T value ) {
	// if 最小値より小さかったら最大値側に循環させる
	if( x < -value ) {
		return x + ( value * 2 );
	}

	// else if 最大値より大きかったら最小値側に循環させる
	else if( x > value ) {
		return x - ( value * 2 );
	}

	// else そのままの値を返す
	return x;
}


template<typename T>
T CirculateClamp( T* const p, const T value ) {
	return *p = CirculateClamp( *p, value );
}



//------------------------------------------------
// 循環クランプ的な(値を循環させる)
// 最小値 <= x <= 最大値
// となるような値を返す
// ただし循環させる
//------------------------------------------------
template<typename T>
T CirculateClamp( const T x, const T min, const T max ) {
	assert( min < max && "[min < max]にしてね" );

	// if 最小値より小さかったら最大値側に循環させる
	if( x < min ) {
		return x + ( max - min );
	}

	// else if 最大値より大きかったら最小値側に循環させる
	else if( x > max ) {
		return x - ( max - min );
	}

	// else そのままの値を返す
	return x;
}



template<typename T>
T CirculateClamp( T* const p, const T min, const T max ) {
	return *p = CirculateClamp( *p, min, max );
}


//------------------------------------------------
// クランプ(値の丸め込み的な)
// x <= | 閾値 |
// となるような値を返す
//------------------------------------------------
template<typename T>
T Clamp( const T x, const T value ) {
	// if 最小値より小さかったら最小値を返す
	if( x < -value ) {
		return -value;
	}

	// else if 最大値より大きかったら最大値を返す
	else if( x > value ) {
		return value;
	}

	// else そのままの値を返す
	return x;
}


template<typename T>
T Clamp( T* const p, const T value ) {
	return *p = Clamp( *p, value );
}



//------------------------------------------------
// クランプ(値の丸め込み的な)
// 最小値 <= x <= 最大値
// となるような値を返す
//------------------------------------------------
template<typename T>
inline T Clamp( const T x, const T min, const T max ) {
	assert( min < max && "[min < max]にしてね" );

	// if 最小値より小さかったら最小値を返す
	if( x < min ) {
		return min;
	}

	// else if 最大値より大きかったら最大値を返す
	else if( x > max ) {
		return max;
	}

	// else そのままの値を返す
	return x;
}


template<typename T>
T Clamp( T* const p, const T min, const T max ) {
	return *p = Clamp( *p, min, max );
}


//------------------------------------------------
// co-secant
//------------------------------------------------
template<typename T>
inline T csc( const T x ) {
	return 1.0f / sin( x );
}


template<>
inline double csc<double>( const double x ) {
	return 1.0 / sin( x );
}


//------------------------------------------------
// co-tangent
//------------------------------------------------
template<typename T>
inline T cot( const T x ) {
	return 1.0f / tan( x );
}


template<>
inline double cot<double>( const double x ) {
	return 1.0 / tan( x );
}


//------------------------------------------------
// lerp(linear-interpolation)
//------------------------------------------------
template<typename T>
inline T Lerp( const T a, const T b, const T t ) {
	return a + ( t * ( b - a ) );
}


template<typename T, typename U>
inline T Lerp( const T a, const T b, const U t ) {
	return a + ( t * ( b - a ) );
}


//------------------------------------------------
// secant
//------------------------------------------------
template<typename T>
inline T sec( const T x ) {
	return 1.0f / cos( x );
}


template<>
inline double sec<double>( const double x ) {
	return 1.0 / cos( x );
}


//------------------------------------------------
// To degree
//------------------------------------------------
template<typename T>
inline T ToDegree( const T radian ) {
	static const T kTemp = 180.0f * liza::math::kReciprocalOfPIf;
	return radian * kTemp;
}


template<>
inline double ToDegree<double>( const double radian ) {
	static const double kTemp = 180.0 * liza::math::kReciprocalOfPId;
	return radian * kTemp;
}


//------------------------------------------------
// To radian
//------------------------------------------------
template<typename T>
inline T ToRadian( const T degree ) {
	static const T kTemp = liza::math::kPIf / 180.0f;
	return degree * kTemp;
}


template<>
inline double ToRadian<double>( const double degree ) {
	static const double kTemp = liza::math::kPId / 180.0;
	return degree * kTemp;
}


#endif // __INL_LIZAMATHMATHUTILITY_INL__