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
#define GRAVITY	(-0.49f)

//==============================================================================
// class implementation
//==============================================================================
// ctor
Uriel::Uriel(ANIMATION_EVENT animation_event, Stage* stage) : AnimationObject(animation_event) {
  dest_position_ = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
  move_ = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
  move_.x = URIEL_MOVE_SPPD;
  jump_before_pos_ = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
  p_stage_ = stage;
  static const float kSize = 100.0f;
  size_ = D3DXVECTOR2(kSize, kSize);
  boro_gage_ = 0.0f;
  boro_gage_max_ = false;
  boro_interval_ = 0;
  charge_flag_ = false;
  runaway_timer_ = 0;
  sleep_timer_ = 0;
  old_position_ = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

  // �X�e�[�W����X�^�[�g�ꏊ��Ⴄ
  pos_ = stage->GetStartMaptip();

  SetAnimaton(animation_event);
}

// dtor
Uriel::~Uriel() {
}

// update
void Uriel::Update(void){
  // �d�͏���
  move_.y += GRAVITY;

  // ��ԕʂ̍X�V
  switch (status_){
  // �X�V�Ȃ�
  case URIEL_STATUS_NONE:
    break;
  // �j���[�g�������
  case URIEL_STATUS_NEUTRAL:
    UpdateNeutral();
    break;
  // �n�C�n�C���
  case URIEL_STATUS_CRAWL:
    UpdateCrawl();
    break;
  // �W�����v���
  case URIEL_STATUS_JUMP:
    UpdateJump();
    break;
  // �\�����
  case URIEL_STATUS_RUNAWAY:
    UpdateRunaway();
    break;
  // ������
  case URIEL_STATUS_SLEEP:
    UpdateSleep();
    break;
  // �n�C�n�C(�`���[�W)���
  case URIEL_STATUS_CHARGECRAWL:
    UpdateChargeCrawl();
    break;
  // �W�����v(�`���[�W)���
  case URIEL_STATUS_CHARGEJUMP:
    UpdateChargeJump();
    break;
  // �S�[�����
  case URIEL_STATUS_GOAL:
    UpdateGoal();
    break;
  }

  // �����̒���
  if (move_.x > 0){
    move_direction_ = DIRECTION_RIGHT;
  } else {
    move_direction_ = DIRECTION_LEFT;
  }

  // �ړ�
  pos_ += move_;

  // TODO (���󊮂؂��ł͂Ȃ�)
  // �ڂ̑O���ǂȂ甽�]
  HIT_CHECK check;
  D3DXVECTOR3 map(0.f, 0.f, 0.f);
  if (move_direction_ == DIRECTION_LEFT){
    map = p_stage_->CheckMapTip(&D3DXVECTOR3(pos_.x + size_.x/2,pos_.y,pos_.z), D3DXVECTOR3(size_.x / 4, 1.0f, 0.0f), &check);
    if (/*check.left == MAP_TYPE_NORMAL ||*/
      check.left == -1){
      move_.x *= -1;
    }
  } else {
    map = p_stage_->CheckMapTip(&pos_, D3DXVECTOR3(size_.x / 4, 1.0f, 0.0f), &check);
    if (/*check.right == MAP_TYPE_NORMAL ||*/
      check.right == -1){
      move_.x *= -1;
    }
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
  if (status_ != URIEL_STATUS_NONE){
    // �A�j���[�V�����X�V
    p_texture_animation_->UpdateAnimation();
  }
}

// draw
void Uriel::PreProccessOfDraw(void) {
  D3DXVECTOR2 texture_uv_ = p_texture_animation_->GetTextureUV();
  D3DXVECTOR2 texture_uv_offset_ = p_texture_animation_->GetTextureUVOffset();

  if (move_direction_ == DIRECTION_RIGHT) {
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
  status_ = animation_event;
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
    if (dest_position_.x - pos_.x > URIEL_MOVE_SPPD){
      move_.x = URIEL_MOVE_SPPD;
    } else if (dest_position_.x - pos_.x < -URIEL_MOVE_SPPD){
      move_.x = -URIEL_MOVE_SPPD;
    } else {
      dest_position_ = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
    }
  }

  // �n�ʂƂ̓����蔻��
  HIT_CHECK check;
  D3DXVECTOR3 map(0.f, 0.f, 0.f);
  map = p_stage_->CheckMapTip(&pos_, D3DXVECTOR3(size_.x / 4, 1.0f, 0.0f), &check);

  // �����n�ʂŖڂ̑O���o���u���b�N�Ȃ�
  if (check.center == MAP_TYPE_NORMAL && check.bottom == MAP_TYPE_NORMAL){
    //pos_.y = map.y + 25.0f * 1.9f + 100.0f;
  }
  // �����n�ʂȂ�
  if (check.center == MAP_TYPE_NORMAL){
      pos_.y = map.y + 25.0f * 1.9f;
      move_.y = 0;
  }

  // �W�����v���邩�`�F�b�N���ăW�����v�ł���Ȃ�W�����v
  if (JumpCheck()){
    SetAnimaton(ANIMATION_URIEL_JUMP);
    D3DXVECTOR2 vector = JumpAngleSeek(50.0f, 150.0f, GRAVITY);
    move_.x = vector.x;
    move_.y = vector.y;
    // �W�����v�O�̍��W��ۑ�
    jump_before_pos_ = pos_;
  }
}

//=============================================================================
// �W�����v��Ԃ̍X�V
//-----------------------------------------------------------------------------
void Uriel::UpdateJump(void){
  // ���ׂ鋗���̌��E�Œn�ʂ�����������
  if (jump_before_pos_.y > pos_.y){
    //move_.x = 0.0f;
  }
  // �n�ʂƂ̓����蔻��
  HIT_CHECK check;
  D3DXVECTOR3 map(0.f, 0.f, 0.f);
  map = p_stage_->CheckMapTip(&pos_, D3DXVECTOR3(size_.x / 4, 1.0f, 0.0f), &check);
  if (check.center == MAP_TYPE_NORMAL){
    SetAnimaton(ANIMATION_URIEL_CRAWL);
    move_.x = URIEL_MOVE_SPPD * (move_.x / abs(move_.x));
  }
}

//=============================================================================
// �\����Ԃ̍X�V
//-----------------------------------------------------------------------------
void Uriel::UpdateRunaway(void){
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
    move_.x = URIEL_MOVE_SPPD;
  }
}

