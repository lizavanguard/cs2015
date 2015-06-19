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
#include "Framework/GameManager/GameManager.h"
#include "Framework/Input/InputManagerHolder.h"
#include "Framework/Input/InputKeyboard.h"

#include "Application/Object/BackGround.h"
#include "Application/Object/Object.h"
#include "Application/Object/player.h"
#include "Application/Object/Ready.h"
#include "Application/Object/Tori.h"
#include "Application/Object/Uriel.h"
#include "Application/Tension/TensionGauge.h"
#include "Application\Object\Object2D\Timer.h"
#include "Application/Stage/Stage.h"

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// class definition
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//------------------------------------------------
// ctor
//------------------------------------------------
SceneGame::SceneGame()
    : is_end_(false)
    , p_back_(nullptr)
    , p_player_(nullptr)
    , p_ready_(nullptr)
    , p_stage_(nullptr)
    , p_tension_gauge_(nullptr)
    , p_tori_(nullptr)
    , p_uriel_(nullptr)
    , p_timer_(nullptr)
{
  p_player_ = new Player(ANIMATION_PLAYER_RATTEL_NONE);

  p_stage_ = new Stage();

  p_tension_gauge_ = new TensionGauge();

  p_uriel_ = new Uriel(ANIMATION_URIEL_CRAWL, p_stage_, p_tension_gauge_);

  p_tori_ = new Tori(ANIMATION_TORI_NONE, p_uriel_, p_stage_->GetGoalMaptip());

  p_ready_ = new Ready();

  p_back_ = new BackGround();

  p_timer_ = new Timer(D3DXVECTOR3(600.0f, 50.0f, 0.0f), 0.0f, D3DXVECTOR2(50.0f, 50.0f), TIMER);
}


//------------------------------------------------
// dtor
//------------------------------------------------
SceneGame::~SceneGame() {
  SafeDelete(p_player_);
  SafeDelete(p_ready_);
  SafeDelete(p_uriel_);
  SafeDelete(p_tori_);
  SafeDelete(p_tension_gauge_);
  SafeDelete(p_stage_);
  SafeDelete(p_back_);
  SafeDelete(p_timer_);
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

  // GAME
//  // 鳥更新
//  p_tori_->Update();
//
//  if (p_tori_->GetHitCheck()){
//    return;
//  }

  p_timer_->Update();

  // ウリエル更新
  p_uriel_->Update();

  // プレイヤー更新
  p_player_->Update(p_uriel_);

  p_tension_gauge_->Update();

  if (InputManagerHolder::Instance().GetInputManager().GetPrimaryKeyboard().IsTrigger(DIK_1)) {
    p_tension_gauge_->IncreaseTension();
  }
  if (InputManagerHolder::Instance().GetInputManager().GetPrimaryKeyboard().IsTrigger(DIK_2)) {
    p_tension_gauge_->CoolDown();
  }
}


//------------------------------------------------
// Draw
//------------------------------------------------
void SceneGame::Draw(void) {
  p_back_->Draw();

  p_stage_->Draw();

  p_uriel_->Draw();

  p_player_->Draw();

  p_timer_->Draw();

//  p_tori_->Draw();

  p_tension_gauge_->Draw();
   
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
