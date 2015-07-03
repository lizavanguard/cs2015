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
#define WIDTH_LENGTH  (50.0f)
#define HEIGHT_LENGTH  (50.0f)
//const int mapdata[] = 
//{
//  4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4,
//  4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4,
//  4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4,
//  4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4,
//  4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4,
//  4, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4,
//  4, 1, 1, 0, 0, 1, 1, 0, 0, 0, 1, 1, 4,
//  4, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 4,
//};
const int mapdata[] = 
{
  4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 4,
  4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 4,
  4, 4, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 4,
  4, 4, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 0, 0, 0, 0, 4, 4,
  4, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 4, 4,
  4, 4, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 4, 4,
  4, 4, 1, 1, 1, 0, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 4, 4,
  4, 4, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 4, 4,
  4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
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
  , map_height_(0){
  auto p_device = DeviceHolder::Instance().GetDevice();
  //-----------そのうちこちらへ移行-----------
  //int no = 1;            // すでにあった場合の変数
  //char *filename;          // 保存する画像の名前
  //filename = (char *)malloc(200);
  //sprintf(filename, "data/Texture/map%03d.png", no);
  //while (1)
  //{
  //  if (fopen(filename, "r") == NULL)
  //  {
  //    //ファイルはねえよ！
  //    break;
  //  }else
  //  {
  //    //ファイルはあるよ!次だ！次っ！
  //    no++;
  //    memset(filename, 0, 200);
  //    sprintf(filename, "data/Texture/map%03d.png", no);
  //  }
  //}
  //texture_id_ = new int[no];
  //for (int i = 0; i < no;i++)
  //{
  //  memset(filename, 0, 200);
  //  sprintf(filename, "data/Texture/map%03d.png", i);
  //  texture_id_[i] = TextureManagerHolder::Instance().GetTextureManager().LoadTexture(filename);
  //}
  //-----------そのうちこちらへ移行-----------

//------------------------------------------------------------------------------ 使うのは今のみ
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
  //map_width_ = 13;
  map_width_ = 23;
  map_height_ = 9;
  map_id_max = 0;
  for (int check = 0; check < map_height_ * map_width_; check++)
  {
    if(mapdata[check] != 0)
    {
      map_id_max ++;
    }
  }
  stage_ = new STG_STR[map_id_max];
  m_mapdata = new int[map_height_ * map_width_];
  int id = 0;
  int map_work = 0;
  int map_id = 0;
  for (int height = 0; height < map_height_; height++)
  {
    for(int width = 0; width < map_width_; width++)
    {
      m_mapdata[map_id] = mapdata[map_id];
      if(mapdata[map_work] != 0)
      {
        stage_[id].pos_ = 
        D3DXVECTOR3(-(map_width_ * WIDTH_LENGTH) + WIDTH_LENGTH + WIDTH_LENGTH * 2 * width,
                    (map_height_ * HEIGHT_LENGTH) - ( HEIGHT_LENGTH + HEIGHT_LENGTH * 2 * height),
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
          case MAP_TYPE_START:
          stage_[id].texture_id_ = texture_id_[MAP_TYPE_START - 1];
          stage_[id].stage_id_ = MAP_TYPE_START;
          break;
          case MAP_TYPE_WALL:
          stage_[id].texture_id_ = texture_id_[MAP_TYPE_NORMAL - 1];
          stage_[id].stage_id_ = MAP_TYPE_WALL;
          break;
        }
        stage_[id].stage_data_id_ = map_id;
        id++;
      }
      map_work++;
      map_id++;
    }
  }
  delete[] texture_id_;
//------------------------------------------------------------------------------ 使うのは今のみ
}

// dtor
Stage::~Stage() {
  delete[] stage_;
  delete[] m_mapdata;
  p_vertex_buffer_->Release();
}

void Stage::SelectStage(char* mapfile) {

  //FILE* fp;
  //int id = 0;
  //if (map_height_ > 0 || map_width_ > 0)
  //{
  //  delete[] stage_;
  //  delete[] m_mapdata;
  //}
  //fp = fopen(mapfile, "rb");
  //fscanf(fp, "%d,%d\n", &map_width_, &map_height_);
  //int map_id;
  //id = 0;
  //map_id_max = 0;
  //m_mapdata = new int[map_height_ * map_height_];
  //for (int x = 0; x < map_width_; x++)
  //{
  //  for (int y = 0; y < map_height_; y++)
  //  {
  //    fscanf(fp, "%2d,", &map_id);
  //    m_mapdata[id] = map_id;
  //    id++;
  //    if(m_mapdata[id] != 0)
  //    {
  //      map_id_max ++;
  //    }
  //  }
  //fprintf(fp, "\n");
  //}
  //fclose(fp);
  //
  //stage_ = new STG_STR[map_id_max];
  //m_mapdata = new int[map_height_ * map_width_];
  //int id = 0;
  //int map_work = 0;
  //int map_id = 0;
  //for (int height = 0; height < map_height_; height++)
  //{
  //  for(int width = 0; width < map_width_; width++)
  //  {
  //    if(m_mapdata[map_work] != 0)
  //    {
  //      stage_[id].pos_ = 
  //      D3DXVECTOR3(-(map_width_ * WIDTH_LENGTH) + WIDTH_LENGTH + WIDTH_LENGTH * 2 * width,
  //                  (map_height_ * HEIGHT_LENGTH) - ( HEIGHT_LENGTH + HEIGHT_LENGTH * 2 * height),
  //                  0.0f);

  //      stage_[id].size_ =
  //      D3DXVECTOR2(WIDTH_LENGTH,
  //                  HEIGHT_LENGTH);
  //      stage_[id].alive_ = true;
  //      switch (mapdata[map_work])
  //      {
  //        case MAP_TYPE_NORMAL:
  //        stage_[id].texture_id_ = texture_id_[MAP_TYPE_NORMAL - 1];
  //        stage_[id].stage_id_ = MAP_TYPE_NORMAL;
  //        break;
  //        case MAP_TYPE_GOAL:
  //        stage_[id].texture_id_ = texture_id_[MAP_TYPE_GOAL - 1];
  //        stage_[id].stage_id_ = MAP_TYPE_GOAL;
  //        break;
  //        case MAP_TYPE_START:
  //        stage_[id].texture_id_ = texture_id_[MAP_TYPE_START - 1];
  //        stage_[id].stage_id_ = MAP_TYPE_START;
  //        break;
  //        case MAP_TYPE_WALL:
  //        stage_[id].texture_id_ = texture_id_[MAP_TYPE_NORMAL - 1];
  //        stage_[id].stage_id_ = MAP_TYPE_WALL;
  //        break;
  //      }
  //      stage_[id].stage_data_id_ = map_id;
  //      id++;
  //    }
  //    map_work++;
  //    map_id++;
  //  }
  //}
}
// draw
void Stage::Draw(void) {
  auto p_device = DeviceHolder::Instance().GetDevice();
  // turn lighting off
  p_device->SetRenderState(D3DRS_LIGHTING, FALSE);

  for (int id = 0; id < map_id_max; id++)
  {
    if (!stage_[id].alive_ || stage_[id].stage_id_ == MAP_TYPE_GOAL || stage_[id].stage_id_ == MAP_TYPE_START) continue;
    Vertex3D data[] ={
      {D3DXVECTOR3( -stage_[id].size_.x, +stage_[id].size_.y, 0.0f), 0xffffffff, D3DXVECTOR2(0.0f, 0.0f)},
      {D3DXVECTOR3( +stage_[id].size_.x, +stage_[id].size_.y, 0.0f), 0xffffffff, D3DXVECTOR2(1.0f, 0.0f)},
      {D3DXVECTOR3( -stage_[id].size_.x, -stage_[id].size_.y, 0.0f), 0xffffffff, D3DXVECTOR2(0.0f, 1.0f)},
      {D3DXVECTOR3( +stage_[id].size_.x, -stage_[id].size_.y, 0.0f), 0xffffffff, D3DXVECTOR2(1.0f, 1.0f)},
    };
    // WVP
    D3DXMATRIX mtx_world;
    D3DXMatrixTranslation(&mtx_world
                         , stage_[id].pos_.x
                         , stage_[id].pos_.y
                         , stage_[id].pos_.z);
    p_device->SetTransform(D3DTS_WORLD, &mtx_world);

    //p_device->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
    TextureManagerHolder::Instance().GetTextureManager().SetTexture(stage_[id].texture_id_);

    p_device->SetFVF(kVertexFVF3D);

    p_device->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, data, sizeof(Vertex3D));
  }
}

