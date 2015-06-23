//==============================================================================
//
// XAudio2Simple
// Author: Shimizu Shoji
//
//==============================================================================
#pragma once
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// include
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
#include <XAudio2.h>

//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// class definition
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
class XAudio2Simple {
public:
  // ctor
  XAudio2Simple();

  // dtor
  ~XAudio2Simple();

  // create a source file
  IXAudio2SourceVoice* CreateSourceVoice(const char* p_filename, bool is_looping);

private:
  bool _InitializeXAudio2(void);
  void _UninitializeXAudio2(void);

  bool _InitializeMasterVoice(void);
  void _UninitializeMasterVoice(void);

  IXAudio2* p_xaudio2_;
  IXAudio2MasteringVoice* p_master_voice_;
};
