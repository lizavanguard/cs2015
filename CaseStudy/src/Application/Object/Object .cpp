//==============================================================================
//
// オブジェクト [Object.cpp]
// Author : Shimizu Shoji
//
// 頂点バッファは切り分ける
//
//==============================================================================
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// include
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "Object.h"
#include "Framework/DirectXHelper/DeviceHolder.h"
#include "Framework/DirectXHelper/DirectXConst.h"
#include "Framework/GameWindow/GameDirectX.h"
#include "Framework/Texture/TextureManagerHolder.h"

//==============================================================================
// class implementation
//==============================================================================
// ctor
Object::Object()
  : pos_(D3DXVECTOR3(0.0f, 0.0f, 0.0f))
  , rot_(D3DXVECTOR2(0.0f, 0.0f))
  , size_(D3DXVECTOR2(0.0f, 0.0f))
  , is_alive_(true)
  , texture_id_(-1) {
  static const float kSize = 45.0f;
  size_ = D3DXVECTOR2(kSize, kSize);
}

// dtor
Object::~Object() {
}

// draw
void Object::Draw(void) {
  auto p_device = DeviceHolder::Instance().GetDevice();

  Vertex2D data[] ={
    { D3DXVECTOR3(pos_.x - size_.x / 2, pos_.y - size_.y / 2, 0.0f), 1.0f, 0xffffffff, D3DXVECTOR2(0.0f, 0.0f) },
    { D3DXVECTOR3(pos_.x + size_.x / 2, pos_.y - size_.y / 2, 0.0f), 1.0f, 0xffffffff, D3DXVECTOR2(1.0f, 0.0f) },
    { D3DXVECTOR3(pos_.x - size_.x / 2, pos_.y + size_.y / 2, 0.0f), 1.0f, 0xffffffff, D3DXVECTOR2(0.0f, 1.0f) },
    { D3DXVECTOR3(pos_.x + size_.x / 2, pos_.y + size_.y / 2, 0.0f), 1.0f, 0xffffffff, D3DXVECTOR2(1.0f, 1.0f) },
  };

  //p_device->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
  TextureManagerHolder::Instance().GetTextureManager().SetTexture(texture_id_);

  p_device->SetFVF(kVertexFVF2D);

  p_device->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, data, sizeof(Vertex2D));
}

// setTexture
void Object::SetTexture(char* texture_name){
  texture_id_ = TextureManagerHolder::Instance().GetTextureManager().LoadTexture(texture_name);
}