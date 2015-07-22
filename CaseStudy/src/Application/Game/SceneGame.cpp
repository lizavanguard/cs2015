//==============================================================================
//
// SceneGame [SceneGame.cpp]
// Author : Shimizu Shoji
//
//==============================================================================
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// include
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "SceneGame.h"
#include "Framework/DrawDebugPrimitive/DrawPrimitive.h"
#include "Framework/GameManager/GameManager.h"
#include "Framework/Input/InputManagerHolder.h"
#include "Framework/Input/InputKeyboard.h"
#include "Framework/Sound/sound.h"
#include "Framework/Utility/PersistentValue.h"

#include "Application/Collison/Collision.h"
#include "Application/Effect/EffectManager.h"
#include "Application/Object/BackGround/BackGroundManager.h"
#include "Application/Object/Object.h"
#include "Application/Object/player.h"
#include "Application/Object/Ready.h"
#include "Application/Object/Tori.h"
#include "Application/Object/Uriel.h"
#include "Application/Tension/TensionGauge.h"
#include "Application\Object\Object2D\Timer.h"
#include "Application\Camera\camera.h"
#include "Application/Stage/Stage.h"
#include "Framework/Scene/SceneManager.h"
#include "Application/Title/SceneTitleFactory.h"
#include "Application/Result/SceneResultFactory.h"
#include "Application/Object/Sang/SangManager.h"
#include "Application/Object/Sang/Butterfly.h"
#include "Application/Object/Sang/Flower.h"
#include "Application/Tutorial/SceneTutorialFactory.h"
#include "Application/GamePause/GamePause.h"
#include "Application/Navi/NaviManager.h"

int SceneGame::select_stage_num_ = 0;

#include "Application/Navi/NaviManager.h"

int SceneGame::select_stage_num_ = 0;

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// class definition
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//------------------------------------------------
// ctor
//------------------------------------------------
SceneGame::SceneGame()
    : is_end_(false)
    , p_background_manager_(nullptr)
    , p_collision_(nullptr)
    , p_player_(nullptr)
    , p_ready_(nullptr)
    , p_stage_(nullptr)
    , p_tension_gauge_(nullptr)
    , p_tori_(nullptr)
    , p_uriel_(nullptr)
    , p_timer_(nullptr)
    , p_camera(nullptr)
    , p_sang_manager_(nullptr)
    , p_camera_(nullptr)
    , p_game_pause_(nullptr)
    , p_navimanager_(nullptr)
{
  p_sang_manager_ = new SangManager();

  p_stage_ = new Stage();
  p_stage_->SelectStage(select_stage_num_);

  p_player_ = new Player(ANIMATION_PLAYER_RATTEL_NONE, p_stage_);

  p_tension_gauge_ = new TensionGauge();

  p_uriel_ = new Uriel(ANIMATION_URIEL_CRAWL, p_stage_, p_tension_gauge_);
  p_sang_manager_->SetUrielPointer(p_uriel_);

  p_tori_ = new Tori(ANIMATION_TORI_DROP, p_uriel_, p_stage_);

  p_ready_ = new Ready();

  p_background_manager_ = new BackGroundManager();

  p_collision_ = new Collision(*p_player_, *p_uriel_, *p_stage_);

  p_camera_ = new Camera(p_player_, p_stage_);

  p_timer_ = new Timer(D3DXVECTOR3(600.0f, 50.0f, 0.0f), 0.0f, D3DXVECTOR2(50.0f, 50.0f), TIMER);

  p_navimanager_ = new NaviManager(*p_camera_, *p_uriel_);

  EffecManagerSingleton::Instance();

  p_game_pause_ = new GamePause;

  PlaySound(SOUND_LABEL_BGM_DEMO0);
}


//------------------------------------------------
// dtor
//------------------------------------------------
SceneGame::~SceneGame() {
  StopSound(SOUND_LABEL_BGM_DEMO0);

  SafeDelete(p_collision_);
  SafeDelete(p_player_);
  SafeDelete(p_ready_);
  SafeDelete(p_uriel_);
  SafeDelete(p_tori_);
  SafeDelete(p_tension_gauge_);
  SafeDelete(p_stage_);
  SafeDelete(p_background_manager_);
  SafeDelete(p_timer_);
  SafeDelete(p_sang_manager_);
  SafeDelete(p_camera_);
  SafeDelete(p_game_pause_);
  SafeDelete(p_navimanager_);
  select_stage_num_ = 0;
}


//------------------------------------------------
// Update
//------------------------------------------------
void SceneGame::Update(SceneManager* p_scene_manager, const float elapsed_time) {
  // READY GO
  if (!p_ready_->IsEnd()) {
    p_ready_->Update();
    return;
  }
  if (!p_game_pause_->GetPause()){
    // GAME
    // 鳥更新
    p_tori_->Update();
    if (p_tori_->GetHitCheck()){
      PersistentValue::Instance().SetData("Score", 10);
      SceneResultFactory* pResultSceneFactory = new SceneResultFactory();
      p_scene_manager->PushNextSceneFactory(pResultSceneFactory);
      return;
    }

    // カメラ更新
    p_camera_->Update();

    // タイマー更新
    p_timer_->Update();

    p_background_manager_->Update();

    p_sang_manager_->Update();

    // プレイヤー更新
    p_player_->Update(p_uriel_);

    // ウリエル更新
    p_uriel_->Update();

    // Effect
    EffecManagerSingleton::Instance().Update();

    p_tension_gauge_->Update();

    // Uriel x Player's boro
    p_collision_->CollideUrielToPlayersBoro();

    // Stage x Player's boro
    p_collision_->CollideStageToPlayersGimmick();

    p_navimanager_->Update();
  }

  p_game_pause_->Update(p_scene_manager, elapsed_time, p_game_pause_);

  if (InputManagerHolder::Instance().GetInputManager().GetPrimaryKeyboard().IsTrigger(DIK_3)) {
    EffecManagerSingleton::Instance().Create(EffectManager::EFFECTTYPE_KIRAKIRA, D3DXVECTOR2(100, -100), D3DXVECTOR2(5, 5), 1.0f);
  }
}


//------------------------------------------------
// Draw
//------------------------------------------------
void SceneGame::Draw(void) {
  p_camera_->Set();
  SetMatrixViewProjectionViewport(p_camera_->GetMatrixViewProjectionViewPort());

  p_background_manager_->Draw();

  p_stage_->Draw();

  p_sang_manager_->Draw();

  p_tori_->Draw();

  p_uriel_->Draw();

  p_player_->Draw();

  p_tension_gauge_->Draw();

  p_navimanager_->Draw();

  p_timer_->Draw();

  EffecManagerSingleton::Instance().Draw();

  p_game_pause_->Draw();

  if (!p_ready_->IsEnd()) {
    p_ready_->Draw();
  }
}


//------------------------------------------------
// get
//------------------------------------------------
bool SceneGame::IsPause(void) const {
  return false;
}
