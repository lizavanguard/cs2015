//==============================================================================
//
// �v���~�e�B�u�Ȍ`��̕`��֐� [DrawPrimitive.h]
// Designed On 2014.02.12 By Shimizu Shoji
//
//==============================================================================
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// �C���N���[�h
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "DrawPrimitive.h"

#include <Windows.h>


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// �\����
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
namespace {

struct VERTEX_2D{
  D3DXVECTOR3 vtx;
  float rhw;
  DWORD diffuse;
  D3DXVECTOR2 tex;
};

const DWORD FVF_VERTEX_2D = D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1;

}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// �O���[�o���ϐ�
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// ���_�o�b�t�@
static LPDIRECT3DVERTEXBUFFER9 g_point_buffer;
static LPDIRECT3DVERTEXBUFFER9 g_line_buffer;
static D3DXVECTOR3 g_cube_pos[ 8 ];
static D3DXVECTOR4 g_cube_pos4[ 8 ];

static int g_cnt = 0;
static int g_line_cnt = 0;

static LPDIRECT3DDEVICE9 g_p_device = nullptr;
static D3DXMATRIX g_view_projection_viewport;

// ���_�錾
static LPDIRECT3DVERTEXDECLARATION9 g_vertex_declaration = NULL;


//==============================================================================
// �֐�������
//==============================================================================
//------------------------------------------------
// HACK: ������
//------------------------------------------------
HRESULT InitDrawPrimitive(LPDIRECT3DDEVICE9 p_device) {
  g_p_device = p_device;

	// �_�p�̃o�b�t�@�m��
	HRESULT hr = g_p_device->CreateVertexBuffer(
		sizeof( VERTEX_2D ) * 30000,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_point_buffer,
		NULL
	);
	if( FAILED( hr ) ) {
		return E_FAIL;
	}

	// ���_�錾�̎��ۂ̍\�����`����
	//#define FVF_VERTEX_2D ( D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1 )
	D3DVERTEXELEMENT9 vertex_element[] = {
		// �p�C�v���C���ԍ�, �I�t�Z�b�g(�o�C�g�P��), �f�N�����[�V�����^�C�v(�T�C�Y,�^), �s��, �p�r, �p�r�ԍ�(�����p�r�ł��ԍ��ŕ����邱�Ƃ��ł���)->���W2�Ƃ���
		// ���W�ϊ��ςݒ��_�Ȃ�^�C�v��FLOAT4, �p�r��POSITIONT
		// UV����Ȃ�^�C�v��FLOAT2, �p�r��TEXCOORD�ɂ���
		{ 0, 0, D3DDECLTYPE_FLOAT4,    D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITIONT, 0 },
		{ 0, 16, D3DDECLTYPE_D3DCOLOR, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_COLOR,    0 },
		{ 0, 20, D3DDECLTYPE_FLOAT2,   D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD,   0 },
		D3DDECL_END()
	};
	
	// ���_�錾���쐬
	g_p_device->CreateVertexDeclaration( vertex_element, &g_vertex_declaration );

  // ���p�̃o�b�t�@�m��
	hr = g_p_device->CreateVertexBuffer(
		sizeof( VERTEX_2D ) * 30000,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_line_buffer,
		NULL
	);
	if( FAILED( hr ) ) {
		return E_FAIL;
	}
	return S_OK;
}


//------------------------------------------------
// HACK:�I������
//------------------------------------------------
void UninitDrawPrimitive( void ) {
	//SafeRelease( g_point_buffer );
	//SafeRelease( g_line_buffer );
	if( g_point_buffer != NULL ) {
		g_point_buffer->Release();
		g_point_buffer = NULL;
	}
	if( g_line_buffer != NULL ) {
		g_line_buffer->Release();
		g_line_buffer = NULL;
	}
}


