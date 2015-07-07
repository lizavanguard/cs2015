//==============================================================================
//
// �t�F�[�h���W���[��[fade.cpp]
// Designed On 2013/07/13 By Shimizu Shoji
//
//==============================================================================
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// �C���N���[�h
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "Fade.h"

#include "Framework/DirectXHelper/DeviceHolder.h"
#include "Framework/FrameworkOption.h"

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// �萔��`
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
static const int kPolygonMax = 1;	// �l�p�`�̃|���S���̐�
static const int kVertexMax = kPolygonMax * 4;

static const float kAlphaMax = 255.0f;
static const float kFadeSpd = 4.0f;

static const float kFadeWidth = kWindowWidth;
static const float kFadeHeight = kWindowHeight + 100;
static const float kFadePosX = kFadeWidth / 2;
static const float kFadePosY = kFadeHeight / 2;


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// �\���̒�`
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
namespace {

//------------------------------------------------
// �I�u�W�F�N�g
//------------------------------------------------
typedef struct {
	D3DXVECTOR3 pos;	// �|���S���̈ʒu(���S�_�����W�Ƃ��ĕێ�����)
	D3DXVECTOR3 spd;	// ���x
	D3DXVECTOR3 rot;	// �|���S���̉�](����)
	D3DXVECTOR3 size;	// �|���S���̃T�C�Y
	float length;		// �|���S���̑Ίp���̒���
	float angle;		// �|���S���̑Ίp���̊p�x
	LPDIRECT3DVERTEXBUFFER9 vtx_buff;	// ���_�o�b�t�@
} Object;

//------------------------------------------------
// �t�F�[�h
//------------------------------------------------
typedef struct {
	Object obj;
	Fades fade_mode;
	float alpha;
} Fade;

typedef struct _Vertex2 {
  D3DXVECTOR3 vtx;		// ���_���W
  float    rhw;		// �������W�̌W��w
  D3DCOLOR diffuse;	// ���ˌ�
  D3DXVECTOR2  tex;		// �e�N�X�`�����W
} Vertex2;

#define FVF_VERTEX_2D ( D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1 )

}


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// �v���g�^�C�v�錾
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
static bool UpdateFadeIn( void );
static bool UpdateFadeOut( void );


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// �O���[�o���ϐ�
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
static LPDIRECT3DVERTEXBUFFER9 g_pD3DVtxBuff = NULL;
Fade g_fade;	// �t�F�[�h


