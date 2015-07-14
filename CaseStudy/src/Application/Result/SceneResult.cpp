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
#include "Framework/Scene/SceneManager.h"
#include "Framework/Utility/PersistentValue.h"

#include "Application/Object/Object2D/Timer.h"
#include "Application/Object/Object2D/ResultTime.h"
#include "Application\Object\Object2D\StartSymbol.h"


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
    , p_start_symbol_(nullptr){

    p_object2D = new Object2D(D3DXVECTOR3(300.0f, 100.0f, 0.0f), D3DXVECTOR2(256.0f, 100.0f), "data/Texture/title.jpg");

    p_result_time = new ResultTime(D3DXVECTOR3(300.0f, 250.0f, 0.0f), 0.0f, D3DXVECTOR2(150.0f, 100.0f) , TIMER);

    int a = PersistentValue::Instance().GetData("Score");

    p_start_symbol_ = new StartSymbol(D3DXVECTOR3(300.0f, 600.0f, 0.0f), 0.0f, D3DXVECTOR2(256.0f, 100.0f));
}

//==============================================================================
// コンストラクタ
// 引数    :  無し
// 戻り値  :  無し
// Author  :  SHOHEI MATSUMOTO
// 更新日  :  2015/06/26
//==============================================================================
SceneResult::~SceneResult() {
    SafeDelete(p_result_time);
    SafeDelete(p_start_symbol_);
    SafeDelete(p_object2D);
}


//==============================================================================
// 更新処理
// 引数    :  SceneManager* p_scene_manager, const float elapsed_time
// 戻り値  :  無し
// Author  :  SHOHEI MATSUMOTO
// 更新日  :  2015/06/26
//==============================================================================
void SceneResult::Update(SceneManager* p_scene_manager, const float elapsed_time) {
    p_result_time->Update();
  
    p_start_symbol_->Update();

  // Next TitleScene
  if (InputManagerHolder::Instance().GetInputManager().GetPrimaryKeyboard().IsTrigger(DIK_N)) {
      SceneTitleFactory* pTitleSceneFactory = new SceneTitleFactory();
      p_scene_manager->PushNextSceneFactory(pTitleSceneFactory);
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
    p_result_time->Draw();

    p_start_symbol_->Draw();

    p_object2D->Draw();
}



// EOF