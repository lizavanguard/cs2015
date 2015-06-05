//==============================================================================
//
// Creation Policy [Creation.hpp]
// Created : Shimizu Shoji
// MEMO:
// �C���X�^���X�̐����j���̕������K��
// �v����`)
// [static method] T* Create(void): �C���X�^���X�̐������s��
// [static method] void Destroy(T*): �C���X�^���X�̔j�����s��
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
// �C���X�^���X�̐����Ƃ���new�ƃf�t�H���g�E�R���X�g���N�^��p����
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
// �C���X�^���X�̐����Ƃ���malloc�ƁA�f�t�H���g�E�R���X�g���N�^��p����
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
// �C���X�^���X��ÓI�ɐ�������
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