D3DXVECTOR3 Stage::CheckMapTip(D3DXVECTOR3* pos, D3DXVECTOR3 size, HIT_CHECK* check)
{
  CheckInit(check);
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
    if (!stage_[id].alive_/* || stage_[id].stage_id_ == MAP_TYPE_GOAL || stage_[id].stage_id_ == MAP_TYPE_START || stage_[id].stage_id_ == MAP_TYPE_WALL*/) continue;
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
        HitManage(stage_[id].stage_data_id_,check);
        return stage_[id].pos_;
      } // if
    }// if
    if (point[3].x >= map_point[2].x && point[3].x <= map_point[2].x)
    {
      if (point[2].y >= map_point[1].y && point[2].y <= map_point[1].y)
      {
        HitManage(stage_[id].stage_data_id_,check);
        return stage_[id].pos_;
      }// if
    }// if
  }// for
  return D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

D3DXVECTOR3 Stage::CheckMapTip2(D3DXVECTOR3* pos, D3DXVECTOR3 size, HIT_CHECK* check)
{
  CheckInit(check);
  int w_id = -1;
  int h_id = -1;
  w_id = (int)(pos->x + map_width_ * WIDTH_LENGTH) / 100;
  h_id = -(int)(pos->y - map_height_ * HEIGHT_LENGTH) / 100;
  int check_id = w_id + h_id * map_width_;
  HitManage(check_id, check);

  // AABB判定のための4点抽出
  D3DXVECTOR3 point[4] =
  {
    D3DXVECTOR3(pos->x - size.x, pos->y - size.y, 0.0f),
    D3DXVECTOR3(pos->x + size.x, pos->y - size.y, 0.0f),
    D3DXVECTOR3(pos->x - size.x, pos->y + size.y, 0.0f),
    D3DXVECTOR3(pos->x + size.x, pos->y + size.y, 0.0f),
  };
  D3DXVECTOR3 map_pos = 
  D3DXVECTOR3(-(map_width_ * WIDTH_LENGTH) + WIDTH_LENGTH + WIDTH_LENGTH * 2 * w_id,
             (map_height_ * HEIGHT_LENGTH) - ( HEIGHT_LENGTH + HEIGHT_LENGTH * 2 * h_id + 1),
                    0.0f);
  
  D3DXVECTOR3 map_point[4] =
  {
    D3DXVECTOR3(map_pos.x - WIDTH_LENGTH, map_pos.y - HEIGHT_LENGTH, 0.0f),
    D3DXVECTOR3(map_pos.x + WIDTH_LENGTH, map_pos.y - HEIGHT_LENGTH, 0.0f),
    D3DXVECTOR3(map_pos.x - WIDTH_LENGTH, map_pos.y + HEIGHT_LENGTH, 0.0f),
    D3DXVECTOR3(map_pos.x + WIDTH_LENGTH, map_pos.y + HEIGHT_LENGTH, 0.0f),
  };
  if (point[1].x >= map_point[0].x && point[0].x <= map_point[1].x)
  {
    if (point[3].y >= map_point[0].y && point[0].y <= map_point[3].y)
    {
      return map_pos;
    } // if
  }// if
  if (point[3].x >= map_point[2].x && point[3].x <= map_point[2].x)
  {
    if (point[2].y >= map_point[1].y && point[2].y <= map_point[1].y)
    {
      return map_pos;
    }// if
  }// if
  return *pos;
}

