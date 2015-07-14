//==============================================================================
//
// 値を継続的に保持するモジュール [PersistentValue.inl]
// Designed On 2014.02.09 By Shimizu Shoji
//
//==============================================================================
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// インクルード
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "PersistentValue.h"


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// 定数定義
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
enum {
	TYPE_NONE,
	TYPE_BOOL,
	TYPE_CHAR,
	TYPE_INT,
	TYPE_UINT,
	TYPE_FLOAT,
	TYPE_STR,
	TYPE_VECTOR3,
	kTypeMax
};


//==============================================================================
// クラス実装部
//==============================================================================
//------------------------------------------------
// constructor
//------------------------------------------------
inline
PersistentValue::PersistentValue() {
	Reset();
}


//------------------------------------------------
// destructor
//------------------------------------------------
inline
PersistentValue::~PersistentValue() {
	Reset();
}


//------------------------------------------------
// delete
//------------------------------------------------
inline
void PersistentValue::Delete( const char* const key ) {
	m_data.erase( key );
}


//------------------------------------------------
// インスタンスの取得
//------------------------------------------------
inline
PersistentValue& PersistentValue::Instance(void) {
	static PersistentValue instance;
	return instance;
}


//------------------------------------------------
// reset
//------------------------------------------------
inline
void PersistentValue::Reset( void ) {
	for( auto it = m_data.begin(); it != m_data.end(); ++it ) {
		_DeleteContents( it->first );
	}
	m_data.clear();
}


//------------------------------------------------
// get
//------------------------------------------------
inline
PersistentValue::Contents::Data PersistentValue::GetData(const char* const key) {
	return m_data[ key ].data;
}


//------------------------------------------------
// set
//------------------------------------------------
inline
void PersistentValue::SetData(const char* const key, const bool data) {
	_DeleteContents( key );
	m_data[ key ].data.b = data;
	m_data[ key ].type = ::TYPE_BOOL;
}


inline
void PersistentValue::SetData(const char* const key, const char data) {
	_DeleteContents( key );
	m_data[ key ].data.c = data;
	m_data[ key ].type = ::TYPE_CHAR;
}


inline
void PersistentValue::SetData(const char* const key, const int data) {
	_DeleteContents( key );
	m_data[ key ].data.n = data;
	m_data[ key ].type = ::TYPE_INT;
}


inline
void PersistentValue::SetData(const char* const key, const unsigned int data) {
	_DeleteContents( key );
	m_data[ key ].data.u = data;
	m_data[ key ].type = ::TYPE_UINT;
}


inline
void PersistentValue::SetData(const char* const key, const float data) {
	_DeleteContents( key );
	m_data[ key ].data.f = data;
	m_data[ key ].type = ::TYPE_FLOAT;
}


inline
void PersistentValue::SetData(const char* const key, const char* const str) {
	_DeleteContents( key );
	m_data[ key ].data.str = new std::string( str );
	m_data[ key ].type = ::TYPE_STR;
}


//------------------------------------------------
// データの削除
//------------------------------------------------
inline
void PersistentValue::_DeleteContents(const char* const key) {
	// if データが存在しないなら
	if( m_data.count( key ) == 0 ) {
		// 何もしない
		return;
	}

	// else データが存在するなら
	switch( m_data[ key ].type ) {
		case TYPE_BOOL:
			m_data[ key ].data.b = 0;
			break;
		case TYPE_CHAR:
			m_data[ key ].data.c = 0;
			break;
		case TYPE_INT:
			m_data[ key ].data.n = 0;
			break;
		case TYPE_UINT:
			m_data[ key ].data.u = 0;
			break;
		case TYPE_FLOAT:
			m_data[ key ].data.f = 0;
			break;
		case TYPE_STR:
			delete m_data[ key ].data.str;
			m_data[ key ].data.str = NULL;
			break;
		default:
			break;
	}
	m_data[ key ].type = ::TYPE_NONE;
}
