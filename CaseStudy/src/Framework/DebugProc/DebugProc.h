//==============================================================================
//
// Print Debug String [DebugProc.h]
//
//==============================================================================
#ifndef __H_DEBUGPROC_H__
#define __H_DEBUGPROC_H__
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// include
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "d3dx9.h"
#include <sstream>


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// class definition
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
class DebugProc { 
public:
	// ctor/dtor
	DebugProc();
	~DebugProc();

	// method
	void Init( LPDIRECT3DDEVICE9 pDevice );
	void Uninit( void );
	static void Print( const char* fmt, ... );
	static void Draw( void );

	// get
	static bool IsEnableDisp( void );

	// set
	static void EnableDisp( bool isDisp );

private:
	// field
	static LPD3DXFONT sm_pD3DXFont;
	static std::ostringstream sm_oss;
	static bool sm_isDisp;
};




#endif // __H_DEBUGPROC_H__
