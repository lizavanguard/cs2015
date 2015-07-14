//******************************************************************************
//
// TitleCharBase  [TitleCharBase.h]
// Author  :  SHOHEI MATSUMOTO
// 更新日  :  2015/06/30
//
//******************************************************************************
//******************************************************************************
// インクルードファイル
//******************************************************************************
#include "Framework\FrameworkOption.h"
#include "Framework/GameWindow/GameDirectX.h"
#include "Framework/Texture/TextureManagerHolder.h"
#include "Framework/GameManager/GameManager.h"

#include "Framework/DebugProc/DebugProc.h"
#include "Application\Object\Object2D\TitleChar.h"
#include "TitleCharBase.h"

//******************************************************************************
// マクロ定義
//******************************************************************************


//******************************************************************************
// プロトタイプ宣言
//******************************************************************************


//******************************************************************************
// メンバ変数:
//******************************************************************************


//******************************************************************************
// グローバル変数:
//******************************************************************************
namespace {

    const char* kTextureFilename[] = { "data/Texture/titleChar.jpg" 
                                        , "data/Texture/titleChar.jpg" 
                                        , "data/Texture/titleChar.jpg" 
                                        , "data/Texture/titleChar.jpg" 
                                        , "data/Texture/titleChar.jpg" 
                                        , "data/Texture/titleChar.jpg" 
                                        , "data/Texture/titleChar.jpg" 
                                        , "data/Texture/titleChar.jpg" };

    const float kCharSpace = 50.0f;

    const D3DXVECTOR3 kStartPos[] = { { 350.0f, 150.0f, 0.0f }
                                    , { 500.0f, 150.0f, 0.0f }
                                    , { 650.0f, 150.0f, 0.0f }
                                    , { 800.0f, 150.0f, 0.0f }
                                    , { 350.0f, 300.0f, 0.0f }
                                    , { 500.0f, 300.0f, 0.0f }
                                    , { 650.0f, 300.0f, 0.0f }
                                    , { 800.0f, 300.0f, 0.0f } };

    const float kPosMoveMax[] = { 100.0f, 100.0f, 100.0f
                                , 100.0f, 100.0f, 100.0f
                                , 100.0f, 100.0f
                                };

    const float kChangeSpeed[] = { 3.5f, 2.5f, 2.5f 
                                 , 3.5f, 2.5f, 2.5f 
                                 , 3.5f, 2.5f
                                 };

    const int kTitleCharNum = 8;


}

//******************************************************************************
// 関数定義
//******************************************************************************
//==============================================================================
// コンストラクタ
// 引数    :  無し
// 戻り値  :  無し
// Author  :  SHOHEI MATSUMOTO
// 更新日  :  2015/06/30
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
// デストラクタ
// 引数    :  無し
// 戻り値  :  無し
// Author  :  SHOHEI MATSUMOTO
// 更新日  :  2015/06/30
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
// 更新処理
// 引数    :  無し
// 戻り値  :  無し
// Author  :  SHOHEI MATSUMOTO
// 更新日  :  2015/06/30
//==============================================================================
void TitleCharBase::Update(){
  for (int i = 0; i < kTitleCharNum; i++){
      p_title_char[i]->Update(kPosMoveMax[i]);
  }
}

//==============================================================================
// 描画処理
// 引数    :  無し
// 戻り値  :  無し
// Author  :  SHOHEI MATSUMOTO
// 更新日  :  2015/06/30
//==============================================================================
void TitleCharBase::Draw(void){
  for (int i = 0; i < kTitleCharNum; i++){
    p_title_char[i]->Draw();
  }
}


// EOF