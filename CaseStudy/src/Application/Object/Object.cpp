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
//------------------------------------------------
// ctor
//------------------------------------------------
Object::Object()
    : pos_(D3DXVECTOR3(0.0f, 0.0f, 0.0f))
    , rot_(D3DXVECTOR2(0.0f, 0.0f))
    , size_(D3DXVECTOR2(0.0f, 0.0f))
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
Object::~Object() {
}

//------------------------------------------------
// Draw
//------------------------------------------------
void Object::Draw(void) {
  PreProccessOfDraw();
  _Draw();
  PostProcessOfDraw();
}

//------------------------------------------------
// SetTexture
//------------------------------------------------
void Object::SetTexture(char* texture_name){
  texture_id_ = TextureManagerHolder::Instance().GetTextureManager().LoadTexture(texture_name);
}

//------------------------------------------------
// Drawの内部処理
//------------------------------------------------
void Object::_Draw(void) {
  auto p_device = DeviceHolder::Instance().GetDevice();

  // turn lighting off
  p_device->SetRenderState(D3DRS_LIGHTING, FALSE);

  // vertices
  const float half_x = size_.x * 0.5f;
  Vertex3D data[] = {
    {D3DXVECTOR3(-half_x, size_.y, 0.0f), 0xffffffff, D3DXVECTOR2(start_uv_.x, start_uv_.y)},  // lt
    {D3DXVECTOR3(+half_x, size_.y, 0.0f), 0xffffffff, D3DXVECTOR2(  end_uv_.x, start_uv_.y)},  // rt
    {D3DXVECTOR3(-half_x,    0.0f, 0.0f), 0xffffffff, D3DXVECTOR2(start_uv_.x,   end_uv_.y)},  // lb
    {D3DXVECTOR3(+half_x,    0.0f, 0.0f), 0xffffffff, D3DXVECTOR2(  end_uv_.x,   end_uv_.y)},  // rb
  };

  // WVP
  D3DXMATRIX mtx_world;
  D3DXMatrixTranslation(&mtx_world, pos_.x, pos_.y, pos_.z);
  p_device->SetTransform(D3DTS_WORLD, &mtx_world);

  D3DXMATRIX mtx_view;
  D3DXMatrixLookAtLH(&mtx_view, &D3DXVECTOR3(0, 0, -1), &D3DXVECTOR3(0, 0, 0), &D3DXVECTOR3(0, 1, 0));
  p_device->SetTransform(D3DTS_VIEW, &mtx_view);

  D3DXMATRIX mtx_projection;
  D3DXMatrixOrthoLH(&mtx_projection, 1280.0f, 720.0f, 0.0f, 10.0f);
  p_device->SetTransform(D3DTS_PROJECTION, &mtx_projection);

  // set texture
  TextureManagerHolder::Instance().GetTextureManager().SetTexture(texture_id_);

  // set fvf
  p_device->SetFVF(kVertexFVF3D);

  // draw
  p_device->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, data, sizeof(Vertex3D));
}