//==============================================================================
// �֐�������
//==============================================================================
//------------------------------------------------
// �t�F�[�h�̏�����
//------------------------------------------------
HRESULT InitFade( void )
{
	// �����p�����[�^
	g_fade.obj.pos = D3DXVECTOR3( kFadePosX, kFadePosY, 0 );
	g_fade.obj.spd = D3DXVECTOR3( 0, 0, 0 );
	g_fade.obj.rot = D3DXVECTOR3( 0, 0, 0 );
	g_fade.obj.size = D3DXVECTOR3( kFadeWidth, kFadeHeight, 0 );
	g_fade.obj.length = 0;
	g_fade.obj.angle = 0;

	// �f�o�C�X�n���h���̎擾
	LPDIRECT3DDEVICE9 pDevice;
  pDevice = DeviceHolder::Instance().GetDevice();

	// ���_�o�b�t�@�̐���(�������̊m��)
	HRESULT hr = pDevice->CreateVertexBuffer(
		sizeof( Vertex2 ) * kVertexMax,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pD3DVtxBuff,
		NULL
	);

	// if �����Ɏ��s������
	if( FAILED( hr ) ) {
		return E_FAIL;
	}

	// �|���S���̑Ίp���̒����̌v�Z
	g_fade.obj.length = sqrtf( ( g_fade.obj.size.x / 2 ) * ( g_fade.obj.size.x / 2 ) + ( g_fade.obj.size.y / 2 ) * ( g_fade.obj.size.y / 2 ) );

	// �|���S���̒��S�_����Ίp���ɑ΂���p�x�̌v�Z
	g_fade.obj.angle = atan2f( g_fade.obj.size.x, g_fade.obj.size.y );

	// �A���t�@�̐ݒ�
	g_fade.alpha = 0.0f;

	// ���_���̐ݒ�
	Vertex2* pVtx;
	// ��L�J�n
	g_pD3DVtxBuff->Lock( 0, 0, ( void** )&pVtx, 0 );
	// ���W�̐ݒ�
	pVtx[ 0 ].vtx.x = g_fade.obj.pos.x - sinf( g_fade.obj.rot.z + g_fade.obj.angle ) * g_fade.obj.length;
	pVtx[ 0 ].vtx.y = g_fade.obj.pos.y - cosf( g_fade.obj.rot.z + g_fade.obj.angle ) * g_fade.obj.length;
	pVtx[ 1 ].vtx.x = g_fade.obj.pos.x + sinf( -g_fade.obj.rot.z + g_fade.obj.angle ) * g_fade.obj.length;
	pVtx[ 1 ].vtx.y = g_fade.obj.pos.y - cosf( -g_fade.obj.rot.z + g_fade.obj.angle ) * g_fade.obj.length;
	pVtx[ 2 ].vtx.x = g_fade.obj.pos.x - sinf( -g_fade.obj.rot.z + g_fade.obj.angle ) * g_fade.obj.length;
	pVtx[ 2 ].vtx.y = g_fade.obj.pos.y + cosf( -g_fade.obj.rot.z + g_fade.obj.angle ) * g_fade.obj.length;
	pVtx[ 3 ].vtx.x = g_fade.obj.pos.x + sinf( g_fade.obj.rot.z + g_fade.obj.angle ) * g_fade.obj.length;
	pVtx[ 3 ].vtx.y = g_fade.obj.pos.y + cosf( g_fade.obj.rot.z + g_fade.obj.angle ) * g_fade.obj.length;

	// rhw�̐ݒ�
	pVtx[ 0 ].rhw = 1.0f;
	pVtx[ 1 ].rhw = 1.0f;
	pVtx[ 2 ].rhw = 1.0f;
	pVtx[ 3 ].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	pVtx[ 0 ].diffuse = D3DCOLOR_RGBA( 0,0,0,(int)g_fade.alpha );
	pVtx[ 1 ].diffuse = D3DCOLOR_RGBA( 0,0,0,(int)g_fade.alpha );
	pVtx[ 2 ].diffuse = D3DCOLOR_RGBA( 0,0,0,(int)g_fade.alpha );
	pVtx[ 3 ].diffuse = D3DCOLOR_RGBA( 0,0,0,(int)g_fade.alpha );

	// �e�N�X�`�����W�̐ݒ�
	pVtx[ 0 ].tex = D3DXVECTOR2( 0.0f, 0.0f );
	pVtx[ 1 ].tex = D3DXVECTOR2( 1.0f, 0.0f );
	pVtx[ 2 ].tex = D3DXVECTOR2( 0.0f, 1.0f );
	pVtx[ 3 ].tex = D3DXVECTOR2( 1.0f, 1.0f );

	// ��L�I��
	g_pD3DVtxBuff->Unlock();

	// �e�N�X�`���̓ǂݍ���
	/*
	D3DXCreateTextureFromFile( pDevice,
							   kTextureFilename,
							   &g_pD3DTex );
	*/

	return S_OK;
}

//------------------------------------------------
// �t�F�[�h�̏I������
//------------------------------------------------
void UninitFade( void )
{
	// ���_�o�b�t�@�̉��
	SafeRelease( g_pD3DVtxBuff );
}

//------------------------------------------------
// �t�F�[�h�̍X�V����
// �t�F�[�h�A�E�g��������true��Ԃ�
// ����ȊO��false
//------------------------------------------------
bool UpdateFade( void )
{
	// ��Ԃɂ�蕪��
	switch( g_fade.fade_mode ){
	case FADE_NONE:
		break;
	case FADE_IN:
		return UpdateFadeIn();
		break;
	case FADE_OUT:
		return UpdateFadeOut();
		break;
	default:
		break;
	}
	return false;
}

