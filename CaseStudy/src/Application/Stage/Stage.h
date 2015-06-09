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
  int up;
  int bottom;
  int right;
  int left;
  int up_right;
  int up_left;
  int bottom_right;
  int bottom_left;
}HIT_CHECK;
enum
{
  MAP_TYPE_NONE = 0,
  MAP_TYPE_NORMAL,
  MAP_TYPE_GOAL,
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


  bool IsAlive(void) const { return is_alive_; }

  // set
  void OnAlive(void) { is_alive_ = true; }
  void OffAlive(void) { is_alive_ = false; }

  D3DXVECTOR3 GetGoalMaptip();

  // Hit
  void CheckMapTip(D3DXVECTOR3* pos, D3DXVECTOR3 size, HIT_CHECK* check);

private:
  void HitManage(int id,HIT_CHECK* check);
  void CheckInit(HIT_CHECK* check);

  int* texture_id_;
  bool is_alive_;
  int map_width_;
  int map_height_;
  int map_id_max;
  STG_STR* stage_;


  LPDIRECT3DVERTEXBUFFER9 p_vertex_buffer_;
};


#endif // __H_OBJECT_H__
