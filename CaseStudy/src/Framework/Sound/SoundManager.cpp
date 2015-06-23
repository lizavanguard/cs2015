//==============================================================================
//
// SoundManager
// Author: Shimizu Shoji
//
//==============================================================================
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// include
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
#include "SoundManager.h"

//------------------------------------------------
// パラメータ
//------------------------------------------------
typedef struct {
  char *pFilename;	// ファイル名
  bool bLoop;			// ループするかどうか
} SoundParam;

// 各音素材のパラメータ
namespace {
SoundParam g_aParam[SoundManager::kSoundMax] = {
  {"data/bgm/BGM_demo00.wav", true},
  {"data/se/SE_uriel_call_0.wav", false},
  {"data/se/SE_uriel_call_1.wav", false},
  {"data/se/SE_uriel_eat.wav", false},
};
}

//==============================================================================
// class implementation
//==============================================================================
//------------------------------------------------
// ctor
//------------------------------------------------
SoundManager::SoundManager() {
  CoInitializeEx(nullptr, COINIT_MULTITHREADED);

  CoUninitialize();

  if (!_InitializeSounds()) {
    CoUninitialize();
    return;
  }
}

//------------------------------------------------
// dtor
//------------------------------------------------
SoundManager::~SoundManager() {
  _UninitializeSounds();
  CoUninitialize();
}


//------------------------------------------------
// セグメント再生(停止)
//------------------------------------------------
HRESULT SoundManager::PlaySound(SoundLabels label)
{
  XAUDIO2_VOICE_STATE xa2state;
  XAUDIO2_BUFFER buffer;

  memset(&buffer, 0, sizeof(XAUDIO2_BUFFER));
  buffer.AudioBytes = g_aSizeAudio[label];
  buffer.pAudioData = g_apDataAudio[label];
  buffer.Flags = XAUDIO2_END_OF_STREAM;
  buffer.LoopCount = g_aParam[label].bLoop ? 0xffffffff : 0;

  // 状態取得
  g_apSourceVoice[label]->GetState(&xa2state);
  if (xa2state.BuffersQueued != 0)
  {// 再生中
    // 一時停止
    g_apSourceVoice[label]->Stop(0);

    // オーディオバッファの削除
    g_apSourceVoice[label]->FlushSourceBuffers();
  }
   
  // オーディオバッファの登録
  g_apSourceVoice[label]->SubmitSourceBuffer(&buffer);

  // 再生
  g_apSourceVoice[label]->Start(0);

  return S_OK;
}

//------------------------------------------------
// セグメント停止
//------------------------------------------------
void SoundManager::StopSound(SoundLabels label)
{
  XAUDIO2_VOICE_STATE xa2state;

  // 状態取得
  g_apSourceVoice[label]->GetState(&xa2state);
  if (xa2state.BuffersQueued != 0)
  {// 再生中
    // 一時停止
    g_apSourceVoice[label]->Stop(0);

    // オーディオバッファの削除
    g_apSourceVoice[label]->FlushSourceBuffers();
  }
}

//------------------------------------------------
// セグメント停止
//------------------------------------------------
void SoundManager::StopSound(void)
{
  // 一時停止
  for (int sound_cnt = 0; sound_cnt < SoundLabels::kSoundMax; sound_cnt++)
  {
    if (g_apSourceVoice[sound_cnt])
    {
      // 一時停止
      g_apSourceVoice[sound_cnt]->Stop(0);
    }
  }
}

