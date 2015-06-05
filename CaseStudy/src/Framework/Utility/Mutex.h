//==============================================================================
//
// Mutexクラス [Mutex.h]
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

// ミューテックスのオープンと解放を自動で行うクラス
class Mutex {
public:
	// ctor/dtor
	Mutex( const std::string& handleName );
	~Mutex();

	// mutexのハンドルを解放する(主導)
	void Release( void );
	void Lock( void );

private:
	// property
	HANDLE hMutex_;
};

} // namespace liza


#endif // __H_LIZAMUTEX_H__