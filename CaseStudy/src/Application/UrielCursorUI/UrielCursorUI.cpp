//==============================================================================
//
// UrielCursorUI
// Author: Shimizu Shoji
//
//==============================================================================
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// include
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
#include "UrielCursorUI.h"

#include "Application/Camera/camera.h"
#include "Application/Object/Object2D/Direction2D.h"
#include "Application/Object/Object2D/UrielCursor.h"
#include "Application/Object/player.h"
#include "Application/Object/Uriel.h"

//==============================================================================
// class implementation
//==============================================================================
//------------------------------------------------
// ctor
//------------------------------------------------
UrielCursorUI::UrielCursorUI(const Camera& camera, const Player& player, const Uriel& uriel)
    : p_direction2d_(nullptr)
    //, p_cursor_(nullptr) {
    , camera_(camera)
    , player_(player)
    , uriel_(uriel) {
  p_direction2d_ = new Direction2D();
}

//------------------------------------------------
// dtor
//------------------------------------------------
UrielCursorUI::~UrielCursorUI() {
  SafeDelete(p_direction2d_);
}

//------------------------------------------------
// Update
//------------------------------------------------
void UrielCursorUI::Update(void) {
  if (!camera_.CheckInScreenRange(uriel_.GetPosition())) {
    p_direction2d_->Dead();
    return;
  }

  p_direction2d_->Alive();
  p_direction2d_->CalcRotationUsingPosition(player_.GetPosition(), uriel_.GetPosition());
}

//------------------------------------------------
// Draw
//------------------------------------------------
void UrielCursorUI::Draw(void) {
  p_direction2d_->Draw();
}
