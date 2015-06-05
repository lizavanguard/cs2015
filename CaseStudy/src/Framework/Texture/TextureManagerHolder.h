//==============================================================================
//
// テクスチャマネージャホルダー [TextureManagerHolder.h]
// Author : Shimizu Shoji
//
//==============================================================================
#pragma once
#ifndef __H_TEXTUREMANAGERHOLDER_H__
#define __H_TEXTUREMANAGERHOLDER_H__
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// include
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "Framework/Texture/TextureManager.h"
#include "Framework/Utility/SingletonHolder.hpp"


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// class definition
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
class _TextureManagerHolder {
public:
  // ctor
  _TextureManagerHolder() {}

  // dtor
  ~_TextureManagerHolder() {}

  // get
  TextureManager& GetTextureManager(void) const { return *pTextureManager_; }

  // set
  void SetTextureManager(TextureManager* pTextureManager) { pTextureManager_ = pTextureManager; }

private:
  TextureManager* pTextureManager_;
};

// singleton
typedef liza::generic::SingletonHolder<_TextureManagerHolder> TextureManagerHolder;


#endif // __H_TEXTUREMANAGERHOLDER_H__
