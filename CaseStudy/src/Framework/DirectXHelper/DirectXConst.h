//==============================================================================
//
// DirectXƒwƒbƒ_ [DirectXConst.h]
// Author : Shimizu Shoji
//
//==============================================================================
#pragma once
#ifndef __H_DIRECTXCONST_H__
#define __H_DIRECTXCONST_H__
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// const
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
const DWORD kVertexFVF2D = D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1;
const DWORD kVertexFVF3D = D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1;


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// struct
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
struct Vertex2D {
  D3DXVECTOR3 vtx;
  float rhw;
  DWORD diffuse;
  D3DXVECTOR2 tex;
};

struct Vertex3D {
  D3DXVECTOR3 vtx;
  DWORD diffuse;
  D3DXVECTOR2 tex;
};

#endif  // __H_DIRECTXCONST_H__
