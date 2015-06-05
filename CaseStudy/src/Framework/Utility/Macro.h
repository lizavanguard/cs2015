//==============================================================================
//
// ユーティリティ マクロ定義 [Macro.h]
// Createad : Shimizu Shoji
//
//==============================================================================
#pragma once
#ifndef __H_LIZAMACROMACRO_H__
#define __H_LIZAMACROMACRO_H__
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// macro definition
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// ユニークな文字列をコンパイル時に生成する
#define __GENERATE_UNIQUE_STRING( F, L ) ( F ## #L )
#define _GENERATE_UNIQUE_STRING( F, L ) __GENERATE_UNIQUE_STRING( F, L )
#define GENERATE_UNIQUE_STRING _GENERATE_UNIQUE_STRING( __FILE__, __LINE__ )

// ユニークな文字列をコンパイル時に生成する(テンプレートクラスの展開に対応)
#define __GENERATE_UNIQUE_STRING_EX( FILE, LINE, FUNC ) ( FILE ## #LINE ## FUNC )
#define _GENERATE_UNIQUE_STRING_EX( FILE, LINE, FUNC ) __GENERATE_UNIQUE_STRING_EX( FILE, LINE, FUNC )
#define GENERATE_UNIQUE_STRING_EX _GENERATE_UNIQUE_STRING_EX( __FILE__, __LINE__, __FUNCTION__ )

#endif // __H_LIZAMACROMACRO_H__