//------------------------------------------------
// �_�̕`��
//------------------------------------------------
void DrawPoint( const int x, const int y, const D3DCOLOR color ) {
	// ���_���̐ݒ�
	VERTEX_2D* vtx;

	// ��L�J�n
	g_point_buffer->Lock( 0, 0, ( void** )&vtx, 0 );

	vtx[ g_cnt ].vtx = D3DXVECTOR3( (float)x, (float)y, 0 );
	vtx[ g_cnt ].rhw = 1.0f;
	vtx[ g_cnt ].diffuse = color;
	vtx[ g_cnt ].tex = D3DXVECTOR2( 1.0f, 0.0f );

	// ��L�I��
	g_point_buffer->Unlock();

	// ���_���̓]��
	//LPDIRECT3DDEVICE9 g_p_device = GetDevice();
	//g_p_device->SetStreamSource( 0, g_point_buffer, 0, sizeof( VERTEX_2D ) );
	//g_p_device->SetFVF( FVF_VERTEX_2D );
	//g_p_device->SetTexture( 0, NULL );
	//g_p_device->DrawPrimitive( D3DPT_POINTLIST, 0, 1 );
	++g_cnt;
}


void DrawPoint( const float x, const float y, const D3DCOLOR color ) {
	// ���_���̐ݒ�
	VERTEX_2D* vtx;

	// ��L�J�n
	g_point_buffer->Lock( 0, 0, ( void** )&vtx, 0 );

	vtx[ g_cnt ].vtx = D3DXVECTOR3( x, y, 0 );
	vtx[ g_cnt ].rhw = 1.0f;
	vtx[ g_cnt ].diffuse = color;
	vtx[ g_cnt ].tex = D3DXVECTOR2( 1.0f, 0.0f );

	// ��L�I��
	g_point_buffer->Unlock();

	// ���_���̓]��
	//LPDIRECT3DDEVICE9 g_p_device = GetDevice();
	//g_p_device->SetStreamSource( 0, g_point_buffer, 0, sizeof( VERTEX_2D ) );
	//g_p_device->SetFVF( FVF_VERTEX_2D );
	//g_p_device->SetTexture( 0, NULL );
	//g_p_device->DrawPrimitive( D3DPT_POINTLIST, 0, 1 );
	++g_cnt;
}


//------------------------------------------------
// ���̕`��
//------------------------------------------------
void DrawLine(
	const float ax, const float ay,
	const float bx, const float by,
	const D3DCOLOR a_color, const D3DCOLOR b_color
) {
	// ���_���̐ݒ�
	VERTEX_2D* vtx;

	// ��L�J�n
	g_line_buffer->Lock( 0, 0, ( void** )&vtx, 0 );

	vtx[ g_line_cnt   ].vtx = D3DXVECTOR3( ax, ay, 0 );
	vtx[ g_line_cnt+1 ].vtx = D3DXVECTOR3( bx, by, 0 );

	vtx[ g_line_cnt   ].rhw = 1.0f;
	vtx[ g_line_cnt+1 ].rhw = 1.0f;

	vtx[ g_line_cnt   ].diffuse = a_color;
	vtx[ g_line_cnt+1 ].diffuse = b_color;

	vtx[ g_line_cnt   ].tex = D3DXVECTOR2( 1.0f, 0 );
	vtx[ g_line_cnt+1 ].tex = D3DXVECTOR2( 1.0f, 0 );

	// ��L�I��
	g_line_buffer->Unlock();
	
	// ���_���̓]��
	//LPDIRECT3DDEVICE9 g_p_device = GetDevice();
	//g_p_device->SetStreamSource( 0, g_line_buffer, 0, sizeof( VERTEX_2D ) );
	//g_p_device->SetFVF( FVF_VERTEX_2D );
	//g_p_device->SetTexture( 0, NULL );
	//g_p_device->DrawPrimitive( D3DPT_LINELIST, 0, 2 );
	g_line_cnt+=2;
}


