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
#include "Application/Tension/TensionGauge.h"
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// define
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#define GRAVITY	(-0.49f)

//==============================================================================
// class implementation
//==============================================================================
// ctor
Uriel::Uriel(ANIMATION_EVENT animation_event, Stage* stage, TensionGauge* p_tension_gauge) : AnimationObject(animation_event) {
  dest_position_ = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
  move_ = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
  move_.x = URIEL_MOVE_SPPD;
  jump_before_pos_ = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
  map_ = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
  p_stage_ = stage;
  p_tension_gauge_ = p_tension_gauge;
  static const float kSize = 100.0f;
  size_ = D3DXVECTOR2(kSize, kSize);
  boro_gage_max_ = false;
  boro_interval_ = 0;
  charge_flag_ = false;
  runaway_timer_ = 0;
  sleep_timer_ = 0;
  old_position_ = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

  // �X�e�[�W����X�^�[�g�ꏊ��Ⴄ
  pos_ = stage->GetStartMaptip();
  HIT_CHECK check;
  D3DXVECTOR3 map(0.f, 0.f, 0.f);
  map = p_stage_->CheckMapTip(&D3DXVECTOR3(pos_.x, pos_.y - size_.y, pos_.z), D3DXVECTOR3(size_.x / 4, 1.0f, 0.0f), &check);
  // �����n�ʂȂ�
  if (check.bottom == MAP_TYPE_NORMAL){
    pos_.y = map.y + 25.0f * 1.9f;
    move_.y = 0;
  }

  old_position_ = pos_;

  SetAnimaton(animation_event);
}

// dtor
Uriel::~Uriel() {
}

// update
void Uriel::Update(void){
  // �d�͏���
  move_.y += GRAVITY;

  if (status_ == URIEL_STATUS_CRAWL ||
    status_ == URIEL_STATUS_CHARGECRAWL){
    if (dest_position_ != D3DXVECTOR3(0.0f, 0.0f, 0.0f)){
      if (dest_position_.x - pos_.x > URIEL_MOVE_SPPD){
        move_.x = URIEL_MOVE_SPPD;
      } else if (dest_position_.x - pos_.x < -URIEL_MOVE_SPPD){
        move_.x = -URIEL_MOVE_SPPD;
      } else {
        dest_position_ = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
      }
    }
  }

  if ((dest_position_.x - pos_.x > (move_.x))){
	  dest_position_ = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
  }
  else if (dest_position_.x - pos_.x < -(move_.x)){
	  dest_position_ = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
  }


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

  // �O��̍��W�ۑ�
  old_position_ = pos_;

  // �Q�Ă��Ȃ���Έړ�
  if (status_ != URIEL_STATUS_SLEEP){
    pos_ += move_;
  }

  // �ڂ̑O���ǂȂ甽�]
  HIT_CHECK check;
  D3DXVECTOR3 map(0.f, 0.f, 0.f);
  if (move_direction_ == DIRECTION_LEFT){
    map = p_stage_->CheckMapTip(&D3DXVECTOR3(pos_.x + size_.x,pos_.y,pos_.z), D3DXVECTOR3(size_.x / 4, 1.0f, 0.0f), &check);
    if (check.left == MAP_TYPE_WALL){
      move_.x *= -1;
    }
  } else {
    map = p_stage_->CheckMapTip(&pos_, D3DXVECTOR3(size_.x / 4, 1.0f, 0.0f), &check);
    if (check.right == MAP_TYPE_WALL){
      move_.x *= -1;
    }
  }

  // �{�[���`���[�W�C���^�[�o�����Ԃ̌���
  if (boro_interval_ > 0)
    -- boro_interval_;

  if (status_ != URIEL_STATUS_NONE){
    // �A�j���[�V�����X�V
    p_texture_animation_->UpdateAnimation();
  }
}

// draw
void Uriel::_PreProcessOfDraw(void) {
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
  if (status_ == URIEL_STATUS_JUMP ||
    status_ == URIEL_STATUS_CHARGEJUMP ||
    status_ == URIEL_STATUS_RUNAWAY) {
    return;
  }
  if (abs(pos.x - pos_.x) < URIEL_INDUCIBLE)
    dest_position_ = pos;
}

