//==============================================================================
//
// UrielCursorUI
// Author: Shimizu Shoji
//
//==============================================================================
#pragma once
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// class declaration
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
class Camera;
class Direction2D;
// class UrielCursor;
class Player;
class Uriel;

//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// class definition
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
class UrielCursorUI {
public:
  // ctor
  UrielCursorUI(const Camera& camera, const Player& player, const Uriel& uriel);

  // dtor
  ~UrielCursorUI();

  // Update
  void Update(void);

  // Draw
  void Draw(void);

private:
  Direction2D* p_direction2d_;
  //UrielCursor* p_cursor_;
  const Camera& camera_;
  const Player& player_;
  const Uriel& uriel_;
};
