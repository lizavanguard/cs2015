//==============================================================================
//
// ’± [Butterfly.cpp]
// Author : Yuji Momoi
//
//==============================================================================
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// include
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "Butterfly.h"
#include "Application/Stage/Stage.h"
#include "Application/Object/Sang/SangManager.h"

//==============================================================================
// class implementation
//==============================================================================
// ctor
Butterfly::Butterfly(ANIMATION_EVENT animation_event,  Stage *stage) : AnimationObject(animation_event) {
  static const float kSize = 100.0f;
  size_ = D3DXVECTOR2(kSize, kSize);
  base_pos_ = D3DXVECTOR3(0, 0, 0);
  move_ = D3DXVECTOR3(0, 0, 0);
  move_.x = kButterFlyMoveSpeed;
  move_direction_ = DIRECTION_RIGHT;
  animation_time_ = 0;
  p_stage_ = stage;
  HIT_CHECK check;
  D3DXVECTOR3 map(0.f, 0.f, 0.f);
  map = p_stage_->CheckMapTip2(&D3DXVECTOR3(pos_.x, pos_.y - size_.y, pos_.z), D3DXVECTOR3(size_.x / 4, 1.0f, 0.0f), &check);
  // ‰º‚ª’n–Ê‚È‚ç
  if (check.bottom == MAP_TYPE_NORMAL){
    pos_.y = map.y + 25.0f * 1.9f;
  }

  SangManager::AddToSang(this, AnimationObject::ANIM_OBJ_TYPE_BUTTERFLY);
}

// dtor
Butterfly::~Butterfly() {
}

// update
void Butterfly::Update(void){
  if (move_direction_ == DIRECTION_RIGHT){
    if ((pos_.x + move_.x) > (base_pos_.x + kMoveAmount)){
      move_.x = -kButterFlyMoveSpeed;
    }
  } else{
    if ((pos_.x - move_.x) < (base_pos_.x - kMoveAmount)){
      move_.x = kButterFlyMoveSpeed;
    }
  }

  // Œü‚«‚Ì’²®
  if (move_.x > 0){
    move_direction_ = DIRECTION_RIGHT;
  } else if(move_.x < 0){
    move_direction_ = DIRECTION_LEFT;
  }

  pos_ += move_;

  p_texture_animation_->UpdateAnimation();
}

// draw
void Butterfly::_PreProcessOfDraw(void) {
  D3DXVECTOR2 texture_uv_ = p_texture_animation_->GetTextureUV();
  D3DXVECTOR2 texture_uv_offset_ = p_texture_animation_->GetTextureUVOffset();

  if (move_direction_ == DIRECTION_RIGHT) {
    texture_uv_.x += texture_uv_offset_.x;
    texture_uv_offset_.x *= -1;
  }

  start_uv_ = texture_uv_;
  end_uv_ = texture_uv_ + texture_uv_offset_;
}

//=============================================================================
// XYZŽ²‚É‰ÁŽZ
//-----------------------------------------------------------------------------
void Butterfly::AddPos(const D3DXVECTOR3& pos){
  if (pos_.x < pos_.x + pos.x){
    move_direction_ = DIRECTION_RIGHT;
  }
  else {
    move_direction_ = DIRECTION_LEFT;
  }
  pos_ += pos;
}

//=============================================================================
// XŽ²‚É‰ÁŽZ
//-----------------------------------------------------------------------------
void Butterfly::AddPosX(float x){
  if (x > 0){
    move_direction_ = DIRECTION_RIGHT;
  }
  else {
    move_direction_ = DIRECTION_LEFT;
  }
  pos_.x += x;
}

//=============================================================================
// À•WÝ’è
//-----------------------------------------------------------------------------
void Butterfly::SetPos(const D3DXVECTOR3& pos){
  pos_ = pos;
  base_pos_ = pos;
  HIT_CHECK check;
  D3DXVECTOR3 map(0.f, 0.f, 0.f);
  map = p_stage_->CheckMapTip2(&D3DXVECTOR3(pos.x, pos.y - size_.y, pos.z), D3DXVECTOR3(size_.x / 4, 1.0f, 0.0f), &check);
  // ‰º‚ª’n–Ê‚È‚ç
  if (check.bottom == MAP_TYPE_NORMAL){
    pos_.y = map.y + 25.0f * 1.9f;
  }
}

// EOF