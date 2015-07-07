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

const char* kTextureFilename = "data/Texture/bo-ro.png";

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
                       const PositionContainer& position_list)
    : p_cursor_(nullptr)
    , p_cursor_value_(nullptr)
    , increment_key_(increment_key)
    , decrement_key_(decrement_key)
    , position_list_(position_list) {
  p_cursor_ = new Cursor(position_list_[0], size, kTextureFilename);
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
void GameCursor::Update(const float elapsed_time) {
  const auto& keyboard = InputManagerHolder::Instance().GetInputManager().GetPrimaryKeyboard();

  if (keyboard.IsTrigger(increment_key_)) {
    p_cursor_value_->Increment();
  }
  if (keyboard.IsTrigger(decrement_key_)) {
    p_cursor_value_->Decrement();
  }

  p_cursor_->SetPosition(position_list_[p_cursor_value_->GetCursor()]);
  p_cursor_->Update(elapsed_time);
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
  return p_cursor_value_->GetCursor();
}