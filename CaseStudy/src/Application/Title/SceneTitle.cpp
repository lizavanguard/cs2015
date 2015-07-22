//******************************************************************************
//
// SceneTitle  [SceneTitle.h]
// Author  :  SHOHEI MATSUMOTO
// 更新日  :  2015/06/26
//
//******************************************************************************
//******************************************************************************
// インクルードファイル
//******************************************************************************
#include "SceneTitle.h"
#include "Framework\FrameworkOption.h"
#include "Framework/Input/InputManagerHolder.h"
#include "Framework/Input/InputKeyboard.h"
#include "Framework/Input/InputXInput.h"

#include "Framework\Scene\SceneManager.h"
#include "Framework/Sound/sound.h"

#include "Application/StageSelect/SceneStageSelectFactory.h"
#include "Application\TitleBase\TitleCharBase.h"
#include "Application/Object/Object2D/StartSymbol.h"

//******************************************************************************
// マクロ定義
//******************************************************************************

//******************************************************************************
// グローバル宣言
//******************************************************************************


//******************************************************************************
// 関数定義
//******************************************************************************
//==============================================================================
// コンストラクタ
// 引数    :  無し
// 戻り値  :  無し
// Author  :  SHOHEI MATSUMOTO
// 更新日  :  2015/06/26
//==============================================================================
SceneTitle::SceneTitle()
  : is_end_(false)
  , p_start_symbol_(nullptr)
  , p_object2D(nullptr)
  , p_title_char_base(nullptr){

    p_start_symbol_ = new StartSymbol(D3DXVECTOR3(640.0f, 550.0f, 0.0f), 0.0f, D3DXVECTOR2(256.0f, 100.0f));

    p_object2D = new Object2D(D3DXVECTOR3(kWindowWidth * 0.5f, 380.0f, 0.0f), D3DXVECTOR2(kWindowWidth, 760.0f), "data/Texture/タイトル(仮).png");

    p_title_char_base = new TitleCharBase();

    PlaySound(SOUND_LABEL_BGM_TITLE);
}

//==============================================================================
// コンストラクタ
// 引数    :  無し
// 戻り値  :  無し
// Author  :  SHOHEI MATSUMOTO
// 更新日  :  2015/06/26
//==============================================================================
SceneTitle::~SceneTitle() {
  StopSound(SOUND_LABEL_BGM_TITLE);

  SafeDelete(p_start_symbol_);
  SafeDelete(p_object2D);
  SafeDelete(p_title_char_base);
}


//==============================================================================
// 更新処理
// 引数    :  SceneManager* p_scene_manager, const float elapsed_time
// 戻り値  :  無し
// Author  :  SHOHEI MATSUMOTO
// 更新日  :  2015/06/26
//==============================================================================
void SceneTitle::Update(SceneManager* p_scene_manager, const float elapsed_time) {
  auto& pKeyboard = InputManagerHolder::Instance().GetInputManager().GetPrimaryKeyboard();
  auto& pJoypad = InputManagerHolder::Instance().GetInputManager().GetPrimaryDevice();
  p_start_symbol_->Update();

  p_title_char_base->Update();

  if (!is_push_title_){
    p_start_symbol_->Update();
  }
  else{
    p_title_window->Update(p_scene_manager, elapsed_time);
  }
  // Next TitleScene
  if (InputManagerHolder::Instance().GetInputManager().GetPrimaryKeyboard().IsTrigger(DIK_RETURN) ||
      InputManagerHolder::Instance().GetInputManager().GetPrimaryDevice().IsTrigger(InputDevice::Pads::PAD_START) ||
      InputManagerHolder::Instance().GetInputManager().GetPrimaryDevice().IsTrigger(InputDevice::Pads::PAD_A)) {
      is_push_title_ = true;
  }
  if (InputManagerHolder::Instance().GetInputManager().GetPrimaryKeyboard().IsTrigger(DIK_BACKSPACE) ||
      InputManagerHolder::Instance().GetInputManager().GetPrimaryDevice().IsTrigger(InputDevice::Pads::PAD_B)){
      is_push_title_ = false;
  }
}


//==============================================================================
// 描画処理
// 引数    :  無し
// 戻り値  :  無し
// Author  :  SHOHEI MATSUMOTO
// 更新日  :  2015/06/26
//==============================================================================
void SceneTitle::Draw(void) {
    p_object2D->Draw();

    p_title_char_base->Draw();

    p_start_symbol_->Draw();
}



// EOF