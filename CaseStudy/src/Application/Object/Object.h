//==============================================================================
//
// オブジェクト [Object.h]
// Author : Shimizu Shoji
//
//==============================================================================
#pragma once
#ifndef __H_OBJECT_H__
#define __H_OBJECT_H__
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// class definition
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
class Object {
public:
  // ctor
  Object();

  // dtor
  virtual ~Object();

  // draw
  void Draw(void);

  // add pos
  void AddPos(const D3DXVECTOR3& pos) { pos_ += pos; }
  void AddPosX(float x) { pos_.x += x; }
  void AddPosY(float y) { pos_.y += y; }
  void AddPosZ(float z) { pos_.z += z; }

  // add rot
  void AddRot(const D3DXVECTOR2& rot) { rot_ += rot; }

  // add size
  void AddSize(const D3DXVECTOR2& size) { size_ += size; }

  // get
  D3DXVECTOR3 GetPos(void) const { return pos_; }
  D3DXVECTOR2 GetRot(void) const { return rot_; }
  D3DXVECTOR2 GetSize(void) const { return size_; }
  bool IsAlive(void) const { return is_alive_; }

  // set
  void SetPos(const D3DXVECTOR3& pos) { pos_ = pos; }
  void SetRot(const D3DXVECTOR2& rot) { rot_ = rot; }
  void SetSize(const D3DXVECTOR2& size) { size_ = size; }
  void SetTextureID(int texture_id) { texture_id_ = texture_id; }
  void OnAlive(void) { is_alive_ = true; }
  void OffAlive(void) { is_alive_ = false; }
  void SetTexture(char* texture_name);

protected:
  D3DXVECTOR3 pos_;
  D3DXVECTOR2 rot_;
  D3DXVECTOR2 size_;
  int texture_id_;
  bool is_alive_;

  LPDIRECT3DVERTEXBUFFER9 p_vertex_buffer_;
};


#endif // __H_OBJECT_H__
