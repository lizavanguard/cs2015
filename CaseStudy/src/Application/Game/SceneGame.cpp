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
    , p_tori_(nullptr)
    , p_uriel_(nullptr)
{
  p_player_ = new Player(ANIMATION_PLAYER_RATTEL_NONE);

  p_stage_ = new Stage();

  p_uriel_ = new Uriel(ANIMATION_URIEL_CRAWL, p_stage_);

  p_tori_ = new Tori(ANIMATION_TORI_NONE, p_uriel_);
  p_tori_->SetPos(p_stage_->GetGoalMaptip());

  p_ready_ = new Ready();

  p_back_ = new BackGround();
}


//------------------------------------------------
// dtor
//------------------------------------------------
SceneGame::~SceneGame() {
  delete p_player_;
  delete p_ready_;
  delete p_uriel_;
  delete p_tori_;
  delete p_stage_;
  delete p_back_;
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

  // ウリエル更新
  p_uriel_->Update();

  // プレイヤー更新
  p_player_->Update(p_uriel_);
}


//------------------------------------------------
// Draw
//------------------------------------------------
void SceneGame::Draw(void) {
  p_back_->Draw();

  p_stage_->Draw();

  p_player_->Draw();

  p_uriel_->Draw();

  p_tori_->Draw();

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
