//==============================================================================
//
// �e�N�X�`���}�l�[�W�� [TextureManager.h]
// Author : Shimizu Shoji
//
//==============================================================================
#pragma once
#ifndef __H_TEXTUREMANAGER_H__
#define __H_TEXTUREMANAGER_H__
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// class definition
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
class TextureManager {
public:
  // ctor
  TextureManager(LPDIRECT3DDEVICE9 pDevice);

  // dtor
  ~TextureManager();

  // �e�N�X�`����ǂݍ���
  // �߂�l�Ƃ���ID���Ԃ��Ă���̂ŁA�ȍ~�͂���ID���g�p���邱��
  // -1���A���Ă����ꍇ�́A�ǂݍ��݃G���[
  int LoadTexture(const char* filename);

  // �e�N�X�`�����Z�b�g����
  void SetTexture(int id);

private:
  static const int kTextureMax = 100;

  int _SearchNotUsedID(void);

  LPDIRECT3DTEXTURE9 textureList_[kTextureMax];
  LPDIRECT3DDEVICE9 pDevice_;
};


#endif  // __H_TEXTUREMANAGER_H__