//------------------------------------------------
// �~�̕`��
//------------------------------------------------
void DrawCircle( const float cx, const float cy, const float r, const D3DCOLOR color, bool is_fill ) {
	if( r == 0 ) {
		return;
	}

	// �~�������߂�
	float len = 2 * D3DX_PI * r / 4.f;
	// �_�̐������߂�
	int num_point = (int)( len + 0.5f );
	// ���̉�]�p�����߂�
	float unit_rot =  2 * D3DX_PI / len / 4.f;

	for( int point_cnt = 0; point_cnt < num_point; ++point_cnt ) {
		float rx = r * cosf( unit_rot * point_cnt );
		float ry = r * sinf( unit_rot * point_cnt );

		// ���ی�
		DrawPoint( cx + rx, cy + ry, color );
		// ���ی�
		DrawPoint( cx - rx, cy + ry, color );
		// ��O�ی�
		DrawPoint( cx - rx, cy - ry, color );
		// ��l�ی�
		DrawPoint( cx + rx, cy - ry, color );

		// if �h��Ԃ��Ȃ�
		if( is_fill ) {
			DrawLine( cx - rx, cy + ry, cx+ rx, cy +ry, color, color );
			DrawLine( cx - rx, cy - ry, cx + rx, cy - ry, color, color );
		}
	}
}


void DrawCircle2( const float _cx, const float _cy, float _diameter, const D3DCOLOR color, bool is_fill ) {
	POINT center = { (int)_cx, (int)_cy };
	int diameter = (int)_diameter;
	LONG cx = 0, cy= diameter/2+1;
	double d;
	d = -diameter*diameter + 4*cy*cy -4*cy +2;
	int dx, dy;
	dx = 4;
	dy = -8*cy+8;
	POINT mirror_center = center;
	if ((diameter&1) ==0){
		mirror_center.x++;
		mirror_center.y++;
	}

	for (cx=0; cx <= cy ; cx++){
		if (d>0) {
			d += dy;
			dy += 8;
			cy--;
		}
		DrawPoint (  cy + center.x,  cx + center.y, color);        // 0-45     �x�̊�
		DrawPoint (  cx + center.x,  cy + center.y, color);        // 45-90    �x�̊�
					  
		DrawPoint ( -cx + mirror_center.x,  cy + center.y, color); // 90-135   �x�̊�
		DrawPoint ( -cy + mirror_center.x,  cx + center.y, color); // 135-180  �x�̊�
					  
		DrawPoint ( -cy + mirror_center.x, -cx + mirror_center.y, color);  // 180-225  �x�̊�
		DrawPoint ( -cx + mirror_center.x, -cy + mirror_center.y, color);  // 225-270  �x�̊�
					  
		DrawPoint (  cx + center.x, -cy + mirror_center.y, color); // 270-315  �x�̊�
		DrawPoint (  cy + center.x, -cx + mirror_center.y, color); // 315-360  �x�̊�

		d += dx;
		dx+=8;
	}
}

// �����Ńj���[�g���@
int root_i(int x){
    int s=1, s2=1;
    do {
        s=(x/s+s)/2; 
        s2=s+1;
        if (s*s<=x && x<s2*s2) break;
    } while(1);
    return s;
}


