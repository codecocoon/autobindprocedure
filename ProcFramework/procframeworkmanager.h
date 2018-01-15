/*
* I take no responsibility for this code and any problems you might get if using it.
* published at https://github.com/codecocoon/autobindprocedure.git
* codecocoon@gmail.com
*/

#ifndef __procframeworkmanager_h__
#define __procframeworkmanager_h__

#include <memory.h>
#include <iostream>
#include "singleton.h"

namespace cocoon {
namespace network {

class procunit
{
public:
	procunit( void ) {}
	procunit( const int in_pk, TCHAR* const in_name )
		: m_pk( in_pk )
		, m_name( in_name )
	{}
	virtual ~procunit( void ) {}

public:
	int get_pk( void ) { return m_pk; }
	TCHAR* get_name( void ) { return m_name; }

public:
	virtual bool run( const int in_data ) = 0;

private:
	int m_pk;
	TCHAR* m_name;
};

//----------------------------------------------------------------------------------------------
class procframework_manager : public singleton< procframework_manager >
{
public:
	procframework_manager( void )
	{
		memset( m_container_procunit, 0x00, sizeof( m_container_procunit ) );
		return;
	}
	~procframework_manager( void ) 
	{
		for ( int i = 0
			  ; 10 >= i
			  ; ++i )
		{
			if ( nullptr != m_container_procunit[ i ] )
			{
				delete m_container_procunit[ i ];
				m_container_procunit[ i ] = nullptr;
			}
		}
		return;
	}

public:
	inline procunit* get_procunit( const int in_pk ) { return m_container_procunit[ in_pk ]; }
	inline bool set_procunit( const int in_pk, procunit* const in_procunit )
	{
		if ( nullptr == in_procunit )
		{
			std::cout << "fail || nullptr == in_procunit" << std::endl;
			return false;
		}

		m_container_procunit[ in_pk ] = in_procunit;
		return true;
	}

private:
	procunit* m_container_procunit[ 10 + 1 ]; //TODO : 이는 auto link에 대한 예제이므로 적절한 컨테이너로 수정해야 합니다.

};

//----------------------------------------------------------------------------------------------
#define g_procframework_manager()				( procframework_manager::get_instance() )
//----------------------------------------------------------------------------------------------

extern procframework_manager* create_procunit( const int in_pk, procunit* const in_procunit );

} // namespace network
} // namespace cocoon

//----------------------------------------------------------------------------------------------
//TODO : 이는 auto link에 대한 예제이므로 run()의 아규먼트들을 자신의 프로젝트에 맞게 수정해야 합니다.
#define register_procunit( _UNITNAME )\
	namespace p_##_UNITNAME\
	{\
		bool run( const int in_data );\
	}\
	class procunit##_UNITNAME\
		: public cocoon::network::procunit\
	{\
	public:\
		procunit##_UNITNAME():cocoon::network::procunit( _UNITNAME, _T( #_UNITNAME ) ){}\
		virtual ~procunit##_UNITNAME(){}\
	public:\
		virtual bool run( const int in_data )\
		{\
			return p_##_UNITNAME::run( in_data );\
		}\
	public:\
		static cocoon::network::procframework_manager* m_procmanager;\
	};\
	cocoon::network::procframework_manager* procunit##_UNITNAME::m_procmanager\
		= cocoon::network::create_procunit( _UNITNAME, new procunit##_UNITNAME );\
	namespace p_##_UNITNAME


#endif // __procframeworkmanager_h__
