//==============================================================================
//
// テクスチャマネージャ [TextureManager.h]
// Author : Shimizu Shoji
//
//==============================================================================
#pragma once
#ifndef __H_TEXTUREMANAGER_H__
#define __H_TEXTUREMANAGER_H__
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// include
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include <string>
#include <map>
#include <deque>

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// class definition
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
class TextureManager {
public:
  // ctor
  TextureManager(LPDIRECT3DDEVICE9 pDevice);

  // dtor
  ~TextureManager();

  // テクスチャを読み込む
  // 戻り値としてIDが返ってくるので、以降はこのIDを使用すること
  // -1が帰ってきた場合は、読み込みエラー
  int LoadTexture(const char* filename);

  // テクスチャをセットする
  void SetTexture(int id);

private:
  // const
  static const int kTextureMax = 100;

  // alias
  typedef std::map<std::string, int> TextureSearchMap;
  typedef std::deque<LPDIRECT3DTEXTURE9> TextureContainer;

  // property
  TextureSearchMap textureSearchMap_;
  TextureContainer textureList_;
  LPDIRECT3DDEVICE9 pDevice_;
};


#endif  // __H_TEXTUREMANAGER_H__
