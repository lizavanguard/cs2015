//==============================================================================
//
// 安全なRelease用テンプレート関数 [SafeRelease.h]
// Created : Shimizu Shoji
//
//==============================================================================
#ifndef __H_SAFERELEASE_H__
#define __H_SAFERELEASE_H__
//==============================================================================
// function implementation
//==============================================================================
//------------------------------------------------
// 渡されたポインタを安全にリリースします
// マクロなんてもう古い！
//------------------------------------------------
template<class Interface>
inline void SafeRelease( Interface** ppInterfaceToRelease ) {
	if( ( *ppInterfaceToRelease ) ) {
		( *ppInterfaceToRelease )->Release();
		( *ppInterfaceToRelease ) = nullptr;
	}
}


template<class Interface>
inline void SafeRelease( Interface*& rpInterfaceToRelease ) {
	if( rpInterfaceToRelease ) {
		rpInterfaceToRelease->Release();
		rpInterfaceToRelease = nullptr;
	}
}


#endif // __H_SAFERELEASE_H__