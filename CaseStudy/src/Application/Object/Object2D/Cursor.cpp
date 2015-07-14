//==============================================================================
//
// Cursor
// Author: Shimizu Shoji
//
//==============================================================================
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// include
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
#include "Cursor.h"

//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// const
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
namespace {

}

//==============================================================================
// class implementation
//==============================================================================
//------------------------------------------------
// ctor
//------------------------------------------------
Cursor::Cursor(const D3DXVECTOR3& position,
               const D3DXVECTOR2& size,
               const char* p_standard_texture_filename,
               const char* p_pushed_texture_filename)
    : Object2D(position, size, p_pushed_texture_filename)
    , standard_texture_id_(-1)
    , pushed_texture_id_(texture_id_)
    , is_pushed_(false) {
  SetTexture(p_standard_texture_filename);
  standard_texture_id_ = texture_id_;
}

//------------------------------------------------
// dtor
//------------------------------------------------
Cursor::~Cursor() {
}

//------------------------------------------------
// Update
//------------------------------------------------
void Cursor::Update(void) {
  if (is_pushed_) {
    texture_id_ = pushed_texture_id_;
  }
  else {
    texture_id_ = standard_texture_id_;
  }
  is_pushed_ = false;
}
