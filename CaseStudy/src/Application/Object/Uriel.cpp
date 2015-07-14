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
#include "Framework/DrawDebugPrimitive/DrawPrimitive.h"
#include "Framework/Sound/sound.h"
#include "Framework/Texture/TextureManagerHolder.h"
#include "Application/Stage/Stage.h"
#include "Application/Tension/TensionGauge.h"
#include "Sang/Butterfly.h"
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// define
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#define GRAVITY (-0.49f)

namespace {

const D3DXVECTOR3 kEatPosOffset = {
  25.0f, 21.0f, 0.0f
};

}

//==============================================================================
// class implementation
//==============================================================================
// ctor
Uriel::Uriel(ANIMATION_EVENT animation_event, Stage* stage, TensionGauge* p_tension_gauge) : AnimationObject(animation_event) {
  dest_position_ = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
  move_ = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
  move_.x = kUrielMoveSpped;
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
  induction_flag_ = false;
  sang_position_ = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
  sang_type_ = ANIM_OBJ_TYPE_NONE;
  sang_direction_ = DIRECTION_RIGHT;
  attractible_flower_timer_ = 0;
  sang_object_ = nullptr;
  prev_sang_object_ = nullptr;
  sang_induction_flag_ = false;
  butterfly_direction_change_flag_ = false;
  move_stop_flag_ = false;

  // �X�e�[�W����X�^�[�g�ꏊ��Ⴄ
  pos_ = stage->GetStartMaptip();
  HIT_CHECK check;
  D3DXVECTOR3 map(0.f, 0.f, 0.f);
  map = p_stage_->CheckMapTip2(&D3DXVECTOR3(pos_.x, pos_.y - size_.y, pos_.z), D3DXVECTOR3(size_.x / 4, 1.0f, 0.0f), &check);
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
  // �\����Ԃł̃W�����v
  case URIEL_STATUS_RUNAWAY_JUMP:
    UpdateRunawayJump();
    break;
  // ������
  case URIEL_STATUS_SLEEP:
    UpdateSleep();
    break;
  // �n�C�n�C(�`���[�W)���
  case URIEL_STATUS_CHARGE_CRAWL:
    UpdateChargeCrawl();
    break;
  // �W�����v(�`���[�W)���
  case URIEL_STATUS_CHARGE_JUMP:
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
  } else if(move_.x < 0){
    move_direction_ = DIRECTION_LEFT;
  }

  // �O��̍��W�ۑ�
  old_position_ = pos_;

  // �Q�Ă��Ȃ���Έړ�
  if (status_ != URIEL_STATUS_SLEEP &&
      !move_stop_flag_){
    pos_ += move_;
  }

  // �ڂ̑O���ǂȂ甽�]
  HIT_CHECK check;
  D3DXVECTOR3 map(0.f, 0.f, 0.f);
  if (move_direction_ == DIRECTION_LEFT){
    map = p_stage_->CheckMapTip2(&D3DXVECTOR3(pos_.x + size_.x - size_.x / 4,pos_.y,pos_.z), D3DXVECTOR3(size_.x / 4, 1.0f, 0.0f), &check);
    if (check.left == MAP_TYPE_WALL ||
       (check.left == MAP_TYPE_NORMAL &&
        check.up_left == MAP_TYPE_NORMAL)){
      move_.x *= -1;
    }
  } else {
    map = p_stage_->CheckMapTip2(&pos_, D3DXVECTOR3(size_.x / 4, 1.0f, 0.0f), &check);
    if (check.right == MAP_TYPE_WALL ||
       (check.right == MAP_TYPE_NORMAL &&
        check.up_right == MAP_TYPE_NORMAL)){
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

  induction_flag_ = false;
  move_stop_flag_ = false;
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

  DrawCircle3D(pos_, static_cast<float>(kUrielInducible) * 2, 0xff00ff00);
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
    status_ == URIEL_STATUS_CHARGE_JUMP ||
    status_ == URIEL_STATUS_RUNAWAY) {
    return;
  }
  HIT_CHECK check;
  p_stage_->CheckMapTip2((D3DXVECTOR3*)&pos, D3DXVECTOR3(size_.x / 4, 1.0f, 0.0f), &check);
  if (check.center == MAP_TYPE_WALL){
    return;
  }
<<<<<<< HEAD
  if (abs(pos.x - pos_.x) < kUrielInducible){
    dest_position_ = pos;
    induction_flag_ = true;
  }
}

