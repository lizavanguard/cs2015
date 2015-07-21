//==============================================================================
//
// 障害物管理クラス [NaviManager.cpp]
// Author : Tomoki Ohashi
//
//==============================================================================
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// include
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "NaviManager.h"
#include "Application/Object/Uriel.h"
#include "Application/Camera/camera.h"
#include "Application/Object/Object2D/Navigation.h"
#include "Framework/FrameworkOption.h"

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// define
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
namespace {
const D3DXVECTOR3 knaviup = {
  kWindowWidth / 2, 70.0f, 0.0f
};
const D3DXVECTOR3 knavibottom = {
  kWindowWidth / 2, kWindowHeight - 40.0f, 0.0f
};
const D3DXVECTOR3 knaviright = {
  kWindowWidth - 70.0f, kWindowHeight / 2, 0.0f
};
const D3DXVECTOR3 knavileft = {
  70.0f, kWindowHeight / 2, 0.0f
};
const float kurielsize = 25.0f;
}
bool AABBCheckNavi(D3DXVECTOR3 a_point[4], D3DXVECTOR3 b_point[4]);
//==============================================================================
// class implementation
//==============================================================================
// ctor
NaviManager::NaviManager(Camera& camera, Uriel& uriel)
: uriel_(uriel)
, camera_(camera){

  p_navigation_[NAVI_UP]	= new NaviGation(knaviup, 10.0f, D3DXVECTOR2(100.0f, 100.0f),NAVI_UP);
  p_navigation_[NAVI_BOTTOM] = new NaviGation(knavibottom, 10.0f, D3DXVECTOR2(100.0f, 100.0f), NAVI_BOTTOM);
  p_navigation_[NAVI_RIGHT] = new NaviGation(knaviright, 10.0f, D3DXVECTOR2(100.0f, 100.0f), NAVI_RIGHT);
  p_navigation_[NAVI_LEFT] = new NaviGation(knavileft, 10.0f, D3DXVECTOR2(100.0f, 100.0f), NAVI_LEFT);
  dir_init();
}

// dtor
NaviManager::~NaviManager() {
  delete p_navigation_[NAVI_UP];
  delete p_navigation_[NAVI_BOTTOM];
  delete p_navigation_[NAVI_RIGHT];
  delete p_navigation_[NAVI_LEFT];
}

// update
void NaviManager::Update(void){
  dir_init();
  dir_update();
  // AABB判定のための4点抽出
  D3DXVECTOR3 camera_pos = camera_.GetPosP();
  D3DXVECTOR3 uriel_pos = uriel_.GetPos();
  D3DXVECTOR3 camera_point[4] =
  {
    D3DXVECTOR3(camera_pos.x - kWindowWidth / 4.0f, camera_pos.y - kWindowHeight / 4.0f, 0.0f),
    D3DXVECTOR3(camera_pos.x + kWindowWidth / 4.0f, camera_pos.y - kWindowHeight / 4.0f, 0.0f),
    D3DXVECTOR3(camera_pos.x - kWindowWidth / 4.0f, camera_pos.y + kWindowHeight / 4.0f, 0.0f),
    D3DXVECTOR3(camera_pos.x + kWindowWidth / 4.0f, camera_pos.y + kWindowHeight / 4.0f, 0.0f),
  };
  D3DXVECTOR3 uriel_point[4] =
  {
    D3DXVECTOR3(uriel_pos.x - kurielsize, uriel_pos.y - kurielsize, 0.0f),
    D3DXVECTOR3(uriel_pos.x + kurielsize, uriel_pos.y - kurielsize, 0.0f),
    D3DXVECTOR3(uriel_pos.x - kurielsize, uriel_pos.y + kurielsize, 0.0f),
    D3DXVECTOR3(uriel_pos.x + kurielsize, uriel_pos.y + kurielsize, 0.0f),
  };
  if (!AABBCheckNavi(uriel_point, camera_point))
  {
    if (!(uriel_point[1].x >= camera_point[0].x && uriel_point[0].x <= camera_point[1].x))
    {
      if (uriel_pos.x > camera_pos.x)b_dir[NAVI_RIGHT] = true;
      if (uriel_pos.x < camera_pos.x)b_dir[NAVI_LEFT] = true;
    }// if
    if (!(uriel_point[3].y >= camera_point[0].y && uriel_point[0].y <= camera_point[3].y))
    {
      if (uriel_pos.y > camera_pos.y)b_dir[NAVI_UP] = true;
      if (uriel_pos.y < camera_pos.y)b_dir[NAVI_BOTTOM] = true;
    } // if
  }
}

// draw
void NaviManager::Draw(void){
  if (b_dir[NAVI_UP])p_navigation_[NAVI_UP]->Draw();
  if (b_dir[NAVI_BOTTOM])p_navigation_[NAVI_BOTTOM]->Draw();
  if (b_dir[NAVI_RIGHT])p_navigation_[NAVI_RIGHT]->Draw();
  if (b_dir[NAVI_LEFT])p_navigation_[NAVI_LEFT]->Draw();
}
bool AABBCheckNavi(D3DXVECTOR3 a_point[4], D3DXVECTOR3 b_point[4])
{
  if (a_point[1].x >= b_point[0].x && a_point[0].x <= b_point[1].x)
  {
    if (a_point[3].y >= b_point[0].y && a_point[0].y <= b_point[3].y)
    {
      return true;
    } // if
  }// if
  if (a_point[3].x >= b_point[2].x && a_point[3].x <= b_point[2].x)
  {
    if (a_point[2].y >= b_point[1].y && a_point[2].y <= b_point[1].y)
    {
      return true;
    }// if
  }// if
  return false;
}
void NaviManager::dir_init()
{
  for (int i = 0; i < NAVI_MAX; i++)
  {
    b_dir[i] = false;
  }
}
void NaviManager::dir_update()
{
  for (int i = 0; i < NAVI_MAX; i++)
  {
    p_navigation_[i]->Update();
  }
}
// EOF