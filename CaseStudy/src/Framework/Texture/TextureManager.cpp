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
// テクスチャを読み込む
// 戻り値としてIDが返ってくるので、以降はこのIDを使用すること
// -1が帰ってきた場合は、読み込みエラー
//------------------------------------------------
int TextureManager::LoadTexture(const char* const filename) {
  // 空きID検索
  // もし ID が検索できなかったら -1 を返す
  const int id = _SearchNotUsedID();
  assert(id != -1 && "IDが足りません");
  if (id == -1) {
    return -1;
  }

  // テクスチャのロード
  HRESULT hr = D3DXCreateTextureFromFile(pDevice_, filename, &textureList_[id]);
  // TOOD: ASSERT
  if (FAILED(hr)) {
    MessageBox(nullptr, "テクスチャロードエラー", "Error", MB_OK);
  }

  return id;
}


//------------------------------------------------
// テクスチャをセットする
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
// 空きIDを検索する
// 空きが無かった場合は-1を返す
//------------------------------------------------
int TextureManager::_SearchNotUsedID(void) {
  for (int textureID = 0; textureID < kTextureMax; ++textureID) {
    // if テクスチャがロードされていなかったら そのIDを返す
    if (!textureList_[textureID]) {
      return textureID;
    }
  }

  // エラー
  return -1;
}
