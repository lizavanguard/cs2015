//==============================================================================
//
// �E���G�� [Uriel.cpp]
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
#define GRAVITY	(-10.0f)

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
  statas_ = animation_event;
  boro_gage_ = 0.0f;
  boro_gage_max_ = false;
  boro_interval_ = 0;
  charge_flag_ = false;
  runaway_timer_ = 0;
  sleep_timer_ = 0;

  // TODO
  // �X�e�[�W����X�^�[�g�ꏊ��Ⴄ
  pos_;
}

// dtor
Uriel::~Uriel() {
}

// update
void Uriel::Update(void){
  // ��ԕʂ̍X�V
  switch (statas_){
  // �X�V�Ȃ�
  case URIEL_STATAS_NONE:
    break;
  // �j���[�g�������
  case URIEL_STATAS_NEUTRAL:
    UpdateNeutral();
    break;
  // �n�C�n�C���
  case URIEL_STATAS_CRAWL:
    UpdateCrawl();
    break;
  // �W�����v���
  case URIEL_STATAS_JUMP:
    UpdateJump();
    break;
  // �\�����
  case URIEL_STATAS_RUNAWAY:
    UpdateRunaway();
    break;
  // ������
  case URIEL_STATAS_SLEEP:
    UpdateSleep();
    break;
  // �n�C�n�C(�`���[�W)���
  case URIEL_STATAS_CHARGECRAWL:
    UpdateChargeCrawl();
    break;
  // �W�����v(�`���[�W)���
  case URIEL_STATAS_CHARGEJUMP:
    UpdateChargeJump();
    break;
  // �S�[�����
  case URIEL_STATAS_GOAL:
    UpdateGoal();
    break;
  }

  // �d�͏���
  //pos_.y += GRAVITY;

  // TODO
  // �ڂ̑O���ǂȂ甽�]
  if (pos_.x + move_speed_ + size_.x / 2 > 640 ||
      pos_.x + move_speed_ - size_.x / 2 < -640){
      move_speed_ *= -1;
    }

  // �{�[���`���[�W�C���^�[�o�����Ԃ̌���
  if (boro_interval_ > 0)
    -- boro_interval_;

  // �{�[���Q�[�W�̌���
  if (!boro_gage_max_ && (boro_gage_ - URIEL_BOROGAGE_SUB_AMOUNT) > 0){
    boro_gage_ -= URIEL_BOROGAGE_SUB_AMOUNT;

    if (boro_gage_ < 0){
      boro_gage_ = 0;
    }
  }

  // �X�e�[�W�̓����蔻��
  p_stage_->CheckMapTip(&pos_, D3DXVECTOR3(50.f, 50.f, 0.f));

  if (statas_ != URIEL_STATAS_NONE){
    // �A�j���[�V�����X�V
    p_texture_animation_->UpdateAnimation();
  }
}

