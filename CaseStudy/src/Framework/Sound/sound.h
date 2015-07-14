//==============================================================================
//
// サウンド処理 [Sound.h]
// Designed On 2014.02.13 By Shimizu Shoji
//
//==============================================================================
#ifndef __H_SOUND_H__
#define __H_SOUND_H__
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// インクルード
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "xaudio2.h"


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// 列挙型定義
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//------------------------------------------------
// サウンドファイル一覧
//------------------------------------------------
typedef enum {
  SOUND_LABEL_BGM_DEMO0,
  SOUND_LABEL_BGM_RESULT,
  SOUND_LABEL_BGM_STAGESELECT,
  SOUND_LABEL_BGM_TITLE,

  SOUND_LABEL_SE_CALL0,
  SOUND_LABEL_SE_CALL1,
  SOUND_LABEL_SE_CANCEL,
  SOUND_LABEL_SE_DECISION,
  SOUND_LABEL_SE_EAT,
  SOUND_LABEL_SE_INDUCE,
  SOUND_LABEL_SE_PLAYER_GIMMICK,
  SOUND_LABEL_SE_PLAYER_BORO,
  kSoundMax
} SoundLabels;

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// プロトタイプ宣言
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//------------------------------------------------
// 初期化
//------------------------------------------------
HRESULT InitSound( HWND hWnd );

//------------------------------------------------
// 終了処理
//------------------------------------------------
void UninitSound( void );

//------------------------------------------------
// 指定ラベルのサウンドを再生
//------------------------------------------------
HRESULT PlaySound( SoundLabels label );

//------------------------------------------------
// 指定ラベルのサウンドを停止
//------------------------------------------------
void StopSound( SoundLabels label );

//------------------------------------------------
// 全てのサウンドを停止
//------------------------------------------------
void StopSound( void );

#endif // __H_SOUND_H__
