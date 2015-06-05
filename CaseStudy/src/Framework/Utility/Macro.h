//==============================================================================
//
// ���[�e�B���e�B �}�N����` [Macro.h]
// Createad : Shimizu Shoji
//
//==============================================================================
#pragma once
#ifndef __H_LIZAMACROMACRO_H__
#define __H_LIZAMACROMACRO_H__
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// macro definition
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// ���j�[�N�ȕ�������R���p�C�����ɐ�������
#define __GENERATE_UNIQUE_STRING( F, L ) ( F ## #L )
#define _GENERATE_UNIQUE_STRING( F, L ) __GENERATE_UNIQUE_STRING( F, L )
#define GENERATE_UNIQUE_STRING _GENERATE_UNIQUE_STRING( __FILE__, __LINE__ )

// ���j�[�N�ȕ�������R���p�C�����ɐ�������(�e���v���[�g�N���X�̓W�J�ɑΉ�)
#define __GENERATE_UNIQUE_STRING_EX( FILE, LINE, FUNC ) ( FILE ## #LINE ## FUNC )
#define _GENERATE_UNIQUE_STRING_EX( FILE, LINE, FUNC ) __GENERATE_UNIQUE_STRING_EX( FILE, LINE, FUNC )
#define GENERATE_UNIQUE_STRING_EX _GENERATE_UNIQUE_STRING_EX( __FILE__, __LINE__, __FUNCTION__ )

#endif // __H_LIZAMACROMACRO_H__