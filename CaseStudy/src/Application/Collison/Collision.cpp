//==============================================================================
//
// Collision
// Author: Shimizu Shoji
//
//==============================================================================
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// include
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
#include "Collision.h"
#include "Application/Object/Uriel.h"
#include "Application/Object/player.h"

#include "Framework/Input/InputManagerHolder.h"
#include "Framework/Input/InputKeyboard.h"
#include "Framework/Collision/CollisionHelper.h"

//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// const
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
namespace {

const float kBoroChargeRange = 10.0f;

}

//==============================================================================
// class implementation
//==============================================================================
//------------------------------------------------
// ctor
//------------------------------------------------
Collision::Collision(Player& player, Uriel& uriel)
    : player_(player)
    , uriel_(uriel) {
}

//------------------------------------------------
// dtor
//------------------------------------------------
Collision::~Collision() {
}

//------------------------------------------------
// Uriel x Player (Boro)
//------------------------------------------------
void Collision::CollideUrielToPlayersBoro(void) {
  // get players state
  if (!player_.IsBoroState()) {
    return;
  }

  // get uriels state
  if (!uriel_.CanBoroCharge()) {
    return;
  }

  const D3DXVECTOR3& uriel_pos = uriel_.GetPos();
  const D3DXVECTOR3& player_pos = player_.GetPos();

  const bool is_hit = IsSphereHit2(uriel_pos.x, uriel_pos.y, kBoroChargeRange,
                                   player_pos.x, player_pos.y, kBoroChargeRange);

  if (is_hit) {
    player_.FinishBoroState();
    uriel_.BoroChage();
  }

  // get uriels position
  // get players position
  // collision uriel x player
}
