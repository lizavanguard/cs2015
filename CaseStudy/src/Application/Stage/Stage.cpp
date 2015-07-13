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
#include "Framework/Input/InputKeyboard.h"
#include "Framework/Input/InputManagerHolder.h"
#include "Framework/Input/InputXInput.h"
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// define
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#define WIDTH_LENGTH  (50.0f)
#define HEIGHT_LENGTH  (50.0f)
#define GIMMICK_RANGE  (16.5f)
namespace {

const D3DXVECTOR2 kGimmickfirst = {
  0.0f, 0.0f
};

const D3DXVECTOR2 kGimmickexpa = {
  1.0f, 1.0f
};
const D3DXVECTOR2 kGimmickdefault = {
  WIDTH_LENGTH, HEIGHT_LENGTH
};
const D3DXVECTOR2 kGimmickover = {
  WIDTH_LENGTH + 10.0f, HEIGHT_LENGTH + 10.0f
};
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// prttype
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
int Max_id_(int width, int height);
bool AABBCheck(D3DXVECTOR3 a_point[4], D3DXVECTOR3 b_point[4]);
//==============================================================================
// class implementation
//==============================================================================
// ctor
Stage::Stage()
  : map_width_(0)
  , map_height_(0){
  auto p_device = DeviceHolder::Instance().GetDevice();

  int no = 1;				// 変数
  char *filename;			// 画像の名前
  filename = (char *)malloc(200);
  FILE* fp;
  sprintf_s(filename,200, "data/Texture/map%03d.png", no);
  while (1)
  {
    fopen_s(&fp,filename, "r");
    if (fp == NULL)
    {
      //ファイルはねえよ！
      break;
    }else
    {
      //ファイルはあるよ!次だ！次っ！
      no++;
      memset(filename, 0, 200);
      sprintf_s(filename,200, "data/Texture/map%03d.png", no);
      fclose(fp);
    }
  }
  texture_id_ = new int[no];
  for (int i = 1; i < no;i++)
  {
    memset(filename, 0, 200);
    sprintf_s(filename,200, "data/Texture/map%03d.png", i);
    texture_id_[i] = TextureManagerHolder::Instance().GetTextureManager().LoadTexture(filename);
  }
  tumiki_id_ = TextureManagerHolder::Instance().GetTextureManager().LoadTexture("data/Texture/tumiki000.png");
  SelectStage("data/map/test.mf");
}

// dtor
Stage::~Stage() {
  delete[] stage_;
  delete[] mapdata_;
  delete[] texture_id_;
}
//
// ステージ読み込み
//
void Stage::SelectStage(char* mapfile) {

  FILE* fp = nullptr;
  int id = 0;
  if (map_height_ > 0 || map_width_ > 0)
  {
    delete[] stage_;
    delete[] mapdata_;
  }
  // ファイル読み込み
  fopen_s(&fp,mapfile, "r");
  if (fp == nullptr)
  {
#ifdef _DEBUG
    MessageBox(nullptr, "存在しないマップファイルを読み込んでいます", "mapfile unfind ", MB_OK);
#endif
    exit(0);
  }
  // マップ縦、横、存在しているブロック数の読み込み
  fscanf_s(fp, "%d,%d,%d\n", &map_width_, &map_height_, &map_id_max);
  int map_id = 0;
  int max = 0;
  id = 0;
  stage_ = NULL;
  mapdata_ = new STG_DATA[map_width_ * map_height_];
  stage_ = new STG_STR[map_id_max];
  // マップデータの読み込み
  for (int height = 0; height < map_height_; height++)
  {
    for(int width = 0; width < map_width_; width++)
    {
      fscanf_s(fp, "%2d,", &map_id);
	  mapdata_[id].id_ = map_id;
	  mapdata_[id].array_id_ = -1;
      id++;
    }
    fscanf_s(fp, "\n");
  }
  fclose(fp);
  fp = nullptr;
  id = 0;
  int map_work = 0;
  map_id = 0;
  select_id_ = 0;
  // タイプ分けとかなんか
  for (int height = 0; height < map_height_; height++)
  {
    for(int width = 0; width < map_width_; width++)
    {
      if (mapdata_[map_work].id_ != 0)
      {
        stage_[id].pos_ = 
        D3DXVECTOR3(-(map_width_ * WIDTH_LENGTH) + WIDTH_LENGTH + WIDTH_LENGTH * 2 * width,
                    (map_height_ * HEIGHT_LENGTH) - ( HEIGHT_LENGTH + HEIGHT_LENGTH * 2 * height),
                    0.0f);
        stage_[id].size_ =
        D3DXVECTOR2(WIDTH_LENGTH,
                    HEIGHT_LENGTH);
        stage_[id].alive_ = true;
        stage_[id].texture_id_ = texture_id_[mapdata_[map_work].id_];
        stage_[id].stage_id_ = mapdata_[map_work].id_;

        stage_[id].color_ = D3DXCOLOR(1.f, 1.f, 1.f, 1.f);
        stage_[id].stage_data_id_ = map_id;
        mapdata_[map_work].array_id_ = id;
        id++;
      }
      map_work++;
      map_id++;
    }
  }

}
//
// draw
//
void Stage::Draw(void) {
  auto p_device = DeviceHolder::Instance().GetDevice();
  // turn lighting off
  p_device->SetRenderState(D3DRS_LIGHTING, FALSE);
  GimmickControll(select_id_);
  for (int id = 0; id < map_id_max; id++)
  {
    if (!stage_[id].alive_ || stage_[id].stage_id_ == MAP_TYPE_GOAL || stage_[id].stage_id_ == MAP_TYPE_START) continue;
    D3DXCOLOR color = 0xffffffff;
	if (id == select_id_) color = 0xffff0000;
    Vertex3D data[] ={
      {D3DXVECTOR3( -stage_[id].size_.x, +stage_[id].size_.y, 0.0f), color, D3DXVECTOR2(0.0f, 0.0f)},
      {D3DXVECTOR3( +stage_[id].size_.x, +stage_[id].size_.y, 0.0f), color, D3DXVECTOR2(1.0f, 0.0f)},
      {D3DXVECTOR3( -stage_[id].size_.x, -stage_[id].size_.y, 0.0f), color, D3DXVECTOR2(0.0f, 1.0f)},
      {D3DXVECTOR3( +stage_[id].size_.x, -stage_[id].size_.y, 0.0f), color, D3DXVECTOR2(1.0f, 1.0f)},
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
    D3DXVECTOR3(pos->x - size.x, pos->y - size.y, 0.0f),
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
    if (AABBCheck(point,map_point))
    {
      HitManage(stage_[id].stage_data_id_,check);
      return stage_[id].pos_;
    }// if
  }// for
  return D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}
//
//
//
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
  if (AABBCheck(point,map_point))
  {
      return map_pos;
  }
  return *pos;
}
//
//
//
void Stage::HitManage(int id, HIT_CHECK* check)
{
  check->center = mapdata_[id + map_width_].id_;
  check->center = check->center == MAP_TYPE_GIMMICK_OFF ? MAP_TYPE_NONE : check->center;
  check->center = check->center == MAP_TYPE_GIMMICK_ON ? MAP_TYPE_NORMAL : check->center;
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
    check->bottom = mapdata_[id].id_;
    check->bottom = check->bottom == MAP_TYPE_GIMMICK_OFF ? MAP_TYPE_NONE : check->bottom;
    check->bottom = check->bottom == MAP_TYPE_GIMMICK_ON ? MAP_TYPE_NORMAL : check->bottom;
  }
  // up
  if (up)
  {
    check->up = mapdata_[map_uriel_h].id_;
    check->up = check->up == MAP_TYPE_GIMMICK_OFF ? MAP_TYPE_NONE : check->up;
    check->up = check->up == MAP_TYPE_GIMMICK_ON ? MAP_TYPE_NORMAL : check->up;
  }
  // right
  if (right)
  {
    check->right = mapdata_[map_uriel_w + 1].id_;
    check->right = check->right == MAP_TYPE_GIMMICK_OFF ? MAP_TYPE_NONE : check->right;
    check->right = check->right == MAP_TYPE_GIMMICK_ON ? MAP_TYPE_NORMAL : check->right;
  }
  // left
  if (left)
  {
    check->left = mapdata_[map_uriel_w - 1].id_;
    check->left = check->left == MAP_TYPE_GIMMICK_OFF ? MAP_TYPE_NONE : check->left;
    check->left = check->left == MAP_TYPE_GIMMICK_ON ? MAP_TYPE_NORMAL : check->left;
  }
  // bottom_right
  if (bottom && right)
  {
    check->bottom_right = mapdata_[id + 1].id_;
    check->bottom_right = check->bottom_right == MAP_TYPE_GIMMICK_OFF ? MAP_TYPE_NONE : check->bottom_right;
    check->bottom_right = check->bottom_right == MAP_TYPE_GIMMICK_ON ? MAP_TYPE_NORMAL : check->bottom_right;
  }
  //
  if (bottom && left)
  {
    check->bottom_left = mapdata_[id - 1].id_;
    check->bottom_left = check->bottom_left == MAP_TYPE_GIMMICK_OFF ? MAP_TYPE_NONE : check->bottom_left;
    check->bottom_left = check->bottom_left == MAP_TYPE_GIMMICK_ON ? MAP_TYPE_NORMAL : check->bottom_left;
  }
  //
  if (up && right)
  {
    check->up_right = mapdata_[map_uriel_h + 1].id_;
    check->up_right = check->up_right == MAP_TYPE_GIMMICK_OFF ? MAP_TYPE_NONE : check->up_right;
    check->up_right = check->up_right == MAP_TYPE_GIMMICK_ON ? MAP_TYPE_NORMAL : check->up_right;
  }
  //
  if (up && left)
  {
    check->up_left = mapdata_[map_uriel_h - 1].id_;
    check->up_left = check->up_left == MAP_TYPE_GIMMICK_OFF ? MAP_TYPE_NONE : check->up_left;
    check->up_left = check->up_left == MAP_TYPE_GIMMICK_ON ? MAP_TYPE_NORMAL :check->up_left;
  }
}
//
//
//
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
// Gimmick
int Stage::GimmickSelect(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
  int w_id = -1;
  int h_id = -1;
  select_id_ = -1;
  size.x = GIMMICK_RANGE;
  size.y = GIMMICK_RANGE;
  size.z = 0.0f;
  w_id = (int)(pos.x + map_width_ * WIDTH_LENGTH) / 100;
  h_id = -(int)(pos.y - map_height_ * HEIGHT_LENGTH) / 100;
  int check_id = w_id + h_id * map_width_;
  bool gimmick_off = mapdata_[check_id].id_ != MAP_TYPE_GIMMICK_OFF;
  bool gimmick_on = mapdata_[check_id].id_ != MAP_TYPE_GIMMICK_ON;
  if (mapdata_[check_id].array_id_ == -1) return -1;
  if (gimmick_off && gimmick_on) return -1;

  // AABB判定のための4点抽出
  D3DXVECTOR3 point[4] =
  {
    D3DXVECTOR3(pos.x - size.x, pos.y - size.y, 0.0f),
    D3DXVECTOR3(pos.x + size.x, pos.y - size.y, 0.0f),
    D3DXVECTOR3(pos.x - size.x, pos.y + size.y, 0.0f),
    D3DXVECTOR3(pos.x + size.x, pos.y + size.y, 0.0f),
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
  if (AABBCheck(point,map_point))
  {
      select_id_ = mapdata_[check_id].array_id_;
      return select_id_;
  }
  return -1;
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
//
void Stage::GimmickControll(int id)
{
  if (id == -1) return;
  auto& pKeyboard = InputManagerHolder::Instance().GetInputManager().GetPrimaryKeyboard();
  auto& pJoypad = InputManagerHolder::Instance().GetInputManager().GetPrimaryDevice();
  bool sizeover = stage_[id].size_.x > kGimmickover.x;
  bool changegimmick = stage_[id].size_.x > kGimmickdefault.x;
  if (mapdata_[stage_[id].stage_data_id_].id_ == MAP_TYPE_GIMMICK_OFF)
  {
    if (pJoypad.IsTrigger(InputDevice::Pads::PAD_Y) || pKeyboard.IsTrigger(DIK_G))
    {
      stage_[id].size_ = kGimmickfirst;
      stage_[id].texture_id_ = tumiki_id_;
    }
    if (pJoypad.IsPress(InputDevice::Pads::PAD_Y) || pKeyboard.IsPress(DIK_G))
    {
      stage_[id].size_ += kGimmickexpa;
      if (sizeover)
      {
        stage_[id].size_  = kGimmickover;
      }
    }
    if (pJoypad.IsRelease(InputDevice::Pads::PAD_Y) || pKeyboard.IsRelease(DIK_G))
    {
      if (changegimmick)
      {
        stage_[id].stage_id_ = MAP_TYPE_GIMMICK_ON;
        mapdata_[stage_[id].stage_data_id_].id_ = MAP_TYPE_GIMMICK_ON;
        stage_[id].size_  = kGimmickdefault;
      }else{
        stage_[id].texture_id_ = texture_id_[MAP_TYPE_GIMMICK_OFF];
        stage_[id].stage_id_ = MAP_TYPE_GIMMICK_OFF;
        mapdata_[stage_[id].stage_data_id_].id_ = MAP_TYPE_GIMMICK_OFF;
        stage_[id].size_  = kGimmickdefault;
      }
    }
  }else
  if (mapdata_[stage_[id].stage_data_id_].id_ == MAP_TYPE_GIMMICK_ON)
  {
    if (pJoypad.IsRelease(InputDevice::Pads::PAD_Y) || pKeyboard.IsRelease(DIK_G))
    {
      stage_[id].texture_id_ = texture_id_[MAP_TYPE_GIMMICK_OFF];
      stage_[id].stage_id_ = MAP_TYPE_GIMMICK_OFF;
      mapdata_[stage_[id].stage_data_id_].id_ = MAP_TYPE_GIMMICK_OFF;
      stage_[id].size_  = kGimmickdefault;
    }
  }
}
// Max_id
int Max_id_(int width, int height)
{
  return 0;
}
bool AABBCheck(D3DXVECTOR3 a_point[4], D3DXVECTOR3 b_point[4])
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