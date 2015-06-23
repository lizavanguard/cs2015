//==============================================================================
//
// BackGroundManager
// Author: Shimizu Shoji
//
//==============================================================================
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// include
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
#include "BackGroundManager.h"

#include <algorithm>

#include "BackGround.h"

//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// const
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
namespace {

const char* kTexturename = "data/Texture/”wŒi.jpg";
const float kUSpeed = 0.0005f;

}

//==============================================================================
// class implementation
//==============================================================================
//------------------------------------------------
// ctor
//------------------------------------------------
BackGroundManager::BackGroundManager() {
  back_grounds_.push_back(new BackGround( kTexturename, kUSpeed));
}

//------------------------------------------------
// dtor
//------------------------------------------------
BackGroundManager::~BackGroundManager() {
  _ForEach([](BackGround* p_background) {
    SafeDelete(p_background);
  });
}

//------------------------------------------------
// Update
//------------------------------------------------
void BackGroundManager::Update(void) {
  _ForEach([](BackGround* p_background) {
    p_background->Update();
  });
}

//------------------------------------------------
// Draw
//------------------------------------------------
void BackGroundManager::Draw(void) {
  _ForEach([](BackGround* p_background) {
    p_background->Draw();
  });
}

//------------------------------------------------
// internal for_each
//------------------------------------------------
void BackGroundManager::_ForEach(void (*function)(BackGround*)) {
  std::for_each(back_grounds_.begin(), back_grounds_.end(), function);
}