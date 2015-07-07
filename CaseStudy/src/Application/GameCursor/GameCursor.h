//==============================================================================
//
// GameCursor
// Author: Shimizu Shoji
//
//==============================================================================
#pragma once
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// include
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
#include <vector>

//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// class declaration
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
class Cursor;
class WrapValue;

//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// class definition
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
class GameCursor {
public:
  // alias
  typedef std::vector<D3DXVECTOR3> PositionContainer;

  // ctor
  GameCursor(const D3DXVECTOR2& size,
             int increment_key,
             int decrement_key,
             int enter_key,
             const PositionContainer& position_list);

  // dtor
  ~GameCursor();

  // Update
  bool Update(float elapsed_time);

  // Draw
  void Draw(void);

  // get
  int GetCursorIndex(void) const;

private:
  bool _ReactInput(void) const;

  Cursor* p_cursor_;
  WrapValue* p_cursor_value_;

  int increment_key_;
  int decrement_key_;
  int enter_key_;
  PositionContainer position_list_;
};
