//==============================================================================
//
// ���S��delete�p�e���v���[�g�֐� [SafeDelete.h]
// Created : Shimizu Shoji
// MEMO:
//  delete��null�`�F�b�N�͕K�v�Ȃ�
//
//==============================================================================
#ifndef __H_SAFEDELETE_H__
#define __H_SAFEDELETE_H__
//==============================================================================
// function implementation
//==============================================================================
//------------------------------------------------
// �n���ꂽ�|�C���^�����S�Ƀf���[�g���܂�
// �}�N���Ȃ�Ă����Â��I
//------------------------------------------------
template<typename Interface>
inline void SafeDelete( Interface*& rpInterfaceToDelete ) {
	delete rpInterfaceToDelete;
	rpInterfaceToDelete = nullptr;
}


//------------------------------------------------
// �n���ꂽ�z��|�C���^�����S�Ƀf���[�g���܂�
// �}�N���Ȃ�Ă����Â��I
//------------------------------------------------
template<typename Interface>
inline void SafeDeleteArray( Interface*& rpInterfacesToDelete ) {
	delete[] rpInterfacesToDelete;
	rpInterfacesToDelete = nullptr;
}


#endif // __H_SAFEDELETE_H__