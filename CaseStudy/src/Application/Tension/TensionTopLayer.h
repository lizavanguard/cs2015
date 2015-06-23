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
  // 0-1�̊ԂŒl��n���ƃT�C�Y���X�V����
  void UpdateSize(float rate);

protected:
  // Draw�̑O�㏈��
  void _PreProcessOfDraw(void) override;
  void _PostProcessOfDraw(void) override;

  float original_height_;
  float original_bottom_;
};
