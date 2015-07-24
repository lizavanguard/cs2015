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
  back_ground_top_ = new BackGround("data/Texture/bg_sky1.png", 0.00025f);
  back_ground_bottom_ = new BackGround("data/Texture/bg_sky2.png", 0.001f);
}

//------------------------------------------------
// dtor
//------------------------------------------------
BackGroundManager::~BackGroundManager() {
  SafeDelete(back_ground_top_);
  SafeDelete(back_ground_bottom_);
}

//------------------------------------------------
// Update
//------------------------------------------------
void BackGroundManager::Update(void) {
  back_ground_top_->Update();
  back_ground_bottom_->Update();
}

//------------------------------------------------
// Draw
//------------------------------------------------
void BackGroundManager::Draw(void) {
  back_ground_top_->Draw();
  back_ground_bottom_->Draw();
}