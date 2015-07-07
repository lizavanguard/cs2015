//==============================================================================
//
// Cursor
// Author: Shimizu Shoji
//
// テクスチャを指定する
// 押された時のテクスチャも指定する
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
  Cursor(const D3DXVECTOR3& position,
         const D3DXVECTOR2& size,
         const char* p_standard_texture_filename,
         const char* p_pushed_texture_filename);

  // dtor
  ~Cursor();

  // Update
  void Update(void);

  // Pushed
  void Pushed(void) { is_pushed_ = true; }

  // set
  void SetPosition(const D3DXVECTOR3& position) { pos_ = position; }

private:
  int standard_texture_id_;
  int pushed_texture_id_;
  bool is_pushed_;
};
