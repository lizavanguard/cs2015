//==============================================================================
//
// ウリエル [Uriel.cpp]
// Author : Yuji Momoi
//
//==============================================================================
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// include
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "Uriel.h"
#include "Framework/DirectXHelper/DeviceHolder.h"
#include "Framework/DirectXHelper/DirectXConst.h"
#include "Framework/Texture/TextureManagerHolder.h"
#include "Application/Stage/Stage.h"
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// define
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#define GRAVITY	(10.0f)

//==============================================================================
// class implementation
//==============================================================================
// ctor
Uriel::Uriel(ANIMATION_EVENT animation_event, Stage* stage) : AnimationObject(animation_event) {
  dest_position_ = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
  move_speed_ = URIEL_MOVE_SPPD;
  p_stage_ = stage;
  static const float kSize = 100.0f;
  size_ = D3DXVECTOR2(kSize, kSize);
  statas_ = URIEL_STATAS_NONE;
}

// dtor
Uriel::~Uriel() {
}

// update
void Uriel::Update(void){
  pos_.y += GRAVITY;
  if (dest_position_ != D3DXVECTOR3(0.0f,0.0f,0.0f)){
    if (dest_position_.x - pos_.x > 1.0f){
      pos_.x += URIEL_MOVE_SPPD;
      move_speed_ = URIEL_MOVE_SPPD;
    } else if (dest_position_.x - pos_.x < -1.0f){
      pos_.x -= URIEL_MOVE_SPPD;
      move_speed_ = -URIEL_MOVE_SPPD;
    } else {
      dest_position_ = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
    }
  } else {
    pos_.x += move_speed_;

    if (pos_.x + move_speed_ > 1280 ||
      pos_.x + move_speed_ < 0){
      move_speed_ *= -1;
    }
  }

  if (move_speed_ < 0){
    move_direction_ = DIRECTION_RIGHT;
  } else {
    move_direction_ = DIRECTION_LEFT;
  }
  p_stage_->CheckMapTip(&pos_,D3DXVECTOR3(50.f,50.f,0.f));

  // アニメーション更新
  p_texture_animation_->UpdateAnimation();
}

// draw
void Uriel::Draw(void) {
  auto p_device = DeviceHolder::Instance().GetDevice();

  Vertex2D data[] = {
    { D3DXVECTOR3(pos_.x - size_.x / 2, pos_.y - size_.y / 2, 0.0f), 1.0f, 0xffffffff, D3DXVECTOR2(0.0f, 0.0f) },
    { D3DXVECTOR3(pos_.x + size_.x / 2, pos_.y - size_.y / 2, 0.0f), 1.0f, 0xffffffff, D3DXVECTOR2(1.0f, 0.0f) },
    { D3DXVECTOR3(pos_.x - size_.x / 2, pos_.y + size_.y / 2, 0.0f), 1.0f, 0xffffffff, D3DXVECTOR2(0.0f, 1.0f) },
    { D3DXVECTOR3(pos_.x + size_.x / 2, pos_.y + size_.y / 2, 0.0f), 1.0f, 0xffffffff, D3DXVECTOR2(1.0f, 1.0f) },
  };

  D3DXVECTOR2 texture_uv_ = p_texture_animation_->GetTextureUV();
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
void Uriel::SetAnimaton(ANIMATION_EVENT animation_event){
  texture_id_ = p_texture_animation_->SetAnimation(animation_event);
}

void Uriel::SetDestPos(const D3DXVECTOR3& pos){
  if (abs(pos.x - pos_.x) < URIEL_INDUCIBLE)
  dest_position_ = pos;
}

//=============================================================================
// ニュートラル状態の更新
//-----------------------------------------------------------------------------

//=============================================================================
// ハイハイ状態の更新
//-----------------------------------------------------------------------------

//=============================================================================
// ジャンプ状態の更新
//-----------------------------------------------------------------------------

//=============================================================================
// 暴走状態の更新
//-----------------------------------------------------------------------------

//=============================================================================
// 眠り状態の更新
//-----------------------------------------------------------------------------

//=============================================================================
// チャージ状態の更新
//-----------------------------------------------------------------------------

//=============================================================================
// ゴール状態の更新
//-----------------------------------------------------------------------------

// EOF