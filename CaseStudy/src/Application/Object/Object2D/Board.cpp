//==============================================================================
//
// Board
// Author: Shimizu Shoji
//
//==============================================================================
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// include
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
#include "Board.h"

//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// const
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
namespace {

const char* kTextureFilename = "data/Texture/square.png";

const DWORD kBoardColor = 0xff000000;
}

//==============================================================================
// class implementation
//==============================================================================
//------------------------------------------------
// ctor
//------------------------------------------------
Board::Board(const D3DXVECTOR3& pos, const D3DXVECTOR2& size)
    : Object2D(pos, size, kTextureFilename) {
  color_ = kBoardColor;
}

//------------------------------------------------
// Drawの前後処理
//------------------------------------------------
void Board::_PreProcessOfDraw(void) {
}

void Board::_PostProcessOfDraw(void) {
}