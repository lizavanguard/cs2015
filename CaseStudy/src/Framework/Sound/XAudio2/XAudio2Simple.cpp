//==============================================================================
//
// XAudio2Simple
// Author: Shimizu Shoji
//
//==============================================================================
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// include
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
#include "XAudio2Simple.h"

//==============================================================================
// class implementation
//==============================================================================
//------------------------------------------------
// ctor
//------------------------------------------------
XAudio2Simple::XAudio2Simple() {
  if (!_InitializeXAudio2()) {
    return;
  }

  if (!_InitializeMasterVoice()) {
    return;
  }
}

//------------------------------------------------
// dtor
//------------------------------------------------
XAudio2Simple::~XAudio2Simple() {
  _UninitializeMasterVoice();
  _UninitializeXAudio2();
}

//------------------------------------------------
// Initialize XAudio2
//------------------------------------------------
bool XAudio2Simple::_InitializeXAudio2(void) {
  HRESULT hr = XAudio2Create(&p_xaudio2_, 0);
  if (FAILED(hr)) {
    MessageBox(nullptr, "XAudio2Simpleオブジェクトの作成に失敗！", "警告！", MB_ICONWARNING);
    return false;
  }
  return true;
}

//------------------------------------------------
// Uninitialize master voice
//------------------------------------------------
void XAudio2Simple::_UninitializeXAudio2(void) {
  if (p_xaudio2_) {
    p_xaudio2_->Release();
    p_xaudio2_ = nullptr;
  }
}

//------------------------------------------------
// Initialize master voice
//------------------------------------------------
bool XAudio2Simple::_InitializeMasterVoice(void) {
  HRESULT hr = p_xaudio2_->CreateMasteringVoice(&p_master_voice_);
  if (FAILED(hr)) {
    MessageBox(nullptr, "マスターボイスの生成に失敗！", "警告！", MB_ICONWARNING);
    //_UninitializeXAudio2();
    return false;
  }
  return true;
}

//------------------------------------------------
// Uninitialize master voice
//------------------------------------------------
void XAudio2Simple::_UninitializeMasterVoice(void) {
  p_master_voice_->DestroyVoice();
  p_master_voice_ = nullptr;
}

//------------------------------------------------
// create a source file
//------------------------------------------------
IXAudio2SourceVoice* XAudio2Simple::CreateSourceVoice(const char* p_filename, bool is_looping) {

}
