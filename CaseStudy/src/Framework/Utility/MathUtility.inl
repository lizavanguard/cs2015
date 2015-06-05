//==============================================================================
//
// ���w�p�ėp�֐��C�����C���w�b�_ [MathUtility.inl]
// Created : Shimizu Shoji
// MEMO:
// �����Ƃ��܂�����������C������
// �^����ꂽ���l���e���v���[�g���ɒ萔�W�J���Ă�����Ȃ��́H
// constexpr�Ƃ��ǂ��Ȃ񂾂�
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
// 2�_�Ԃ̋����̓���Ԃ�
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
// 2�_�Ԃ̋�����Ԃ�
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
// �z�N�����v�I��(�l���z������)
// x <= | 臒l |
// �ƂȂ�悤�Ȓl��Ԃ�
// �������z������
//------------------------------------------------
template<typename T>
T CirculateClamp( const T x, const T value ) {
	// if �ŏ��l��菬����������ő�l���ɏz������
	if( x < -value ) {
		return x + ( value * 2 );
	}

	// else if �ő�l���傫��������ŏ��l���ɏz������
	else if( x > value ) {
		return x - ( value * 2 );
	}

	// else ���̂܂܂̒l��Ԃ�
	return x;
}


template<typename T>
T CirculateClamp( T* const p, const T value ) {
	return *p = CirculateClamp( *p, value );
}



//------------------------------------------------
// �z�N�����v�I��(�l���z������)
// �ŏ��l <= x <= �ő�l
// �ƂȂ�悤�Ȓl��Ԃ�
// �������z������
//------------------------------------------------
template<typename T>
T CirculateClamp( const T x, const T min, const T max ) {
	assert( min < max && "[min < max]�ɂ��Ă�" );

	// if �ŏ��l��菬����������ő�l���ɏz������
	if( x < min ) {
		return x + ( max - min );
	}

	// else if �ő�l���傫��������ŏ��l���ɏz������
	else if( x > max ) {
		return x - ( max - min );
	}

	// else ���̂܂܂̒l��Ԃ�
	return x;
}



template<typename T>
T CirculateClamp( T* const p, const T min, const T max ) {
	return *p = CirculateClamp( *p, min, max );
}


//------------------------------------------------
// �N�����v(�l�̊ۂߍ��ݓI��)
// x <= | 臒l |
// �ƂȂ�悤�Ȓl��Ԃ�
//------------------------------------------------
template<typename T>
T Clamp( const T x, const T value ) {
	// if �ŏ��l��菬����������ŏ��l��Ԃ�
	if( x < -value ) {
		return -value;
	}

	// else if �ő�l���傫��������ő�l��Ԃ�
	else if( x > value ) {
		return value;
	}

	// else ���̂܂܂̒l��Ԃ�
	return x;
}


template<typename T>
T Clamp( T* const p, const T value ) {
	return *p = Clamp( *p, value );
}



//------------------------------------------------
// �N�����v(�l�̊ۂߍ��ݓI��)
// �ŏ��l <= x <= �ő�l
// �ƂȂ�悤�Ȓl��Ԃ�
//------------------------------------------------
template<typename T>
inline T Clamp( const T x, const T min, const T max ) {
	assert( min < max && "[min < max]�ɂ��Ă�" );

	// if �ŏ��l��菬����������ŏ��l��Ԃ�
	if( x < min ) {
		return min;
	}

	// else if �ő�l���傫��������ő�l��Ԃ�
	else if( x > max ) {
		return max;
	}

	// else ���̂܂܂̒l��Ԃ�
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