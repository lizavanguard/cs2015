//==============================================================================
//
// �l���p���I�ɕێ����郂�W���[�� [PersistentValue.h]
// Designed On 2014.02.09 By Shimizu Shoji
// ������̕ێ����ۑ�
// ����̂܂܂ł����Ȃ����삷�邪�A�g�����ɂ���Ă͔��Ɋ댯
//
//==============================================================================
#ifndef __H_PERSISTENTVALUE_H__
#define __H_PERSISTENTVALUE_H__
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// �C���N���[�h
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include <map>
#include <string>


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// ���C�u�����̃����N
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#ifdef _DEBUG
#pragma comment( lib, "PersistentValueLib_d" )
#else
#pragma comment( lib, "PersistentValueLib" )
#endif


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// �N���X��`
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
