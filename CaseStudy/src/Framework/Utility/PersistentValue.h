//==============================================================================
//
// 値を継続的に保持するモジュール [PersistentValue.h]
// Designed On 2014.02.09 By Shimizu Shoji
// 文字列の保持が課題
// 現状のままでも問題なく動作するが、使い方によっては非常に危険
//
//==============================================================================
#ifndef __H_PERSISTENTVALUE_H__
#define __H_PERSISTENTVALUE_H__
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// インクルード
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include <map>
#include <string>


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// ライブラリのリンク
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifdef _DEBUG
#pragma comment( lib, "PersistentValueLib_d" )
#else
#pragma comment( lib, "PersistentValueLib" )
#endif


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// クラス定義
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
class PersistentValue {
private:
	// type
	struct Contents {
		union Data {
			bool b;
			char c;
			int n;
			unsigned int u;
			float f;
			std::string* str;

			operator bool() const { return b; }
			operator char() const { return c; }
			operator int() const { return n; }
			operator unsigned int() const { return u; }
			operator float() const { return f; }
			operator std::string() const { return *str; }
			operator const char*() const { return str->c_str(); }
		} data;
		int type;
	};

	// typedef
	typedef std::map<const char*,Contents> container_type;

private:
	// constructor
	PersistentValue();
	PersistentValue( const PersistentValue& rhs );
	PersistentValue& operator=( const PersistentValue& rhs );
	~PersistentValue();

public:
	// method
	static PersistentValue& Instance( void );
	void Delete( const char* key );
	void Reset( void );

	// get
	Contents::Data GetData( const char* key );

	// set
	void SetData( const char* key, bool data );
	void SetData( const char* key, char data );
	void SetData( const char* key, int data );
	void SetData( const char* key, unsigned int data );
	void SetData( const char* key, float data );
	void SetData( const char* key, const char* str );

private:
	// method
	void _DeleteContents( const char* key );

	// field
	container_type m_data;
};

#include "PersistentValue.inl"

#endif // __H_PERSISTENTVALUE_H__
