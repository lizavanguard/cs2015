//==============================================================================
//
// š [Tori.cpp]
// Author : Yuji Momoi
//
//==============================================================================
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// include
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "Tori.h"
#include "Framework/DirectXHelper/DeviceHolder.h"
#include "Framework/DirectXHelper/DirectXConst.h"
#include "Framework/Texture/TextureManagerHolder.h"

//==============================================================================
// class implementation
//==============================================================================
// ctor
Tori::Tori(ANIMATION_EVENT animation_event, Uriel *uriel) : AnimationObject(animation_event) {
  move_speed_ = FLY_TO_TOP_SPEED;
  motion_timer_ = 0;
  static const float kSize = 100.0f;
  size_ = D3DXVECTOR2(kSize, kSize);
  p_uriel_ = uriel;
  hit_flag_ = false;
  happy_flag_ = false;
  animation_time_ = 0;
}

// dtor
Tori::~Tori() {
}

// update
void Tori::Update(void){
  // Aj[VXV
  p_texture_animation_->UpdateAnimation();

  if (hit_flag_ && happy_flag_){
    ++motion_timer_;
    if (move_speed_ <= 0.2f){
      pos_.y += move_speed_;
    }
    move_speed_ -= (FLY_TO_TOP_SPEED / (animation_time_ * 2));

    if (motion_timer_ >= animation_time_){
      motion_timer_ = -animation_time_;
    }
    else if (motion_timer_ == 0){
      move_speed_ = FLY_TO_TOP_SPEED;
    }

  } else if (hit_flag_ && !happy_flag_){
    ++motion_timer_;

    if (motion_timer_ >= 20){
      happy_flag_ = true;
      move_speed_ = 0;
      p_texture_animation_->SetAnimation(ANIMATION_TORI_FLY_TOP);
      animation_time_ = p_texture_animation_->GetAnimationChangeTime();
      motion_timer_ = -animation_time_;
    }
  } else {
    D3DXVECTOR3 uriel_pos_ = p_uriel_->GetPos();
    D3DXVECTOR2 uriel_size_ = p_uriel_->GetSize();
    if ((pos_.x + size_.x / 2) > (uriel_pos_.x - uriel_size_.x / 2) &&
      (pos_.x - size_.x / 2) < (uriel_pos_.x - uriel_size_.x / 2)){
      hit_flag_ = true;
      p_texture_animation_->SetAnimation(ANIMATION_TORI_HAPPY);
    }
  }
}

// draw
void Tori::PreProccessOfDraw(void) {
  D3DXVECTOR2 texture_uv_ = p_texture_animation_->GetTextureUV();
  D3DXVECTOR2 texture_uv_offset_ = p_texture_animation_->GetTextureUVOffset();

  if (move_direction_ == DIRECTION_LEFT) {
    texture_uv_.x += texture_uv_offset_.x;
    texture_uv_offset_.x *= -1;
  }

  SetStartUV(D3DXVECTOR2(texture_uv_));
  SetEndUV(D3DXVECTOR2(texture_uv_ + texture_uv_offset_));
}

//=============================================================================
// XYZ˛ÉÁZ
//-----------------------------------------------------------------------------
void Tori::AddPos(const D3DXVECTOR3& pos){
  if (pos_.x < pos_.x + pos.x){
    move_direction_ = DIRECTION_RIGHT;
  }
  else {
    move_direction_ = DIRECTION_LEFT;
  }
  pos_ += pos;
}

//=============================================================================
// X˛ÉÁZ
//-----------------------------------------------------------------------------
void Tori::AddPosX(float x){
  if (x > 0){
    move_direction_ = DIRECTION_RIGHT;
  }
  else {
    move_direction_ = DIRECTION_LEFT;
  }
  pos_.x += x;
}

// EOF