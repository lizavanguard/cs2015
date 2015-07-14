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
             int cancel_key,
             const PositionContainer& position_list);

  // dtor
  ~GameCursor();

  // Update
  void Update(float elapsed_time);

  // Draw
  void Draw(void);

  // get
  int GetCursorIndex(void) const;
  int GetCursorIndexOld(void) const { return old_cursor_index_; }
  bool IsJustEntered(void) const { return is_just_entered_; }  // ñ{ìñÇÕÉäÉXÉiÅ[Çìoò^ÇµÇΩÇ¢ÇÊÇÀ
  bool IsJustCanceled(void) const { return is_just_canceled_; }
  bool IsJustMoved(void) const { return is_just_moved_; }

private:
  void _ReactInput(void);

  const int increment_key_;
  const int decrement_key_;
  const int enter_key_;
  const int cancel_key_;
  const PositionContainer position_list_;

  Cursor* p_cursor_;
  WrapValue* p_cursor_value_;

  int old_cursor_index_;
  bool is_just_entered_;
  bool is_just_canceled_;
  bool is_just_moved_;
};
