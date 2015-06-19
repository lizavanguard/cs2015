//==============================================================================
//
// TensionTopLayer
// Author: Shimizu Shoji
//
//==============================================================================
#pragma once
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// include
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
#include "Application/Object/Object2D/Object2D.h"

//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// class definition
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
class TensionTopLayer : public Object2D {
public:
  // ctor
  TensionTopLayer(const D3DXVECTOR3& pos, const D3DXVECTOR2& size);

  // Update size
  // 0-1の間で値を渡すとサイズを更新する
  void UpdateSize(float rate);

protected:
  // Drawの前後処理
  void _PreProcessOfDraw(void) override;
  void _PostProcessOfDraw(void) override;

  float original_height_;
  float original_bottom_;
};
