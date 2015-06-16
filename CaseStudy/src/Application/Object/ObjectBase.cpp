//==============================================================================
//
// Object Base
// Author : Shimizu Shoji
//
//==============================================================================
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// include
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "ObjectBase.h"
#include "Framework/Texture/TextureManagerHolder.h"

//==============================================================================
// class implementation
//==============================================================================
//------------------------------------------------
// ctor
//------------------------------------------------
ObjectBase::ObjectBase()
    : pos_(D3DXVECTOR3(0.0f, 0.0f, 0.0f))
    , rot_(0.0f)
    , size_(D3DXVECTOR2(0.0f, 0.0f))
    , color_(0xffffffff)
    , start_uv_(D3DXVECTOR2(0.0f, 0.0f))
    , end_uv_(D3DXVECTOR2(1.0f, 1.0f))
    , is_alive_(true)
    , texture_id_(-1) {
  static const float kSizeX = 128.0f;
  static const float kSizeY = 128.0f;
  size_ = D3DXVECTOR2(kSizeX, kSizeY);
}

//------------------------------------------------
// dtor
//------------------------------------------------
ObjectBase::~ObjectBase() {
}

//------------------------------------------------
// Draw
//------------------------------------------------
void ObjectBase::Draw(void) {
  _PreProcessOfDraw();
  _Draw();
  _PostProcessOfDraw();
}

//------------------------------------------------
// SetTexture
//------------------------------------------------
void ObjectBase::SetTexture(const char* texture_name) {
  texture_id_ = TextureManagerHolder::Instance().GetTextureManager().LoadTexture(texture_name);
}
