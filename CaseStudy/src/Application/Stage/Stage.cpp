//==============================================================================
//
// オブジェクト [Stage.cpp]
// Author : Ohashi Tomoki
//
// とりあえず配列でマップ情報を保持
//
//==============================================================================
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// include
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "Stage.h"
#include "Framework/DirectXHelper/DeviceHolder.h"
#include "Framework/DirectXHelper/DirectXConst.h"
#include "Framework/GameWindow/GameDirectX.h"
#include "Framework/Texture/TextureManagerHolder.h"
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// define
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#define WIDTH_LENGTH	(50.0f)
#define HEIGHT_LENGTH	(50.0f)
const int mapdata[] = 
{
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
};
enum
{
  MAP_TYPE_NONE = 0,
  MAP_TYPE_NORMAL,
  MAP_TYPE_GOAL,
};
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// prttype
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
int Max_id_(int width,int height);
//==============================================================================
// class implementation
//==============================================================================
// ctor
Stage::Stage()
  : map_width_(0)
  , map_height_(0)
  , is_alive_(true) {
  auto p_device = DeviceHolder::Instance().GetDevice();

  // HACK:
  p_device->CreateVertexBuffer(
    sizeof(Vertex2D) * 4,
    D3DUSAGE_WRITEONLY,
    kVertexFVF2D,
    D3DPOOL_MANAGED,
    &p_vertex_buffer_,
	nullptr);
  texture_id_ = new int[2];
  texture_id_[0] = TextureManagerHolder::Instance().GetTextureManager().LoadTexture("data/Texture/block00.png");
  texture_id_[1] = TextureManagerHolder::Instance().GetTextureManager().LoadTexture("data/Texture/map001.jpg");
  map_width_ = 13;
  map_height_ = 8;
  map_id_max = 0;
  for (int check = 0; check < map_height_ * map_width_; check++)
  {
    if(mapdata[check] != 0)
    {
      map_id_max ++;
    }
  }
  stage_ = new STG_STR[map_id_max];
  int id = 0;
  int map_work = 0;
  for (int height = 0; height < map_height_; height++)
  {
    for(int width = 0; width < map_width_; width++)
    {
      if(mapdata[map_work] != 0)
      {
        stage_[id].pos_ = 
        D3DXVECTOR3(WIDTH_LENGTH + WIDTH_LENGTH * 2 * width,
                    HEIGHT_LENGTH + HEIGHT_LENGTH * 2 * height,
                    0.0f);

        stage_[id].size_ =
        D3DXVECTOR2(WIDTH_LENGTH,
                    HEIGHT_LENGTH);
        stage_[id].alive_ = true;
        switch (mapdata[map_work])
        {
          case MAP_TYPE_NORMAL:
          stage_[id].texture_id_ = texture_id_[MAP_TYPE_NORMAL - 1];
          stage_[id].stage_id_ = MAP_TYPE_NORMAL;
          break;
          case MAP_TYPE_GOAL:
          stage_[id].texture_id_ = texture_id_[MAP_TYPE_GOAL - 1];
          stage_[id].stage_id_ = MAP_TYPE_GOAL;
          break;
        }
        id++;
      }
    map_work++;
    }
  }
  delete[] texture_id_;
}

// dtor
Stage::~Stage() {
  p_vertex_buffer_->Release();
  delete[] stage_;
}