//------------------------------------------------
// Initialize Sounds
//------------------------------------------------
bool SoundManager::_InitializeSounds(void) {
  // サウンドデータの初期化
  for (int sound_cnt = 0; sound_cnt < kSoundMax; sound_cnt++) {
    HANDLE hFile;
    DWORD dwChunkSize = 0;
    DWORD dwChunkPosition = 0;
    DWORD dwFiletype;
    WAVEFORMATEXTENSIBLE wfx;
    XAUDIO2_BUFFER buffer;

    // バッファのクリア
    memset(&wfx, 0, sizeof(WAVEFORMATEXTENSIBLE));
    memset(&buffer, 0, sizeof(XAUDIO2_BUFFER));

    // サウンドデータファイルの生成
    hFile = CreateFile(g_aParam[sound_cnt].pFilename, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
    if (hFile == INVALID_HANDLE_VALUE) {
      MessageBox(nullptr, "サウンドデータファイルの生成に失敗！(1)", "警告！", MB_ICONWARNING);
      return false;
    }

    // ファイルポインタを先頭に移動
    if (SetFilePointer(hFile, 0, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER) {
      MessageBox(nullptr, "サウンドデータファイルの生成に失敗！(2)", "警告！", MB_ICONWARNING);
      return false;
    }

    // WAVEファイルのチェック
    HRESULT hr = CheckChunk(hFile, 'FFIR', &dwChunkSize, &dwChunkPosition);
    if (FAILED(hr)) {
      MessageBox(nullptr, "WAVEファイルのチェックに失敗！(1)", "警告！", MB_ICONWARNING);
      return false;
    }
    hr = ReadChunkData(hFile, &dwFiletype, sizeof(DWORD), dwChunkPosition);
    if (FAILED(hr)) {
      MessageBox(nullptr, "WAVEファイルのチェックに失敗！(2)", "警告！", MB_ICONWARNING);
      return false;
    }
    if (dwFiletype != 'EVAW') {
      MessageBox(nullptr, "WAVEファイルのチェックに失敗！(3)", "警告！", MB_ICONWARNING);
      return false;
    }

    // フォーマットチェック
    hr = CheckChunk(hFile, ' tmf', &dwChunkSize, &dwChunkPosition);
    if (FAILED(hr)) {
      MessageBox(nullptr, "フォーマットチェックに失敗！(1)", "警告！", MB_ICONWARNING);
      return false;
    }
    hr = ReadChunkData(hFile, &wfx, dwChunkSize, dwChunkPosition);
    if (FAILED(hr)) {
      MessageBox(nullptr, "フォーマットチェックに失敗！(2)", "警告！", MB_ICONWARNING);
      return false;
    }

    // オーディオデータ読み込み
    hr = CheckChunk(hFile, 'atad', &g_aSizeAudio[sound_cnt], &dwChunkPosition);
    if (FAILED(hr))
    {
      MessageBox(nullptr, "オーディオデータ読み込みに失敗！(1)", "警告！", MB_ICONWARNING);
      return false;
    }
    g_apDataAudio[sound_cnt] = (BYTE*)malloc(g_aSizeAudio[sound_cnt]);
    hr = ReadChunkData(hFile, g_apDataAudio[sound_cnt], g_aSizeAudio[sound_cnt], dwChunkPosition);
    if (FAILED(hr))
    {
      MessageBox(nullptr, "オーディオデータ読み込みに失敗！(2)", "警告！", MB_ICONWARNING);
      return false;
    }

    // ソースボイスの生成
    //hr = g_pXAudio2->CreateSourceVoice(&g_apSourceVoice[sound_cnt], &(wfx.Format));
    if (FAILED(hr))
    {
      MessageBox(nullptr, "ソースボイスの生成に失敗！", "警告！", MB_ICONWARNING);
      return false;
    }

    memset(&buffer, 0, sizeof(XAUDIO2_BUFFER));
    buffer.AudioBytes = g_aSizeAudio[sound_cnt];
    buffer.pAudioData = g_apDataAudio[sound_cnt];
    buffer.Flags = XAUDIO2_END_OF_STREAM;
    buffer.LoopCount = 0;

    // オーディオバッファの登録
    g_apSourceVoice[sound_cnt]->SubmitSourceBuffer(&buffer);
  }

  return true;
}

//------------------------------------------------
// Uninitialize Sounds
//------------------------------------------------
void SoundManager::_UninitializeSounds(void) {
  // 一時停止
  for (int sound_cnt = 0; sound_cnt < kSoundMax; sound_cnt++)
  {
    if (g_apSourceVoice[sound_cnt])
    {
      // 一時停止
      g_apSourceVoice[sound_cnt]->Stop(0);

      // ソースボイスの破棄
      g_apSourceVoice[sound_cnt]->DestroyVoice();
      g_apSourceVoice[sound_cnt] = NULL;

      // オーディオデータの開放
      free(g_apDataAudio[sound_cnt]);
      g_apDataAudio[sound_cnt] = NULL;
    }
  }
}

//------------------------------------------------
// チャンクのチェック
//------------------------------------------------
HRESULT SoundManager::CheckChunk(HANDLE hFile, DWORD format, DWORD *pChunkSize, DWORD *pChunkDataPosition)
{
  HRESULT hr = S_OK;
  DWORD dwRead;
  DWORD dwChunkType;
  DWORD dwChunkDataSize;
  DWORD dwRIFFDataSize = 0;
  DWORD dwFileType;
  DWORD dwBytesRead = 0;
  DWORD dwOffset = 0;

  if (SetFilePointer(hFile, 0, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER)
  {// ファイルポインタを先頭に移動
    return HRESULT_FROM_WIN32(GetLastError());
  }

  while (hr == S_OK)
  {
    if (ReadFile(hFile, &dwChunkType, sizeof(DWORD), &dwRead, NULL) == 0)
    {// チャンクの読み込み
      hr = HRESULT_FROM_WIN32(GetLastError());
    }

    if (ReadFile(hFile, &dwChunkDataSize, sizeof(DWORD), &dwRead, NULL) == 0)
    {// チャンクデータの読み込み
      hr = HRESULT_FROM_WIN32(GetLastError());
    }

    switch (dwChunkType)
    {
      case 'FFIR':
        dwRIFFDataSize = dwChunkDataSize;
        dwChunkDataSize = 4;
        if (ReadFile(hFile, &dwFileType, sizeof(DWORD), &dwRead, NULL) == 0)
        {// ファイルタイプの読み込み
          hr = HRESULT_FROM_WIN32(GetLastError());
        }
        break;

      default:
        if (SetFilePointer(hFile, dwChunkDataSize, NULL, FILE_CURRENT) == INVALID_SET_FILE_POINTER)
        {// ファイルポインタをチャンクデータ分移動
          return HRESULT_FROM_WIN32(GetLastError());
        }
    }

    dwOffset += sizeof(DWORD) * 2;
    if (dwChunkType == format)
    {
      *pChunkSize = dwChunkDataSize;
      *pChunkDataPosition = dwOffset;

      return S_OK;
    }

    dwOffset += dwChunkDataSize;
    if (dwBytesRead >= dwRIFFDataSize)
    {
      return S_FALSE;
    }
  }

  return S_OK;
}

//------------------------------------------------
// チャンクデータの読み込み
//------------------------------------------------
HRESULT SoundManager::ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset)
{
  DWORD dwRead;

  if (SetFilePointer(hFile, dwBufferoffset, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER)
  {// ファイルポインタを指定位置まで移動
    return HRESULT_FROM_WIN32(GetLastError());
  }

  if (ReadFile(hFile, pBuffer, dwBuffersize, &dwRead, NULL) == 0)
  {// データの読み込み
    return HRESULT_FROM_WIN32(GetLastError());
  }

  return S_OK;
}

