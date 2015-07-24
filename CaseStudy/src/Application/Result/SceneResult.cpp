//******************************************************************************
//
// SceneResult  [SceneResult.h]
// Author  :  SHOHEI MATSUMOTO
// 更新日  :  2015/06/26
//
//******************************************************************************
//******************************************************************************
// インクルードファイル
//******************************************************************************
#include "SceneResult.h"
#include "Framework\FrameworkOption.h"
#include "Application/Title/SceneTitleFactory.h"
#include "Application/Game/SceneGameFactory.h"
#include "Framework/Input/InputManagerHolder.h"
#include "Framework/Input/InputKeyboard.h"
#include "Framework\Input\InputDevice.h"
#include "Framework/Scene/SceneManager.h"
#include "Framework/Sound/sound.h"
#include "Framework/Utility/PersistentValue.h"

#include "Application/Object/Object2D/Timer.h"
#include "Application/Object/Object2D/ResultTime.h"
#include "Application\Object\Object2D\StartSymbol.h"
#include "Application\Object\BackGround\BackGroundManager.h"

//******************************************************************************
// 定数定義
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
SceneResult::SceneResult()
    : is_end_(false)
    , p_result_time(nullptr)
    , p_object2D(nullptr)
    , p_start_symbol_(nullptr)
    , p_background_manager_(nullptr)
    , p_time_up_(nullptr)
    ,time_up_(false){

  p_background_manager_ = new BackGroundManager();

  p_object2D = new Object2D(D3DXVECTOR3(300.0f, 100.0f, 0.0f), D3DXVECTOR2(256.0f, 100.0f), "data/Texture/result_message.png");

  p_time_up_ = new Object2D(D3DXVECTOR3(600.0f, 250.0f, 0.0f), D3DXVECTOR2(600.0f, 100.0f), "data/Texture/game_timeup.png");

  int resultTime = PersistentValue::Instance().GetData("Score");

  if (resultTime <= 0){
    time_up_ = true;
  }

  p_result_time = new ResultTime(D3DXVECTOR3(300.0f, 250.0f, 0.0f), 0.0f, D3DXVECTOR2(150.0f, 100.0f), resultTime,TIMER);

  p_start_symbol_ = new StartSymbol(D3DXVECTOR3(300.0f, 600.0f, 0.0f), 0.0f, D3DXVECTOR2(256.0f, 100.0f));

  PlaySound(SOUND_LABEL_BGM_RESULT);
}

//==============================================================================
// コンストラクタ
// 引数    :  無し
// 戻り値  :  無し
// Author  :  SHOHEI MATSUMOTO
// 更新日  :  2015/06/26
//==============================================================================
SceneResult::~SceneResult() {
  StopSound(SOUND_LABEL_BGM_RESULT);

  SafeDelete(p_result_time);
  SafeDelete(p_start_symbol_);
  SafeDelete(p_background_manager_);
  SafeDelete(p_object2D);
  SafeDelete(p_time_up_);
}


//==============================================================================
// 更新処理
// 引数    :  SceneManager* p_scene_manager, const float elapsed_time
// 戻り値  :  無し
// Author  :  SHOHEI MATSUMOTO
// 更新日  :  2015/06/26
//==============================================================================
void SceneResult::Update(SceneManager* p_scene_manager, const float elapsed_time) {
  p_background_manager_->Update();

  if (p_result_time->GetEnd()){
    // Next TitleScene
    if (InputManagerHolder::Instance().GetInputManager().GetPrimaryKeyboard().IsTrigger(DIK_RETURN)||
      InputManagerHolder::Instance().GetInputManager().GetPrimaryDevice().IsTrigger(InputDevice::Pads::PAD_START) ||
      InputManagerHolder::Instance().GetInputManager().GetPrimaryDevice().IsTrigger(InputDevice::Pads::PAD_A)) {
      SceneTitleFactory* pTitleSceneFactory = new SceneTitleFactory();
      p_scene_manager->PushNextSceneFactory(pTitleSceneFactory);
    }
  }

  p_result_time->Update();

  if (p_result_time->GetEnd() || time_up_){
    p_start_symbol_->Update();
  }
}


//==============================================================================
// 描画処理
// 引数    :  無し
// 戻り値  :  無し
// Author  :  SHOHEI MATSUMOTO
// 更新日  :  2015/06/26
//==============================================================================
void SceneResult::Draw(void) {
  p_background_manager_->Draw();

  if (!time_up_){
    p_result_time->Draw();
  } else{
    p_time_up_->Draw();
  }

  if (p_result_time->GetEnd() || time_up_){
    p_start_symbol_->Draw();
  }

  p_object2D->Draw();
}



// EOF