//=============================================================================
// �n�C�n�C(�`���[�W)��Ԃ̍X�V
//-----------------------------------------------------------------------------
void Uriel::UpdateChargeCrawl(void){
  if (dest_position_ != D3DXVECTOR3(0.0f, 0.0f, 0.0f)){
    if (dest_position_.x - pos_.x > URIEL_MOVE_SPPD){
      move_.x = URIEL_MOVE_SPPD;
    } else if (dest_position_.x - pos_.x < -URIEL_MOVE_SPPD){
      move_.x = -URIEL_MOVE_SPPD;
    } else {
      dest_position_ = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
    }
  }

  // �n�ʂƂ̓����蔻��
  HIT_CHECK check;
  D3DXVECTOR3 map(0.f, 0.f, 0.f);
  map = p_stage_->CheckMapTip(&pos_, D3DXVECTOR3(size_.x / 4, 1.0f, 0.0f), &check);

  // �����n�ʂŖڂ̑O���o���u���b�N�Ȃ�
  if (check.center == MAP_TYPE_NORMAL && check.bottom == MAP_TYPE_NORMAL){
    //pos_.y = map.y + 25.0f * 1.9f + 100.0f;
  }
  // �����n�ʂȂ�
  if (check.center == MAP_TYPE_NORMAL){
      pos_.y = map.y + 25.0f * 1.9f;
      move_.y = 0;
  }

  // �W�����v���邩�`�F�b�N���ăW�����v�ł���Ȃ�W�����v
  if (JumpCheck()){
    SetAnimaton(ANIMATION_URIEL_JUMP);
    D3DXVECTOR2 vector = JumpAngleSeek(50.0f, 250.0f, GRAVITY);
    move_.x = vector.x;
    move_.y = vector.y;
    // �W�����v�O�̍��W��ۑ�
    jump_before_pos_ = pos_;
  }

  // boro_interval_��0�ȉ��Ȃ�`���[�W���[�h���~�߂�
  if (boro_interval_ <= 0){
    charge_flag_ = false;

    // boro_gage_max_��true�Ȃ�\��
    if (boro_gage_max_){
      SetAnimaton(ANIMATION_URIEL_RUNAWAY);
      runaway_timer_ = URIEL_RUNAWAY_TIME;
      move_.x = URIEL_MOVE_RUNAWAY_SPPD;
    } else {
      // �ʏ�ɖ߂�
      SetAnimaton(ANIMATION_URIEL_CRAWL);
      move_.x = URIEL_MOVE_SPPD;
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

//=============================================================================
// �W�����v�ł��邩�̃`�F�b�N
//-----------------------------------------------------------------------------
bool Uriel::JumpCheck(void){
  switch (status_)
  {
  case URIEL_STATUS_CRAWL:
    return CrawlJumpCheck();
    break;
  case URIEL_STATUS_CHARGECRAWL:
    return ChargeCrawlJumpCheck();
    break;
  default:
    return false;
    break;
  }
}

//=============================================================================
// �n�C�n�C��ԂŃW�����v�ł��邩�̃`�F�b�N
//-----------------------------------------------------------------------------
bool Uriel::CrawlJumpCheck(void){
  HIT_CHECK check;
  p_stage_->CheckMapTip(&pos_, D3DXVECTOR3(size_.x / 4, 1.0f, 0.0f), &check);

  if (check.center == MAP_TYPE_NORMAL){
    // �E�ɐi��ł�ꍇ
    if (move_direction_ == DIRECTION_RIGHT){
      if (check.right == 0){
        p_stage_->CheckMapTip(&D3DXVECTOR3(pos_.x + size_.x, pos_.y, pos_.z),
                               D3DXVECTOR3(size_.x / 4, 1.0f, 0.0f), &check);
        if (check.right == MAP_TYPE_NORMAL){
          return true;
        }
      }
    }
    // ���ɐi��ł�ꍇ
    else if (move_direction_ == DIRECTION_LEFT){
      if (check.left == 0){
        p_stage_->CheckMapTip(&D3DXVECTOR3(pos_.x - size_.x, pos_.y, pos_.z),
                               D3DXVECTOR3(size_.x / 4, 1.0f, 0.0f), &check);
        if (check.left == MAP_TYPE_NORMAL){
          return true;
        }
      }
    }
  }
  return false;
}

//=============================================================================
// �`���[�W�n�C�n�C��ԂŃW�����v�ł��邩�̃`�F�b�N
//-----------------------------------------------------------------------------
bool Uriel::ChargeCrawlJumpCheck(void){
  HIT_CHECK check;
  p_stage_->CheckMapTip(&pos_, D3DXVECTOR3(size_.x / 4, 1.0f, 0.0f), &check);

  if (check.center == MAP_TYPE_NORMAL){
    // �E�ɐi��ł�ꍇ
    if (move_direction_ == DIRECTION_RIGHT){
      if (check.right == 0){
        p_stage_->CheckMapTip(&D3DXVECTOR3(pos_.x + size_.x * 2, pos_.y, pos_.z),
                               D3DXVECTOR3(size_.x / 4, 1.0f, 0.0f), &check);
        if (check.center == MAP_TYPE_NONE && check.right == MAP_TYPE_NORMAL){
          return true;
        }
      }
    }
    // ���ɐi��ł�ꍇ
    else if (move_direction_ == DIRECTION_LEFT){
      if (check.left == 0){
        p_stage_->CheckMapTip(&D3DXVECTOR3(pos_.x - size_.x, pos_.y, pos_.z),
                               D3DXVECTOR3(size_.x / 4, 1.0f, 0.0f), &check);
        if (check.left == MAP_TYPE_NORMAL){
          return true;
        }
      }
    }
  }
  return false;
}

//=============================================================================
// �W�����v���邽�����Ƌ����Ƃ�����d�͂�n���Έړ��ʂ��Ԃ��Ă���(2D�p)
//-----------------------------------------------------------------------------
D3DXVECTOR2 Uriel::JumpAngleSeek(float top, float length, float gravity)
{
  D3DXVECTOR2 move(0,0);
  float v = 0.0f;
  float rot = 0.0f;
  float time = 0.0f;
  float g = abs(gravity);
  rot = atanf((top * 4) / length);
  v = sqrtf(g * top * 2) / sinf(rot);
  time = 2 * sqrtf((2 * top) / g);
  move.x = v * cosf(rot);
  move.y = v * sinf(rot) - (g * time);
  move.x = move.x * (move_.x / abs(move_.x));
  move.y = move.y * -1;
  return move;
}
// EOF