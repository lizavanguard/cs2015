//******************************************************************************
//
// カメラ処理  [camera.cpp]
// Author  :  SHOHEI MATSUMOTO
// 更新日  :  2015/06/09
//
//******************************************************************************
//******************************************************************************
// インクルードファイル
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
// マクロ定義
//******************************************************************************


//******************************************************************************
// プロトタイプ宣言
//******************************************************************************


//******************************************************************************
// メンバ変数:
//******************************************************************************


//******************************************************************************
// グローバル変数:
//******************************************************************************
static const float kCameraSpeed = 10.0f;
static const float kStartZoomRate = 2.0f;

//******************************************************************************
// 関数定義
//******************************************************************************
//==============================================================================
// コンストラクタ
// 引数    :  無し
// 戻り値  :  無し
// Author  :  SHOHEI MATSUMOTO
// 更新日  :  2015/06/09
//==============================================================================
Camera::Camera(Player* player , Stage* stage){
  player_ = player;
  stage_ = stage;
  const D3DXVECTOR3 player_start_position = player->GetPos();
  posP_ = D3DXVECTOR3(player_start_position.x, player_start_position.y, -5.0f);
  posR_ = player_start_position;
  vecU_ = D3DXVECTOR3(0.0f , 1.0f , 0.0f);
  rot_ = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
  zoomRate_ = kStartZoomRate;
  localView_ = D3DXVECTOR2(kWindowWidth / zoomRate_, kWindowHeight / zoomRate_);
  localScreenFrame_ = localView_;

  _CreateViewPortMatrix(&mtxViewport_, static_cast<unsigned int>(kWindowWidth), static_cast<unsigned int>(kWindowHeight));
}

//==============================================================================
// デストラクタ
// 引数    :  無し
// 戻り値  :  無し
// Author  :  SHOHEI MATSUMOTO
// 更新日  :  2015/06/09
//==============================================================================
Camera::~Camera(void){

}

//==============================================================================
// 更新処理
// 引数    :  無し
// 戻り値  :  無し
// Author  :  SHOHEI MATSUMOTO
// 更新日  :  2015/06/09
//==============================================================================
void Camera::Update(){
  auto& pKeyboard = InputManagerHolder::Instance().GetInputManager().GetPrimaryKeyboard();
//  auto& pJoypad = InputManagerHolder::Instance().GetInputManager().GetPrimaryDevice();

  // カメラの範囲外
  if (player_->GetPos().x > (localView_.x / 5.0f * 2.0f) + posP_.x){
      posP_.x += kCameraSpeed;
      posR_.x += kCameraSpeed;
      localScreenFrame_.x += kCameraSpeed;
  }
  if (player_->GetPos().x < (-localView_.x / 5.0f * 2.0f) + posP_.x){
      posP_.x -= kCameraSpeed;
      posR_.x -= kCameraSpeed;
      localScreenFrame_.x -= kCameraSpeed;
  }
  if (player_->GetPos().y > (localView_.y / 5.0f * 1.3f) + posP_.y){
      posP_.y += kCameraSpeed;
      posR_.y += kCameraSpeed;
      localScreenFrame_.y += kCameraSpeed;
  }
  if (player_->GetPos().y < (-localView_.y / 5.0f * 2.4f) + posP_.y){
      posP_.y -= kCameraSpeed;
      posR_.y -= kCameraSpeed;
      localScreenFrame_.y -= kCameraSpeed;
  }

}

//==============================================================================
// 描画処理
// 引数    :  無し
// 戻り値  :  無し
// Author  :  SHOHEI MATSUMOTO
// 更新日  :  2015/06/09
//==============================================================================
void Camera::Set(void){
  auto p_device = DeviceHolder::Instance().GetDevice();

  // ビューマトリックス初期化
  D3DXMatrixIdentity(&mtxView_);
  // ビューマトリックスの作成
  D3DXMatrixLookAtLH(&mtxView_,
      &posP_,
      &posR_,
      &vecU_);
  // ビューマトリックスの設定
  p_device->SetTransform(D3DTS_VIEW, &mtxView_);
  // ビューマトリックスの初期化
  D3DXMatrixIdentity(&mtxProjection_);
  D3DXMatrixOrthoLH(&mtxProjection_, kWindowWidth / zoomRate_, kWindowHeight / zoomRate_, 0.0f, 10.0f);
  // プロジェクションマトリックスの設定
  p_device->SetTransform(D3DTS_PROJECTION, &mtxProjection_);
}

D3DXMATRIX* Camera::_CreateViewPortMatrix(D3DXMATRIX* out, const unsigned int w, const unsigned int h) {
  float W = w * 0.5f;
  float H = h * 0.5f;

  // スケール(W,-H)と平行移動(W,H)の合成変換
  out->_11 = W; out->_12 = 0; out->_13 = 0; out->_14 = 0;
  out->_21 = 0; out->_22 = -H; out->_23 = 0; out->_24 = 0;
  out->_31 = 0; out->_32 = 0; out->_33 = 1; out->_34 = 0;
  out->_41 = W; out->_42 = H; out->_43 = 0; out->_44 = 1;

  return out;
}


// EOF