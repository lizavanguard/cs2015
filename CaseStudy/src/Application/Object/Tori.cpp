//==============================================================================
//
// 鳥 [Tori.cpp]
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
#include "Application/Stage/Stage.h"

//==============================================================================
// class implementation
//==============================================================================
// ctor
Tori::Tori(ANIMATION_EVENT animation_event, Uriel *uriel, Stage *stage) : AnimationObject(animation_event) {
  move_speed_ = FLY_TO_TOP_SPEED;
  motion_timer_ = 0;
  static const float kSize = 100.0f;
  size_ = D3DXVECTOR2(kSize, kSize);
  p_uriel_ = uriel;
  hit_flag_ = false;
  happy_flag_ = false;
  animation_time_ = 0;
  p_stage_ = stage;
  pos_ = stage->GetGoalMaptip();
  HIT_CHECK check;
  D3DXVECTOR3 map(0.f, 0.f, 0.f);
  map = p_stage_->CheckMapTip2(&D3DXVECTOR3(pos_.x, pos_.y - size_.y, pos_.z), D3DXVECTOR3(size_.x / 4, 1.0f, 0.0f), &check);
  // 下が地面なら
  if (check.bottom == MAP_TYPE_NORMAL){
    pos_.y = map.y + 25.0f * 1.9f;
  }

}

// dtor
Tori::~Tori() {
}

// update
void Tori::Update(void){
  // アニメーション更新
  p_texture_animation_->UpdateAnimation();

  if (hit_flag_ && happy_flag_){
    ++motion_timer_;
    if (move_speed_ >= 0.2f){
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

    if (motion_timer_ >= TIME_TO_FLY_TO_BECOME_GEALTHY){
      happy_flag_ = true;
      move_speed_ = 0;
      p_texture_animation_->SetAnimation(ANIMATION_TORI_FLY_TOP);
      animation_time_ = p_texture_animation_->GetAnimationChangeTime();
      motion_timer_ = -animation_time_;
    }
  } else {
    if (p_uriel_->CheckHit(pos_, size_)) {
      hit_flag_ = true;
      p_texture_animation_->SetAnimation(ANIMATION_TORI_HAPPY);
    }
  }
}

// draw
void Tori::_PreProcessOfDraw(void) {
  D3DXVECTOR2 texture_uv_ = p_texture_animation_->GetTextureUV();
  D3DXVECTOR2 texture_uv_offset_ = p_texture_animation_->GetTextureUVOffset();

  if (move_direction_ == DIRECTION_LEFT) {
    texture_uv_.x += texture_uv_offset_.x;
    texture_uv_offset_.x *= -1;
  }

  start_uv_ = texture_uv_;
  end_uv_ = texture_uv_ + texture_uv_offset_;
}

//=============================================================================
// XYZ軸に加算
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
// X軸に加算
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