//------------------------------------------------
// �t�F�[�h�̕`�揈��
//------------------------------------------------
void DrawFade( void )
{
	// �f�o�C�X�n���h���̎擾
  LPDIRECT3DDEVICE9 m_device = DeviceHolder::Instance().GetDevice();
	
	// �����_�[�X�e�[�g�p�����[�^�̐ݒ�
	// �w�ʃJ�����O
	m_device->SetRenderState( D3DRS_CULLMODE, D3DCULL_CCW );
	// Z�o�b�t�@�g�p
	m_device->SetRenderState( D3DRS_ZENABLE, TRUE );
	// �A���t�@�u�����h�g�p
	m_device->SetRenderState( D3DRS_ALPHABLENDENABLE, TRUE );
	// �\�[�X�ƑΏۂ̃A���t�@�u�����h�䗦�ݒ�
	m_device->SetRenderState( D3DRS_SRCBLEND, D3DBLEND_SRCALPHA );
	// �\�[�X�̃A���t�@�����̂܂܎g�p���A�Ώۂ͂���̕␔�H���Ƃ�
	m_device->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA );
	
	// ���_�X�g���[���Ƀo�C���h
	m_device->SetStreamSource( 0, g_pD3DVtxBuff, 0, sizeof( Vertex2 ) );

	// FVF�̐ݒ�
	m_device->SetFVF( FVF_VERTEX_2D );

	// �e�N�X�`���̃Z�b�g
	m_device->SetTexture( 0, NULL );

	// �|���S���̕`��
	m_device->DrawPrimitive( D3DPT_TRIANGLESTRIP, 0, 2 );
}

//------------------------------------------------
// �t�F�[�h�̐ݒ�
//------------------------------------------------
void SetFade( Fades fade )
{
	g_fade.fade_mode = fade;
}


//==============================================================================
// �����֐�������
//==============================================================================
//------------------------------------------------
// �t�F�[�h�C���̍X�V����
//------------------------------------------------
static bool UpdateFadeIn( void ) {
	// �A���t�@�̌��Z
  bool done_fade_in = false;
  g_fade.alpha -= kFadeSpd;
	// if �A���t�@�̍ŏ��l���z���Ă�����
	if( g_fade.alpha <= 0 ) {
		// �ŏ��l��ݒ肵�Ēʏ��Ԃ�
		g_fade.alpha = 0;
		g_fade.fade_mode = FADE_NONE;
    done_fade_in = true;
  }

	// ���_���̐ݒ�
	Vertex2* pVtx;
	// ��L�J�n
	g_pD3DVtxBuff->Lock( 0, 0, ( void** )&pVtx, 0 );

	// ���ˌ��̐ݒ�
	pVtx[ 0 ].diffuse = D3DCOLOR_RGBA( 0,0,0,(int)g_fade.alpha );
	pVtx[ 1 ].diffuse = D3DCOLOR_RGBA( 0,0,0,(int)g_fade.alpha );
	pVtx[ 2 ].diffuse = D3DCOLOR_RGBA( 0,0,0,(int)g_fade.alpha );
	pVtx[ 3 ].diffuse = D3DCOLOR_RGBA( 0,0,0,(int)g_fade.alpha );

	// ��L�I��
	g_pD3DVtxBuff->Unlock();

  return done_fade_in;
}

//------------------------------------------------
// �t�F�[�h�A�E�g�̍X�V����
//------------------------------------------------
static bool UpdateFadeOut( void ) {
	bool done_fade_out = false;
	// �A���t�@�̉��Z
	g_fade.alpha += kFadeSpd;
	// if �A���t�@�̍ő�l�𒴂��Ă�����
	if( g_fade.alpha > kAlphaMax ) {
		// �ő�l��ݒ肵�Ēʏ��Ԃ�
		g_fade.alpha = kAlphaMax;
		g_fade.fade_mode = FADE_NONE;
		done_fade_out = true;
	}

	// ���_���̐ݒ�
	Vertex2* pVtx;
	// ��L�J�n
	g_pD3DVtxBuff->Lock( 0, 0, ( void** )&pVtx, 0 );

	// ���ˌ��̐ݒ�
	pVtx[ 0 ].diffuse = D3DCOLOR_RGBA( 0,0,0,(int)g_fade.alpha );
	pVtx[ 1 ].diffuse = D3DCOLOR_RGBA( 0,0,0,(int)g_fade.alpha );
	pVtx[ 2 ].diffuse = D3DCOLOR_RGBA( 0,0,0,(int)g_fade.alpha );
	pVtx[ 3 ].diffuse = D3DCOLOR_RGBA( 0,0,0,(int)g_fade.alpha );

	// ��L�I��
	g_pD3DVtxBuff->Unlock();

	return done_fade_out;
}
