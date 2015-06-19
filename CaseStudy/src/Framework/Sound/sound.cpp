//==============================================================================
//
// サウンド処理 [Sound.cpp]
// Designed On 2014.02.13 By Shimizu Shoji
//
//==============================================================================
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// インクルード
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "sound.h"


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// 構造体定義
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//------------------------------------------------
// パラメータ
//------------------------------------------------
typedef struct {
	char *pFilename;	// ファイル名
	bool bLoop;			// ループするかどうか
} SoundParam;


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// プロトタイプ宣言
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//------------------------------------------------
//------------------------------------------------
HRESULT CheckChunk( HANDLE hFile, DWORD format, DWORD *pChunkSize, DWORD *pChunkDataPosition );

//------------------------------------------------
//------------------------------------------------
HRESULT ReadChunkData( HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset );


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// グローバル変数
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
IXAudio2 *g_pXAudio2 = NULL;								// XAudio2オブジェクトへのインターフェイス
IXAudio2MasteringVoice *g_pMasteringVoice = NULL;			// マスターボイス
IXAudio2SourceVoice *g_apSourceVoice[ kSoundMax ] = {};	// ソースボイス
BYTE *g_apDataAudio[ kSoundMax ] = {};					// オーディオデータ
DWORD g_aSizeAudio[ kSoundMax ] = {};					// オーディオデータサイズ

// 各音素材のパラメータ
SoundParam g_aParam[ kSoundMax ] = {
  {"data/bgm/BGM_demo00.wav", true},
  {"data/se/SE_uriel_call_0.wav", false},
  {"data/se/SE_uriel_call_1.wav", false},
  {"data/se/SE_uriel_eat.wav", false},
};


