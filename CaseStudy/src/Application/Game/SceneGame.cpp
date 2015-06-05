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

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// class definition
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//------------------------------------------------
// ctor
//------------------------------------------------
SceneGame::SceneGame()
  : is_end_(false), p_object_(nullptr)
{
  p_player = new Player(ANIMATION_PLAYER_RATTEL_NONE);
  p_stage_ = new Stage();
  p_uriel_ = new Uriel(ANIMATION_URIEL_CRAWL, p_stage_);
  p_tori_ = new Tori(ANIMATION_TORI_NONE, p_uriel_);
  p_tori_->SetPos(p_stage_->GetGoalMaptip());
  p_object_ = new Object();
  p_object_->SetTexture("data/Texture/ready_sign_00.png");
  p_object_->SetSize(D3DXVECTOR2(640, 360));
  p_object_->SetPos(D3DXVECTOR3(640, 360, 0));
  start_event_ = true;
  start_event_timer_ = 0;
  p_back_ = new Object();
  p_back_->SetTexture("data/Texture/背景.jpg");
  p_back_->SetSize(D3DXVECTOR2(1280, 720));
  p_back_->SetPos(D3DXVECTOR3(640, 360, 0));

}


//------------------------------------------------
// dtor
//------------------------------------------------
SceneGame::~SceneGame() {
  delete p_player;
  delete p_object_;
  delete p_uriel_;
  delete p_tori_;
  delete p_stage_;
  delete p_back_;
}


//------------------------------------------------
// Update
//------------------------------------------------
void SceneGame::Update(SceneManager* pSceneManager, const float elapsedTime) {

  if (start_event_){
      ++start_event_timer_;

      if (start_event_timer_ == 30){
        p_object_->SetTexture("data/Texture/ready_sign_01.png");
      }
      else if (start_event_timer_ > 60){
        start_event_ = false;
      }
      return;
  }

//  // 鳥更新
//  p_tori_->Update();
//
//  if (p_tori_->GetHitCheck()){
//    return;
//  }

  // ウリエル更新
  p_uriel_->Update();

  // プレイヤー更新
  p_player->Update(p_uriel_);
}


//------------------------------------------------
// Draw
//------------------------------------------------
void SceneGame::Draw(void) {
  p_back_->Draw();
  p_stage_->Draw();
  p_player->Draw();
  p_uriel_->Draw();
  p_tori_->Draw();
  //
  if (start_event_)
    p_object_->Draw();
}


//------------------------------------------------
// get
//------------------------------------------------
bool SceneGame::IsPause(void) const {
  return false;
}
