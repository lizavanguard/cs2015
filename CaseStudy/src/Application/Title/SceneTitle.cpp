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

#include "Framework\Scene\SceneManager.h"
#include "Framework/Sound/sound.h"
#include "Application\Object\BackGround\BackGroundManager.h"
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
  , p_background_manager_(nullptr)
  , p_start_symbol_(nullptr)
  , p_title_char_base(nullptr){

    p_background_manager_ = new BackGroundManager();

    p_start_symbol_ = new StartSymbol(D3DXVECTOR3(640.0f, 550.0f, 0.0f), 0.0f, D3DXVECTOR2(256.0f, 100.0f));

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

  SafeDelete(p_background_manager_);
  SafeDelete(p_start_symbol_);
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
  p_background_manager_->Update();

  p_start_symbol_->Update();

  p_title_char_base->Update();

  // Next TitleScene
  if (InputManagerHolder::Instance().GetInputManager().GetPrimaryKeyboard().IsTrigger(DIK_N)) {
      p_scene_manager->PushNextSceneFactory(new SceneStageSelectFactory());
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
    p_background_manager_->Draw();

    p_title_char_base->Draw();

    p_start_symbol_->Draw();
}



// EOF