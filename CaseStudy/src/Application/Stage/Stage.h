//==============================================================================
//
// オブジェクト [Stage.h]
// Author : Shimizu Shoji
//
//==============================================================================
#pragma once
#ifndef __H_STAGE_H__
#define __H_STAGE_H__


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// struct definition
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
typedef struct STAGE_STR
{
  int stage_id_;
  int stage_data_id_;
  int texture_id_;
  bool alive_;
  D3DXVECTOR3 pos_;
  D3DXVECTOR2 size_;
}STG_STR;

typedef struct HIT_CHECK_
{
  char center;
  char up;
  char bottom;
  char right;
  char left;
  char up_right;
  char up_left;
  char bottom_right;
  char bottom_left;
}HIT_CHECK;
enum
{
  MAP_TYPE_NONE = 0,
  MAP_TYPE_NORMAL,
  MAP_TYPE_GOAL,
  MAP_TYPE_START,
  MAP_TYPE_WALL,
};
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// class definition
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
class Stage {
public:
  // ctor
  Stage();

  // dtor
  virtual ~Stage();

  // draw
  void Draw(void);


  D3DXVECTOR3 GetGoalMaptip();

  // スタート座標の取得(by Momoi)
  D3DXVECTOR3 GetStartMaptip();

  // Hit
  D3DXVECTOR3 CheckMapTip(D3DXVECTOR3* pos, D3DXVECTOR3 size, HIT_CHECK* check);

private:
  void HitManage(int id,HIT_CHECK* check);
  void CheckInit(HIT_CHECK* check);

  int* texture_id_;
  int map_width_;
  int map_height_;
  int map_id_max;
  STG_STR* stage_;


  LPDIRECT3DVERTEXBUFFER9 p_vertex_buffer_;
};


#endif // __H_OBJECT_H__
