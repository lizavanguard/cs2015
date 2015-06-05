//==============================================================================
//
// DirectX�p [GameDirectX.h]
// Created : Shimizu Shoji
//
//==============================================================================
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// include
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "GameDirectX.h"
#include "../DirectXHelper/DeviceHolder.h"
#include "../GameManager/GameManager.h"
#include "../Utility/Utility.h"


//==============================================================================
// class implementation
//==============================================================================
//------------------------------------------------
// ctor
//------------------------------------------------
GameDirectX::GameDirectX() : pD3D_( nullptr ), pDevice_( nullptr ), pGameManager_( nullptr ) {
}


//------------------------------------------------
// dtor
//------------------------------------------------
GameDirectX::~GameDirectX() {
}


//------------------------------------------------
// Initialize
//------------------------------------------------
void GameDirectX::Initialize( HINSTANCE hInstance, HWND hWnd ) {
	// Direct3D�I�u�W�F�N�g�̐���
	pD3D_ = Direct3DCreate9( D3D_SDK_VERSION );

	// if �쐬�ł��Ȃ�������
	if( !pD3D_ ) {
		// �G���[�ʒm
		return;
	}

	// ���݂̃f�B�X�v���C���[�h���擾
	D3DDISPLAYMODE d3ddm;
	HRESULT hr = pD3D_->GetAdapterDisplayMode( D3DADAPTER_DEFAULT, &d3ddm );
	// if �f�B�X�v���C���[�h���擾�ł��Ȃ�������
	if( FAILED( hr ) ) {
		// �G���[�ʒm
		return;
	}

	// �f�o�C�X�̃v���[���e�[�V�����p�����[�^�̐ݒ�
	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory( &d3dpp, sizeof( d3dpp ) );							// ���[�N���[���N���A
	d3dpp.BackBufferCount        = 1;								// �o�b�N�o�b�t�@�̐�
	d3dpp.BackBufferWidth        = 1280;					// �Q�[����ʃT�C�Y(��)
	d3dpp.BackBufferHeight       = 760;				// �Q�[����ʃT�C�Y(����)
	d3dpp.BackBufferFormat       = D3DFMT_UNKNOWN;				// �o�b�N�o�b�t�@�̃t�H�[�}�b�g�͌��ݐݒ肳��Ă�����̂��g��
	d3dpp.SwapEffect             = D3DSWAPEFFECT_DISCARD;		// �f���M���ɓ������ăt���b�v����
	d3dpp.Windowed               = true;						// �E�B���h�E���[�h
	d3dpp.EnableAutoDepthStencil = TRUE;							// �f�v�X�o�b�t�@�i�y�o�b�t�@�j�ƃX�e���V���o�b�t�@���쐬
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;					// �f�v�X�o�b�t�@�Ƃ���16bit���g��

	// if �E�B���h�E���[�h�Ȃ�
	// TODO: �E�B���h�E���[�h�ؑ�
	if( true ) {
		d3dpp.BackBufferFormat           = D3DFMT_UNKNOWN;							// �o�b�N�o�b�t�@
		d3dpp.FullScreen_RefreshRateInHz = 0;											// ���t���b�V�����[�g
		d3dpp.PresentationInterval       = D3DPRESENT_INTERVAL_IMMEDIATE;		// �C���^�[�o��
	}
	// else �t���X�N���[�����[�h�Ȃ�
	else {
		d3dpp.BackBufferFormat           = D3DFMT_R5G6B5;						// �o�b�N�o�b�t�@
		d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;			// ���t���b�V�����[�g
		d3dpp.PresentationInterval       = D3DPRESENT_INTERVAL_DEFAULT;	// �C���^�[�o��
	}

	// �f�o�C�X�I�u�W�F�N�g�̐���
	// [�f�o�C�X�쐬����]<�`��>��<���_����>���n�[�h�E�F�A�ōs��
	hr = pD3D_->CreateDevice(
		D3DADAPTER_DEFAULT,		// �f�B�X�v���C�A�_�v�^
		D3DDEVTYPE_HAL,		// �f�B�X�v���C�^�C�v
		hWnd,		// �t�H�[�J�X����E�C���h�E�ւ̃n���h��
		D3DCREATE_HARDWARE_VERTEXPROCESSING,	// �f�o�C�X�쐬����̑g�ݍ��킹
		&d3dpp,		// �f�o�C�X�̃v���[���e�[�V�����p�����[�^
		&pDevice_		// �f�o�C�X�C���^�[�t�F�[�X�ւ̃|�C���^
	);

	// if ��L�̐ݒ肪���s������
	if( FAILED( hr ) ) {
		// [�f�o�C�X�쐬����]<�`��>���n�[�h�E�F�A�ōs���A<���_����>��CPU�ōs��
		hr = pD3D_->CreateDevice(
			D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			hWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&d3dpp,
			&pDevice_
		);

		// if ��L�̐ݒ肪���s������
		if( FAILED( hr ) ) {
			// [�f�o�C�X�쐬����]<�`��>��<���_����>��CPU�ōs�Ȃ�
			hr = pD3D_->CreateDevice(
				D3DADAPTER_DEFAULT,
				D3DDEVTYPE_REF,
				hWnd,
				D3DCREATE_SOFTWARE_VERTEXPROCESSING,
				&d3dpp,
				&pDevice_
			);

			// if ��L�̐ݒ肪���s������
			if( FAILED( hr ) ){
				// �G���[�ʒm
				return;
			}
		}
	}

	// �w�ʃJ�����O
	pDevice_->SetRenderState( D3DRS_CULLMODE, D3DCULL_CCW );

	// Z�o�b�t�@�g�p
	pDevice_->SetRenderState( D3DRS_ZENABLE, TRUE );

	// �A���t�@�u�����h�g�p
	pDevice_->SetRenderState( D3DRS_ALPHABLENDENABLE, TRUE );
	// �\�[�X�ƑΏۂ̃A���t�@�u�����h�䗦�ݒ�
	pDevice_->SetRenderState( D3DRS_SRCBLEND, D3DBLEND_SRCALPHA );
	// �\�[�X�̃A���t�@�����̂܂܎g�p���A�Ώۂ͂���̕␔�H���Ƃ�
	pDevice_->SetRenderState( D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA );

	// �T���v���[�X�e�[�g�p�����[�^�̐ݒ�
	// �e�N�X�`���A�h���b�V���O����(U�l)��ݒ�
	pDevice_->SetSamplerState( 0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP );
	// �e�N�X�`���A�h���b�V���O����(V�l)��ݒ�
	pDevice_->SetSamplerState( 0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP );
	// �e�N�X�`���k���t�B���^���[�h��ݒ�
	pDevice_->SetSamplerState( 0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR );
	// �e�N�X�`���g��t�B���^���[�h��ݒ�
	pDevice_->SetSamplerState( 0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR );

	// �e�N�X�`���X�e�[�W�X�e�[�g�̐ݒ�
	// �A���t�@�u�����f�B���O����
	pDevice_->SetTextureStageState( 0, D3DTSS_ALPHAOP, D3DTOP_MODULATE );
	// �ŏ��̃A���t�@����
	pDevice_->SetTextureStageState( 0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE );
	// 2�Ԗڂ̃A���t�@����
	pDevice_->SetTextureStageState( 0, D3DTSS_ALPHAARG2, D3DTA_CURRENT );

  // �z���_�[�ɓn�����Ⴄ
  DeviceHolder::Instance().SetDevice(pDevice_);

  // �Q�[���}�l�[�W��
  GameManager::Instance(hInstance, hWnd, pDevice_);

	return;
}


//------------------------------------------------
// Finalize
//------------------------------------------------
void GameDirectX::Finalize( void ) {
	SafeRelease( pDevice_ );
	SafeRelease( pD3D_ );
}


//------------------------------------------------
// Update
//------------------------------------------------
void GameDirectX::Update( const float elapsedTime ) {
  GameManager::Instance().Update(elapsedTime);
}


//------------------------------------------------
// Draw
//------------------------------------------------
void GameDirectX::Draw( void ) {
	// �w�i�F���w��
	pDevice_->Clear(
		0,
		nullptr,
		( D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER ),	// ���[�h
		D3DCOLOR_RGBA( 0, 128, 128, 0 ),	// �w�i�F
		1.0f,		// Z�[�x
		0
	);

	if( SUCCEEDED( pDevice_->BeginScene() ) ) {

		GameManager::Instance().Draw();

		pDevice_->EndScene();
	}

	pDevice_->Present( nullptr, nullptr, nullptr, nullptr );
}