//==============================================================================
//
// Board
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
class Board : public Object2D {
public:
  // ctor
  Board(const D3DXVECTOR3& pos, const D3DXVECTOR2& size);

protected:
  // Draw�̑O�㏈��
  void _PreProcessOfDraw(void) override;
  void _PostProcessOfDraw(void) override;
};