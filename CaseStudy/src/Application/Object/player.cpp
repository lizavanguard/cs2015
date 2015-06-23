//******************************************************************************
//
// �v���C���[����  [plyaer.h]
// Author  :  SHOHEI MATSUMOTO
// �X�V��  :  2015/05/22
//
//******************************************************************************
//******************************************************************************
// �C���N���[�h�t�@�C��
//******************************************************************************
#include "Framework/DirectXHelper/DeviceHolder.h"
#include "Framework/DirectXHelper/DirectXConst.h"
#include "Framework/Input/InputManagerHolder.h"
#include "Framework/Input/InputKeyboard.h"
#include "Framework/Sound/sound.h"
#include "Framework/Texture/TextureManagerHolder.h"
#include "AnimationObject\TextureAnimation.h"
#include "Uriel.h"
#include "player.h"

//******************************************************************************
// �萔��`
//******************************************************************************
namespace {

const float kPlayerMoveSpeed = 10.0f;
const int kBoroRecastTime = 60;

}

//******************************************************************************
// �֐���`
//******************************************************************************
//==============================================================================
// �R���X�g���N�^
// ����    :  ANIMATION_EVENT animation_event
// �߂�l  :  ����
// Author  :  SHOHEI MATSUMOTO
// �X�V��  :  2015/05/22
//==============================================================================
Player::Player(ANIMATION_EVENT animation_event)
  : AnimationObject(animation_event)
  , player_mode_(MODE_NORMAL)
  , count_(0)
  , is_eat_(false) {
}

//==============================================================================
// �f�X�g���N�^
// ����    :  ����
// �߂�l  :  ����
// Author  :  SHOHEI MATSUMOTO
// �X�V��  :  2015/05/22
//==============================================================================
Player::~Player(void){
}

//==============================================================================
// �X�V����
// ����    :  Uriel *uriel_
// �߂�l  :  ����
// Author  :  SHOHEI MATSUMOTO
// �X�V��  :  2015/05/22
//==============================================================================
void Player::Update(Uriel *uriel_){
  auto& pKeyboard = InputManagerHolder::Instance().GetInputManager().GetPrimaryKeyboard();
  // �ړ�
  if (pKeyboard.IsPress(DIK_W)) {
    pos_.y += kPlayerMoveSpeed;
  }
  if (pKeyboard.IsPress(DIK_S)) {
    pos_.y -= kPlayerMoveSpeed;
  }
  if (pKeyboard.IsPress(DIK_A)) {
    pos_.x -= kPlayerMoveSpeed;
  }
  if (pKeyboard.IsPress(DIK_D)) {
    pos_.x += kPlayerMoveSpeed;
  }

  if (pKeyboard.IsPress(DIK_9)) {
	  //uriel_->SetAnimaton(ANIMATION_URIEL_RUNAWAY);
	  uriel_->BoroChage();
  }

  // �K���K�����[�h�ؑ�
  // �U��
  if (pKeyboard.IsPress(DIK_RETURN)){
    ChangeAnimation(MODE_GUIDE);
    PlaySound(SOUND_LABEL_SE_CALL0);
  }
  else if (pKeyboard.IsRelease(DIK_RETURN)){
    ChangeAnimation(MODE_NORMAL);
  }
  // �M�~�b�NON/OFF
  if (pKeyboard.IsTrigger(DIK_G)){
    ChangeAnimation(MODE_GIMMICK);
    PlaySound(SOUND_LABEL_SE_CALL1);
  }

  // �{�[��
  if (pKeyboard.IsTrigger(DIK_B)) {
    // �E���G������񂪐H�ׂĂ��Ȃ������� �{�[�����o��
    if (!is_eat_) {
      ChangeAnimation(MODE_BORO);
      PlaySound(SOUND_LABEL_SE_EAT);
    }
  }
  else if (pKeyboard.IsRelease(DIK_B)) {
    ChangeAnimation(MODE_NORMAL);
  }


  // ���[�h
  switch (player_mode_) {
    case MODE_NORMAL: // �ʏ펞
      break;
    case MODE_BORO: // �{�[��
      // if �E���G������񂪃{�[���H�ׂ��� �ʏ��Ԃɖ߂�
      // if (uriel->BoroCharge()) {
      if (pKeyboard.IsTrigger(DIK_N)) {
         ChangeAnimation(MODE_NORMAL);
         is_eat_ = true;
       }

      break;
    case MODE_GUIDE: // �U��
      // �E���G�������ړ�
      uriel_->SetDestPos(pos_);
      // �U�����[�h����莞�Ԉȏ�
      break;
    case MODE_GIMMICK: // �M�~�b�N
      // if �M�~�b�N�̃A�j���[�V�������I�������� �ʏ탂�[�h�ɖ߂�
      if (count_ >= /*p_texture_animation_->GetAnimationTime()*/ 60) {
        ChangeAnimation(MODE_NORMAL);
      }
      break;
  }

  // �A�j���[�V�����X�V
  p_texture_animation_->UpdateAnimation();

  // �{�[�����H�ׂ��Ă����� ��莞�Ԍo�߂Ō��ɖ߂�
  if (is_eat_ && count_ > kBoroRecastTime) {
    is_eat_ = false;
  }

  ++count_;
}

//==============================================================================
// �`�揈��
// ����    :  ����
// �߂�l  :  ����
// Author  :  SHOHEI MATSUMOTO
// �X�V��  :  2015/05/22
//==============================================================================
void Player::_PreProcessOfDraw(void){
  D3DXVECTOR2 texture_uv_ = p_texture_animation_->GetTextureUV();
  D3DXVECTOR2 texture_uv_offset_ = p_texture_animation_->GetTextureUVOffset();

  if (move_direction_ == DIRECTION_LEFT) {
      texture_uv_.x += texture_uv_offset_.x;
      texture_uv_offset_.x *= -1;
  }

  start_uv_ = texture_uv_;
  end_uv_ = texture_uv_ + texture_uv_offset_;
}

//==============================================================================
// �A�j���[�V�����Z�b�g����
// ����    :  PLAYER_MODE mode_
// �߂�l  :  ����
// Author  :  SHOHEI MATSUMOTO
// �X�V��  :  2015/05/29
//==============================================================================
void Player::ChangeAnimation(PLAYER_MODE mode){
  // if �v���C���[���[�h����v���Ă��Ȃ������� �A�j���[�V�����̕ύX
  if (player_mode_ != mode){
    switch (mode){
    case MODE_NORMAL:
      texture_id_ = p_texture_animation_->SetAnimation(ANIMATION_PLAYER_RATTEL_NONE);
      break;
    case MODE_BORO:
      texture_id_ = p_texture_animation_->SetAnimation(ANIMATION_PLAYER_RATTEL_BORO);
      break;
    case MODE_GUIDE:
      texture_id_ = p_texture_animation_->SetAnimation(ANIMATION_PLAYER_RATTEL_SHAKE);
      break;
    case MODE_GIMMICK:
      texture_id_ = p_texture_animation_->SetAnimation(ANIMATION_PLAYER_RATTEL_GIMMICK);
      break;
    }
    player_mode_ = mode;
  }

  // �J�E���g���Z�b�g
  count_ = 0;
}

// EOF