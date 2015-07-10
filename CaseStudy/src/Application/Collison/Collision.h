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
class Stage;

//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// class definition
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
class Collision {
public:
  // ctor
  Collision(Player& player, Uriel& uriel, Stage& stage);

  // dtor
  ~Collision();

  // Uriel x Player (Boro)
  void CollideUrielToPlayersBoro(void);

  // Stage x Player (Gimmick)
  void CollideStageToPlayersGimmick(void);
private:
  Player& player_;
  Uriel& uriel_;
  Stage& stage_;
};
