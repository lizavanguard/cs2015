//******************************************************************************
//
// ナンバーオブジェクト処理  [NumberObject.h]
// Author  :  SHOHEI MATSUMOTO
// 更新日  :  2015/06/16
//
//******************************************************************************
//******************************************************************************
// インクルードファイル
//******************************************************************************
#include "Framework/DirectXHelper/DeviceHolder.h"
#include "Framework/DirectXHelper/DirectXConst.h"
#include "Framework/GameWindow/GameDirectX.h"
#include "Framework/Texture/TextureManagerHolder.h"
#include "NumberObject.h"
#include "Framework\GameManager\GameManager.h"
#include "Framework\DebugProc\DebugProc.h"

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
static const char *s_NumberData[] = {
    "data/Texture/number_simple.png" ,
    "data/Texture/figure_all.png",
};

//******************************************************************************
// 関数定義
//******************************************************************************
//==============================================================================
// コンストラクタ
// 引数    :  無し
// 戻り値  :  無し
// Author  :  SHOHEI MATSUMOTO
// 更新日  :  2015/06/12
//==============================================================================
NumberObject::NumberObject(const D3DXVECTOR3 &pos, const float &rot, const D3DXVECTOR2 &size, NUMBER_TYPE type) :Object2D(pos, size, s_NumberData[type]) {
  value_ = 0;

  //pos_ = pos;
  rot_ = rot;
  //size_ = size;
  type_ = type;
  //SetTexture(s_NumberData[type]);
}

//==============================================================================
// デストラクタ
// 引数    :  無し
// 戻り値  :  無し
// Author  :  SHOHEI MATSUMOTO
// 更新日  :  2015/06/12
//==============================================================================
//NumberObject::~NumberObject(void){
//
//}

//==============================================================================
// 初期化
// 引数    :  無し
// 戻り値  :  無し
// Author  :  SHOHEI MATSUMOTO
// 更新日  :  2015/06/16
//==============================================================================
//void NumberObject::Init(D3DXVECTOR3 pos, D3DXVECTOR2 rot, D3DXVECTOR2 size, NUMBER_TYPE type){
//  auto p_device = DeviceHolder::Instance().GetDevice();
//
//  SetPos(pos);
//  SetRot(rot);
//  SetSize(size);
//
//  // HACK:
//  //p_device->CreateVertexBuffer(
//  //    sizeof(Vertex2D) * 4,
//  //    D3DUSAGE_WRITEONLY,
//  //    kVertexFVF2D,
//  //    D3DPOOL_MANAGED,
//  //    &p_vertex_buffer_,
//  //    nullptr);
//
//  texture_id_ = TextureManagerHolder::Instance().GetTextureManager().LoadTexture(s_NumberData[type]);
//}

void NumberObject::Update(){
}

//==============================================================================
// 描画処理
// 引数    :  無し
// 戻り値  :  無し
// Author  :  SHOHEI MATSUMOTO
// 更新日  :  2015/06/12
//==============================================================================
void NumberObject::_PreProcessOfDraw(void){
    start_uv_ = (D3DXVECTOR2((float)value_ / 10.0f, 0.0f));
    end_uv_ = (D3DXVECTOR2((float)value_ / 10.0f + NUMBER_DIVISION, 1.0f));
}

void NumberObject::_PostProcessOfDraw(void){
}


// EOF