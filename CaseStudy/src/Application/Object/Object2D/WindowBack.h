//******************************************************************************
//
// WindowBack  [WindowBack.h]
// Author  :  SHOHEI MATSUMOTO
// 更新日  :  2015/07/07
//
//******************************************************************************
//******************************************************************************
// インクルードガード
//******************************************************************************
#ifndef _WINDOWBACK_H_
#define _WINDOWBACK_H_

//******************************************************************************
// インクルードファイル
//******************************************************************************
#include "Object2D.h"

//******************************************************************************
// ライブラリのリンク
//******************************************************************************


//******************************************************************************
// マクロ定義
//******************************************************************************


//******************************************************************************
// 構造体定義
//******************************************************************************

//******************************************************************************
// クラス定義
//******************************************************************************
class WindowBack : public Object2D{
  // enum ======================================
public:

  // funciton ==================================
public:
  // ctor
  WindowBack(const D3DXVECTOR3 &pos, const float &rot, const D3DXVECTOR2 &size);
  void Update();
  // draw
  void _PreProcessOfDraw(void);
  void _PostProcessOfDraw(void);
  // set
  void SetTexColor(D3DXCOLOR color){ color_ = color; }

protected:
private:


  // parameter =================================
public:

protected:

private:
  D3DXCOLOR tex_color_;
};

//******************************************************************************
// プロトタイプ宣言
//******************************************************************************



#endif
// EOF