void DrawCircle3( const float _cx, const float _cy, float _diameter, const D3DCOLOR color, bool is_fill ) {
	RECT _rc = { 0, 0, 1280, 720 };
	RECT* rc = &_rc;
	POINT center = { (int)_cx, (int)_cy };
	int diameter = (int)_diameter;
	long cx = 0, cy=diameter/2, *px, *py, tmp;
	long dx, dy, x_sign, y_sign, num_eigth, r_root2;
	double d;
	r_root2 = (diameter>3)? root_i(diameter*diameter/8) :1;
	tmp = r_root2*r_root2*8-diameter*diameter;
	if (abs(tmp)>abs(tmp+8*(2*r_root2+1))) r_root2++;   // r*��Q�̋ߎ��l

	d = -diameter*diameter + 4*cy*cy -4*cy +2;
	dx = 4;
	dy = -8*cy+8;
	POINT mirror_center = center, now_center, start_po[8], end_po[8];
	if ((diameter&1) ==0){
		mirror_center.x++;
		mirror_center.y++;
	}

	// �N���b�s���O
	//POINT *p_po1, *p_po2;
	for(num_eigth=0; num_eigth <8; num_eigth++){
		start_po[num_eigth].y=diameter/2;
		start_po[num_eigth].x=0;
		end_po[num_eigth].x=end_po[num_eigth].y=r_root2;
	}

	for(int li=0;li<4;li++){
		if (li==0) { cy = center.y-(rc->bottom-1);  y_sign=-1;  }
		if (li==1) { cy = mirror_center.x-rc->left; y_sign=1;       }
		if (li==2) { cy = mirror_center.y-rc->top;  y_sign=1;   }
		if (li==3) { cy = center.x-(rc->right-1);   y_sign=-1;  }

		if (abs(cy)>=(diameter/2)) {
			if (((li==0 || li==3) && cy<0) || ((li==1 || li==2) && cy>0)) continue; // �~�͔͈͓�
			else return ;   // �~�͊��S�ɔ͈͊O
		}

		tmp = diameter*diameter -4*cy*cy;
		cx = root_i(tmp/4); // n=tmp/4; if (tmp%4) n++;
		tmp -= 4*cx*cx;
		if (abs(tmp)>=abs(tmp -8*cx-4)) cx++;

		/*
			�_�Q|�P�^       [0] 0-45�x�̊�      [1] 45-90�x�̊�
			�R�_|�^�O       [2] 90-135�x�̊�    [3] 135-180�x�̊�
			------��------
			�S�^|�_�V       [4] 225-270�x�̊�   [5] 180-225�x�̊�
			�^�T|�U�_       [6] 270-315�x�̊�   [7] 315-360�x�̊�
		*/
		if (cy*y_sign>r_root2){
			// 1,2 �� 3,4 �� 5,6 �� 7,0
			if (start_po[li*2+1].x<abs(cx)) {
					start_po[li*2+1].y = abs(cy);
					start_po[li*2+1].x = abs(cx);
			}
			if (start_po[(li*2+2)%8].x<abs(cx)) {
					start_po[(li*2+2)%8].y = abs(cy);
					start_po[(li*2+2)%8].x = abs(cx);
			}
		}
		else {
			start_po[li*2+1].y = start_po[(li*2+2)%8].y = 0;        // �͈͊O�w��
			start_po[li*2+1].x = start_po[(li*2+2)%8].x = diameter; // �͈͊O�w��
			if (cy*y_sign<=r_root2 && cy*y_sign>0){
					// �͈͊O�w�� �c 1,2 �� 3,4 �� 5,6 �� 7,0
					// 0,3 �� 2,5 �� 4,7 �� 6,1
					if (end_po[li*2].x>abs(cy)) {
						end_po[li*2].y = abs(cx);
						end_po[li*2].x = abs(cy);
					}
					if (end_po[(li*2+3)%8].x>abs(cy)) {
						end_po[(li*2+3)%8].y = abs(cx);
						end_po[(li*2+3)%8].x = abs(cy);
					}
			}
			else {
					start_po[li*2].y = start_po[(li*2+3)%8].y = 0;
					start_po[li*2].x = start_po[(li*2+3)%8].x = diameter;
					if (cy*y_sign<=0 && cy*y_sign>-r_root2){
						// �͈͊O�w�� �c 0,3 �� 2,5 �� 4,7 �� 6,1
						// 4,7 �� 6,1 �� 0,3 �� 2,5
						if (start_po[(li*2+4)%8].x<abs(cy)) {
							start_po[(li*2+4)%8].y = abs(cx);
							start_po[(li*2+4)%8].x = abs(cy);
						}
						if (start_po[(li*2+7)%8].x<abs(cy)) {
							start_po[(li*2+7)%8].y = abs(cx);
							start_po[(li*2+7)%8].x = abs(cy);
						}
					}
					else {
						start_po[(li*2+4)%8].y = start_po[(li*2+7)%8].y = 0;
						start_po[(li*2+4)%8].x = start_po[(li*2+7)%8].x = diameter;
					//  if (cy<-r_root2 && cy>(diameter/2)) ���m��ς�
						// �͈͊O�w�� �c 4,7 �� 6,1 �� 0,3 �� 2,5
						// 5,6 �� 7,0 �� 1,2 �� 3,4
						if (end_po[(li*2+5)%8].x>abs(cx)) {
							end_po[(li*2+5)%8].y = abs(cy);
							end_po[(li*2+5)%8].x = abs(cx);
						}
						if (end_po[(li*2+6)%8].x>abs(cx)) {
							end_po[(li*2+6)%8].y = abs(cy);
							end_po[(li*2+6)%8].x = abs(cx);
						}
					}
			}
		}
	}

	// ���C�����[�v
	for(num_eigth=0; num_eigth<8 ; num_eigth++){
		/*
			�_�Q|�P�^       [0] 0-45�x�̊�      [1] 45-90�x�̊�
			�R�_|�^�O       [2] 90-135�x�̊�    [3] 135-180�x�̊�
			------��------
			�S�^|�_�V       [4] 180-225�x�̊�   [5] 225-270�x�̊�
			�^�T|�U�_       [6] 270-315�x�̊�   [7] 315-360�x�̊�
		*/
		if (num_eigth<4){
					now_center.y = center.y; y_sign=1; }            // 0,1,2,3
		else{   now_center.y = mirror_center.y; y_sign=-1; }    // 4,5,6,7
		if ((num_eigth%6)<=1){
					now_center.x = center.x;  x_sign=1; }           // 0,1,6,7
		else {  now_center.x = mirror_center.x; x_sign=-1; }    // 2,3,4,5
		if ((num_eigth%4)%3){
					px = &cx; py = &cy; }   // 0,3,4,7
		else {  px = &cy; py = &cx; }   // 1,2,5,6

		// �����l
		cy=start_po[num_eigth].y;
		cx=start_po[num_eigth].x;

		// d �l
		d = 4*cx*cx+4*cy*cy -4*cy+2 - diameter * diameter;
		dx = 8*cx+4;
		dy = -8*cy+8;

		// �`�惋�[�v
		for (;cx<=end_po[num_eigth].x;cx++){
			if (d>0) {
					d += dy;
					dy+=8;
					cy--;
			}
			DrawPoint ( (*px)*x_sign + now_center.x, (*py)*y_sign + now_center.y, color);  // �`��

			d += dx;
			dx+=8;
		}
	}
}