//=============================================================================
// �{�[���`���[�W
//-----------------------------------------------------------------------------
bool Uriel::BoroChage(void){
  if (status_ == URIEL_STATUS_JUMP ||
    status_ == URIEL_STATUS_CHARGEJUMP ||
    status_ == URIEL_STATUS_RUNAWAY ||
    status_ == URIEL_STATUS_SLEEP) {
    return false;
  }
  if (!charge_flag_ && boro_interval_ <= 0){
    SetAnimaton(ANIMATION_URIEL_CHARGECRAWL);
    charge_flag_ = true;
    move_.x = (move_.x / abs(move_.x)) * URIEL_MOVE_CHARGE_SPEED;
    boro_interval_ = URIEL_BOROCHAGE_INTERVAL;
    if (p_tension_gauge_->IncreaseTension()){
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
  // �n�ʂƂ̓����蔻��
  HIT_CHECK check;
  D3DXVECTOR3 map(0.f, 0.f, 0.f);
  map = p_stage_->CheckMapTip(&pos_, D3DXVECTOR3(size_.x / 4, 1.0f, 0.0f), &check);

  // �����n�ʂȂ�
  if (check.bottom == MAP_TYPE_NORMAL){
      pos_.y = map.y + 25.0f * 1.9f;
      move_.y = 0;
  }

  // �W�����v���邩�`�F�b�N���ăW�����v�ł���Ȃ�W�����v
  BLOCK_DATA data;
  data = LoadCheck();
  if (data == BLOCK_DATA_JUMP){
    SetAnimaton(ANIMATION_URIEL_JUMP);
    D3DXVECTOR2 vector = JumpAngleSeek(50.0f, 150.0f, 0.0f, GRAVITY);
    move_.x = vector.x;
    move_.y = vector.y;
    // �W�����v�O�̍��W��ۑ�
    jump_before_pos_ = pos_;
  }

  // �o��K�i�Ȃ���
  else if (data == BLOCK_DATA_UP_STAIRS){
    SetAnimaton(ANIMATION_URIEL_JUMP);
    D3DXVECTOR2 vector = JumpAngleSeek(100.0f, 75.0f, 100.0f, GRAVITY);
    move_.x = vector.x;
    move_.y = vector.y;
    // �W�����v�O�̍��W��ۑ�
    jump_before_pos_ = pos_;
  }

  // ����K�i�Ȃ�~���
  else if (data == BLOCK_DATA_DOWN_STAIRS){
    SetAnimaton(ANIMATION_URIEL_JUMP);
    D3DXVECTOR2 vector = JumpAngleSeek(0.0f, 25.0f, -100.0f, GRAVITY);
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
  // �n�ʂƂ̓����蔻��
  HIT_CHECK check;
  D3DXVECTOR3 map(0.f, 0.f, 0.f);
  map = p_stage_->CheckMapTip(&pos_, D3DXVECTOR3(size_.x / 4, 1.0f, 0.0f), &check);
  if (check.bottom == MAP_TYPE_NORMAL){
    SetAnimaton(ANIMATION_URIEL_CRAWL);
    move_.x = URIEL_MOVE_SPPD * (move_.x / abs(move_.x));
    pos_.y = map.y + 25.0f * 1.9f;
    move_.y = 0.0f;
  }
}

//=============================================================================
// �\����Ԃ̍X�V
//-----------------------------------------------------------------------------
void Uriel::UpdateRunaway(void){
  // �n�ʂƂ̓����蔻��
  HIT_CHECK check;
  D3DXVECTOR3 map(0.f, 0.f, 0.f);
  map = p_stage_->CheckMapTip(&pos_, D3DXVECTOR3(size_.x / 4, 1.0f, 0.0f), &check);

  // �����n�ʂȂ�
  if (check.bottom == MAP_TYPE_NORMAL){
      pos_.y = map.y + 25.0f * 1.9f;
      move_.y = 0;
  }

  if (move_direction_ == DIRECTION_LEFT){
    map = p_stage_->CheckMapTip(&D3DXVECTOR3(pos_.x + size_.x,pos_.y,pos_.z), D3DXVECTOR3(size_.x / 4, 1.0f, 0.0f), &check);
    if (check.left == MAP_TYPE_NORMAL){
      move_.x *= -1;
    }
  } else {
    map = p_stage_->CheckMapTip(&pos_, D3DXVECTOR3(size_.x / 4, 1.0f, 0.0f), &check);
    if (check.right == MAP_TYPE_NORMAL){
      move_.x *= -1;
    }
  }

  // ��莞�Ԗ\�������疰��
  if (runaway_timer_ >= URIEL_RUNAWAY_TIME){
    SetAnimaton(ANIMATION_URIEL_SLEEP);
    runaway_timer_ = 0;
    p_tension_gauge_->CoolDown();
    boro_gage_max_ = false;
  }

  ++runaway_timer_;
}

//=============================================================================
// �����Ԃ̍X�V
//-----------------------------------------------------------------------------
void Uriel::UpdateSleep(void){
  // �n�ʂƂ̓����蔻��
  HIT_CHECK check;
  D3DXVECTOR3 map(0.f, 0.f, 0.f);
  map = p_stage_->CheckMapTip(&pos_, D3DXVECTOR3(size_.x / 4, 1.0f, 0.0f), &check);

  // �����n�ʂȂ�
  if (check.bottom == MAP_TYPE_NORMAL){
      pos_.y = map.y + 25.0f * 1.9f;
      move_.y = 0;
  }

  ++ sleep_timer_;

  if (sleep_timer_ > URIEL_SLEEP_TIME){
    SetAnimaton(ANIMATION_URIEL_CRAWL);
    sleep_timer_ = 0;
    move_.x = URIEL_MOVE_SPPD * (move_.x / abs(move_.x));
  }
}

//=============================================================================
// �n�C�n�C(�`���[�W)��Ԃ̍X�V
//-----------------------------------------------------------------------------
void Uriel::UpdateChargeCrawl(void){
  // �n�ʂƂ̓����蔻��
  HIT_CHECK check;
  D3DXVECTOR3 map(0.f, 0.f, 0.f);
  map = p_stage_->CheckMapTip(&pos_, D3DXVECTOR3(size_.x / 4, 1.0f, 0.0f), &check);

  // �����n�ʂȂ�
  if (check.bottom == MAP_TYPE_NORMAL){
      pos_.y = map.y + 25.0f * 1.9f;
      move_.y = 0;
  }

  // �W�����v���邩�`�F�b�N���ăW�����v�ł���Ȃ�W�����v
  BLOCK_DATA data;
  data = LoadCheck();
  if (data == BLOCK_DATA_JUMP){
    SetAnimaton(ANIMATION_URIEL_CHARGEJUMP);
    D3DXVECTOR2 vector = JumpAngleSeek(50.0f, 250.0f, 0.0f, GRAVITY);
    move_.x = vector.x;
    move_.y = vector.y;
    // �W�����v�O�̍��W��ۑ�
    jump_before_pos_ = pos_;
  }

  // �o��K�i�Ȃ���
  else if (data == BLOCK_DATA_UP_STAIRS){
    SetAnimaton(ANIMATION_URIEL_CHARGEJUMP);
    D3DXVECTOR2 vector = JumpAngleSeek(100.0f, 50.0f, 100.0f, GRAVITY);
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
      runaway_timer_ = 0;
      move_.x = URIEL_MOVE_RUNAWAY_SPPD * (move_.x / abs(move_.x));
    } else {
      // �ʏ�ɖ߂�
      SetAnimaton(ANIMATION_URIEL_CRAWL);
      move_.x = URIEL_MOVE_SPPD * (move_.x / abs(move_.x));
    }
  }
}

//=============================================================================
// �W�����v(�`���[�W)��Ԃ̍X�V
//-----------------------------------------------------------------------------
void Uriel::UpdateChargeJump(void){
  // �n�ʂƂ̓����蔻��
  HIT_CHECK check;
  D3DXVECTOR3 map(0.f, 0.f, 0.f);
  map = p_stage_->CheckMapTip(&pos_, D3DXVECTOR3(size_.x / 4, 1.0f, 0.0f), &check);
  if (check.bottom == MAP_TYPE_NORMAL){
    SetAnimaton(ANIMATION_URIEL_CHARGECRAWL);
    move_.x = URIEL_MOVE_CHARGE_SPEED * (move_.x / abs(move_.x));
    pos_.y = map.y + 25.0f * 1.9f;
    move_.y = 0.0f;
  }
}

//=============================================================================
// �S�[����Ԃ̍X�V
//-----------------------------------------------------------------------------
void Uriel::UpdateGoal(void){

}

//=============================================================================
// ���̃`�F�b�N
//-----------------------------------------------------------------------------
BLOCK_DATA Uriel::LoadCheck(void){
  switch (status_)
  {
  case URIEL_STATUS_CRAWL:
    return CrawlLoadCheck();
    break;
  case URIEL_STATUS_CHARGECRAWL:
    return ChargeCrawlLoadCheck();
    break;
  default:
    return BLOCK_DATA_ERROR;
    break;
  }
}

//=============================================================================
// �I�u�W�F�N�g�Ƃ�Hit����(by Shimizu)
//-----------------------------------------------------------------------------
bool Uriel::CheckHit(const D3DXVECTOR3& pos, const D3DXVECTOR2& size) {
  // if ��`�H�H���m�̔�����ۂ� TODO: �֐���
  return (pos.x + size.x / 2) > (pos_.x - size_.x / 2) &&
         (pos.x - size.x / 2) < (pos_.x - size_.x / 2);
}

//=============================================================================
// �n�C�n�C��Ԃł̃`�F�b�N
//-----------------------------------------------------------------------------
BLOCK_DATA Uriel::CrawlLoadCheck(void){
  HIT_CHECK check,checkold;
  map_ = p_stage_->CheckMapTip(&pos_, D3DXVECTOR3(size_.x / 4, 1.0f, 0.0f), &check);
  p_stage_->CheckMapTip(&old_position_, D3DXVECTOR3(size_.x / 4, 1.0f, 0.0f), &checkold);

  // �ڂ̑O�ɒn�ʂ������Ă��̌������ɃW�����v�ł���n�ʂ�����ꍇ
  if (check.bottom == MAP_TYPE_NORMAL){
    // �E�ɐi��ł�ꍇ
    if (move_direction_ == DIRECTION_RIGHT){
      if (check.bottom_right == MAP_TYPE_NONE){
        p_stage_->CheckMapTip(&D3DXVECTOR3(pos_.x + size_.x, pos_.y, pos_.z),
                               D3DXVECTOR3(size_.x / 4, 1.0f, 0.0f), &check);
        if (check.bottom_right == MAP_TYPE_NORMAL){
          return BLOCK_DATA_JUMP;
        }
      }
    }
    // ���ɐi��ł�ꍇ
    else if (move_direction_ == DIRECTION_LEFT){
      if (check.bottom_left == MAP_TYPE_NONE){
        p_stage_->CheckMapTip(&D3DXVECTOR3(pos_.x - size_.x, pos_.y, pos_.z),
                               D3DXVECTOR3(size_.x / 4, 1.0f, 0.0f), &check);
        if (check.bottom_left == MAP_TYPE_NORMAL){
          return BLOCK_DATA_JUMP;
        }
      }
    }
  }

  // �o��K�i�����ׂ�
  map_ = p_stage_->CheckMapTip(&D3DXVECTOR3(pos_.x, pos_.y, pos_.z),
                                D3DXVECTOR3(size_.x / 4, size_.y / 4, 0.0f), &check);
  if (check.bottom == MAP_TYPE_NORMAL){
    // �E�ɐi��ł�ꍇ
    if (move_direction_ == DIRECTION_RIGHT){
      if(check.right == MAP_TYPE_NORMAL){
        map_ = p_stage_->CheckMapTip(&D3DXVECTOR3(pos_.x + size_.x / 4, pos_.y, pos_.z),
                                D3DXVECTOR3(size_.x / 4, size_.y / 4, 0.0f), &check);
        if (check.up_right == MAP_TYPE_NONE ||
            check.up_right == MAP_TYPE_START ||
            check.up_right == MAP_TYPE_GOAL){
          if (abs(pos_.x - map_.x) < size_.x / 4)
            return BLOCK_DATA_UP_STAIRS;
        }
      }
    }

    // ���ɐi��ł�ꍇ
    else{
      if(check.left == MAP_TYPE_NORMAL){
        p_stage_->CheckMapTip(&D3DXVECTOR3(pos_.x - size_.x + size_.x / 10 * 7, pos_.y, pos_.z),
                               D3DXVECTOR3(size_.x / 4, 1.0f, 0.0f), &check);
        if (check.up_left == MAP_TYPE_NONE ||
            check.up_left == MAP_TYPE_START ||
            check.up_left == MAP_TYPE_GOAL){
          if (abs(pos_.x - map_.x) < size_.x / 4)
            return BLOCK_DATA_UP_STAIRS;
        }
      }
    }
  }

  // ����K�i�����ׂ�
  map_ = p_stage_->CheckMapTip(&D3DXVECTOR3(pos_.x, pos_.y, pos_.z),
                                D3DXVECTOR3(size_.x / 4, 1.0f, 0.0f), &check);
  p_stage_->CheckMapTip(&old_position_, D3DXVECTOR3(size_.x / 4, 1.0f, 0.0f), &checkold);
  if (check.bottom == MAP_TYPE_NORMAL){
    // �E�ɐi��ł�ꍇ
    if (move_direction_ == DIRECTION_RIGHT){
      p_stage_->CheckMapTip(&D3DXVECTOR3(pos_.x + size_.x / 4, pos_.y, pos_.z),
                             D3DXVECTOR3(size_.x / 4, 1.0f, 0.0f), &check);
      if (check.bottom_right == MAP_TYPE_NONE){
        p_stage_->CheckMapTip(&D3DXVECTOR3(pos_.x + size_.x / 4, pos_.y - size_.y, pos_.z),
                               D3DXVECTOR3(size_.x / 4, 1.0f, 0.0f), &check);
        if (check.bottom_right == MAP_TYPE_NORMAL){
          return BLOCK_DATA_DOWN_STAIRS;
        }
      }
    }

    // ���ɐi��ł�ꍇ
    else{
      p_stage_->CheckMapTip(&D3DXVECTOR3(pos_.x + size_.x, pos_.y, pos_.z),
                               D3DXVECTOR3(size_.x / 4, 1.0f, 0.0f), &check);
      if(move_direction_ == DIRECTION_LEFT){
        p_stage_->CheckMapTip(&D3DXVECTOR3(pos_.x + size_.x + size_.x / 10 * 2, pos_.y, pos_.z),
                               D3DXVECTOR3(size_.x / 4, 1.0f, 0.0f), &check);
        if (check.bottom_left == MAP_TYPE_NONE){
      p_stage_->CheckMapTip(&D3DXVECTOR3(pos_.x + size_.x + size_.x / 10 * 2, pos_.y - size_.y, pos_.z),
                             D3DXVECTOR3(size_.x / 4, 1.0f, 0.0f), &check);
          if (check.bottom_left == MAP_TYPE_NORMAL){
            return BLOCK_DATA_DOWN_STAIRS;
          }
        }
      }
    }
  }

  return BLOCK_DATA_ERROR;
}

//=============================================================================
// �`���[�W�n�C�n�C��Ԃł̃`�F�b�N
//-----------------------------------------------------------------------------
BLOCK_DATA Uriel::ChargeCrawlLoadCheck(void){
  HIT_CHECK check;
  p_stage_->CheckMapTip(&pos_, D3DXVECTOR3(size_.x / 4, 1.0f, 0.0f), &check);

  if (check.bottom == MAP_TYPE_NORMAL){
    // �E�ɐi��ł�ꍇ
    if (move_direction_ == DIRECTION_RIGHT){
      p_stage_->CheckMapTip(&pos_, D3DXVECTOR3(size_.x / 4 * 3, 1.0f, 0.0f), &check);
      if (check.bottom_right == MAP_TYPE_NONE){
        p_stage_->CheckMapTip(&D3DXVECTOR3(pos_.x + size_.x, pos_.y, pos_.z),
                               D3DXVECTOR3(size_.x / 4, 1.0f, 0.0f), &check);
        if (check.bottom_left == MAP_TYPE_NORMAL){
          return BLOCK_DATA_JUMP;
        }
        p_stage_->CheckMapTip(&D3DXVECTOR3(pos_.x + size_.x * 2, pos_.y, pos_.z),
                               D3DXVECTOR3(size_.x / 4, 1.0f, 0.0f), &check);
        if (check.bottom_right == MAP_TYPE_NORMAL){
          return BLOCK_DATA_JUMP;
        }
      }
    }
    // ���ɐi��ł�ꍇ
    else if (move_direction_ == DIRECTION_LEFT){
      p_stage_->CheckMapTip(&D3DXVECTOR3(pos_.x + size_.x, pos_.y, pos_.z), D3DXVECTOR3(1.0f, 1.0f, 0.0f), &check);
      if (check.bottom_left == MAP_TYPE_NONE){
        p_stage_->CheckMapTip(&D3DXVECTOR3(pos_.x - size_.x, pos_.y, pos_.z),
                               D3DXVECTOR3(size_.x / 4, 1.0f, 0.0f), &check);
        if (check.bottom_left == MAP_TYPE_NORMAL){
          return BLOCK_DATA_JUMP;
        }
        p_stage_->CheckMapTip(&D3DXVECTOR3(pos_.x - size_.x * 2, pos_.y, pos_.z),
                               D3DXVECTOR3(size_.x / 4, 1.0f, 0.0f), &check);
        if (check.bottom_left == MAP_TYPE_NORMAL){
          return BLOCK_DATA_JUMP;
        }
      }
    }
  }

  // �o��K�i�����ׂ�
  map_ = p_stage_->CheckMapTip(&D3DXVECTOR3(pos_.x + size_.x / 4, pos_.y, pos_.z),
                                D3DXVECTOR3(size_.x / 4, 1.0f, 0.0f), &check);
  if (check.bottom == MAP_TYPE_NORMAL){
    // �E�ɐi��ł�ꍇ
    if (move_direction_ == DIRECTION_RIGHT){
      if(check.right == MAP_TYPE_NORMAL){
        p_stage_->CheckMapTip(&D3DXVECTOR3(pos_.x + size_.x / 4, pos_.y + size_.y, pos_.z),
                               D3DXVECTOR3(size_.x / 4, 1.0f, 0.0f), &check);
        if (check.right == MAP_TYPE_NONE ||
            check.right == MAP_TYPE_START ||
            check.right == MAP_TYPE_GOAL){
          return BLOCK_DATA_UP_STAIRS;
        }
      }
    }

    // ���ɐi��ł�ꍇ
    else{
      if(check.left == MAP_TYPE_NORMAL){
        p_stage_->CheckMapTip(&D3DXVECTOR3(pos_.x - size_.x + size_.x / 4 * 3, pos_.y + size_.y, pos_.z),
                               D3DXVECTOR3(size_.x / 4, 1.0f, 0.0f), &check);
        if (check.left == MAP_TYPE_NONE ||
            check.left == MAP_TYPE_START ||
            check.left == MAP_TYPE_GOAL){
          return BLOCK_DATA_UP_STAIRS;
        }
      }
    }
  }
  return BLOCK_DATA_ERROR;
}

//=============================================================================
// �W�����v���鍂���Ƌ����ƖړI�n�̍��፷�Ƃ�����d�͂�n���Έړ��ʂ��Ԃ��Ă���(2D�p)
//-----------------------------------------------------------------------------
D3DXVECTOR2 Uriel::JumpAngleSeek(float top, float length, float difference_in_height, float gravity)
{
  D3DXVECTOR2 move(0,0);
  float v = 0.0f;
  float rot = 0.0f;
  float time = 0.0f;
  float g = abs(gravity);

  time = (sqrtf(2 * g * (top - difference_in_height)) + sqrtf(2 * g * top)) / g;
  rot = atanf(time * sqrt(2 * g * (top - difference_in_height)) / length);
  v = sqrtf((length / time) * (length / time) + 2 * g * (top - difference_in_height));
  move.x = v * cosf(rot);
  move.y = v * sinf(rot) - (g * time);
  move.x = move.x * (move_.x / abs(move_.x));
  move.y = move.y * -1;

  return move;
}
// EOF