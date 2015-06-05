//==============================================================================
//
// Creation Policy [Creation.hpp]
// Created : Shimizu Shoji
// MEMO:
// インスタンスの生成破棄の方式を規定
// 要件定義)
// [static method] T* Create(void): インスタンスの生成を行う
// [static method] void Destroy(T*): インスタンスの破棄を行う
//
//==============================================================================
#pragma once
#ifndef __HPP_LIZAGENERICCREATION_HPP__
#define __HPP_LIZAGENERICCREATION_HPP__
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// include
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include <assert.h>


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// class definition
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
namespace liza {
	namespace generic {

//------------------------------------------------
// インスタンスの生成としてnewとデフォルト・コンストラクタを用いる
//------------------------------------------------
template<typename T>
struct CreateUsingNew {

	static T* Create( void ) {
		return new T;
	}

	static void Destroy( T* pInstance ) {
		assert( pInstance != nullptr );
		delete pInstance;
	}

};


//------------------------------------------------
// インスタンスの生成としてmallocと、デフォルト・コンストラクタを用いる
//------------------------------------------------
template<typename T>
struct CreateUsingMalloc {

	static T* Create( void ) {
		return (T*)realloc( nullptr, sizeof( T ) );
	}

	static void Destroy( T* pInstance ) {
		assert( pInstance != nullptr );
		realloc( pInstance, 0 );
	}

};


//------------------------------------------------
// インスタンスを静的に生成する
//------------------------------------------------
template<typename T>
struct CreateStatic {

	static T* Create( void ) {
		static T instance;
		return &instance;
	}

	static void Destroy( T* pInstance ) {
		assert( pInstance != nullptr );
	}

};

	} // namespace generic
} // namespace liza


#endif // __HPP_LIZAGENERICCREATION_HPP__