//==============================================================================
// 関数実装部
//==============================================================================
//------------------------------------------------
// 初期化
//------------------------------------------------
HRESULT InitSound( HWND hWnd ) {
	HRESULT hr;

	// COMライブラリの初期化
	CoInitializeEx( NULL, COINIT_MULTITHREADED );

	// XAudio2オブジェクトの作成
	hr = XAudio2Create( &g_pXAudio2, 0 );
	if( FAILED( hr ) ) {
		MessageBox( hWnd, "XAudio2オブジェクトの作成に失敗！", "警告！", MB_ICONWARNING );

		// COMライブラリの終了処理
		CoUninitialize();
		return E_FAIL;
	}
	
	// マスターボイスの生成
	hr = g_pXAudio2->CreateMasteringVoice( &g_pMasteringVoice );
	if( FAILED( hr ) ) {
		MessageBox( hWnd, "マスターボイスの生成に失敗！", "警告！", MB_ICONWARNING );

		if( g_pXAudio2 ) {
			// XAudio2オブジェクトの開放
			g_pXAudio2->Release();
			g_pXAudio2 = NULL;
		}

		// COMライブラリの終了処理
		CoUninitialize();

		return E_FAIL;
	}

	// サウンドデータの初期化
	for( int sound_cnt = 0; sound_cnt < kSoundMax; sound_cnt++ ) {
		HANDLE hFile;
		DWORD dwChunkSize = 0;
		DWORD dwChunkPosition = 0;
		DWORD dwFiletype;
		WAVEFORMATEXTENSIBLE wfx;
		XAUDIO2_BUFFER buffer;

		// バッファのクリア
		memset( &wfx, 0, sizeof( WAVEFORMATEXTENSIBLE ) );
		memset( &buffer, 0, sizeof( XAUDIO2_BUFFER ) );

		// サウンドデータファイルの生成
		hFile = CreateFile( g_aParam[ sound_cnt ].pFilename, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL );
		if( hFile == INVALID_HANDLE_VALUE ) {
			MessageBox( hWnd, "サウンドデータファイルの生成に失敗！(1)", "警告！", MB_ICONWARNING );
			return HRESULT_FROM_WIN32( GetLastError() );
		}

		// ファイルポインタを先頭に移動
		if( SetFilePointer( hFile, 0, NULL, FILE_BEGIN ) == INVALID_SET_FILE_POINTER ) {
			MessageBox( hWnd, "サウンドデータファイルの生成に失敗！(2)", "警告！", MB_ICONWARNING );
			return HRESULT_FROM_WIN32( GetLastError() );
		}
	
		// WAVEファイルのチェック
		hr = CheckChunk( hFile, 'FFIR', &dwChunkSize, &dwChunkPosition );
		if( FAILED( hr ) ) {
			MessageBox( hWnd, "WAVEファイルのチェックに失敗！(1)", "警告！", MB_ICONWARNING );
			return S_FALSE;
		}
		hr = ReadChunkData( hFile, &dwFiletype, sizeof(DWORD), dwChunkPosition );
		if( FAILED( hr ) ) {
			MessageBox( hWnd, "WAVEファイルのチェックに失敗！(2)", "警告！", MB_ICONWARNING );
			return S_FALSE;
		}
		if( dwFiletype != 'EVAW' ) {
			MessageBox( hWnd, "WAVEファイルのチェックに失敗！(3)", "警告！", MB_ICONWARNING );
			return S_FALSE;
		}
	
		// フォーマットチェック
		hr = CheckChunk( hFile, ' tmf', &dwChunkSize, &dwChunkPosition );
		if( FAILED( hr ) ) {
			MessageBox( hWnd, "フォーマットチェックに失敗！(1)", "警告！", MB_ICONWARNING );
			return S_FALSE;
		}
		hr = ReadChunkData( hFile, &wfx, dwChunkSize, dwChunkPosition );
		if( FAILED( hr ) ) {
			MessageBox(hWnd, "フォーマットチェックに失敗！(2)", "警告！", MB_ICONWARNING);
			return S_FALSE;
		}

		// オーディオデータ読み込み
		hr = CheckChunk(hFile, 'atad', &g_aSizeAudio[sound_cnt], &dwChunkPosition);
		if(FAILED(hr))
		{
			MessageBox(hWnd, "オーディオデータ読み込みに失敗！(1)", "警告！", MB_ICONWARNING);
			return S_FALSE;
		}
		g_apDataAudio[sound_cnt] = (BYTE*)malloc(g_aSizeAudio[sound_cnt]);
		hr = ReadChunkData(hFile, g_apDataAudio[sound_cnt], g_aSizeAudio[sound_cnt], dwChunkPosition);
		if(FAILED(hr))
		{
			MessageBox(hWnd, "オーディオデータ読み込みに失敗！(2)", "警告！", MB_ICONWARNING);
			return S_FALSE;
		}
	
		// ソースボイスの生成
		hr = g_pXAudio2->CreateSourceVoice(&g_apSourceVoice[sound_cnt], &(wfx.Format));
		if(FAILED(hr))
		{
			MessageBox(hWnd, "ソースボイスの生成に失敗！", "警告！", MB_ICONWARNING);
			return S_FALSE;
		}

		memset(&buffer, 0, sizeof(XAUDIO2_BUFFER));
		buffer.AudioBytes = g_aSizeAudio[sound_cnt];
		buffer.pAudioData = g_apDataAudio[sound_cnt];
		buffer.Flags      = XAUDIO2_END_OF_STREAM;
		buffer.LoopCount  = 0;

		// オーディオバッファの登録
		g_apSourceVoice[sound_cnt]->SubmitSourceBuffer(&buffer);
	}

	return S_OK;
}

