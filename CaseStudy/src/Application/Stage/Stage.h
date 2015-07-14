//==============================================================================
//
// オブジェクト [Stage.h]
// Author : Ohashi Tomoki
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
  D3DXCOLOR color_;
}STG_STR;

typedef struct STAGE_DATA
{
	int id_;
	int array_id_;
}STG_DATA;

typedef struct HIT_CHECK_
{
  int center;
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
  MAP_TYPE_START,
  MAP_TYPE_WALL,
  MAP_TYPE_GIMMICK_OFF,
  MAP_TYPE_SANG_BUTTEFRY,
  MAP_TYPE_SANG_FLOWER,
  MAP_TYPE_GIMMICK_ON = 99,
};
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// class declaration
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
class Player;

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// class definition
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
class Stage {
public:
  // ctor
  Stage();
  //----------------------------------------------------------------------------
  // ステージセレクト
  // 引数:char* マップデータを入れてください
  // 存在しない場合勝手に終了()
  //----------------------------------------------------------------------------
  void SelectStage(char*);

  // dtor
  virtual ~Stage();

  // draw
  void Draw(void);

  D3DXVECTOR3 GetGoalMaptip();

  // スタート座標の取得(by Momoi)
  D3DXVECTOR3 GetStartMaptip();

  // Hit
  D3DXVECTOR3 CheckMapTip(D3DXVECTOR3* pos, D3DXVECTOR3 size, HIT_CHECK* check);

  // Hit
  D3DXVECTOR3 CheckMapTip2(D3DXVECTOR3* pos, D3DXVECTOR3 size, HIT_CHECK* check);

  // ステージサイズの取得(by rockman)
  D3DXVECTOR2 GetStageSize(void){return D3DXVECTOR2(map_width_*100.0f, map_height_*100.0f); }

  int GimmickSelect(D3DXVECTOR3 pos, D3DXVECTOR3 size);

  static bool GetGimmickCreate(){ return gimmick_create_; }
  static void SetGimmickCreate(bool tf){ gimmick_create_ = tf; }
private:
  void HitManage(int id,HIT_CHECK* check);
  void CheckInit(HIT_CHECK* check);
  void GimmickControll(int id);

  int* texture_id_;
  int tumiki_id_;
  int map_width_;
  int map_height_;
  int map_id_max;
  int select_id_;
  int select_prev_id;
  STG_STR* stage_;
  STG_DATA* mapdata_;
  LPDIRECT3DVERTEXBUFFER9 p_vertex_buffer_;
  static bool gimmick_create_;
};


#endif // __H_OBJECT_H__
