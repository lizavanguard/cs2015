//******************************************************************************
//
// GamePause  [GamePause.cpp]
// Author  :  SHOHEI MATSUMOTO
// 更新日  :  2015/07/07
//
//******************************************************************************
//******************************************************************************
// インクルードファイル
//******************************************************************************
#include "GamePause.h"
#include "Framework/FrameworkOption.h"
#include "Application/Title/SceneTitleFactory.h"
#include "Application/Game/SceneGameFactory.h"
#include "Framework/Input/InputManagerHolder.h"
#include "Framework/Input/InputKeyboard.h"
#include "Framework/Input/InputXInput.h"

#include "Application/GamePause/GamePauseWindow.h"

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
// 更新日  :  2015/07/07
//==============================================================================
GamePause::GamePause()
  : is_end_(false)
  , is_pause_(false)
  , p_game_pause_window_(nullptr){

    p_game_pause_window_ = new GamePauseWindow;
}

//==============================================================================
// コンストラクタ
// 引数    :  無し
// 戻り値  :  無し
// Author  :  SHOHEI MATSUMOTO
// 更新日  :  2015/07/07
//==============================================================================
GamePause::~GamePause() {
    SafeDelete(p_game_pause_window_);
}


//==============================================================================
// 更新処理
// 引数    :  無し
// 戻り値  :  無し
// Author  :  SHOHEI MATSUMOTO
// 更新日  :  2015/07/07
//==============================================================================
void GamePause::Update(SceneManager* p_scene_manager, const float elapsed_time, GamePause* p_game_pause_) {
  auto& pJoypad = InputManagerHolder::Instance().GetInputManager().GetPrimaryDevice();
  // タイトル・ステージセレクト・リトライ・戻る
  if (is_pause_){
      p_game_pause_window_->Update(p_scene_manager, elapsed_time, p_game_pause_);
    // Next TitleScene
  }
  if (pJoypad.IsTrigger(InputDevice::Pads::PAD_START) || InputManagerHolder::Instance().GetInputManager().GetPrimaryKeyboard().IsTrigger(DIK_P)) {
      if (is_pause_)
        SetPause(false);
      else
        SetPause(true);
  }
}


//==============================================================================
// 描画処理
// 引数    :  無し
// 戻り値  :  無し
// Author  :  SHOHEI MATSUMOTO
// 更新日  :  2015/07/07
//==============================================================================
void GamePause::Draw(void) {
  if (is_pause_){
      p_game_pause_window_->Draw();
  }
}



// EOF