// draw
void Stage::Draw(void) {
  auto p_device = DeviceHolder::Instance().GetDevice();

  static const float kSize = 40.0f;

  for (int id = 0; id < map_id_max; id++)
  {
    if (!stage_[id].alive_ || stage_[id].stage_id_ == MAP_TYPE_GOAL) continue;
    Vertex2D data[] ={
      {D3DXVECTOR3(stage_[id].pos_.x - stage_[id].size_.x, stage_[id].pos_.y - stage_[id].size_.y, 0.0f), 1.0f, 0xffffffff, D3DXVECTOR2(0.0f, 0.0f)},
      {D3DXVECTOR3(stage_[id].pos_.x + stage_[id].size_.x, stage_[id].pos_.y - stage_[id].size_.y, 0.0f), 1.0f, 0xffffffff, D3DXVECTOR2(1.0f, 0.0f)},
      {D3DXVECTOR3(stage_[id].pos_.x - stage_[id].size_.x, stage_[id].pos_.y + stage_[id].size_.y, 0.0f), 1.0f, 0xffffffff, D3DXVECTOR2(0.0f, 1.0f)},
      {D3DXVECTOR3(stage_[id].pos_.x + stage_[id].size_.x, stage_[id].pos_.y + stage_[id].size_.y, 0.0f), 1.0f, 0xffffffff, D3DXVECTOR2(1.0f, 1.0f)},
    };

    //p_device->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
    TextureManagerHolder::Instance().GetTextureManager().SetTexture(stage_[id].texture_id_);

    p_device->SetFVF(kVertexFVF2D);

    p_device->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, data, sizeof(Vertex2D));
  }
}

void Stage::CheckMapTip(D3DXVECTOR3* pos, D3DXVECTOR3 size)
{
  // AABB判定のための4点抽出
  D3DXVECTOR3 point[4] = 
  {
    D3DXVECTOR3(pos->x - size.x, pos->y - size.y,0.0f),
    D3DXVECTOR3(pos->x + size.x, pos->y - size.y, 0.0f),
    D3DXVECTOR3(pos->x - size.x, pos->y + size.y, 0.0f),
    D3DXVECTOR3(pos->x + size.x, pos->y + size.y, 0.0f),
  };
  for (int id = 0; id < map_id_max; id++)
  {
    if (!stage_[id].alive_) continue;
    D3DXVECTOR3 map_point[4] = 
    {
      D3DXVECTOR3(stage_[id].pos_.x - stage_[id].size_.x, stage_[id].pos_.y - stage_[id].size_.y, 0.0f),
      D3DXVECTOR3(stage_[id].pos_.x + stage_[id].size_.x, stage_[id].pos_.y - stage_[id].size_.y, 0.0f),
      D3DXVECTOR3(stage_[id].pos_.x - stage_[id].size_.x, stage_[id].pos_.y + stage_[id].size_.y, 0.0f),
      D3DXVECTOR3(stage_[id].pos_.x + stage_[id].size_.x, stage_[id].pos_.y + stage_[id].size_.y, 0.0f),
    };
    if (point[1].x >= map_point[0].x && point[0].x <= map_point[1].x)
    {
      if (point[3].y >= map_point[0].y && point[0].y <= map_point[3].y)
      {
        HitManage(stage_[id].stage_id_,pos,size,stage_[id].pos_,stage_[id].size_);
      } // if
    }// if
    if (point[3].x >= map_point[2].x && point[3].x <= map_point[2].x)
    {
      if (point[2].y >= map_point[1].y && point[2].y <= map_point[1].y)
      {
        HitManage(stage_[id].stage_id_,pos,size,stage_[id].pos_,stage_[id].size_);
      }// if
    }// if
  }// for
}
void Stage::HitManage(int type
,D3DXVECTOR3* pos
,D3DXVECTOR3  size
,D3DXVECTOR3 mappos
,D3DXVECTOR2 mapsize)
{
  switch (type)
  {
  case MAP_TYPE_NORMAL:
    if(pos->y + size.y < mappos.y + mapsize.y)
    {
      pos->y = mappos.y - mapsize.y * 1.8f;
    }
    break;
  case MAP_TYPE_GOAL:
    // ゴールの処理入れてね♪
    break;
  }
}
D3DXVECTOR3 Stage::GetGoalMaptip()
{
  for (int id = 0; id < map_id_max; id++)
  {
    if(stage_[id].stage_id_ == MAP_TYPE_GOAL)
    {
      return stage_[id].pos_;
    }
  }// for
  return D3DXVECTOR3(0.0f,0.0f,0.0f);
}
// Max_id
int Max_id_(int width, int height)
{
  return 0;
}