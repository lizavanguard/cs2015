//==============================================================================
//
// SoundManager
// Author: Shimizu Shoji
//
//==============================================================================
#pragma once
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// include
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
#include "xaudio2.h"

//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// class definition
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
class SoundManager {
public:
  typedef enum {
    SOUND_LABEL_BGM_DEMO0,
    SOUND_LABEL_SE_CALL0,
    SOUND_LABEL_SE_CALL1,
    SOUND_LABEL_SE_EAT,
    kSoundMax
  } SoundLabels;

  // ctor
  SoundManager();

  // dtor
  ~SoundManager();

  HRESULT PlaySound(SoundLabels label);

  void StopSound(SoundLabels label);

  void StopSound(void);

private:
  bool _InitializeSounds(void);
  void _UninitializeSounds(void);

  HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD *pChunkSize, DWORD *pChunkDataPosition);

  HRESULT ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);

  IXAudio2SourceVoice *g_apSourceVoice[kSoundMax];	// ソースボイス
  BYTE *g_apDataAudio[kSoundMax];					// オーディオデータ
  DWORD g_aSizeAudio[kSoundMax];					// オーディオデータサイズ
};
