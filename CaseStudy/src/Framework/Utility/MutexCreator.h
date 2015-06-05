//==============================================================================
//
// Mutex�쐬�N���X [MutexCreator.h]
// Created : Shimizu Shoji
//
//==============================================================================
#pragma once
#ifndef __H_LIZAMUTEXCREATOR_H__
#define __H_LIZAMUTEXCREATOR_H__
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// include
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include <Windows.h>
#include <memory>
#include "Mutex.h"
#include <string>


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// class definition
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
namespace liza {

class MutexCreator {
public:
	// ctor/dtor
	MutexCreator();
	~MutexCreator();

	// method
	// �~���[�e�b�N�X���쐬���ĕԂ�
	std::shared_ptr<Mutex> Create( void );

private:
	// property
	static unsigned int s_mutexCnt_;

	HANDLE hMutex_;
	std::string handleName_;
};

} // namespace liza


#endif // __H_LIZAMUTEXCREATOR_H__