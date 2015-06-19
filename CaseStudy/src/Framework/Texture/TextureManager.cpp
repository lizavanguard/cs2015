//==============================================================================
//
// �e�N�X�`���}�l�[�W�� [TextureManager.cpp]
// Author : Shimizu Shoji
//
//==============================================================================
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// include
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "TextureManager.h"
#include "Framework/Utility/Utility.h"


//==============================================================================
// class implementation
//==============================================================================
//------------------------------------------------
// ctor
//------------------------------------------------
TextureManager::TextureManager(LPDIRECT3DDEVICE9 pDevice) : pDevice_(pDevice) {
  for (int textureID = 0; textureID < kTextureMax; ++textureID) {
    textureList_[textureID] = nullptr;
  }
}


//------------------------------------------------
// dtor
//------------------------------------------------
TextureManager::~TextureManager() {
  for (int textureID = 0; textureID < kTextureMax; ++textureID) {
    SafeRelease(textureList_[textureID]);
  }
}


//------------------------------------------------
// �e�N�X�`����ǂݍ���
// �߂�l�Ƃ���ID���Ԃ��Ă���̂ŁA�ȍ~�͂���ID���g�p���邱��
// -1���A���Ă����ꍇ�́A�ǂݍ��݃G���[
//------------------------------------------------
int TextureManager::LoadTexture(const char* const filename) {
  // ��ID����
  // ���� ID �������ł��Ȃ������� -1 ��Ԃ�
  const int id = _SearchNotUsedID();
  assert(id != -1 && "ID������܂���");
  if (id == -1) {
    return -1;
  }

  // �e�N�X�`���̃��[�h
  HRESULT hr = D3DXCreateTextureFromFile(pDevice_, filename, &textureList_[id]);
  // TOOD: ASSERT
  if (FAILED(hr)) {
    MessageBox(nullptr, "�e�N�X�`�����[�h�G���[", "Error", MB_OK);
  }

  return id;
}


//------------------------------------------------
// �e�N�X�`�����Z�b�g����
//------------------------------------------------
void TextureManager::SetTexture(const int id) {
  // TODO : ASSERT
  // set texture
  if (id < 0 || id >= kTextureMax){
    pDevice_->SetTexture(0, nullptr);
  } else {
    pDevice_->SetTexture(0, textureList_[id]);
  }
}


//------------------------------------------------
// ��ID����������
// �󂫂����������ꍇ��-1��Ԃ�
//------------------------------------------------
int TextureManager::_SearchNotUsedID(void) {
  for (int textureID = 0; textureID < kTextureMax; ++textureID) {
    // if �e�N�X�`�������[�h����Ă��Ȃ������� ����ID��Ԃ�
    if (!textureList_[textureID]) {
      return textureID;
    }
  }

  // �G���[
  return -1;
}
