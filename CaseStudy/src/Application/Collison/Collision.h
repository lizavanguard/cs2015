//==============================================================================
//
// Collision
// Author: Shimizu Shoji
//
//==============================================================================
#pragma once
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// class declaration
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
class Player;
class Uriel;

//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// class definition
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
class Collision {
public:
  // ctor
  Collision(Player& player, Uriel& uriel);

  // dtor
  ~Collision();

  // Uriel x Player (Boro)
  void CollideUrielToPlayersBoro(void);

private:
  Player& player_;
  Uriel& uriel_;
};
