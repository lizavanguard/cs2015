//******************************************************************************
//
// カメラ処理  [camera.h]
// Author  :  SHOHEI MATSUMOTO
// 更新日  :  2015/06/09
//
//******************************************************************************
//******************************************************************************
// インクルードガード
//******************************************************************************
#ifndef _CAMERA_H_
#define _CAMERA_H_

//******************************************************************************
// インクルードファイル
//******************************************************************************
#include "Framework\FrameworkOption.h"
#include "Application\Object\player.h"

//******************************************************************************
// ライブラリのリンク
//******************************************************************************


//******************************************************************************
// マクロ定義
//******************************************************************************
static const float kHalfWindowWidth = kWindowWidth * 0.5f;
static const float kHalfWindowHeight = kWindowHeight * 0.5f;

//******************************************************************************
// 構造体定義
//******************************************************************************


//******************************************************************************
// クラス定義
//******************************************************************************
class Camera{
public:
    // enum

public:
    // funciton ==================================
    // ctor
    Camera(Player* player, Stage * stage);

    // dtor
    virtual ~Camera();

    // update
    void Update(void);

    // draw
    void Set(void);

    // add posP
    void AddPosP(const D3DXVECTOR3& pos) { posP_ += pos; }
    void AddPosPX(float x) { posP_.x += x; }
    void AddPosPY(float y) { posP_.y += y; }
    void AddPosPZ(float z) { posP_.z += z; }
    // add posR
    void AddPosR(const D3DXVECTOR3& pos) { posR_ += pos; }
    void AddPosRX(float x) { posR_.x += x; }
    void AddPosRY(float y) { posR_.y += y; }
    void AddPosRZ(float z) { posR_.z += z; }

    // add rot
    void AddRot(const D3DXVECTOR3& rot) { rot_ += rot; }

    // get
    D3DXVECTOR3 GetPosP(void) const { return posP_; }
    D3DXVECTOR3 GetPosR(void) const { return posR_; }
    D3DXVECTOR3 GetRot(void) const { return rot_; }
    D3DXMATRIX GetView(void) const { return mtxView_; }
    D3DXMATRIX GetProjection(void) const { return mtxProjection_; }
    D3DXMATRIX GetMatrixViewProjectionViewPort(void) const { return mtxView_ * mtxProjection_ * mtxViewport_; }

    // set
    void SetPosP(const D3DXVECTOR3& pos) { posP_ = pos; }
    void SetPosR(const D3DXVECTOR3& pos) { posR_ = pos; }
    void SetRot(const D3DXVECTOR3& rot) { rot_ = rot; }

    // set
    void SetDestPos(const D3DXVECTOR3& pos);

    void CallPos(const D3DXVECTOR3& pos){ pos_dest_ = pos; call_flg_ = true; move_mode_change_ = false; }
    void CancelCall(void){ call_flg_ = false; move_accele_ = 0.0f; }

private:


    // parameter =================================
public:

protected:

private:
    D3DXMATRIX* _CreateViewPortMatrix(D3DXMATRIX* out, const unsigned int w, const unsigned int h);

    D3DXVECTOR3 posP_;            // カメラの視点
    D3DXVECTOR3 posR_;            // カメラの注視点(向き)
    D3DXVECTOR3 vecU_;            // カメラの上方向ベクトル
    D3DXVECTOR3 rot_;             // カメラの向き
    D3DXMATRIX mtxView_;          // ビューマトリックス
    D3DXMATRIX mtxProjection_;    // プロジェクションマトリックス
    D3DXMATRIX mtxViewport_;      // ビューポートマトリックス
    float zoomRate_;
    D3DXVECTOR2 localView_;
    D3DXVECTOR2 localScreenFrame_;
    bool call_flg_;               // カメラ呼び出し
    bool move_mode_change_;
    D3DXVECTOR3 pos_dest_;         // 目的地
    float move_accele_;        // 加速移動係数
    Player *player_;
    Stage *stage_;
};

//******************************************************************************
// プロトタイプ宣言
//******************************************************************************



#endif
// EOF