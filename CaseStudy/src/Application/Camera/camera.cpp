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
  posP_ = D3DXVECTOR3(0.0f , 0.0f , -5.0f);
  posR_ = D3DXVECTOR3(0.0f , 0.0f , 0.0f);
  vecU_ = D3DXVECTOR3(0.0f , 1.0f , 0.0f);
  rot_ = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
  zoomRate_ = kStartZoomRate;
  localView_ = D3DXVECTOR2(kWindowWidth / zoomRate_, kWindowHeight / zoomRate_);
  localScreenFrame_ = localView_;
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

// EOF