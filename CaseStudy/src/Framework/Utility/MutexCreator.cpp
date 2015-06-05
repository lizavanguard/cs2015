//==============================================================================
//
// Mutex�쐬�N���X [MutexCreator.cpp]
// Created : Shimizu Shoji
//
//==============================================================================
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// include
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "MutexCreator.h"
#include "Framework/Utility/Macro.h"


//==============================================================================
// class implementation
//==============================================================================
//------------------------------------------------
// instance
//------------------------------------------------
unsigned int liza::MutexCreator::s_mutexCnt_ = 0;


//------------------------------------------------
// ctor
//------------------------------------------------
liza::MutexCreator::MutexCreator() {
	// �n���h�����̍쐬
	handleName_ = GENERATE_UNIQUE_STRING_EX;
	
	// �n���h���������Ȃ��悤�ɒ���
	char buf[8];
	_itoa_s( s_mutexCnt_, buf, 10 );
	handleName_ += buf;
	++s_mutexCnt_;

	// �n���h���̍쐬
	hMutex_ = CreateMutex( nullptr, FALSE, handleName_.c_str() );
}


//------------------------------------------------
// dtor
//------------------------------------------------
liza::MutexCreator::~MutexCreator() {
	CloseHandle( hMutex_ );
}


//------------------------------------------------
// get mutex
//------------------------------------------------
std::shared_ptr<liza::Mutex> liza::MutexCreator::Create( void ) {
	return std::shared_ptr<liza::Mutex>( new Mutex( handleName_ ) );
}