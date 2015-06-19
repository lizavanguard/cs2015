//******************************************************************************
//
// �^�C�}�[����  [timer.h]
// Author  :  SHOHEI MATSUMOTO
// �X�V��  :  2015/06/16
//
//******************************************************************************
//******************************************************************************
// �C���N���[�h�t�@�C��
//******************************************************************************
#include "Framework/DirectXHelper/DeviceHolder.h"
#include "Framework/DirectXHelper/DirectXConst.h"
#include "Framework/Texture/TextureManagerHolder.h"
#include "Object2D.h"
#include "Timer.h"
#include "Framework\GameManager\GameManager.h"
#include "Framework\DebugProc\DebugProc.h"

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
// ����    :  
// �߂�l  :  ����
// Author  :  SHOHEI MATSUMOTO
// �X�V��  :  2015/06/16
//==============================================================================
Timer::Timer(const D3DXVECTOR3 &pos, const float &rot, const D3DXVECTOR2 &size, NUMBER_TYPE type){
  value_ = TIMER_COUNT;
  count_ = 0;

  p_numberObject_ = new NumberObject * [2];

  for (int num = 0; num < MAX_FIGURE; num++)
  {
      p_numberObject_[num] = new NumberObject(D3DXVECTOR3(pos.x + 40.0f*num, pos.y, pos.z), rot, size, type);
      p_numberObject_[num]->SetValue(0);
  }
}

//==============================================================================
// �f�X�g���N�^
// ����    :  ����
// �߂�l  :  ����
// Author  :  SHOHEI MATSUMOTO
// �X�V��  :  2015/06/16
//==============================================================================
Timer::~Timer(void){
  for (int num = 0; num < MAX_FIGURE; num++){
    delete p_numberObject_[num];
    p_numberObject_[num] = nullptr;
  }
  delete[] p_numberObject_;
  p_numberObject_ = nullptr;
}

//==============================================================================
// �X�V����
// ����    :  ����
// �߂�l  :  ����
// Author  :  SHOHEI MATSUMOTO
// �X�V��  :  2015/06/16
//==============================================================================
void Timer::Update(){
  ++count_;
  if ((count_ % 30) == 0)
  {
    --value_;
    // �^�C�����Z�b�g
    if (value_ < 0)
        value_ = TIMER_COUNT;
    count_ = 0;
  }
  // ���̐ݒ�ϐ�
  unsigned int figure = (unsigned int)pow((float)FIGURE_DEFINE, MAX_FIGURE);
  for (int num = 0; num < MAX_FIGURE; num++)
  {
    // ����̌��̒l������
    int value = (value_ % figure) / (figure / FIGURE_DEFINE);
    // �l���Z�b�g
    p_numberObject_[num]->SetValue(value);
    // �����炵
    figure /= FIGURE_DEFINE;
  }
}

//==============================================================================
// �`�揈��
// ����    :  ����
// �߂�l  :  ����
// Author  :  SHOHEI MATSUMOTO
// �X�V��  :  2015/06/16
//==============================================================================
void Timer::Draw(void){
  for (int num = 0; num < MAX_FIGURE; num++)
  {
      p_numberObject_[num]->Draw();
  }
}


// EOF