//==============================================================================
//
// ���S��Release�p�e���v���[�g�֐� [SafeRelease.h]
// Created : Shimizu Shoji
//
//==============================================================================
#ifndef __H_SAFERELEASE_H__
#define __H_SAFERELEASE_H__
//==============================================================================
// function implementation
//==============================================================================
//------------------------------------------------
// �n���ꂽ�|�C���^�����S�Ƀ����[�X���܂�
// �}�N���Ȃ�Ă����Â��I
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