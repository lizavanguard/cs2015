//******************************************************************************
//
// �N���A�^�C������  [ResultTime.h]
// Author  :  SHOHEI MATSUMOTO
// �X�V��  :  2015/06/29
//
//******************************************************************************
//******************************************************************************
// �C���N���[�h�t�@�C��
//******************************************************************************
#include "Framework\FrameworkOption.h"
#include "Framework/DirectXHelper/DeviceHolder.h"
#include "Framework/DirectXHelper/DirectXConst.h"
#include "Framework/Texture/TextureManagerHolder.h"

#include "Object2D.h"
#include "ResultTime.h"
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
namespace{
    const int kCountMax = kFPS * 5;

    const int kCountLimit = 99;

    const int kResultTime = 60;
}

//******************************************************************************
// �֐���`
//******************************************************************************
//==============================================================================
// �R���X�g���N�^
// ����    :  
// �߂�l  :  ����
// Author  :  SHOHEI MATSUMOTO
// �X�V��  :  2015/06/29
//==============================================================================
ResultTime::ResultTime(const D3DXVECTOR3 &pos, const float &rot, const D3DXVECTOR2 &size, NUMBER_TYPE type){
  value_ = 0;
  count_ = 0;
//  timer_value = timer->GetTimeValue();
  p_number_object_ = new NumberObject *[MAX_FIGURE];

  for (int num = 0; num < MAX_FIGURE; num++)
  {
      p_number_object_[num] = new NumberObject(D3DXVECTOR3(pos.x + 100.0f*num, pos.y, pos.z), rot, size, type);
      p_number_object_[num]->SetValue(0);
  }
}

//==============================================================================
// �f�X�g���N�^
// ����    :  ����
// �߂�l  :  ����
// Author  :  SHOHEI MATSUMOTO
// �X�V��  :  2015/06/29
//==============================================================================
ResultTime::~ResultTime(void){
  for (int num = 0; num < MAX_FIGURE; num++){
      delete p_number_object_[num];
      p_number_object_[num] = nullptr;
  }
  delete[] p_number_object_;
  p_number_object_ = nullptr;
}

//==============================================================================
// �X�V����
// ����    :  ����
// �߂�l  :  ����
// Author  :  SHOHEI MATSUMOTO
// �X�V��  :  2015/06/29
//==============================================================================
void ResultTime::Update(){
  // �J�E���g��
  if (count_ > kCountMax){
      value_ = kResultTime;
  }
  else{
      value_ += 21;
      ++count_;
  }
  if (value_ > kCountLimit)
      value_ -= kCountLimit;
  // ���̐ݒ�ϐ�
  unsigned int figure = (unsigned int)pow((float)FIGURE_DEFINE, MAX_FIGURE);
  for (int num = 0; num < MAX_FIGURE; num++)
  {
    // ����̌��̒l������
    int value = (value_ % figure) / (figure / FIGURE_DEFINE);
    // �l���Z�b�g
    p_number_object_[num]->SetValue(value);
    // �����炵
    figure /= FIGURE_DEFINE;
  }
}

//==============================================================================
// �`�揈��
// ����    :  ����
// �߂�l  :  ����
// Author  :  SHOHEI MATSUMOTO
// �X�V��  :  2015/06/29
//==============================================================================
void ResultTime::Draw(void){
  for (int num = 0; num < MAX_FIGURE; num++)
  {
      p_number_object_[num]->Draw();
  }
}


// EOF