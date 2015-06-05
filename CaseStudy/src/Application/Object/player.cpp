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
#include "Framework/Texture/TextureManagerHolder.h"
#include "AnimationObject\TextureAnimation.h"
#include "Uriel.h"
#include "player.h"

//******************************************************************************
// �}�N����`
//******************************************************************************


//******************************************************************************
// �v���g�^�C�v�錾
//******************************************************************************


//******************************************************************************
// �����o�ϐ�:
//******************************************************************************


//******************************************************************************
// �O���[�o���ϐ�:
//******************************************************************************


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
Player::Player(ANIMATION_EVENT animation_event) :AnimationObject(animation_event){
  player_mode_ = MODE_NONE;
  action_flag_ = false;
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
      AddPosY(-PLAYER_MOVE_SPEED);
  }
  if (pKeyboard.IsPress(DIK_S)) {
      AddPosY(PLAYER_MOVE_SPEED);
  }
  if (pKeyboard.IsPress(DIK_A)) {
      AddPosX(-PLAYER_MOVE_SPEED);
  }
  if (pKeyboard.IsPress(DIK_D)) {
      AddPosX(PLAYER_MOVE_SPEED);
  }
  // �K���K�����[�h�ؑ�
  // �E�U��
  if (pKeyboard.IsPress(DIK_RETURN)){
      SetAnimation(MODE_GUIDE);
      action_flag_ = true;
  }
  else if (pKeyboard.IsRelease(DIK_RETURN)){
      SetAnimation(MODE_NONE);
      action_flag_ = false;
  }


  if (player_mode_ == MODE_GUIDE){
      uriel_->SetDestPos(GetPos());
  }
  // �U�����[�h����莞�Ԉȏ�

  // �M�~�b�NON/OFF  
  //if (pKeyboard.IsTrigger(DIK_K)){
  //    SetAnimation(MODE_GIMMICK);
  //    action_flag_ = true;
  //}

  // �A�j���[�V�����X�V
  p_texture_animation_->UpdateAnimation();
}

//==============================================================================
// �`�揈��
// ����    :  ����
// �߂�l  :  ����
// Author  :  SHOHEI MATSUMOTO
// �X�V��  :  2015/05/22
//==============================================================================
void Player::Draw(void){
  auto p_device = DeviceHolder::Instance().GetDevice();

  static const float kSize = 50.0f;
  Vertex2D data[] = {
    { D3DXVECTOR3(pos_.x - kSize, pos_.y - kSize, 0.0f), 1.0f, 0xffffffff, D3DXVECTOR2(0.0f, 0.0f) },
    { D3DXVECTOR3(pos_.x + kSize, pos_.y - kSize, 0.0f), 1.0f, 0xffffffff, D3DXVECTOR2(1.0f, 0.0f) },
    { D3DXVECTOR3(pos_.x - kSize, pos_.y + kSize, 0.0f), 1.0f, 0xffffffff, D3DXVECTOR2(0.0f, 1.0f) },
    { D3DXVECTOR3(pos_.x + kSize, pos_.y + kSize, 0.0f), 1.0f, 0xffffffff, D3DXVECTOR2(1.0f, 1.0f) },
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

//==============================================================================
// �A�j���[�V�����Z�b�g����
// ����    :  PLAYER_MODE mode_
// �߂�l  :  ����
// Author  :  SHOHEI MATSUMOTO
// �X�V��  :  2015/05/29
//==============================================================================
void Player::SetAnimation(PLAYER_MODE mode_){
    if (player_mode_ != mode_){
        switch (mode_){
        case MODE_NONE:
            texture_id_ = p_texture_animation_->SetAnimation(ANIMATION_PLAYER_RATTEL_NONE);
            break;
        case MODE_GUIDE:
            texture_id_ = p_texture_animation_->SetAnimation(ANIMATION_PLAYER_RATTEL_SHAKE);
            break;
        case MODE_GIMMICK:
            texture_id_ = p_texture_animation_->SetAnimation(ANIMATION_PLAYER_RATTEL_SHAKE);
            break;
        }
        player_mode_ = mode_;
    }
}

// EOF