void DrawCircle3D(const D3DXVECTOR3& position, const float diameter, const D3DCOLOR color, const bool is_fill) {
  D3DXVECTOR3 transformed_position;
  D3DXVec3TransformCoord(&transformed_position, &position, &g_view_projection_viewport);
  DrawCircle2(transformed_position.x, transformed_position.y, diameter, color);
}

//------------------------------------------------
// ��`�̕`��
//------------------------------------------------
void DrawRect( const float ax, const float ay, const float bx, const float by, const D3DCOLOR color, bool is_fill ) {
	// ��
	DrawLine( ax, ay, ax, by, color, color );
	// ��
	DrawLine( ax, ay, bx, ay, color, color );
	// �E
	DrawLine( bx, ay, bx, by, color, color );
	// ��
	DrawLine( ax, by, bx, by, color, color );

	// if �h��Ԃ��Ȃ�
	if( is_fill ) {
		int dy = (int)( by - ay );
		for( int line_cnt = 0; line_cnt < dy; ++line_cnt ) {
			DrawLine( ax, ay + line_cnt, bx, ay + line_cnt, color, color );
		}
	}

}


//------------------------------------------------
// �����̂̕`��
//------------------------------------------------
void DrawCube(
	const float cx, const float cy, const float cz, 
	const float width, const float height, const float depth,
	const D3DCOLOR color
) {

}


