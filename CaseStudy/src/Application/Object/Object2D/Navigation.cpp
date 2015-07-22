//******************************************************************************
//
// �i���o�[�I�u�W�F�N�g����  [NaviGation.h]
// Author  :  SHOHEI MATSUMOTO
// �X�V��  :  2015/06/16
//
//******************************************************************************
//******************************************************************************
// �C���N���[�h�t�@�C��
//******************************************************************************
#include "Framework/DirectXHelper/DeviceHolder.h"
#include "Framework/DirectXHelper/DirectXConst.h"
#include "Framework/GameWindow/GameDirectX.h"
#include "Framework/Texture/TextureManagerHolder.h"
#include "NaviGation.h"
#include "Framework\GameManager\GameManager.h"
#include "Framework\DebugProc\DebugProc.h"

#include "Application/Camera/camera.h"
#include "Application/Object/Uriel.h"
//******************************************************************************
// �}�N����`
//******************************************************************************

namespace {

const float ksizespeed = 5.0f;
const float kfullsize = 250.0f;
const float kminsize = 100.0f;
}
//******************************************************************************
// �v���g�^�C�v�錾
//******************************************************************************


//******************************************************************************
// �����o�ϐ�:
//******************************************************************************


//******************************************************************************
// �O���[�o���ϐ�:
//******************************************************************************
static const char *s_Navigation[] = {
    "data/Texture/arrow_up.png",
    "data/Texture/arrow_bottom.png",
    "data/Texture/arrow_right.png",
    "data/Texture/arrow_left.png",
};

//******************************************************************************
// �֐���`
//******************************************************************************
//==============================================================================
// �R���X�g���N�^
// ����    :  ����
// �߂�l  :  ����
// Author  :  SHOHEI MATSUMOTO
// �X�V��  :  2015/06/12
//==============================================================================
NaviGation::NaviGation(const D3DXVECTOR3 &pos, const float &rot, const D3DXVECTOR2 &size,int type)
:Object2D(pos, size, s_Navigation[0])
{
  //pos_ = pos;
  rot_ = rot;
  size_ = size;
  size_change = ksizespeed;
  SetTexture(s_Navigation[type]);
}

//==============================================================================
// �f�X�g���N�^
// ����    :  ����
// �߂�l  :  ����
// Author  :  SHOHEI MATSUMOTO
// �X�V��  :  2015/06/12
//==============================================================================
//NaviGation::~NaviGation(void){
//
//}

void NaviGation::Update(){
  size_.x += size_change;
  size_.y += size_change;
  if (size_.x > kfullsize)
  {
    size_.x = kfullsize;
    size_.y = kfullsize;
    size_change *= -1;
  }
  if (size_.x < kminsize)
  {
    size_.x = kminsize;
    size_.y = kminsize;
    size_change *= -1;
  }
}

//==============================================================================
// �`�揈��
// ����    :  ����
// �߂�l  :  ����
// Author  :  SHOHEI MATSUMOTO
// �X�V��  :  2015/06/12
//==============================================================================
void NaviGation::_PreProcessOfDraw(void){
}

void NaviGation::_PostProcessOfDraw(void){
}


// EOF