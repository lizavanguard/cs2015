//==============================================================================
//
// Object Base
// Author : Shimizu Shoji
//
//==============================================================================
#pragma once
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// class definition
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
class ObjectBase {
public:
  // ctor
  ObjectBase();

  // dtor
  virtual ~ObjectBase();

  // Draw
  // ������p��������_��
  void Draw(void);

  void SetTexture(const char* texture_name);

protected:
  // Draw�̓�������
  // ���������p�������
  virtual void _PreProcessOfDraw(void) = 0;
  virtual void _Draw(void) = 0;
  virtual void _PostProcessOfDraw(void) = 0;

  D3DXVECTOR3 pos_;
  float rot_;
  D3DXVECTOR2 size_;

  DWORD color_;
  D3DXVECTOR2 start_uv_;
  D3DXVECTOR2 end_uv_;
  int texture_id_;
  bool is_alive_;

  LPDIRECT3DVERTEXBUFFER9 p_vertex_buffer_;
};
