//==============================================================================
//
// アニメーションオブジェクト [AnimationObject.cpp]
// Author : Yuji Momoi
//
//==============================================================================
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// include
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "AnimationObject.h"
#include "Framework/DirectXHelper/DeviceHolder.h"
#include "Framework/DirectXHelper/DirectXConst.h"
#include "Framework/Texture/TextureManagerHolder.h"
#include "TextureAnimation.h"

//==============================================================================
// class implementation
//==============================================================================
// ctor
AnimationObject::AnimationObject(ANIMATION_EVENT animation_event) : Object() {
  p_texture_animation_ = NULL;
  move_direction_ = DIRECTION_RIGHT;
  auto p_device = DeviceHolder::Instance().GetDevice();

  pos_.x = 640;
  pos_.y = 360;

  // HACK:
  p_device->CreateVertexBuffer(
    sizeof(Vertex2D) * 4,
    D3DUSAGE_WRITEONLY,
    kVertexFVF2D,
    D3DPOOL_MANAGED,
    &p_vertex_buffer_,
    nullptr);

  p_texture_animation_ = new TextureAnimation();
  texture_id_ = p_texture_animation_->SetAnimation(animation_event);
}

// dtor
AnimationObject::~AnimationObject() {
  p_vertex_buffer_->Release();

  delete p_texture_animation_;
}

// create
AnimationObject *AnimationObject::Create(ANIMATION_EVENT animation_event, const D3DXVECTOR3& pos, const D3DXVECTOR2& size){
  AnimationObject *obj = new AnimationObject(animation_event);
  obj->SetPos(pos);
  obj->SetSize(size);

  return obj;
}

// draw
void AnimationObject::Draw(void) {
  auto p_device = DeviceHolder::Instance().GetDevice();

  p_texture_animation_ -> UpdateAnimation();

  Vertex2D data[] ={
    {D3DXVECTOR3(pos_.x - size_.x / 2, pos_.y - size_.y / 2, 0.0f), 1.0f, 0xffffffff, D3DXVECTOR2(0.0f, 0.0f)},
    {D3DXVECTOR3(pos_.x + size_.x / 2, pos_.y - size_.y / 2, 0.0f), 1.0f, 0xffffffff, D3DXVECTOR2(1.0f, 0.0f)},
    {D3DXVECTOR3(pos_.x - size_.x / 2, pos_.y + size_.y / 2, 0.0f), 1.0f, 0xffffffff, D3DXVECTOR2(0.0f, 1.0f)},
    {D3DXVECTOR3(pos_.x + size_.x / 2, pos_.y + size_.y / 2, 0.0f), 1.0f, 0xffffffff, D3DXVECTOR2(1.0f, 1.0f)},
  };

  D3DXVECTOR2 texture_uv_ = p_texture_animation_ -> GetTextureUV();
  D3DXVECTOR2 texture_uv_offset_ = p_texture_animation_->GetTextureUVOffset();

  if (move_direction_ == DIRECTION_LEFT) {
    texture_uv_.x += texture_uv_offset_.x;
    texture_uv_offset_.x *= -1;
  }

  data[0].tex = D3DXVECTOR2(texture_uv_.x, texture_uv_.y);
  data[1].tex = D3DXVECTOR2(texture_uv_.x + texture_uv_offset_.x, texture_uv_.y);
  data[2].tex = D3DXVECTOR2(texture_uv_.x, texture_uv_.y + texture_uv_offset_.y);
  data[3].tex = D3DXVECTOR2(texture_uv_.x + texture_uv_offset_.x, texture_uv_.y + texture_uv_offset_.y);

  TextureManagerHolder::Instance().GetTextureManager().SetTexture(texture_id_);

  p_device->SetFVF(kVertexFVF2D);

  p_device->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, data, sizeof(Vertex2D));
}

//=============================================================================
// アニメーションの設定
//-----------------------------------------------------------------------------
void AnimationObject::SetAnimaton(ANIMATION_EVENT animation_event){
  texture_id_ = p_texture_animation_->SetAnimation(animation_event);
}

//=============================================================================
// XYZ軸に加算
//-----------------------------------------------------------------------------
void AnimationObject::AddPos(const D3DXVECTOR3& pos){
  if (pos_.x < pos_.x + pos.x){
    move_direction_ = DIRECTION_RIGHT;
  } else {
    move_direction_ = DIRECTION_LEFT;
  }
  pos_ += pos;
}

//=============================================================================
// X軸に加算
//-----------------------------------------------------------------------------
void AnimationObject::AddPosX(float x){
  if (x > 0){
    move_direction_ = DIRECTION_RIGHT;
  } else {
    move_direction_ = DIRECTION_LEFT;
  }
  pos_.x += x;
}

// EOF