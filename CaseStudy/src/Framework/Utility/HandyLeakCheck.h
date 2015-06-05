//==============================================================================
//
// HandyLeakCheck.h [HandyLeakCheck.h]
// Created : Shimizu Shoji
//
//==============================================================================
#pragma once
#ifndef __H_HANDYLEAKCHECK_H__
#define __H_HANDYLEAKCHECK_H__
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// include
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>


//==============================================================================
// function implementation
//==============================================================================
namespace liza {
	namespace utility {

//------------------------------------------------
// �Ƃ肠�����ȈՓI�ȃ��[�N�`�F�b�N�@�\�ł�
// �����w�肵�Ă��邩�m�肽�������璲�ׂĂ�������
//------------------------------------------------
inline void BeginLeakCheck( void ) {
	_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
}

	} // namespace utility
} // namespace liza


#endif // __H_HANDYLEAKCHECK_H__