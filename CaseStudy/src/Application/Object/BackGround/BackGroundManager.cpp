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

const struct {
  char* p_texturename;
  float scroll_speed;
} kBackGroundData[] = {
  {"data/Texture/bg_sky1.png", 0.00025f},
  {"data/Texture/bg_sky2.png", 0.001f},
};
const unsigned int kBGMax = sizeof(kBackGroundData) / sizeof(*kBackGroundData);

}

//==============================================================================
// class implementation
//==============================================================================
//------------------------------------------------
// ctor
//------------------------------------------------
BackGroundManager::BackGroundManager() {
  for (int bg_count = 0; bg_count < kBGMax; ++bg_count) {
    back_grounds_.push_back(
      new BackGround(kBackGroundData[bg_count].p_texturename, kBackGroundData[bg_count].scroll_speed));
  }
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