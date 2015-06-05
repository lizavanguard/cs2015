//==============================================================================
//
// Print Debug String [DebugProc.cpp]
//
//==============================================================================
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// include
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "DebugProc.h"
#include <stdarg.h>
#include <windows.h>


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// constant difinition
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
static const RECT kDrawedRect = { 100, 100, 200, 200 };


//==============================================================================
// class implementation
//==============================================================================
//------------------------------------------------
// instance
//------------------------------------------------
LPD3DXFONT DebugProc::sm_pD3DXFont = nullptr;
std::ostringstream DebugProc::sm_oss;
bool DebugProc::sm_isDisp = true;


//------------------------------------------------
// ctor
//------------------------------------------------
DebugProc::DebugProc() {
}


//------------------------------------------------
// dtor
//------------------------------------------------
DebugProc::~DebugProc() {
}

	
//------------------------------------------------
// init
//------------------------------------------------
void DebugProc::Init( LPDIRECT3DDEVICE9 pDevice ) {
	// D3DXFont�I�u�W�F�N�g�̐���
	HRESULT hr = D3DXCreateFont(
		pDevice,
		16, // ����
		0, // ������
		FW_NORMAL, // ����
		1, // �~�b�v�}�b�v
		FALSE, // �Α�
		SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS,
		DEFAULT_QUALITY,
		DEFAULT_PITCH || FF_DONTCARE,
		"",
		&sm_pD3DXFont
	);
	if( FAILED( hr ) ) {
		// TODO:
		return;
	}
}


//------------------------------------------------
// uninit
//------------------------------------------------
void DebugProc::Uninit( void ) {
	sm_pD3DXFont->Release();
}


//------------------------------------------------
// print
//------------------------------------------------
void DebugProc::Print( const char* fmt, ... ) {
#ifdef _DEBUG

	// ���ꂩ�H
	if( !sm_isDisp ) {
		return;
	}

	// �ϒ������̎擾�J�n
	va_list args;
	va_start( args, fmt );

	// �t�H�[�}�b�g���當����̍\��
	char buff[ 1024 ];
	vsnprintf_s( buff, _TRUNCATE, fmt, args );

	// �ϒ������̎擾�I��
	va_end( args );

	// �X�g���[���ɓ˂�����
	sm_oss << buff;

#endif // _DEBUG
}


//------------------------------------------------
// draw
//------------------------------------------------
void DebugProc::Draw( void ) {
#ifdef _DEBUG
	// �`��
	RECT rect = kDrawedRect;
	sm_pD3DXFont->DrawTextA(
		nullptr,
		sm_oss.str().c_str(),
		-1,
		&rect,
		DT_LEFT | DT_NOCLIP,
		D3DCOLOR_RGBA( 255,0,255,255 )
	);

	// �o�b�t�@�폜
	sm_oss.str( "" );
	sm_oss.clear( std::ostringstream::goodbit );

	// �`�悳�ꂽ��
	sm_isDisp = true;
#endif // _DEBUG
}


//------------------------------------------------
// get
//------------------------------------------------
bool DebugProc::IsEnableDisp( void ) {
	return sm_isDisp;
}


//------------------------------------------------
// set
//------------------------------------------------
void DebugProc::EnableDisp( const bool isDisp ) {
	sm_isDisp = isDisp;
}
