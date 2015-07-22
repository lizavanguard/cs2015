//==============================================================================
//
// SceneTutorial [SceneTutorial.cpp]
// Author : Yuji Momoi
//
//==============================================================================
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// include
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "SceneTutorial.h"
#include "Application/Tutorial/TutorialEvent.h"
#include "Framework/DrawDebugPrimitive/DrawPrimitive.h"
#include "Framework/GameManager/GameManager.h"
#include "Framework/Input/InputManagerHolder.h"
#include "Framework/Input/InputKeyboard.h"
#include "Framework/Sound/sound.h"

#include "Framework/Scene/SceneManager.h"
#include "Application/Title/SceneTitleFactory.h"
#include "Application/Game/SceneGameFactory.h"
#include "Application/Collison/Collision.h"
#include "Application/Object/Object.h"
#include "Application/Object/player.h"
#include "Application/Object/Tori.h"
#include "Application/Object/Uriel.h"
#include "Application/Tension/TensionGauge.h"
#include "Application\Object\Object2D\Timer.h"
#include "Application\Camera\camera.h"
#include "Application/Stage/Stage.h"
#include "Application/Tutorial/SceneTutorialFactory.h"
#include "Application/Tutorial/TutorialBackGround.h"

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// class definition
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//------------------------------------------------
// ctor
//------------------------------------------------
SceneTutorial::SceneTutorial()
    : is_end_(false)
    , p_collision_(nullptr)
    , p_player_(nullptr)
    , p_stage_(nullptr)
    , p_tension_gauge_(nullptr)
    , p_tori_(nullptr)
    , p_uriel_(nullptr)
    , p_camera(nullptr)
    , p_tutorial_event_(nullptr)
    , p_tutorial_backGround_(nullptr)
{
  p_stage_ = new Stage();

  p_player_ = new Player(ANIMATION_PLAYER_RATTEL_NONE, p_stage_);

  p_tension_gauge_ = new TensionGauge();

  p_uriel_ = new Uriel(ANIMATION_URIEL_CRAWL, p_stage_, p_tension_gauge_);
  p_uriel_->SetDirection(AnimationObject::DIRECTION_LEFT);

  p_tori_ = new Tori(ANIMATION_TORI_DROP, p_uriel_, p_stage_);

  D3DXVECTOR2 size = p_stage_->GetStageSize();
  D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
  pos.y = -(size.y / 2) + 50.0f;
  p_tutorial_backGround_ = new TutorialBackGround(pos, size, "data/Texture/kids_room.jpg");

  p_collision_ = new Collision(*p_player_, *p_uriel_, *p_stage_);

  p_camera = new Camera(p_player_, p_stage_);
  pos = p_uriel_->GetPos();
  pos.y += 100.0f;
  p_camera->SetPosR(pos);

  p_tutorial_event_ = new TutorialEvent(p_uriel_, p_player_, p_stage_);

  PlaySound(SOUND_LABEL_BGM_DEMO0);
}


//------------------------------------------------
// dtor
//------------------------------------------------
SceneTutorial::~SceneTutorial() {
  StopSound(SOUND_LABEL_BGM_DEMO0);

  SafeDelete(p_collision_);
  SafeDelete(p_player_);
  SafeDelete(p_uriel_);
  SafeDelete(p_tori_);
  SafeDelete(p_tension_gauge_);
  SafeDelete(p_stage_);
  SafeDelete(p_camera);
  SafeDelete(p_tutorial_event_);
  SafeDelete(p_tutorial_backGround_);
}


//------------------------------------------------
// Update
//------------------------------------------------
void SceneTutorial::Update(SceneManager* p_scene_manager, const float elapsed_time) {
  // TutorialEvent
  p_tutorial_event_->Update();

  // GAME
  // 鳥更新
  p_tori_->Update();
  if (p_tori_->GetHitCheck()){
    return;
  }

  D3DXVECTOR3 pos = p_uriel_->GetPos();
  pos.y += 100.0f;
  p_camera->CallAlways(pos);

  // カメラ更新
  p_camera->Update();

  // プレイヤー更新
  p_player_->Update(p_uriel_);

  // ウリエル更新
  p_uriel_->Update();

  p_tension_gauge_->Update();

  // Uriel x Player's boro
  p_collision_->CollideUrielToPlayersBoro();

  // Stage x Player's boro
  p_collision_->CollideStageToPlayersGimmick();


  // Next TitleScene
  if (InputManagerHolder::Instance().GetInputManager().GetPrimaryKeyboard().IsTrigger(DIK_T)) {
    SceneGameFactory* pGameSceneFactory = new SceneGameFactory();
    p_scene_manager->PushNextSceneFactory(pGameSceneFactory);
  }

}


//------------------------------------------------
// Draw
//------------------------------------------------
void SceneTutorial::Draw(void) {
  p_camera->Set();
  SetMatrixViewProjectionViewport(p_camera->GetMatrixViewProjectionViewPort());

  //p_background_->Draw();
  p_tutorial_backGround_->Draw();

  p_stage_->Draw();

  p_tori_->Draw();

  p_uriel_->Draw();

  p_player_->Draw();

  p_tension_gauge_->Draw();

  if (p_tutorial_event_->ViewEvent()){
    p_tutorial_event_->Draw();
  }
}


//------------------------------------------------
// get
//------------------------------------------------
bool SceneTutorial::IsPause(void) const {
  return false;
}