// draw
void Uriel::PreProccessOfDraw(void) {
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
// �A�j���[�V�����̐ݒ�
//-----------------------------------------------------------------------------
void Uriel::SetAnimaton(ANIMATION_EVENT animation_event){
  texture_id_ = p_texture_animation_->SetAnimation(animation_event);
  statas_ = animation_event;
}

//=============================================================================
// �E���G���̖ړI�n�_�ݒ�
//-----------------------------------------------------------------------------
void Uriel::SetDestPos(const D3DXVECTOR3& pos){
  if (abs(pos.x - pos_.x) < URIEL_INDUCIBLE)
    dest_position_ = pos;
}

//=============================================================================
// �{�[���`���[�W
//-----------------------------------------------------------------------------
bool Uriel::BoroChage(void){
  if (!charge_flag_ && boro_interval_ <= 0){
    SetAnimaton(ANIMATION_URIEL_CHARGECRAWL);
    charge_flag_ = true;
    boro_interval_ = URIEL_BOROCHAGE_INTERVAL;
    boro_gage_ += URIEL_BOROGAGE_ADD_AMOUNT;
    if (boro_gage_ > 100.0f){
      boro_gage_ = 100.0f;
      boro_gage_max_ = true;
    }
    return true;
  }

  return false;
}

//=============================================================================
// �j���[�g������Ԃ̍X�V
//-----------------------------------------------------------------------------
void Uriel::UpdateNeutral(void){

}

//=============================================================================
// �n�C�n�C��Ԃ̍X�V
//-----------------------------------------------------------------------------
void Uriel::UpdateCrawl(void){
  if (dest_position_ != D3DXVECTOR3(0.0f, 0.0f, 0.0f)){
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
  }

  // TODO
  // �ڂ̑O�����Ȃ�W�����v(1�}�X����)

  if (move_speed_ < 0){
    move_direction_ = DIRECTION_RIGHT;
  } else {
    move_direction_ = DIRECTION_LEFT;
  }
}

//=============================================================================
// �W�����v��Ԃ̍X�V
//-----------------------------------------------------------------------------
void Uriel::UpdateJump(void){

}

//=============================================================================
// �\����Ԃ̍X�V
//-----------------------------------------------------------------------------
void Uriel::UpdateRunaway(void){
  if (dest_position_ != D3DXVECTOR3(0.0f, 0.0f, 0.0f)){
    if (dest_position_.x - pos_.x > 1.0f){
      pos_.x += URIEL_MOVE_RUNAWAY_SPPD;
      move_speed_ = URIEL_MOVE_RUNAWAY_SPPD;
    } else if (dest_position_.x - pos_.x < -1.0f){
      pos_.x -= URIEL_MOVE_RUNAWAY_SPPD;
      move_speed_ = -URIEL_MOVE_RUNAWAY_SPPD;
    } else {
      dest_position_ = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
    }
  } else {
    pos_.x += move_speed_;
  }

  if (move_speed_ < 0){
    move_direction_ = DIRECTION_RIGHT;
  } else {
    move_direction_ = DIRECTION_LEFT;
  }

  // ��莞�Ԗ\�������疰��
  if (runaway_timer_ >= URIEL_RUNAWAY_TIME){
    SetAnimaton(ANIMATION_URIEL_SLEEP);
    runaway_timer_ = 0;
  }

  ++runaway_timer_;
}

//=============================================================================
// �����Ԃ̍X�V
//-----------------------------------------------------------------------------
void Uriel::UpdateSleep(void){
  ++ sleep_timer_;

  if (sleep_timer_ > URIEL_SLEEP_TIME){
    SetAnimaton(ANIMATION_URIEL_CRAWL);
    sleep_timer_ = 0;
    move_speed_ = URIEL_MOVE_SPPD;
  }
}

//=============================================================================
// �n�C�n�C(�`���[�W)��Ԃ̍X�V
//-----------------------------------------------------------------------------
void Uriel::UpdateChargeCrawl(void){
  // TODO
  // �ڂ̑O�����Ȃ�W�����v(�Q�}�X�܂Ŕ�ׂ�)

  // boro_interval_��0�ȉ��Ȃ�`���[�W���[�h���~�߂�
  if (boro_interval_ < 0){
    charge_flag_ = false;

    // boro_gage_max_��true�Ȃ�\��
    if (boro_gage_max_){
      SetAnimaton(ANIMATION_URIEL_RUNAWAY);
      runaway_timer_ = URIEL_RUNAWAY_TIME;
      move_speed_ = URIEL_MOVE_RUNAWAY_SPPD;
    }
  }
}

//=============================================================================
// �W�����v(�`���[�W)��Ԃ̍X�V
//-----------------------------------------------------------------------------
void Uriel::UpdateChargeJump(void){

}

//=============================================================================
// �S�[����Ԃ̍X�V
//-----------------------------------------------------------------------------
void Uriel::UpdateGoal(void){

}

// EOF