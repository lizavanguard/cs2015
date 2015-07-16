//==============================================================================
//
// アニメーションオブジェクト [TutorialBackGround.cpp]
// Author : Yuji Momoi
//
//==============================================================================
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// include
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "TutorialBackGround.h"
#include "Framework/DirectXHelper/DeviceHolder.h"
#include "Framework/DirectXHelper/DirectXConst.h"
#include "Framework/Texture/TextureManagerHolder.h"

//==============================================================================
// class implementation
//==============================================================================
// ctor
TutorialBackGround::TutorialBackGround(const D3DXVECTOR3& pos, const D3DXVECTOR2& size, const char* p_texture_filename) : Object() {
  pos_ = pos;
  size_ = size;
  texture_id_ = TextureManagerHolder::Instance().GetTextureManager().LoadTexture(p_texture_filename);
}

// dtor
TutorialBackGround::~TutorialBackGround() {

}

// update
void TutorialBackGround::Update(void){
}

// draw
void TutorialBackGround::_PreProcessOfDraw(void) {
  auto p_device = DeviceHolder::Instance().GetDevice();
}

// draw
void TutorialBackGround::_PostProcessOfDraw(void) {
}

// EOF