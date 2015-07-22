//******************************************************************************
//
// TitleCharBase  [TitleCharBase.h]
// Author  :  SHOHEI MATSUMOTO
// �X�V��  :  2015/06/30
//
//******************************************************************************
//******************************************************************************
// �C���N���[�h�t�@�C��
//******************************************************************************
#include "Framework\FrameworkOption.h"
#include "Framework/GameWindow/GameDirectX.h"
#include "Framework/Texture/TextureManagerHolder.h"
#include "Framework/GameManager/GameManager.h"

#include "Framework/DebugProc/DebugProc.h"
#include "Application\Object\Object2D\TitleChar.h"
#include "TitleCharBase.h"

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
namespace {

    const char* kTextureFilename[] = { "data/Texture/��.png" 
                                        , "data/Texture/��.png" 
                                        , "data/Texture/��.png" 
                                        , "data/Texture/��.png" 
                                        , "data/Texture/��.png" 
                                        , "data/Texture/��.png" 
                                        , "data/Texture/��.png" 
                                        , "data/Texture/��.png" };

    const float kCharSpace = 150.0f;

    const float kCharSpace2 = 25.0f;

    const float kHalfWindowWidth = kWindowWidth * 0.5f;

    const D3DXVECTOR3 kStartPos[] = { { -75.0f - kCharSpace2 - kCharSpace + kHalfWindowWidth, 150.0f, 0.0f }
                                    , { -75.0f - kCharSpace2 + kHalfWindowWidth, 150.0f, 0.0f }
                                    , { 75.0f - kCharSpace2 + kHalfWindowWidth, 150.0f, 0.0f }
                                    , { 75.0f - kCharSpace2 + kCharSpace + kHalfWindowWidth, 150.0f, 0.0f }
                                    , { -75.0f + kCharSpace2 - kCharSpace + kHalfWindowWidth, 300.0f, 0.0f }
                                    , { -75.0f + kCharSpace2 + kHalfWindowWidth, 300.0f, 0.0f }
                                    , { 75.0f + kCharSpace2 + kHalfWindowWidth, 300.0f, 0.0f }
                                    , { 75.0f + kCharSpace2 + kCharSpace + kHalfWindowWidth, 300.0f, 0.0f } };

    const float kPosMoveMax[] = { 50.0f, 50.0f, 50.0f
                                , 50.0f, 50.0f, 50.0f
                                , 50.0f, 50.0f
                                };

    const float kChangeSpeed[] = { 2.0f, 1.8f, 1.6f 
                                 , 1.4f, 1.4f, 1.6f 
                                 , 1.8f, 2.0f
                                 };

    const int kTitleCharNum = 8;


}

//******************************************************************************
// �֐���`
//******************************************************************************
//==============================================================================
// �R���X�g���N�^
// ����    :  ����
// �߂�l  :  ����
// Author  :  SHOHEI MATSUMOTO
// �X�V��  :  2015/06/30
//==============================================================================
TitleCharBase::TitleCharBase() 
    : p_title_char(nullptr){

    p_title_char = new TitleChar* [kTitleCharNum];

    for (int i = 0; i < kTitleCharNum; i++)
    {
        p_title_char[i] = new TitleChar(kStartPos[i], 0.0f, D3DXVECTOR2(100.0f, 100.0f), 
                                         kChangeSpeed[i] , kPosMoveMax[i], kTextureFilename[i]);
    }

}

//==============================================================================
// �f�X�g���N�^
// ����    :  ����
// �߂�l  :  ����
// Author  :  SHOHEI MATSUMOTO
// �X�V��  :  2015/06/30
//==============================================================================
TitleCharBase::~TitleCharBase(void){
  for (int i = 0; i < kTitleCharNum; i++){
      delete p_title_char[i];
      p_title_char[i] = nullptr;
  }
  delete[] p_title_char;
  p_title_char = nullptr;
}

//==============================================================================
// �X�V����
// ����    :  ����
// �߂�l  :  ����
// Author  :  SHOHEI MATSUMOTO
// �X�V��  :  2015/06/30
//==============================================================================
void TitleCharBase::Update(){
  for (int i = 0; i < kTitleCharNum; i++){
      p_title_char[i]->Update(kPosMoveMax[i]);
  }
}

//==============================================================================
// �`�揈��
// ����    :  ����
// �߂�l  :  ����
// Author  :  SHOHEI MATSUMOTO
// �X�V��  :  2015/06/30
//==============================================================================
void TitleCharBase::Draw(void){
  for (int i = 0; i < kTitleCharNum; i++){
    p_title_char[i]->Draw();
  }
}


// EOF