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
#include "Application/Stage/Stage.h"

#include "Framework/Collision/CollisionHelper.h"
#include "Framework/Input/InputManagerHolder.h"
#include "Framework/Input/InputKeyboard.h"
#include "Framework/Sound/Sound.h"
#include "Framework/DrawDebugPrimitive/DrawPrimitive.h"

//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
// const
//--=----=----=----=----=----=----=----=----=----=----=----=----=----=----=----=
namespace {

const float kEatRange = 5.0f;
const float kBoroRange = 16.5f;
const float kGimmickRange = 16.5f;

}

//==============================================================================
// class implementation
//==============================================================================
//------------------------------------------------
// ctor
//------------------------------------------------
Collision::Collision(Player& player, Uriel& uriel, Stage& stage)
    : player_(player)
	, uriel_(uriel)
	, stage_(stage) {
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
  // HACK
  const D3DXVECTOR3& uriel_pos = uriel_.GetEatPos();
  const D3DXVECTOR3& player_pos = player_.GetBoroPos();

  DrawCircle3D(uriel_pos, kEatRange * 4, 0xffff0000);
  DrawCircle3D(player_pos, kBoroRange * 4, 0xffff0000);

  // get players state
  if (!player_.IsBoroState()) {
    return;
  }

  // get uriels state
  if (!uriel_.CheckBoro()) {
    return;
  }

  const bool is_hit = IsSphereHit2(uriel_pos.x, uriel_pos.y, kEatRange,
                                   player_pos.x, player_pos.y, kBoroRange);

  if (is_hit) {
    if (!uriel_.BoroChage()) {
      return;
    }
    player_.FinishBoroState();
    PlaySound(SOUND_LABEL_SE_EAT);
  }
}

//------------------------------------------------
// Stage x Player (Gimmick)
//------------------------------------------------
void Collision::CollideStageToPlayersGimmick(void)
{
  // HACK
  const D3DXVECTOR3& player_pos = player_.GetBoroPos();
  const D3DXVECTOR3& player_size = D3DXVECTOR3(kGimmickRange
                                             , kGimmickRange
                                             , 0.0f);
  int stage_id = -1;

  DrawCircle3D(player_pos, kGimmickRange * 4, 0xffff0000);

  stage_id = stage_.GimmickSelect(player_pos, player_size);
  // get players state
  if (player_.GetPlayerMode() != Player::MODE_GIMMICK) {
    return;
  }

  //stage_.GimmickChange(stage_id);
  //const bool is_hit = IsSphereHit2(uriel_pos.x, uriel_pos.y, kEatRange,
  //                                 player_pos.x, player_pos.y, kBoroRange);

  //if (is_hit) {
  //  if (!uriel_.BoroChage()) {
  //    return;
  //  }
  //  player_.FinishBoroState();
  //  PlaySound(SOUND_LABEL_SE_EAT);
  //}
}