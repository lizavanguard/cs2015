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

  pos_.x = 0;
  pos_.y = 0;

  p_texture_animation_ = new TextureAnimation();
  texture_id_ = p_texture_animation_->SetAnimation(animation_event);
}

// dtor
AnimationObject::~AnimationObject() {
  delete p_texture_animation_;
}

// create
AnimationObject *AnimationObject::Create(ANIMATION_EVENT animation_event, const D3DXVECTOR3& pos, const D3DXVECTOR2& size){
  AnimationObject *obj = new AnimationObject(animation_event);
  obj->pos_ = pos;
  obj->size_ = size;
  return obj;
}

// draw
void AnimationObject::_PreProcessOfDraw(void) {
  auto p_device = DeviceHolder::Instance().GetDevice();

  p_texture_animation_ -> UpdateAnimation();

  D3DXVECTOR2 texture_uv_ = p_texture_animation_ -> GetTextureUV();
  D3DXVECTOR2 texture_uv_offset_ = p_texture_animation_->GetTextureUVOffset();

  if (move_direction_ == DIRECTION_LEFT) {
    texture_uv_.x += texture_uv_offset_.x;
    texture_uv_offset_.x *= -1;
  }

  start_uv_ = texture_uv_;
  end_uv_ = texture_uv_ + texture_uv_offset_;
}

// draw
void AnimationObject::_PostProcessOfDraw(void) {
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