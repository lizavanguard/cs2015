//==============================================================================
//
// Cursor
// Author: Shimizu Shoji
//
// �e�N�X�`�����w�肷��
// �X�V�ŗh�ꂽ�肷��
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
class Cursor : public Object2D {
public:
  // ctor
  Cursor(const D3DXVECTOR3& position, const D3DXVECTOR2& size, const char* p_filename);

  // dtor
  ~Cursor();

  // Update
  void Update(float elapsed_time);

private:
  float time_;
};
