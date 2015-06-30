//==============================================================================
//
// �v���~�e�B�u�Ȍ`��̕`��֐� [DrawPrimitive.h]
// Designed On 2014.02.12 By Shimizu Shoji
//
//==============================================================================
#ifndef __H_DRAWPRIMITIVE_H__
#define __H_DRAWPRIMITIVE_H__
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// �C���N���[�h
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "d3dx9.h"


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// �v���g�^�C�v�錾
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// HACK:
HRESULT InitDrawPrimitive( LPDIRECT3DDEVICE9 pDevice );
void UninitDrawPrimitive( void );


//------------------------------------------------
// �_�̕`��
//------------------------------------------------
void DrawPoint( int x, int y, D3DCOLOR color = 0xffffffff );
void DrawPoint( float x, float y, D3DCOLOR color = 0xffffffff );


//------------------------------------------------
// ���̕`��
//------------------------------------------------
void DrawLine( float ax, float ay, float bx, float by, D3DCOLOR a_color = 0xffffffff, D3DCOLOR b_color = 0xffffffff );
// �����`��
void DrawLine2( float ax, float ay, float bx, float by, D3DCOLOR a_color = 0xffffffff, D3DCOLOR b_color = 0xffffffff );


//------------------------------------------------
// �~�̕`��
//------------------------------------------------
void DrawCircle( float cx, float cy, float r, D3DCOLOR color = 0xffffffff, bool is_fill = false );
// �����`��
// ���a���w�肵�Ă�
void DrawCircle2( float cx, float cy, float diameter, D3DCOLOR color = 0xffffffff, bool is_fill = false );
//void DrawCircle3( float cx, float cy, float diameter, D3DCOLOR color = 0xffffffff, bool is_fill = false );

void DrawCircle3D(const D3DXVECTOR3& position, float diameter, D3DCOLOR color = 0xffffffff, bool is_fill = false);


//------------------------------------------------
// ��`�̕`��
//------------------------------------------------
void DrawRect( float ax, float ay, float bx, float by, D3DCOLOR color = 0xffffffff , bool is_fill = false );


//------------------------------------------------
// �����̂̕`��
//------------------------------------------------
void DrawCube( float cx, float cy, float cz, float width, float height, float depth, D3DCOLOR color );
// HACK:
void DrawCube( float cx, float cy, float cz, float width, float height, float depth, D3DCOLOR color, const D3DXMATRIX& mtx );

void SetMatrixViewProjectionViewport(const D3DXMATRIX& view_projection_viewport);

void DrawAll( void );
#endif // __H_DRAWPRIMITIVE_H__
