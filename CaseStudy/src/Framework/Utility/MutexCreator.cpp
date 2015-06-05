//==============================================================================
//
// Mutex作成クラス [MutexCreator.cpp]
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
	// ハンドル名の作成
	handleName_ = GENERATE_UNIQUE_STRING_EX;
	
	// ハンドル名が被らないように調整
	char buf[8];
	_itoa_s( s_mutexCnt_, buf, 10 );
	handleName_ += buf;
	++s_mutexCnt_;

	// ハンドルの作成
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