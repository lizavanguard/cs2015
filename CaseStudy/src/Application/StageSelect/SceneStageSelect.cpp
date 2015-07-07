//==============================================================================
//
// SceneStageSelect
// Author: Shimizu Shoji
//
//==============================================================================
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// include
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
#include "SceneStageSelect.h"

#include "Application/Game/SceneGameFactory.h"
#include "Application/Object/Object2D/Object2D.h"
#include "Application/Object/BackGround/BackGroundManager.h"
#include "Framework/FrameworkOption.h"
#include "Framework/Input/InputKeyboard.h"
#include "Framework/Input/InputManagerHolder.h"
#include "Framework/Scene/SceneManager.h"

//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// const
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
namespace {

const int kNumTop = 3;
const int kNumBottom = 2;

const D3DXVECTOR3 kCenterPosition = {kWindowWidth * 0.5f, 450.0f, 0.0f};
const D3DXVECTOR2 kSize = {200.0f, 200.0f};
const D3DXVECTOR2 kMargin = {75.0f, 50.0f};
const D3DXVECTOR2 kStride = kSize + kMargin;

// Ç‡Ç¡Ç∆àÍî âªÇµÇƒÇ‡Ç¢Ç¢Ç™ÅAÉÅÉìÉhÉC
const D3DXVECTOR3 kTopStartPosition = {
  kCenterPosition.x - kStride.x,
  kCenterPosition.y - (kStride.y * 0.5f),
  kCenterPosition.z
};
const D3DXVECTOR3 kBottomStartPosition = {
  kCenterPosition.x - (kStride.x * 0.5f),
  kCenterPosition.y + (kStride.y * 0.5f),
  kCenterPosition.z
};
const char* kTextureFilename = "data/Texture/tex_anim_04.png";

const D3DXVECTOR3 kNameCenterPosition = {kWindowWidth * 0.5f, 150.0f, 0.0f};
const D3DXVECTOR2 kNameSize = {400.0f, 100.0f};
const char* kNameTextureFilename = "data/Texture/tex_anim_04.png";

const D3DXVECTOR2 kCursorSize = {100.0f, 100.0f};
const char* kCursorTextureFilename = "data/Texture/bo-ro.png";
}

//==============================================================================
// class implementation
//==============================================================================
//------------------------------------------------
// ctor
//------------------------------------------------
SceneStageSelect::SceneStageSelect()
    : p_background_manager_(nullptr)
    , p_cursor_(nullptr)
    , p_cursor_value_(nullptr)
    , p_name_(nullptr) {
  for (int top_count = 0; top_count < kNumTop; ++top_count) {
    D3DXVECTOR3 position = kTopStartPosition;
    position.x += kStride.x * top_count;
    p_thumbnails_[top_count] = new Object2D(position, kSize, kTextureFilename);
  }
  for (int bottom_count = 0; bottom_count < kNumBottom; ++bottom_count) {
    D3DXVECTOR3 position = kBottomStartPosition;
    position.x += kStride.x * bottom_count;
    p_thumbnails_[kNumTop + bottom_count] = new Object2D(position, kSize, kTextureFilename);
  }

  p_name_ = new Object2D(kNameCenterPosition, kNameSize, kNameTextureFilename);

  p_background_manager_ = new BackGroundManager();

  p_cursor_ = new Object2D(p_thumbnails_[0]->GetPosition(), kCursorSize, kCursorTextureFilename);
  p_cursor_value_ = new Cursor<kStageMax>();
}

//------------------------------------------------
// dtor
//------------------------------------------------
SceneStageSelect::~SceneStageSelect() {
  SafeDelete(p_cursor_value_);
  SafeDelete(p_cursor_);

  SafeDelete(p_background_manager_);

  SafeDelete(p_name_);

  for (auto p_thumb : p_thumbnails_) {
    SafeDelete(p_thumb);
  }
}

//------------------------------------------------
// Update
//------------------------------------------------
void SceneStageSelect::Update(SceneManager* p_scene_manager, const float elapsed_time) {
  p_background_manager_->Update();

  auto& keyboard = InputManagerHolder::Instance().GetInputManager().GetPrimaryKeyboard();
  if(keyboard.IsTrigger(DIK_A)) {
    p_scene_manager->PushNextSceneFactory(new SceneGameFactory());
  }

  if (keyboard.IsTrigger(DIK_LEFT)) {
    p_cursor_value_->Decrement();
  }
  if (keyboard.IsTrigger(DIK_RIGHT)) {
    p_cursor_value_->Increment();
  }

  p_cursor_->SetPosition(p_thumbnails_[p_cursor_value_->GetCursor()]->GetPosition());
}

//------------------------------------------------
// Draw
//------------------------------------------------
void SceneStageSelect::Draw(void) {
  p_background_manager_->Draw();

  for (auto p_thumb : p_thumbnails_) {
    p_thumb->Draw();
  }

  p_cursor_->Draw();

  p_name_->Draw();
}
