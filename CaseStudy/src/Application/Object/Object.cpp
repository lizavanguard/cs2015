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
Object::Object() {
}

//------------------------------------------------
// dtor
//------------------------------------------------
Object::~Object() {
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
    {D3DXVECTOR3(-half_x, size_.y, 0.0f), color_, D3DXVECTOR2(start_uv_.x, start_uv_.y)},  // lt
    {D3DXVECTOR3(+half_x, size_.y, 0.0f), color_, D3DXVECTOR2(  end_uv_.x, start_uv_.y)},  // rt
    {D3DXVECTOR3(-half_x,    0.0f, 0.0f), color_, D3DXVECTOR2(start_uv_.x,   end_uv_.y)},  // lb
    {D3DXVECTOR3(+half_x,    0.0f, 0.0f), color_, D3DXVECTOR2(  end_uv_.x,   end_uv_.y)},  // rb
  };

  // WVP
  D3DXMATRIX mtx_world;
  D3DXMatrixTranslation(&mtx_world, pos_.x, pos_.y, pos_.z);
  p_device->SetTransform(D3DTS_WORLD, &mtx_world);

  // set texture
  TextureManagerHolder::Instance().GetTextureManager().SetTexture(texture_id_);

  // set fvf
  p_device->SetFVF(kVertexFVF3D);

  // draw
  p_device->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, data, sizeof(Vertex3D));
}
