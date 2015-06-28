//==============================================================================
//
// Ready
// Author: Shimizu Shoji
//
//==============================================================================
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// include
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
#include "Ready.h"
#include "Framework/Texture/TextureManagerHolder.h"

//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// const
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
namespace {

const char* kTexturenames[] = {
  "data/Texture/ready_sign_00.png",
  "data/Texture/ready_sign_01.png",
};

const int kReadyDisplayTime = 30;
const int kEndTime = 60;

const D3DXVECTOR3 kInitialPos = {640.0f, 360.0f, 0.0f};
const D3DXVECTOR2 kSize = {640.0f, 360.0f};

}

//==============================================================================
// class implementation
//==============================================================================
//------------------------------------------------
// ctor
//------------------------------------------------
Ready::Ready()
    : Object2D(kInitialPos, kSize, nullptr)
    , count_(0)
    , is_end_(false) {
  for (int texture_count = 0; texture_count < kTextureAnimationMax; ++texture_count) {
    texture_ids_[texture_count] =
      TextureManagerHolder::Instance().GetTextureManager().LoadTexture(kTexturenames[texture_count]);
  }
  texture_id_ = texture_ids_[0];
}

//------------------------------------------------
// dtor
//------------------------------------------------
Ready::~Ready() {
}

//------------------------------------------------
// Update
//------------------------------------------------
void Ready::Update(void) {
  ++count_;

  // if レディ表示時間が終了したら ゴー表示
  if (count_ == kReadyDisplayTime) {
    texture_id_ = texture_ids_[1];
  }
  else if (count_ > kEndTime) {
    is_end_ = true;
  }
}

//------------------------------------------------
// Draw
//------------------------------------------------
void Ready::_PreProcessOfDraw(void) {
}

void Ready::_PostProcessOfDraw(void) {
}
