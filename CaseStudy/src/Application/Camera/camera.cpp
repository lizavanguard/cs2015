//******************************************************************************
//
// �J��������  [camera.cpp]
// Author  :  SHOHEI MATSUMOTO
// �X�V��  :  2015/06/09
//
//******************************************************************************
//******************************************************************************
// �C���N���[�h�t�@�C��
//******************************************************************************
#include "Framework/DirectXHelper/DeviceHolder.h"
#include "Framework/DirectXHelper/DirectXConst.h"
#include "Framework/Input/InputManagerHolder.h"
#include "Framework/Input/InputXInput.h"
#include "Framework/Input/InputKeyboard.h"
#include "Application\Game\SceneGame.h"
#include "Application\Stage\Stage.h"
#include "Camera.h"

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
static const float kCameraSpeed = 10.0f;
static const float kStartZoomRate = 2.0f;

//******************************************************************************
// �֐���`
//******************************************************************************
//==============================================================================
// �R���X�g���N�^
// ����    :  ����
// �߂�l  :  ����
// Author  :  SHOHEI MATSUMOTO
// �X�V��  :  2015/06/09
//==============================================================================
Camera::Camera(Player* player , Stage* stage){
  player_ = player;
  stage_ = stage;
  posP_ = D3DXVECTOR3(0.0f , 0.0f , -5.0f);
  posR_ = D3DXVECTOR3(0.0f , 0.0f , 0.0f);
  vecU_ = D3DXVECTOR3(0.0f , 1.0f , 0.0f);
  rot_ = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
  zoomRate_ = kStartZoomRate;
  localView_ = D3DXVECTOR2(kWindowWidth / zoomRate_, kWindowHeight / zoomRate_);
  localScreenFrame_ = localView_;
}

//==============================================================================
// �f�X�g���N�^
// ����    :  ����
// �߂�l  :  ����
// Author  :  SHOHEI MATSUMOTO
// �X�V��  :  2015/06/09
//==============================================================================
Camera::~Camera(void){

}

//==============================================================================
// �X�V����
// ����    :  ����
// �߂�l  :  ����
// Author  :  SHOHEI MATSUMOTO
// �X�V��  :  2015/06/09
//==============================================================================
void Camera::Update(){
  auto& pKeyboard = InputManagerHolder::Instance().GetInputManager().GetPrimaryKeyboard();
//  auto& pJoypad = InputManagerHolder::Instance().GetInputManager().GetPrimaryDevice();

  // �J�����͈̔͊O
  if (player_->GetPos().x > (localView_.x / 5.0f * 2.0f) + posP_.x){
      posP_.x += kCameraSpeed;
      posR_.x += kCameraSpeed;
      localScreenFrame_.x += kCameraSpeed;
  }
  if (player_->GetPos().x < (-localView_.x / 5.0f * 2.0f) + posP_.x){
      posP_.x -= kCameraSpeed;
      posR_.x -= kCameraSpeed;
      localScreenFrame_.x -= kCameraSpeed;
  }
  if (player_->GetPos().y > (localView_.y / 5.0f * 1.3f) + posP_.y){
      posP_.y += kCameraSpeed;
      posR_.y += kCameraSpeed;
      localScreenFrame_.y += kCameraSpeed;
  }
  if (player_->GetPos().y < (-localView_.y / 5.0f * 2.4f) + posP_.y){
      posP_.y -= kCameraSpeed;
      posR_.y -= kCameraSpeed;
      localScreenFrame_.y -= kCameraSpeed;
  }

}

//==============================================================================
// �`�揈��
// ����    :  ����
// �߂�l  :  ����
// Author  :  SHOHEI MATSUMOTO
// �X�V��  :  2015/06/09
//==============================================================================
void Camera::Set(void){
  auto p_device = DeviceHolder::Instance().GetDevice();

  // �r���[�}�g���b�N�X������
  D3DXMatrixIdentity(&mtxView_);
  // �r���[�}�g���b�N�X�̍쐬
  D3DXMatrixLookAtLH(&mtxView_,
      &posP_,
      &posR_,
      &vecU_);
  // �r���[�}�g���b�N�X�̐ݒ�
  p_device->SetTransform(D3DTS_VIEW, &mtxView_);
  // �r���[�}�g���b�N�X�̏�����
  D3DXMatrixIdentity(&mtxProjection_);
  D3DXMatrixOrthoLH(&mtxProjection_, kWindowWidth / zoomRate_, kWindowHeight / zoomRate_, 0.0f, 10.0f);
  // �v���W�F�N�V�����}�g���b�N�X�̐ݒ�
  p_device->SetTransform(D3DTS_PROJECTION, &mtxProjection_);
}

// EOF