void Stage::HitManage(int id, HIT_CHECK* check)
{
  check->center = m_mapdata[id + map_width_];
  int data_id_ = map_width_ * map_height_;
  int map_uriel_h = id - map_width_ * 2;
  int map_uriel_w = id - map_width_;
  // マップチェック
  bool bottom  = id < data_id_;
  bool up = map_uriel_h > 0;
  bool right = map_uriel_w % (map_width_) + 1 != map_width_;
  bool left = map_uriel_w % (map_width_) - 1 != -1;
  // bottom
  if (bottom)
  {
    check->bottom = m_mapdata[id];
  }
  // up
  if (up)
  {
    check->up = m_mapdata[map_uriel_h];
  }
  // right
  if (right)
  {
    check->right = m_mapdata[map_uriel_w + 1];
  }
  // left
  if (left)
  {
    check->left = m_mapdata[map_uriel_w - 1];
  }
  // bottom_right
  if (bottom && right)
  {
    check->bottom_right = m_mapdata[id + 1];
  }
  //
  if (bottom && left)
  {
    check->bottom_left = m_mapdata[id - 1];
  }
  //
  if (up && right)
  {
    check->up_right = m_mapdata[map_uriel_h + 1];
  }
  //
  if (up && left)
  {
    check->up_left = m_mapdata[map_uriel_h - 1];
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

D3DXVECTOR3 Stage::GetStartMaptip()
{
  for (int id = 0; id < map_id_max; id++)
  {
    if (stage_[id].stage_id_ == MAP_TYPE_START)
    {
      return stage_[id].pos_;
    }
  }// for
  return D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}
//
void Stage::CheckInit(HIT_CHECK* check)
{
  check->center = -1;
  check->up = -1;
  check->bottom = -1;
  check->right = -1;
  check->left = -1;
  check->up_right = -1;
  check->up_left = -1;
  check->bottom_right = -1;
  check->bottom_left = -1;
}
// Max_id
int Max_id_(int width, int height)
{
  return 0;
}