//------------------------------------------------
// 終了処理
//------------------------------------------------
void UninitSound(void)
{
	// 一時停止
	for(int sound_cnt = 0; sound_cnt < kSoundMax; sound_cnt++)
	{
		if(g_apSourceVoice[sound_cnt])
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
	
	// マスターボイスの破棄
	g_pMasteringVoice->DestroyVoice();
	g_pMasteringVoice = NULL;
	
	if(g_pXAudio2)
	{
		// XAudio2オブジェクトの開放
		g_pXAudio2->Release();
		g_pXAudio2 = NULL;
	}
	
	// COMライブラリの終了処理
	CoUninitialize();
}

//------------------------------------------------
// セグメント再生(停止)
//------------------------------------------------
HRESULT PlaySound(SoundLabels label)
{
	XAUDIO2_VOICE_STATE xa2state;
	XAUDIO2_BUFFER buffer;

	memset(&buffer, 0, sizeof(XAUDIO2_BUFFER));
	buffer.AudioBytes = g_aSizeAudio[label];
	buffer.pAudioData = g_apDataAudio[label];
	buffer.Flags      = XAUDIO2_END_OF_STREAM;
	buffer.LoopCount  = g_aParam[ label ].bLoop ? 0xffffffff : 0;

	// 状態取得
	g_apSourceVoice[label]->GetState(&xa2state);
	if(xa2state.BuffersQueued != 0)
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
void StopSound(SoundLabels label)
{
	XAUDIO2_VOICE_STATE xa2state;

	// 状態取得
	g_apSourceVoice[label]->GetState(&xa2state);
	if(xa2state.BuffersQueued != 0)
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
void StopSound(void)
{
	// 一時停止
	for(int sound_cnt = 0; sound_cnt < kSoundMax; sound_cnt++)
	{
		if(g_apSourceVoice[sound_cnt])
		{
			// 一時停止
			g_apSourceVoice[sound_cnt]->Stop(0);
		}
	}
}


//==============================================================================
// 内部関数実装部
//==============================================================================
//------------------------------------------------
// チャンクのチェック
//------------------------------------------------
HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD *pChunkSize, DWORD *pChunkDataPosition)
{
	HRESULT hr = S_OK;
	DWORD dwRead;
	DWORD dwChunkType;
	DWORD dwChunkDataSize;
	DWORD dwRIFFDataSize = 0;
	DWORD dwFileType;
	DWORD dwBytesRead = 0;
	DWORD dwOffset = 0;
	
	if(SetFilePointer(hFile, 0, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER)
	{// ファイルポインタを先頭に移動
		return HRESULT_FROM_WIN32(GetLastError());
	}
	
	while(hr == S_OK)
	{
		if(ReadFile(hFile, &dwChunkType, sizeof(DWORD), &dwRead, NULL) == 0)
		{// チャンクの読み込み
			hr = HRESULT_FROM_WIN32(GetLastError());
		}

		if(ReadFile(hFile, &dwChunkDataSize, sizeof(DWORD), &dwRead, NULL) == 0)
		{// チャンクデータの読み込み
			hr = HRESULT_FROM_WIN32(GetLastError());
		}

		switch(dwChunkType)
		{
		case 'FFIR':
			dwRIFFDataSize  = dwChunkDataSize;
			dwChunkDataSize = 4;
			if(ReadFile(hFile, &dwFileType, sizeof(DWORD), &dwRead, NULL) == 0)
			{// ファイルタイプの読み込み
				hr = HRESULT_FROM_WIN32(GetLastError());
			}
			break;

		default:
			if(SetFilePointer(hFile, dwChunkDataSize, NULL, FILE_CURRENT) == INVALID_SET_FILE_POINTER)
			{// ファイルポインタをチャンクデータ分移動
				return HRESULT_FROM_WIN32(GetLastError());
			}
		}

		dwOffset += sizeof(DWORD) * 2;
		if(dwChunkType == format)
		{
			*pChunkSize         = dwChunkDataSize;
			*pChunkDataPosition = dwOffset;

			return S_OK;
		}

		dwOffset += dwChunkDataSize;
		if(dwBytesRead >= dwRIFFDataSize)
		{
			return S_FALSE;
		}
	}
	
	return S_OK;
}

//------------------------------------------------
// チャンクデータの読み込み
//------------------------------------------------
HRESULT ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset)
{
	DWORD dwRead;
	
	if(SetFilePointer(hFile, dwBufferoffset, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER)
	{// ファイルポインタを指定位置まで移動
		return HRESULT_FROM_WIN32(GetLastError());
	}

	if(ReadFile(hFile, pBuffer, dwBuffersize, &dwRead, NULL) == 0)
	{// データの読み込み
		return HRESULT_FROM_WIN32(GetLastError());
	}
	
	return S_OK;
}

