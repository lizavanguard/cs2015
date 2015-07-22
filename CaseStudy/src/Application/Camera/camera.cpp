//******************************************************************************
//
// �J��������  [camera.cpp]
// Author  :  SHOHEI MATSUMOTO
// �X�V��  :  2015/07/03
//
//******************************************************************************
//******************************************************************************
// �C���N���[�h�t�@�C��
//******************************************************************************
#include "Framework/DirectXHelper/DeviceHolder.h"
#include "Framework/DirectXHelper/DirectXConst.h"
#include "Framework/Input/InputManagerHolder.h"
#include "Framework/Input/InputXInput.h"
#include "Framework/Input/InputKeyboard.h"
#include "Application\Game\SceneGame.h"
#include "Application\Stage\Stage.h"
#include "Camera.h"

//******************************************************************************
// �}�N����`
//******************************************************************************


//******************************************************************************
// �v���g�^�C�v�錾
//******************************************************************************


//******************************************************************************
// �����o�ϐ�:
//******************************************************************************


//******************************************************************************
// �O���[�o���ϐ�:
//******************************************************************************
static const float kCameraSpeed = 10.0f;
static const float kStartZoomRate = 2.0f;
static const float kAcceleValue = 0.02f;

//******************************************************************************
// �֐���`
//******************************************************************************
//==============================================================================
// �R���X�g���N�^
// ����    :  ����
// �߂�l  :  ����
// Author  :  SHOHEI MATSUMOTO
// �X�V��  :  2015/07/03
//==============================================================================
Camera::Camera(Player* player, Stage* stage)
    : player_(nullptr)
    , stage_(nullptr)
    , posP_(D3DXVECTOR3(0.0f, 0.0f, 0.0f))
    , posR_(D3DXVECTOR3(0.0f, 0.0f, 0.0f))
    , vecU_(D3DXVECTOR3(0.0f, 0.0f, 0.0f))
    , rot_(D3DXVECTOR3(0.0f, 0.0f, 0.0f))
    , call_flg_(false)
    , move_mode_change_(false)
    , move_accele_(0.0f){
    player_ = player;
    stage_ = stage;
    const D3DXVECTOR3 player_start_position = player->GetPos();
    posP_ = D3DXVECTOR3(player_start_position.x, player_start_position.y, -5.0f);
    posR_ = player_start_position;
    vecU_ = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
    rot_ = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
    zoomRate_ = kStartZoomRate;
    localView_ = D3DXVECTOR2(kWindowWidth / zoomRate_, kWindowHeight / zoomRate_);
    localScreenFrame_ = localView_;
    _CreateViewPortMatrix(&mtxViewport_, static_cast<unsigned int>(kWindowWidth), static_cast<unsigned int>(kWindowHeight));
}

//==============================================================================
// �f�X�g���N�^
// ����    :  ����
// �߂�l  :  ����
// Author  :  SHOHEI MATSUMOTO
// �X�V��  :  2015/07/03
//==============================================================================
Camera::~Camera(void){

}

