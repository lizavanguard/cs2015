//==============================================================================
//
// 安全なdelete用テンプレート関数 [SafeDelete.h]
// Created : Shimizu Shoji
// MEMO:
//  deleteにnullチェックは必要ない
//
//==============================================================================
#ifndef __H_SAFEDELETE_H__
#define __H_SAFEDELETE_H__
//==============================================================================
// function implementation
//==============================================================================
//------------------------------------------------
// 渡されたポインタを安全にデリートします
// マクロなんてもう古い！
//------------------------------------------------
template<typename Interface>
inline void SafeDelete( Interface*& rpInterfaceToDelete ) {
	delete rpInterfaceToDelete;
	rpInterfaceToDelete = nullptr;
}


//------------------------------------------------
// 渡された配列ポインタを安全にデリートします
// マクロなんてもう古い！
//------------------------------------------------
template<typename Interface>
inline void SafeDeleteArray( Interface*& rpInterfacesToDelete ) {
	delete[] rpInterfacesToDelete;
	rpInterfacesToDelete = nullptr;
}


#endif // __H_SAFEDELETE_H__