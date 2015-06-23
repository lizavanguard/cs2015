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
// �p�����[�^
//------------------------------------------------
typedef struct {
  char *pFilename;	// �t�@�C����
  bool bLoop;			// ���[�v���邩�ǂ���
} SoundParam;

// �e���f�ނ̃p�����[�^
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
// �Z�O�����g�Đ�(��~)
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

  // ��Ԏ擾
  g_apSourceVoice[label]->GetState(&xa2state);
  if (xa2state.BuffersQueued != 0)
  {// �Đ���
    // �ꎞ��~
    g_apSourceVoice[label]->Stop(0);

    // �I�[�f�B�I�o�b�t�@�̍폜
    g_apSourceVoice[label]->FlushSourceBuffers();
  }
   
  // �I�[�f�B�I�o�b�t�@�̓o�^
  g_apSourceVoice[label]->SubmitSourceBuffer(&buffer);

  // �Đ�
  g_apSourceVoice[label]->Start(0);

  return S_OK;
}

//------------------------------------------------
// �Z�O�����g��~
//------------------------------------------------
void SoundManager::StopSound(SoundLabels label)
{
  XAUDIO2_VOICE_STATE xa2state;

  // ��Ԏ擾
  g_apSourceVoice[label]->GetState(&xa2state);
  if (xa2state.BuffersQueued != 0)
  {// �Đ���
    // �ꎞ��~
    g_apSourceVoice[label]->Stop(0);

    // �I�[�f�B�I�o�b�t�@�̍폜
    g_apSourceVoice[label]->FlushSourceBuffers();
  }
}

//------------------------------------------------
// �Z�O�����g��~
//------------------------------------------------
void SoundManager::StopSound(void)
{
  // �ꎞ��~
  for (int sound_cnt = 0; sound_cnt < SoundLabels::kSoundMax; sound_cnt++)
  {
    if (g_apSourceVoice[sound_cnt])
    {
      // �ꎞ��~
      g_apSourceVoice[sound_cnt]->Stop(0);
    }
  }
}