void DrawCube( float cx, float cy, float cz, float width, float height, float depth, D3DCOLOR color, const D3DXMATRIX& mtx ) {
	// ���_���̐ݒ�
	float half_width = width * 0.5f;
	float half_depth = depth * 0.5f;

	g_cube_pos[ 0 ] = D3DXVECTOR3( cx - half_width, cy + height, cz - half_depth );
	g_cube_pos[ 1 ] = D3DXVECTOR3( cx + half_width, cy + height, cz - half_depth );
	g_cube_pos[ 2 ] = D3DXVECTOR3( cx - half_width, cy, cz - half_depth );
	g_cube_pos[ 3 ] = D3DXVECTOR3( cx + half_width, cy, cz - half_depth );

	g_cube_pos[ 4 ] = D3DXVECTOR3( cx - half_width, cy + height, cz + half_depth );
	g_cube_pos[ 5 ] = D3DXVECTOR3( cx + half_width, cy + height, cz + half_depth );
	g_cube_pos[ 6 ] = D3DXVECTOR3( cx - half_width, cy, cz + half_depth );
	g_cube_pos[ 7 ] = D3DXVECTOR3( cx + half_width, cy, cz + half_depth );

	// ���_�̍��W�ϊ�
	for( int i = 0; i < 8; ++i ) {
		D3DXVec3Transform( &g_cube_pos4[ i ], &g_cube_pos[ i ], &mtx );
		g_cube_pos4[ i ].x /= g_cube_pos4[ i ].w;
		g_cube_pos4[ i ].y /= g_cube_pos4[ i ].w;
	}

	// ���C���̕`��
	DrawLine( g_cube_pos4[ 0 ].x, g_cube_pos4[ 0 ].y, g_cube_pos4[ 1 ].x, g_cube_pos4[ 1 ].y, color, color );
	DrawLine( g_cube_pos4[ 0 ].x, g_cube_pos4[ 0 ].y, g_cube_pos4[ 2 ].x, g_cube_pos4[ 2 ].y, color, color );
	DrawLine( g_cube_pos4[ 1 ].x, g_cube_pos4[ 1 ].y, g_cube_pos4[ 3 ].x, g_cube_pos4[ 3 ].y, color, color );
	DrawLine( g_cube_pos4[ 2 ].x, g_cube_pos4[ 2 ].y, g_cube_pos4[ 3 ].x, g_cube_pos4[ 3 ].y, color, color );

	DrawLine( g_cube_pos4[ 0 ].x, g_cube_pos4[ 0 ].y, g_cube_pos4[ 4 ].x, g_cube_pos4[ 4 ].y, color, color );
	DrawLine( g_cube_pos4[ 1 ].x, g_cube_pos4[ 1 ].y, g_cube_pos4[ 5 ].x, g_cube_pos4[ 5 ].y, color, color );
	DrawLine( g_cube_pos4[ 2 ].x, g_cube_pos4[ 2 ].y, g_cube_pos4[ 6 ].x, g_cube_pos4[ 6 ].y, color, color );
	DrawLine( g_cube_pos4[ 3 ].x, g_cube_pos4[ 3 ].y, g_cube_pos4[ 7 ].x, g_cube_pos4[ 7 ].y, color, color );

	DrawLine( g_cube_pos4[ 4 ].x, g_cube_pos4[ 4 ].y, g_cube_pos4[ 5 ].x, g_cube_pos4[ 5 ].y, color, color );
	DrawLine( g_cube_pos4[ 6 ].x, g_cube_pos4[ 6 ].y, g_cube_pos4[ 7 ].x, g_cube_pos4[ 7 ].y, color, color );
	DrawLine( g_cube_pos4[ 4 ].x, g_cube_pos4[ 4 ].y, g_cube_pos4[ 6 ].x, g_cube_pos4[ 6 ].y, color, color );
	DrawLine( g_cube_pos4[ 5 ].x, g_cube_pos4[ 5 ].y, g_cube_pos4[ 7 ].x, g_cube_pos4[ 7 ].y, color, color );
}

void SetMatrixViewProjectionViewport(const D3DXMATRIX& view_projection_viewport) {
  g_view_projection_viewport = view_projection_viewport;
}

void DrawAll( void ) {
  if (g_cnt != 0) {
	g_p_device->SetStreamSource( 0, g_point_buffer, 0, sizeof( VERTEX_2D ) );
	//g_p_device->SetFVF( FVF_VERTEX_2D );
	g_p_device->SetVertexDeclaration( g_vertex_declaration );
	g_p_device->SetTexture( 0, NULL );
	g_p_device->DrawPrimitive( D3DPT_POINTLIST, 0, g_cnt );
	g_cnt = 0;
  }

  if (g_line_cnt != 0) {
	g_p_device->SetStreamSource( 0, g_line_buffer, 0, sizeof( VERTEX_2D ) );
	//g_p_device->SetFVF( FVF_VERTEX_2D );
	g_p_device->SetVertexDeclaration( g_vertex_declaration );
	g_p_device->SetTexture( 0, NULL );
	g_p_device->DrawPrimitive( D3DPT_LINELIST, 0, g_line_cnt );
	g_line_cnt = 0;
  }
}