//==============================================================================
// �X�V����
// ����    :  ����
// �߂�l  :  ����
// Author  :  SHOHEI MATSUMOTO
// �X�V��  :  2015/07/03
//==============================================================================
void Camera::Update(){
    auto& pKeyboard = InputManagerHolder::Instance().GetInputManager().GetPrimaryKeyboard();
    //  auto& pJoypad = InputManagerHolder::Instance().GetInputManager().GetPrimaryDevice();

    if (pKeyboard.IsPress(DIK_UP)) {
        posP_.y += kCameraSpeed;
        posR_.y += kCameraSpeed;
    }
    if (pKeyboard.IsPress(DIK_DOWN)) {
        posP_.y += -kCameraSpeed;
        posR_.y += -kCameraSpeed;
    }
    if (pKeyboard.IsPress(DIK_LEFT)) {
        posP_.x += -kCameraSpeed;
        posR_.x += -kCameraSpeed;
    }
    if (pKeyboard.IsPress(DIK_RIGHT)) {
        posP_.x += kCameraSpeed;
        posR_.x += kCameraSpeed;
    }

    // �J�������Ă΂�Ă��Ȃ�
    if (call_flg_ == false){
        // �J�����͈̔͊O
        if (player_->GetPos().x > (localView_.x / 5.0f * 2.0f) + posP_.x){
            posP_.x += kCameraSpeed;
            posR_.x += kCameraSpeed;
            //          localScreenFrame_.x += kCameraSpeed;
        }
        if (player_->GetPos().x < (-localView_.x / 5.0f * 2.0f) + posP_.x){
            posP_.x -= kCameraSpeed;
            posR_.x -= kCameraSpeed;
            //          localScreenFrame_.x -= kCameraSpeed;
        }
        if (player_->GetPos().y >(localView_.y / 5.0f * 1.3f) + posP_.y){
            posP_.y += kCameraSpeed;
            posR_.y += kCameraSpeed;
            //          localScreenFrame_.y += kCameraSpeed;
        }
        if (player_->GetPos().y < (-localView_.y / 5.0f * 2.4f) + posP_.y){
            posP_.y -= kCameraSpeed;
            posR_.y -= kCameraSpeed;
            //          localScreenFrame_.y -= kCameraSpeed;
        }
    }
    // �Ă΂�Ă�
    else{
        D3DXVECTOR3 vecPos = pos_dest_ - posR_;
        move_accele_ += kAcceleValue;
        if (D3DXVec2LengthSq(&D3DXVECTOR2(vecPos.x, vecPos.y)) <= 0.0f){
            posR_ = pos_dest_;
            posP_.x = posR_.x;
            posP_.y = posR_.y;
        }
        // �����x�����
        else{
            posR_.x = posR_.x + sinf(move_accele_) * vecPos.x;
            posR_.y = posR_.y + sinf(move_accele_) * vecPos.y;
            posP_.x = posR_.x;
            posP_.y = posR_.y;
        }
    }

    if (InputManagerHolder::Instance().GetInputManager().GetPrimaryKeyboard().IsTrigger(DIK_C)) {
        CallPos(D3DXVECTOR3(500.0f, 200.0f, 0.0f));
    }
    if (InputManagerHolder::Instance().GetInputManager().GetPrimaryKeyboard().IsTrigger(DIK_X)){
        CancelCall();
    }

}

//==============================================================================
// �`�揈��
// ����    :  ����
// �߂�l  :  ����
// Author  :  SHOHEI MATSUMOTO
// �X�V��  :  2015/07/03
//==============================================================================
void Camera::Set(void){
    auto p_device = DeviceHolder::Instance().GetDevice();

    // �r���[�}�g���b�N�X������
    D3DXMatrixIdentity(&mtxView_);
    // �r���[�}�g���b�N�X�̍쐬
    D3DXMatrixLookAtLH(&mtxView_,
        &posP_,
        &posR_,
        &vecU_);
    // �r���[�}�g���b�N�X�̐ݒ�
    p_device->SetTransform(D3DTS_VIEW, &mtxView_);
    // �r���[�}�g���b�N�X�̏�����
    D3DXMatrixIdentity(&mtxProjection_);
    D3DXMatrixOrthoLH(&mtxProjection_, kWindowWidth / zoomRate_, kWindowHeight / zoomRate_, 0.0f, 10.0f);
    // �v���W�F�N�V�����}�g���b�N�X�̐ݒ�
    p_device->SetTransform(D3DTS_PROJECTION, &mtxProjection_);
}

D3DXMATRIX* Camera::_CreateViewPortMatrix(D3DXMATRIX* out, const unsigned int w, const unsigned int h) {
    float W = w * 0.5f;
    float H = h * 0.5f;

    // �X�P�[��(W,-H)�ƕ��s�ړ�(W,H)�̍����ϊ�
    out->_11 = W; out->_12 = 0; out->_13 = 0; out->_14 = 0;
    out->_21 = 0; out->_22 = -H; out->_23 = 0; out->_24 = 0;
    out->_31 = 0; out->_32 = 0; out->_33 = 1; out->_34 = 0;
    out->_41 = W; out->_42 = H; out->_43 = 0; out->_44 = 1;

    return out;
}

// EOF