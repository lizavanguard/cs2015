//==============================================================================
//
// Mutex�N���X [Mutex.h]
// Created : Shimizu Shoji
//
//==============================================================================
#pragma once
#ifndef __H_LIZAMUTEX_H__
#define __H_LIZAMUTEX_H__
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// include
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include <Windows.h>
#include <string>


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// class definition
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
namespace liza {

// �~���[�e�b�N�X�̃I�[�v���Ɖ���������ōs���N���X
class Mutex {
public:
	// ctor/dtor
	Mutex( const std::string& handleName );
	~Mutex();

	// mutex�̃n���h�����������(�哱)
	void Release( void );
	void Lock( void );

private:
	// property
	HANDLE hMutex_;
};

} // namespace liza


#endif // __H_LIZAMUTEX_H__