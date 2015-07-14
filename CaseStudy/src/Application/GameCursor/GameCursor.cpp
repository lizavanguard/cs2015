//==============================================================================
//
// GameCursor
// Author: Shimizu Shoji
//
//==============================================================================
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// include
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
#include "GameCursor.h"

#include "Application/Object/Object2D/Cursor.h"
#include "Application/Utility/WrapValue.h"
#include "Framework/Input/InputManagerHolder.h"
#include "Framework/Input/InputKeyboard.h"

//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// const
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
namespace {

const char* kTextureFilename = "data/Texture/cursol_up.png";
const char* kPushedTextureFilename = "data/Texture/cursol_down.png";

}


//==============================================================================
// class implementation
//==============================================================================
//------------------------------------------------
// ctor
//------------------------------------------------
GameCursor::GameCursor(const D3DXVECTOR2& size,
                       const int increment_key,
                       const int decrement_key,
                       const int enter_key,
                       const PositionContainer& position_list)
    : increment_key_(increment_key)
    , decrement_key_(decrement_key)
    , enter_key_(enter_key)
    , position_list_(position_list)
    , p_cursor_(nullptr)
    , p_cursor_value_(nullptr)
    , old_cursor_index_(0)
    , is_just_entered_(false)
    , is_just_moved_(false) {
  p_cursor_ = new Cursor(position_list_[0], size, kTextureFilename, kPushedTextureFilename);
  p_cursor_value_ = new WrapValue(position_list_.size());
}

//------------------------------------------------
// dtor
//------------------------------------------------
GameCursor::~GameCursor() {
  SafeDelete(p_cursor_value_);
  SafeDelete(p_cursor_);
}

//------------------------------------------------
// Update
//------------------------------------------------
void GameCursor::Update(const float) {
  old_cursor_index_ = p_cursor_value_->GetValue();

  _ReactInput();

  p_cursor_->SetPosition(position_list_[p_cursor_value_->GetValue()]);
  p_cursor_->Update();
}

//------------------------------------------------
// Draw
//------------------------------------------------
void GameCursor::Draw(void) {
  p_cursor_->Draw();
}

//------------------------------------------------
// get
//------------------------------------------------
int GameCursor::GetCursorIndex(void) const {
  return p_cursor_value_->GetValue();
}

void GameCursor::_ReactInput(void) {
  is_just_moved_ = false;
  is_just_entered_ = false;

  const auto& keyboard = InputManagerHolder::Instance().GetInputManager().GetPrimaryKeyboard();
  if (keyboard.IsTrigger(enter_key_)) {
    p_cursor_->Pushed();
    is_just_entered_ = true;
  }

  if (keyboard.IsTrigger(increment_key_)) {
    p_cursor_value_->Increment();
    is_just_moved_ = true;
  }
  if (keyboard.IsTrigger(decrement_key_)) {
    p_cursor_value_->Decrement();
    is_just_moved_ = true;
  }
}