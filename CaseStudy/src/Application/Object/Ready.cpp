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

const D3DXVECTOR3 kInitialPos = {0, -180, 0};
const D3DXVECTOR2 kSize = {640, 360};

}

//==============================================================================
// class implementation
//==============================================================================
//------------------------------------------------
// ctor
//------------------------------------------------
Ready::Ready() : count_(0), is_end_(false) {
  for (int texture_count = 0; texture_count < kTextureAnimationMax; ++texture_count) {
    texture_ids_[texture_count] =
      TextureManagerHolder::Instance().GetTextureManager().LoadTexture(kTexturenames[texture_count]);
  }
  SetTextureID(texture_ids_[0]);

  SetSize(kSize);
  SetPos(kInitialPos);
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
    SetTextureID(texture_ids_[1]);
  }
  else if (count_ > kEndTime) {
    is_end_ = true;
  }
}

//------------------------------------------------
// Draw
//------------------------------------------------
void Ready::PreProccessOfDraw(void) {
}

void Ready::PostProcessOfDraw(void) {
}
