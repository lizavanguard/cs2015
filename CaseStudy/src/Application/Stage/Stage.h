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
  int texture_id_;
  D3DXVECTOR3 pos_;
//  D3DXVECTOR2 rot_;
  D3DXVECTOR2 size_;
  bool alive_;
}STG_STR;

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
  void CheckMapTip(D3DXVECTOR3* pos,D3DXVECTOR3 size);

private:
  void HitManage(int type
,D3DXVECTOR3* pos
,D3DXVECTOR3  size
,D3DXVECTOR3 mappos
,D3DXVECTOR2 mapsize);
  int* texture_id_;
  bool is_alive_;
  int map_width_;
  int map_height_;
  int map_id_max;
  STG_STR* stage_;


  LPDIRECT3DVERTEXBUFFER9 p_vertex_buffer_;
};


#endif // __H_OBJECT_H__