//------------------------------------------------
// Initialize Sounds
//------------------------------------------------
bool SoundManager::_InitializeSounds(void) {
  // �T�E���h�f�[�^�̏�����
  for (int sound_cnt = 0; sound_cnt < kSoundMax; sound_cnt++) {
    HANDLE hFile;
    DWORD dwChunkSize = 0;
    DWORD dwChunkPosition = 0;
    DWORD dwFiletype;
    WAVEFORMATEXTENSIBLE wfx;
    XAUDIO2_BUFFER buffer;

    // �o�b�t�@�̃N���A
    memset(&wfx, 0, sizeof(WAVEFORMATEXTENSIBLE));
    memset(&buffer, 0, sizeof(XAUDIO2_BUFFER));

    // �T�E���h�f�[�^�t�@�C���̐���
    hFile = CreateFile(g_aParam[sound_cnt].pFilename, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
    if (hFile == INVALID_HANDLE_VALUE) {
      MessageBox(nullptr, "�T�E���h�f�[�^�t�@�C���̐����Ɏ��s�I(1)", "�x���I", MB_ICONWARNING);
      return false;
    }

    // �t�@�C���|�C���^��擪�Ɉړ�
    if (SetFilePointer(hFile, 0, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER) {
      MessageBox(nullptr, "�T�E���h�f�[�^�t�@�C���̐����Ɏ��s�I(2)", "�x���I", MB_ICONWARNING);
      return false;
    }

    // WAVE�t�@�C���̃`�F�b�N
    HRESULT hr = CheckChunk(hFile, 'FFIR', &dwChunkSize, &dwChunkPosition);
    if (FAILED(hr)) {
      MessageBox(nullptr, "WAVE�t�@�C���̃`�F�b�N�Ɏ��s�I(1)", "�x���I", MB_ICONWARNING);
      return false;
    }
    hr = ReadChunkData(hFile, &dwFiletype, sizeof(DWORD), dwChunkPosition);
    if (FAILED(hr)) {
      MessageBox(nullptr, "WAVE�t�@�C���̃`�F�b�N�Ɏ��s�I(2)", "�x���I", MB_ICONWARNING);
      return false;
    }
    if (dwFiletype != 'EVAW') {
      MessageBox(nullptr, "WAVE�t�@�C���̃`�F�b�N�Ɏ��s�I(3)", "�x���I", MB_ICONWARNING);
      return false;
    }

    // �t�H�[�}�b�g�`�F�b�N
    hr = CheckChunk(hFile, ' tmf', &dwChunkSize, &dwChunkPosition);
    if (FAILED(hr)) {
      MessageBox(nullptr, "�t�H�[�}�b�g�`�F�b�N�Ɏ��s�I(1)", "�x���I", MB_ICONWARNING);
      return false;
    }
    hr = ReadChunkData(hFile, &wfx, dwChunkSize, dwChunkPosition);
    if (FAILED(hr)) {
      MessageBox(nullptr, "�t�H�[�}�b�g�`�F�b�N�Ɏ��s�I(2)", "�x���I", MB_ICONWARNING);
      return false;
    }

    // �I�[�f�B�I�f�[�^�ǂݍ���
    hr = CheckChunk(hFile, 'atad', &g_aSizeAudio[sound_cnt], &dwChunkPosition);
    if (FAILED(hr))
    {
      MessageBox(nullptr, "�I�[�f�B�I�f�[�^�ǂݍ��݂Ɏ��s�I(1)", "�x���I", MB_ICONWARNING);
      return false;
    }
    g_apDataAudio[sound_cnt] = (BYTE*)malloc(g_aSizeAudio[sound_cnt]);
    hr = ReadChunkData(hFile, g_apDataAudio[sound_cnt], g_aSizeAudio[sound_cnt], dwChunkPosition);
    if (FAILED(hr))
    {
      MessageBox(nullptr, "�I�[�f�B�I�f�[�^�ǂݍ��݂Ɏ��s�I(2)", "�x���I", MB_ICONWARNING);
      return false;
    }

    // �\�[�X�{�C�X�̐���
    //hr = g_pXAudio2->CreateSourceVoice(&g_apSourceVoice[sound_cnt], &(wfx.Format));
    if (FAILED(hr))
    {
      MessageBox(nullptr, "�\�[�X�{�C�X�̐����Ɏ��s�I", "�x���I", MB_ICONWARNING);
      return false;
    }

    memset(&buffer, 0, sizeof(XAUDIO2_BUFFER));
    buffer.AudioBytes = g_aSizeAudio[sound_cnt];
    buffer.pAudioData = g_apDataAudio[sound_cnt];
    buffer.Flags = XAUDIO2_END_OF_STREAM;
    buffer.LoopCount = 0;

    // �I�[�f�B�I�o�b�t�@�̓o�^
    g_apSourceVoice[sound_cnt]->SubmitSourceBuffer(&buffer);
  }

  return true;
}

//------------------------------------------------
// Uninitialize Sounds
//------------------------------------------------
void SoundManager::_UninitializeSounds(void) {
  // �ꎞ��~
  for (int sound_cnt = 0; sound_cnt < kSoundMax; sound_cnt++)
  {
    if (g_apSourceVoice[sound_cnt])
    {
      // �ꎞ��~
      g_apSourceVoice[sound_cnt]->Stop(0);

      // �\�[�X�{�C�X�̔j��
      g_apSourceVoice[sound_cnt]->DestroyVoice();
      g_apSourceVoice[sound_cnt] = NULL;

      // �I�[�f�B�I�f�[�^�̊J��
      free(g_apDataAudio[sound_cnt]);
      g_apDataAudio[sound_cnt] = NULL;
    }
  }
}

//------------------------------------------------
// �`�����N�̃`�F�b�N
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
  {// �t�@�C���|�C���^��擪�Ɉړ�
    return HRESULT_FROM_WIN32(GetLastError());
  }

  while (hr == S_OK)
  {
    if (ReadFile(hFile, &dwChunkType, sizeof(DWORD), &dwRead, NULL) == 0)
    {// �`�����N�̓ǂݍ���
      hr = HRESULT_FROM_WIN32(GetLastError());
    }

    if (ReadFile(hFile, &dwChunkDataSize, sizeof(DWORD), &dwRead, NULL) == 0)
    {// �`�����N�f�[�^�̓ǂݍ���
      hr = HRESULT_FROM_WIN32(GetLastError());
    }

    switch (dwChunkType)
    {
      case 'FFIR':
        dwRIFFDataSize = dwChunkDataSize;
        dwChunkDataSize = 4;
        if (ReadFile(hFile, &dwFileType, sizeof(DWORD), &dwRead, NULL) == 0)
        {// �t�@�C���^�C�v�̓ǂݍ���
          hr = HRESULT_FROM_WIN32(GetLastError());
        }
        break;

      default:
        if (SetFilePointer(hFile, dwChunkDataSize, NULL, FILE_CURRENT) == INVALID_SET_FILE_POINTER)
        {// �t�@�C���|�C���^���`�����N�f�[�^���ړ�
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
// �`�����N�f�[�^�̓ǂݍ���
//------------------------------------------------
HRESULT SoundManager::ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset)
{
  DWORD dwRead;

  if (SetFilePointer(hFile, dwBufferoffset, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER)
  {// �t�@�C���|�C���^���w��ʒu�܂ňړ�
    return HRESULT_FROM_WIN32(GetLastError());
  }

  if (ReadFile(hFile, pBuffer, dwBuffersize, &dwRead, NULL) == 0)
  {// �f�[�^�̓ǂݍ���
    return HRESULT_FROM_WIN32(GetLastError());
  }

  return S_OK;
}

