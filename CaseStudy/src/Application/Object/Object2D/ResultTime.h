//******************************************************************************
//
// クリアタイム処理  [Resultime.h]
// Author  :  SHOHEI MATSUMOTO
// 更新日  :  2015/06/29
//
//******************************************************************************
//******************************************************************************
// インクルードガード
//******************************************************************************
#ifndef _RESULTTIME_H_
#define _RESULTTIME_H_

//******************************************************************************
// インクルードファイル
//******************************************************************************
#include "NumberObject.h"

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
class NumberObject;
class Object2D;
class ResultTime{
  public:
  // modemanaged


  // funciton ==================================
public:
  // ctor
    ResultTime(const D3DXVECTOR3 &pos, const float &rot, const D3DXVECTOR2 &size, const int &value, NUMBER_TYPE type);
  // dtor
  virtual ~ResultTime();
  // update
  void Update();
  // draw
  void Draw(void);
  // reset
  void Reset(void);


protected:

private:


  // parameter =================================
public:

protected:

private:
  int count_;
  int value_;
  int timer_value_;
  NumberObject **p_number_object_;
  Object2D *p_object2D_;
};

//******************************************************************************
// プロトタイプ宣言
//******************************************************************************



#endif
// EOF