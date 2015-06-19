//==============================================================================
//
// Object2D
// Author : Shimizu Shoji
//
//==============================================================================
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// include
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "Object2D.h"
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
Object2D::Object2D(const D3DXVECTOR3& pos, const D3DXVECTOR2& size, const char* p_texture_filename) {
  SetTexture(p_texture_filename);
  pos_ = pos;
  size_ = size;
}

//------------------------------------------------
// dtor
//------------------------------------------------
Object2D::~Object2D() {
}

//------------------------------------------------
// Draw‚Ì“à•”ˆ—
//------------------------------------------------
void Object2D::_Draw(void) {
  auto p_device = DeviceHolder::Instance().GetDevice();

  // turn lighting off
  p_device->SetRenderState(D3DRS_LIGHTING, FALSE);

  // vertices
  const D3DXVECTOR2 size_half = size_ * 0.5f;
  Vertex2D data[] = {
    {D3DXVECTOR3(pos_.x - size_half.x, pos_.y - size_half.y, pos_.z), 1.0f, color_, D3DXVECTOR2(start_uv_.x, start_uv_.y)},  // lt
    {D3DXVECTOR3(pos_.x + size_half.x, pos_.y - size_half.y, pos_.z), 1.0f, color_, D3DXVECTOR2(  end_uv_.x, start_uv_.y)},  // rt
    {D3DXVECTOR3(pos_.x - size_half.x, pos_.y + size_half.y, pos_.z), 1.0f, color_, D3DXVECTOR2(start_uv_.x,   end_uv_.y)},  // lb
    {D3DXVECTOR3(pos_.x + size_half.x, pos_.y + size_half.y, pos_.z), 1.0f, color_, D3DXVECTOR2(  end_uv_.x,   end_uv_.y)},  // rb
  };

  // set texture
  TextureManagerHolder::Instance().GetTextureManager().SetTexture(texture_id_);

  // set fvf
  p_device->SetFVF(kVertexFVF2D);

  // draw
  p_device->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, data, sizeof(Vertex2D));
}