//=============================================================================
// �E���G���̖ړI�n�_�ݒ�(��Q���p)
//-----------------------------------------------------------------------------
void Uriel::SetDestPos(const D3DXVECTOR3& pos, ANIM_OBJ_TYPE anim_obj_type, DIRECTION direction, AnimationObject* anim_obj){
  if (status_ == URIEL_STATUS_JUMP ||
    status_ == URIEL_STATUS_CHARGE_JUMP ||
    status_ == URIEL_STATUS_RUNAWAY) {
    return;
  }
  if (anim_obj_type == ANIM_OBJ_TYPE_FLOWER &&
    anim_obj == sang_object_){
    return;
  }
  HIT_CHECK check;
  p_stage_->CheckMapTip2((D3DXVECTOR3*)&pos, D3DXVECTOR3(size_.x / 4, 1.0f, 0.0f), &check);
  if (check.center == MAP_TYPE_WALL){
    return;
  }
  if (abs(pos.x - pos_.x) < kUrielInducible){
    if (anim_obj_type == ANIM_OBJ_TYPE_BUTTERFLY){
      if ((move_direction_ == DIRECTION_RIGHT && (pos.x - pos_.x) > 0) ||
          (move_direction_ == DIRECTION_RIGHT && (pos.x - pos_.x) < kUrielLockButterflyLength)){
        if (direction == DIRECTION_RIGHT){
          sang_position_ = D3DXVECTOR3(pos.x - kUrielChaseTheButterflyOffset, pos.y, pos.z);
        }
      }
      if ((move_direction_ == DIRECTION_LEFT && (pos.x - pos_.x) < 0) ||
          (move_direction_ == DIRECTION_LEFT && (pos.x - pos_.x) > kUrielLockButterflyLength))
        if (direction == DIRECTION_LEFT){
          sang_position_ = D3DXVECTOR3(pos.x + kUrielChaseTheButterflyOffset, pos.y, pos.z);
        }
      if (anim_obj == sang_object_ &&
        direction != sang_direction_){
        butterfly_direction_change_flag_ = true;
      }
    }
    else if (anim_obj_type == ANIM_OBJ_TYPE_FLOWER){
      sang_position_ = pos;
    }
    sang_type_ = anim_obj_type;
    sang_direction_ = direction;
    attractible_flower_timer_ = 0;
    sang_object_ = anim_obj;
    sang_induction_flag_ = true;
=======
  if (abs(pos.x - pos_.x) < kUrielInducible) {
    dest_position_ = pos;
    PlaySound(SOUND_LABEL_SE_CALL0);
>>>>>>> f43beb0fb6de50a84a67056bae845a6725c781ac
  }
}

//=============================================================================
// �{�[���`���[�W
//-----------------------------------------------------------------------------
bool Uriel::BoroChage(void){
  if (status_ == URIEL_STATUS_JUMP ||
    status_ == URIEL_STATUS_CHARGE_JUMP ||
    status_ == URIEL_STATUS_RUNAWAY ||
    status_ == URIEL_STATUS_RUNAWAY_JUMP ||
    status_ == URIEL_STATUS_SLEEP) {
    return false;
  }
  if (!charge_flag_ && boro_interval_ <= 0){
    SetAnimaton(ANIMATION_URIEL_CHARGE_CRAWL);
    charge_flag_ = true;
    move_.x = (move_.x / abs(move_.x)) * kUrielMoveChargeSpeed;
    boro_interval_ = kUrielBorochageInterval;
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
  HIT_CHECK check_center,check_right,check_left;
  D3DXVECTOR3 map(0.f, 0.f, 0.f);
  map = p_stage_->CheckMapTip2(&pos_, D3DXVECTOR3(size_.x / 4, 1.0f, 0.0f), &check_center);
  p_stage_->CheckMapTip2(&D3DXVECTOR3(pos_.x + size_.x / 4, pos_.y, pos_.z), D3DXVECTOR3(size_.x / 4, 1.0f, 0.0f), &check_right);
  p_stage_->CheckMapTip2(&D3DXVECTOR3(pos_.x - size_.x / 4, pos_.y, pos_.z), D3DXVECTOR3(size_.x / 4, 1.0f, 0.0f), &check_left);

  // �����n�ʂȂ�
  if (check_center.bottom == MAP_TYPE_NORMAL ||
      check_right.bottom == MAP_TYPE_NORMAL ||
      check_left.bottom == MAP_TYPE_NORMAL){
    pos_.y = map.y + 25.0f * 1.9f;
    move_.y = 0;
  } else {
    SetAnimaton(ANIMATION_URIEL_JUMP);
    move_.x = 0;
    return;
  }

  // �ړI�n�֌���������
  if (dest_position_ != D3DXVECTOR3(0.0f, 0.0f, 0.0f)){
    if (dest_position_.x - pos_.x > kUrielMoveSpped){
      move_.x = kUrielMoveSpped;
    } else if (dest_position_.x - pos_.x < -kUrielMoveSpped){
      move_.x = -kUrielMoveSpped;
    } else {
      dest_position_ = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
    }
  }

  // ������Q���̏ꍇ
  if (sang_type_ == ANIM_OBJ_TYPE_BUTTERFLY && !induction_flag_){
    // ��Q���֌���������
    if (sang_position_ != D3DXVECTOR3(0.0f, 0.0f, 0.0f) &&
        sang_induction_flag_ &&
        abs(sang_position_.y - pos_.y) < 25.0f &&
        abs(sang_position_.x - pos_.x) < kUrielLockButterflyLength){
      if (sang_position_.x - pos_.x + move_.x> Butterfly::kButterFlyMoveSpeed){
        move_.x = Butterfly::kButterFlyMoveSpeed;
      } else if (sang_position_.x - pos_.x + move_.x< -Butterfly::kButterFlyMoveSpeed){
        move_.x = -Butterfly::kButterFlyMoveSpeed;
      }
    }
  } // sang_type_ == ANIM_OBJ_TYPE_BUTTERFLY

  // �Ԃ���Q���̏ꍇ
  else if (sang_type_ == ANIM_OBJ_TYPE_FLOWER && !induction_flag_){
    // ��Q���֌���������
    if (sang_position_ != D3DXVECTOR3(0.0f, 0.0f, 0.0f) &&
        sang_induction_flag_ &&
        abs(sang_position_.y - pos_.y) < 25.0f){
        if (abs(sang_position_.x - pos_.x) < kUrielLookFlowerLength){
        attractible_flower_timer_++;
        move_.x = 0;
      } else if (sang_position_.x - pos_.x > kUrielMoveSpped &&
          move_direction_ == DIRECTION_RIGHT){
        move_.x = kUrielMoveSpped;
      } else if (sang_position_.x - pos_.x < -kUrielMoveSpped &&
                 move_direction_ == DIRECTION_LEFT){
        move_.x = -kUrielMoveSpped;
      }
    }

    if ((attractible_flower_timer_ > kUrielAttractibleFlower) &&
         sang_induction_flag_){
      prev_sang_object_ = sang_object_;
      sang_induction_flag_ = false;
      if (move_direction_ == DIRECTION_RIGHT){
        move_.x = kUrielMoveSpped;
      } else {
        move_.x = -kUrielMoveSpped;
      }
    } else if ((abs(sang_position_.x - pos_.x) > kUrielLookFlowerLength) &&
               !sang_induction_flag_){
      attractible_flower_timer_ = 0;
      sang_object_ = nullptr;
      sang_position_ = D3DXVECTOR3(0, 0, 0);
    }

  } // sang_type_ == ANIM_OBJ_TYPE_FLOWER

  // �W�����v���邩�`�F�b�N���ăW�����v�ł���Ȃ�W�����v
  BLOCK_DATA data;
  data = LoadCheck();
  if (data == BLOCK_DATA_JUMP){
    SetAnimaton(ANIMATION_URIEL_JUMP);
    D3DXVECTOR2 vector = JumpAngleSeek(50.0f, 150.0f, 0.0f, GRAVITY);
    move_.x = vector.x;
    move_.y = vector.y;
  }

  // �o��K�i�Ȃ���
  else if (data == BLOCK_DATA_UP_STAIRS){
    SetAnimaton(ANIMATION_URIEL_JUMP);
    D3DXVECTOR2 vector = JumpAngleSeek(100.0f, 75.0f, 100.0f, GRAVITY);
    move_.x = vector.x;
    move_.y = vector.y;
  }

}

//=============================================================================
// �W�����v��Ԃ̍X�V
//-----------------------------------------------------------------------------
void Uriel::UpdateJump(void){
  // �ړI�n�֌���������
  if (dest_position_ != D3DXVECTOR3(0.0f, 0.0f, 0.0f)){
    if (dest_position_.x - pos_.x < kUrielMoveSpped &&
        dest_position_.x - pos_.x > -kUrielMoveSpped){
      dest_position_ = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
    }
  }

  // �n�ʂƂ̓����蔻��
  HIT_CHECK check;
  D3DXVECTOR3 map(0.f, 0.f, 0.f);
  map = p_stage_->CheckMapTip2(&pos_, D3DXVECTOR3(size_.x / 4, 1.0f, 0.0f), &check);
  if (check.bottom == MAP_TYPE_NORMAL){
    SetAnimaton(ANIMATION_URIEL_CRAWL);
    if (move_direction_ == DIRECTION_RIGHT){
      move_.x = kUrielMoveSpped;
    } else {
      move_.x = -kUrielMoveSpped;
    }
    pos_.y = map.y + 25.0f * 1.9f;
    move_.y = 0.0f;
  }
}

//=============================================================================
// �\����Ԃ̍X�V
//-----------------------------------------------------------------------------
void Uriel::UpdateRunaway(void){
  // �ړI�n�֌���������
  if (dest_position_ != D3DXVECTOR3(0.0f, 0.0f, 0.0f)){
    if (dest_position_.x - pos_.x > kUrielMoveRunawaySpped){
      move_.x = kUrielMoveRunawaySpped;
    } else if (dest_position_.x - pos_.x < -kUrielMoveRunawaySpped){
      move_.x = -kUrielMoveRunawaySpped;
    } else {
      dest_position_ = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
    }
  }

  // �n�ʂƂ̓����蔻��
  HIT_CHECK check_center,check_right,check_left;
  D3DXVECTOR3 map(0.f, 0.f, 0.f);
  map = p_stage_->CheckMapTip2(&pos_, D3DXVECTOR3(size_.x / 4, 1.0f, 0.0f), &check_center);
  p_stage_->CheckMapTip2(&D3DXVECTOR3(pos_.x + size_.x / 4, pos_.y, pos_.z), D3DXVECTOR3(size_.x / 4, 1.0f, 0.0f), &check_right);
  p_stage_->CheckMapTip2(&D3DXVECTOR3(pos_.x - size_.x / 4, pos_.y, pos_.z), D3DXVECTOR3(size_.x / 4, 1.0f, 0.0f), &check_left);

  // �����n�ʂȂ�
  if (check_center.bottom == MAP_TYPE_NORMAL ||
      check_right.bottom == MAP_TYPE_NORMAL ||
      check_left.bottom == MAP_TYPE_NORMAL){
      pos_.y = map.y + 25.0f * 1.9f;
      move_.y = 0;
  } else {
    SetAnimaton(ANIMATION_URIEL_RUNAWAY_JUMP);
    move_.x = 0;
  }

  if (check_right.left == MAP_TYPE_NORMAL &&
      check_left.right == MAP_TYPE_NORMAL){
    move_.x = 0;
  } else if (move_direction_ == DIRECTION_LEFT &&
             check_right.left == MAP_TYPE_NORMAL){
    move_.x *= -1;
  }
  else if (move_direction_ == DIRECTION_RIGHT &&
           check_left.right == MAP_TYPE_NORMAL){
    move_.x *= -1;
  }

  // ��莞�Ԗ\�������疰��
  if (runaway_timer_ >= kUrielRunnawayTime){
    SetAnimaton(ANIMATION_URIEL_SLEEP);
    runaway_timer_ = 0;
    p_tension_gauge_->CoolDown();
    boro_gage_max_ = false;
  }

  ++runaway_timer_;
}

//=============================================================================
// �\����Ԃł̃W�����v�̍X�V
//-----------------------------------------------------------------------------
void Uriel::UpdateRunawayJump(){
  // �ړI�n�֌���������
  if (dest_position_ != D3DXVECTOR3(0.0f, 0.0f, 0.0f)){
    if (dest_position_.x - pos_.x < kUrielMoveRunawaySpped &&
        dest_position_.x - pos_.x > -kUrielMoveRunawaySpped){
      dest_position_ = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
    }
  }

  // �n�ʂƂ̓����蔻��
  HIT_CHECK check;
  D3DXVECTOR3 map(0.f, 0.f, 0.f);
  map = p_stage_->CheckMapTip2(&pos_, D3DXVECTOR3(size_.x / 4, 1.0f, 0.0f), &check);
  if (check.bottom == MAP_TYPE_NORMAL){
    SetAnimaton(ANIMATION_URIEL_RUNAWAY);
    if (move_direction_ == DIRECTION_RIGHT){
      move_.x = kUrielMoveRunawaySpped;
    } else {
      move_.x = -kUrielMoveRunawaySpped;
    }
    pos_.y = map.y + 25.0f * 1.9f;
    move_.y = 0.0f;
  }
}

//=============================================================================
// �����Ԃ̍X�V
//-----------------------------------------------------------------------------
void Uriel::UpdateSleep(void){
  // �n�ʂƂ̓����蔻��
  HIT_CHECK check;
  D3DXVECTOR3 map(0.f, 0.f, 0.f);
  map = p_stage_->CheckMapTip2(&pos_, D3DXVECTOR3(size_.x / 4, 1.0f, 0.0f), &check);

  // �����n�ʂȂ�
  if (check.bottom == MAP_TYPE_NORMAL){
      pos_.y = map.y + 25.0f * 1.9f;
      move_.y = 0;
  }

  ++ sleep_timer_;

  if (sleep_timer_ > kUrielSleepTime){
    SetAnimaton(ANIMATION_URIEL_CRAWL);
    sleep_timer_ = 0;
    if (move_direction_ == DIRECTION_RIGHT){
      move_.x = kUrielMoveSpped;
    } else {
      move_.x = -kUrielMoveSpped;
    }
  }
}

//=============================================================================
// �n�C�n�C(�`���[�W)��Ԃ̍X�V
//-----------------------------------------------------------------------------
void Uriel::UpdateChargeCrawl(void){
  // �n�ʂƂ̓����蔻��
  HIT_CHECK check_center,check_right,check_left;
  D3DXVECTOR3 map(0.f, 0.f, 0.f);
  map = p_stage_->CheckMapTip2(&pos_, D3DXVECTOR3(size_.x / 4, 1.0f, 0.0f), &check_center);
  p_stage_->CheckMapTip2(&D3DXVECTOR3(pos_.x + size_.x / 4, pos_.y, pos_.z), D3DXVECTOR3(size_.x / 4, 1.0f, 0.0f), &check_right);
  p_stage_->CheckMapTip2(&D3DXVECTOR3(pos_.x - size_.x / 4, pos_.y, pos_.z), D3DXVECTOR3(size_.x / 4, 1.0f, 0.0f), &check_left);

  // �����n�ʂȂ�
  if (check_center.bottom == MAP_TYPE_NORMAL ||
      check_right.bottom == MAP_TYPE_NORMAL ||
      check_left.bottom == MAP_TYPE_NORMAL){
      pos_.y = map.y + 25.0f * 1.9f;
      move_.y = 0;
  } else {
    SetAnimaton(ANIMATION_URIEL_CHARGE_JUMP);
    move_.x = 0;
 }

  // �ړI�n�֌���������
  if (dest_position_ != D3DXVECTOR3(0.0f, 0.0f, 0.0f)){
    if (dest_position_.x - pos_.x > kUrielMoveChargeSpeed){
      move_.x = kUrielMoveChargeSpeed;
    } else if (dest_position_.x - pos_.x < -kUrielMoveChargeSpeed){
      move_.x = -kUrielMoveChargeSpeed;
    } else {
      dest_position_ = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
    }
  }

  // ������Q���̏ꍇ
  if (sang_type_ == ANIM_OBJ_TYPE_BUTTERFLY && !induction_flag_){
    // ��Q���֌���������
    if (sang_position_ != D3DXVECTOR3(0.0f, 0.0f, 0.0f) &&
        sang_induction_flag_ &&
        abs(sang_position_.y - pos_.y) < 25.0f &&
        abs(sang_position_.x - pos_.x) < kUrielLockButterflyLength){
      if (sang_position_.x - pos_.x > Butterfly::kButterFlyMoveSpeed){
        move_.x = Butterfly::kButterFlyMoveSpeed;
      } else if (sang_position_.x - pos_.x < -Butterfly::kButterFlyMoveSpeed){
        move_.x = -Butterfly::kButterFlyMoveSpeed;
      }
    }
  } // sang_type_ == ANIM_OBJ_TYPE_BUTTERFLY

  // �Ԃ���Q���̏ꍇ
  else if (sang_type_ == ANIM_OBJ_TYPE_FLOWER && !induction_flag_){
    // ��Q���֌���������
    if (sang_position_ != D3DXVECTOR3(0.0f, 0.0f, 0.0f) &&
        sang_induction_flag_ &&
        abs(sang_position_.y - pos_.y) < 25.0f){
        if (abs(sang_position_.x - pos_.x) < kUrielLookFlowerLength){
        attractible_flower_timer_++;
        move_.x = 0;
      } else if (sang_position_.x - pos_.x > kUrielMoveSpped &&
          move_direction_ == DIRECTION_RIGHT){
        move_.x = kUrielMoveChargeSpeed;
      } else if (sang_position_.x - pos_.x < -kUrielMoveSpped &&
                 move_direction_ == DIRECTION_LEFT){
        move_.x = -kUrielMoveChargeSpeed;
      }
    }

    if ((attractible_flower_timer_ > kUrielAttractibleFlower) &&
         sang_induction_flag_){
      prev_sang_object_ = sang_object_;
      sang_induction_flag_ = false;
      if (move_direction_ == DIRECTION_RIGHT){
        move_.x = kUrielMoveChargeSpeed;
      } else {
        move_.x = -kUrielMoveChargeSpeed;
      }
    } else if ((abs(sang_position_.x - pos_.x) > kUrielLookFlowerLength) &&
               !sang_induction_flag_){
      attractible_flower_timer_ = 0;
      sang_object_ = nullptr;
      sang_position_ = D3DXVECTOR3(0, 0, 0);
    }

  } // sang_type_ == ANIM_OBJ_TYPE_FLOWER

  // �W�����v���邩�`�F�b�N���ăW�����v�ł���Ȃ�W�����v
  BLOCK_DATA data;
  data = LoadCheck();
  if (data == BLOCK_DATA_JUMP){
    SetAnimaton(ANIMATION_URIEL_CHARGE_JUMP);
    D3DXVECTOR2 vector = JumpAngleSeek(50.0f, 250.0f, 0.0f, GRAVITY);
    move_.x = vector.x;
    move_.y = vector.y;
  }

  // �o��K�i�Ȃ���
  else if (data == BLOCK_DATA_UP_STAIRS){
    SetAnimaton(ANIMATION_URIEL_CHARGE_JUMP);
    D3DXVECTOR2 vector = JumpAngleSeek(100.0f, 75.0f, 100.0f, GRAVITY);
    move_.x = vector.x;
    move_.y = vector.y;
  }

  // boro_interval_��0�ȉ��Ȃ�`���[�W���[�h���~�߂�
  if (boro_interval_ <= 0){
    charge_flag_ = false;

    // boro_gage_max_��true�Ȃ�\��
    if (boro_gage_max_){
      SetAnimaton(ANIMATION_URIEL_RUNAWAY);
      runaway_timer_ = 0;
      if (move_direction_ == DIRECTION_RIGHT){
        move_.x = kUrielMoveRunawaySpped;
      } else {
        move_.x = -kUrielMoveRunawaySpped;
      }
    } else {
      // �ʏ�ɖ߂�
      SetAnimaton(ANIMATION_URIEL_CRAWL);
      if (move_direction_ == DIRECTION_RIGHT){
        move_.x = kUrielMoveSpped;
      } else {
        move_.x = -kUrielMoveSpped;
      }
    }
  }
}

//=============================================================================
// �W�����v(�`���[�W)��Ԃ̍X�V
//-----------------------------------------------------------------------------
void Uriel::UpdateChargeJump(void){
  // �ړI�n�֌���������
  if (dest_position_ != D3DXVECTOR3(0.0f, 0.0f, 0.0f)){
    if (dest_position_.x - pos_.x < kUrielMoveChargeSpeed &&
        dest_position_.x - pos_.x > -kUrielMoveChargeSpeed){
      dest_position_ = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
    }
  }

  // �n�ʂƂ̓����蔻��
  HIT_CHECK check;
  D3DXVECTOR3 map(0.f, 0.f, 0.f);
  map = p_stage_->CheckMapTip2(&pos_, D3DXVECTOR3(size_.x / 4, 1.0f, 0.0f), &check);
  if (check.bottom == MAP_TYPE_NORMAL){
    SetAnimaton(ANIMATION_URIEL_CHARGE_CRAWL);
    if (move_direction_ == DIRECTION_RIGHT){
      move_.x = kUrielMoveChargeSpeed;
    } else {
      move_.x = -kUrielMoveChargeSpeed;
    }
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
  case URIEL_STATUS_CHARGE_CRAWL:
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
  

  const bool is_hit_x = (pos.x + size.x / 2) > (pos_.x - size_.x / 2) &&
                        (pos.x - size.x / 2) < (pos_.x - size_.x / 2);
  const bool is_hit_y = (pos.y + size.y / 2) >= (pos_.y - size_.y / 2) &&
                        (pos.y - size.y / 2) <= (pos_.y - size_.y / 2);

  return is_hit_x && is_hit_y;
}

//=============================================================================
// �{�[������
//-----------------------------------------------------------------------------
bool Uriel::CheckImageHit(const D3DXVECTOR3& pos, const D3DXVECTOR2& size) {
  D3DXVECTOR3 boro_pos = pos;
  //boro_pos.y += size_.y * 0.5f;

  return CheckHit(boro_pos, size);
}

//=============================================================================
// �n�C�n�C��Ԃł̃`�F�b�N
//-----------------------------------------------------------------------------
BLOCK_DATA Uriel::CrawlLoadCheck(void){
  HIT_CHECK check,checkold;
  map_ = p_stage_->CheckMapTip2(&pos_, D3DXVECTOR3(size_.x / 4, 1.0f, 0.0f), &check);
  p_stage_->CheckMapTip2(&old_position_, D3DXVECTOR3(size_.x / 4, 1.0f, 0.0f), &checkold);

  // �ڂ̑O�ɒn�ʂ������Ă��̌������ɃW�����v�ł���n�ʂ�����ꍇ
  if (check.bottom == MAP_TYPE_NORMAL){
    // �E�ɐi��ł�ꍇ
    if (move_direction_ == DIRECTION_RIGHT){
      if (check.bottom_right == MAP_TYPE_NONE){
        p_stage_->CheckMapTip2(&D3DXVECTOR3(pos_.x + move_.x, pos_.y, pos_.z),
                                D3DXVECTOR3(size_.x / 4, 1.0f, 0.0f), &check);
        if (check.bottom_right == MAP_TYPE_NORMAL){
          return BLOCK_DATA_JUMP;
        }
      }
    }
    // ���ɐi��ł�ꍇ
    else if (move_direction_ == DIRECTION_LEFT){
      if (check.bottom_left == MAP_TYPE_NONE){
        p_stage_->CheckMapTip2(&D3DXVECTOR3(pos_.x + move_.x, pos_.y, pos_.z),
                                D3DXVECTOR3(size_.x / 4, 1.0f, 0.0f), &check);
        if (check.bottom_left == MAP_TYPE_NORMAL){
          return BLOCK_DATA_JUMP;
        }
      }
    }
  }

  // �o��K�i�����ׂ�
  map_ = p_stage_->CheckMapTip2(&D3DXVECTOR3(pos_.x, pos_.y, pos_.z),
                                 D3DXVECTOR3(size_.x / 4, size_.y / 4, 0.0f), &check);
  if (check.bottom == MAP_TYPE_NORMAL){
    // �E�ɐi��ł�ꍇ
    if (move_direction_ == DIRECTION_RIGHT){
      if(check.right == MAP_TYPE_NORMAL){
        map_ = p_stage_->CheckMapTip2(&D3DXVECTOR3(pos_.x + size_.x / 4, pos_.y, pos_.z),
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
        p_stage_->CheckMapTip2(&D3DXVECTOR3(pos_.x - size_.x / 4, pos_.y, pos_.z),
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

  return BLOCK_DATA_ERROR;
}

//=============================================================================
// �`���[�W�n�C�n�C��Ԃł̃`�F�b�N
//-----------------------------------------------------------------------------
BLOCK_DATA Uriel::ChargeCrawlLoadCheck(void){
  HIT_CHECK check;
  p_stage_->CheckMapTip2(&pos_, D3DXVECTOR3(size_.x / 4, 1.0f, 0.0f), &check);

  if (check.bottom == MAP_TYPE_NORMAL){
    // �E�ɐi��ł�ꍇ
    if (move_direction_ == DIRECTION_RIGHT){
      if (check.bottom_right == MAP_TYPE_NONE){
        p_stage_->CheckMapTip2(&D3DXVECTOR3(pos_.x + move_.x, pos_.y, pos_.z),
                                D3DXVECTOR3(size_.x / 4, 1.0f, 0.0f), &check);
        if (check.bottom == MAP_TYPE_NONE){
          if (check.bottom_right == MAP_TYPE_NORMAL){
            return BLOCK_DATA_JUMP;
          }
          p_stage_->CheckMapTip2(&D3DXVECTOR3(pos_.x + size_.x + move_.x, pos_.y, pos_.z),
                                  D3DXVECTOR3(size_.x / 4, 1.0f, 0.0f), &check);
          if (check.bottom_right == MAP_TYPE_NORMAL){
            return BLOCK_DATA_JUMP;
          }
        }
      }
    }
    // ���ɐi��ł�ꍇ
    else if (move_direction_ == DIRECTION_LEFT){
      if (check.bottom_left == MAP_TYPE_NONE){
        p_stage_->CheckMapTip2(&D3DXVECTOR3(pos_.x + move_.x, pos_.y, pos_.z),
                                D3DXVECTOR3(size_.x / 4, 1.0f, 0.0f), &check);
        if (check.bottom == MAP_TYPE_NONE){
          if (check.bottom_left == MAP_TYPE_NORMAL){
            return BLOCK_DATA_JUMP;
          }
          p_stage_->CheckMapTip2(&D3DXVECTOR3(pos_.x - size_.x + move_.x, pos_.y, pos_.z),
                                  D3DXVECTOR3(size_.x / 4, 1.0f, 0.0f), &check);
          if (check.bottom_left == MAP_TYPE_NORMAL){
            return BLOCK_DATA_JUMP;
          }
        }
      }
    }
  }

  // �o��K�i�����ׂ�
  map_ = p_stage_->CheckMapTip2(&D3DXVECTOR3(pos_.x, pos_.y, pos_.z),
                                 D3DXVECTOR3(size_.x / 4, size_.y / 4, 0.0f), &check);
  if (check.bottom == MAP_TYPE_NORMAL){
    // �E�ɐi��ł�ꍇ
    if (move_direction_ == DIRECTION_RIGHT){
      if(check.right == MAP_TYPE_NORMAL){
        map_ = p_stage_->CheckMapTip2(&D3DXVECTOR3(pos_.x + size_.x / 4, pos_.y, pos_.z),
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
        p_stage_->CheckMapTip2(&D3DXVECTOR3(pos_.x + size_.x / 4, pos_.y, pos_.z),
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

//=============================================================================
// �ړ������̎w��
//-----------------------------------------------------------------------------
void Uriel::SetDirection(DIRECTION direction){
  if (move_direction_ != direction){
    move_.x *= -1;
  }
  move_direction_ = direction;
}

//=============================================================================
// �H�ׂ�ʒu��Ԃ�
//-----------------------------------------------------------------------------
const D3DXVECTOR3 Uriel::GetEatPos(void) const {
  D3DXVECTOR3 pos_offset = kEatPosOffset;
  if (this->move_direction_ == AnimationObject::DIRECTION::DIRECTION_LEFT) {
    pos_offset.x *= -1;
  }
  return pos_ + pos_offset;
}

// EOF