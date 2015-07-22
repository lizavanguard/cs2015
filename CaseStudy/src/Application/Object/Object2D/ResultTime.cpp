//******************************************************************************
//
// �N���A�^�C������  [ResultTime.h]
// Author  :  SHOHEI MATSUMOTO
// �X�V��  :  2015/07/14
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

    const int kCountLimit = kOneMinute * 60;
}

//******************************************************************************
// �֐���`
//******************************************************************************
//==============================================================================
// �R���X�g���N�^
// ����    :  
// �߂�l  :  ����
// Author  :  SHOHEI MATSUMOTO
// �X�V��  :  2015/07/14
//==============================================================================
ResultTime::ResultTime(const D3DXVECTOR3 &pos, const float &rot, const D3DXVECTOR2 &size, const int &value, NUMBER_TYPE type){
  value_ = 0;
  count_ = 0;
  timer_value_ = value;

  p_number_object_ = new NumberObject *[kMaxFigure];

  for (int num = 0; num < 2; num++)
  {
      p_number_object_[num] = new NumberObject(D3DXVECTOR3(pos.x + 100.0f*num, pos.y, pos.z), rot, size, type);
      p_number_object_[num]->SetValue(0);
  }
  for (int num = 2; num < 4; num++)
  {
      p_number_object_[num] = new NumberObject(D3DXVECTOR3(pos.x + 100.0f*num+20.0f, pos.y, pos.z), rot, size, type);
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
    for (int num = 0; num < kMaxFigure; num++){
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
// �X�V��  :  2015/07/14
//==============================================================================
void ResultTime::Update(){
  // ��莞�Ԃ���������^�C����\������
  if (count_ > kCountMax){
      value_ = timer_value_;
  }
  // �K���ɒl�𓮂���
  else{
      value_ += 2121;
      ++count_;
  }
  if (value_ > kCountLimit)
      value_ -= kCountLimit;
  // ���ԕϐ�
  int minuteTime = value_ / kOneMinute;
  int secondTime = value_ - minuteTime * kOneMinute;
  // ���̐ݒ�ϐ�
  unsigned int figure = (unsigned int)pow((float)kFigureDefine, kMaxFigure*0.5f);
  // ��
  for (int num = 0; num < 2; num++)
  {
      // ����̌��̒l������
      int value = (minuteTime % figure) / (figure / kFigureDefine);
      // �l���Z�b�g
      p_number_object_[num]->SetValue(value);
      // �����炵
      figure /= kFigureDefine;
  }
  // �b
  figure = (unsigned int)pow((float)kFigureDefine, kMaxFigure*0.5f);
  for (int num = 2; num < 4; num++)
  {
      // ����̌��̒l������
      int value = (secondTime % figure) / (figure / kFigureDefine);
      // �l���Z�b�g
      p_number_object_[num]->SetValue(value);
      // �����炵
      figure /= kFigureDefine;
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
  for (int num = 0; num < kMaxFigure; num++)
  {
      p_number_object_[num]->Draw();
  }
}


// EOF