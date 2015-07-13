//==============================================================================
//
// テクスチャマネージャ [TextureManager.cpp]
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
// テクスチャを読み込む
// 戻り値としてIDが返ってくるので、以降はこのIDを使用すること
// -1が帰ってきた場合は、読み込みエラー
//------------------------------------------------
int TextureManager::LoadTexture(const char* const filename) {
  if (!filename) {
    return -1;
  }

  auto it = textureSearchMap_.find(filename);
  if (it != textureSearchMap_.end()) {
    return it->second;
  }

  // テクスチャの登録
  LPDIRECT3DTEXTURE9 pTexture = nullptr;
  HRESULT hr = D3DXCreateTextureFromFile(pDevice_, filename, &pTexture);
  textureList_.push_back(pTexture);

  // IDの登録
  const int id = textureList_.size() - 1;
  textureSearchMap_.insert(std::make_pair(filename, id));

  return id;
}


//------------------------------------------------
// テクスチャをセットする
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
