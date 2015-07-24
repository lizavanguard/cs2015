//******************************************************************************
//
// GamePauseWindow  [GamePauseWindow.cpp]
// Author  :  SHOHEI MATSUMOTO
// 更新日  :  2015/07/07
//
//******************************************************************************
//******************************************************************************
// インクルードファイル
//******************************************************************************
#include "GamePauseWindow.h"
#include "Framework\FrameworkOption.h"
#include "Framework/Input/InputManagerHolder.h"
#include "Framework/Input/InputKeyboard.h"
#include "Framework\Scene\SceneManager.h"
#include "Framework/Input/InputXInput.h"

#include "Application\Game\SceneGameFactory.h"
#include "Application\Title\SceneTitleFactory.h"
#include "Application\StageSelect\SceneStageSelectFactory.h"
#include "Application/Object/Object2D/WindowBack.h"
#include "Application\Object\Object2D\Char.h"
#include "Application\GameCursor\GameCursor.h"

//******************************************************************************
// マクロ定義
//******************************************************************************

//******************************************************************************
// グローバル宣言
//******************************************************************************
namespace{

  const D3DXVECTOR3 kWinPos = { kWindowWidth * 0.5f, kWindowHeight * 0.5f + 20.0f, 0.0f };
  const D3DXVECTOR2 kWinSize = { 500.0f, 765.0f };

  const D3DXVECTOR3 kPauseCharPos = { kWindowWidth * 0.5f, kWindowHeight * 0.5f - 275.0f , 0.0f};
  const D3DXVECTOR2 kPauseCharSize = { 250.0f , 120.0f};

  const D3DXVECTOR3 kCharPos[] = { { kWindowWidth * 0.5f + 175.0f, kWindowHeight * 0.5f - 75.0f, 0.0f }, 
      { kWindowWidth * 0.5f + 175.0f, kWindowHeight * 0.5f + 60.0f, 0.0f },
      { kWindowWidth * 0.5f + 175.0f, kWindowHeight * 0.5f + 200.0f, 0.0f },
      { kWindowWidth * 0.5f + 175.0f, kWindowHeight * 0.5f + 340.0f, 0.0f },
                             };
  const D3DXVECTOR2 kCharSize[] = { { 300.0f, 100.0f },
                                  { 300.0f, 100.0f },
                                  { 300.0f, 100.0f },
                                  { 300.0f, 100.0f },
                              };

  const D3DXVECTOR2 kCursorSize = { 100.0f, 100.0f };
  const char* kCursorTextureFilename = "data/Texture/bo-ro.png";

  const float kRot = 0.0f;

}

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
GamePauseWindow::GamePauseWindow()
  : p_window_back_(nullptr)
  , p_char_(nullptr)
  , p_object2D_(nullptr)
  , p_game_cursor_(nullptr){

  p_window_back_ = new WindowBack(kWinPos, kRot, kWinSize);

  GameCursor::PositionContainer position_list;
  for (int thumb_count = 0; thumb_count < MAX; ++thumb_count) {
      position_list.push_back(kCharPos[thumb_count]);
  }
  p_game_cursor_ = new GameCursor(kCursorSize, DIK_RIGHT, DIK_LEFT, DIK_RETURN, DIK_BACKSPACE, position_list);
}

//==============================================================================
// コンストラクタ
// 引数    :  無し
// 戻り値  :  無し
// Author  :  SHOHEI MATSUMOTO
// 更新日  :  2015/07/07
//==============================================================================
GamePauseWindow::~GamePauseWindow() {
    SafeDelete(p_window_back_);
    SafeDelete(p_game_cursor_);
}


//==============================================================================
// 更新処理
// 引数    :  無し
// 戻り値  :  無し
// Author  :  SHOHEI MATSUMOTO
// 更新日  :  2015/07/07
//==============================================================================
void GamePauseWindow::Update(SceneManager* p_scene_manager, const float elapsed_time, GamePause* p_game_pause_) {

  p_game_cursor_->Update(elapsed_time);

  const int index = p_game_cursor_->GetCursorIndex();

  auto& keyboard = InputManagerHolder::Instance().GetInputManager().GetPrimaryKeyboard();
  auto& pJoypad = InputManagerHolder::Instance().GetInputManager().GetPrimaryDevice();
  if (keyboard.IsTrigger(DIK_RETURN) || pJoypad.IsTrigger(InputDevice::Pads::PAD_A)) {
      if (index == GAMESCENE_BACK)
          p_game_pause_->SetPause(false);
      else if (index == RETRY)
           p_scene_manager->PushNextSceneFactory(new SceneGameFactory());
      else if (index == STAGE_SELECT)
          p_scene_manager->PushNextSceneFactory(new SceneStageSelectFactory());
      else if (index == TITLESCENE_BACK)
          p_scene_manager->PushNextSceneFactory(new SceneTitleFactory());
  }

}


//==============================================================================
// 描画処理
// 引数    :  無し
// 戻り値  :  無し
// Author  :  SHOHEI MATSUMOTO
// 更新日  :  2015/07/07
//==============================================================================
void GamePauseWindow::Draw(void) {
  p_window_back_->Draw();

  p_game_cursor_->Draw();
}



// EOF