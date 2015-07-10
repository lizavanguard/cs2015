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
}


//------------------------------------------------
// dtor
//------------------------------------------------
TextureManager::~TextureManager() {
  for (auto pTexture : textureList_) {
    SafeRelease(pTexture);
  }
  textureList_.clear();
  textureSearchMap_.clear();
}


//------------------------------------------------
// �e�N�X�`����ǂݍ���
// �߂�l�Ƃ���ID���Ԃ��Ă���̂ŁA�ȍ~�͂���ID���g�p���邱��
// -1���A���Ă����ꍇ�́A�ǂݍ��݃G���[
//------------------------------------------------
int TextureManager::LoadTexture(const char* const filename) {
  if (!filename) {
    return -1;
  }

  auto it = textureSearchMap_.find(filename);
  if (it != textureSearchMap_.end()) {
    return it->second;
  }

  // �e�N�X�`���̓o�^
  LPDIRECT3DTEXTURE9 pTexture = nullptr;
  HRESULT hr = D3DXCreateTextureFromFile(pDevice_, filename, &pTexture);
  textureList_.push_back(pTexture);

  // ID�̓o�^
  const int id = textureList_.size() - 1;
  textureSearchMap_.insert(std::make_pair(filename, id));

  return id;
}


//------------------------------------------------
// �e�N�X�`�����Z�b�g����
//------------------------------------------------
void TextureManager::SetTexture(const int _id) {
  const unsigned int id = static_cast<unsigned int>(_id);
  assert(0 <= id && id < textureList_.size());

  if (id < 0 || textureList_.size() <= id){
    pDevice_->SetTexture(0, nullptr);
  }
  else {
    pDevice_->SetTexture(0, textureList_[id]);
  }
}
