/*
* I take no responsibility for this code and any problems you might get if using it.
* published at https://github.com/codecocoon/autobindprocedure.git
* codecocoon@gmail.com
*/

#include "stdafx.h"
#include <iostream>
#include "procframeworkmanager.h"
#include "log_helper.h"

//----------------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------------
enum packetopcode
{
	packetopcode_login,
	packetopcode_logout,
};

//----------------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------------
register_procunit( packetopcode_login )
{
	bool run( const int in_data )
	{
		int sum = in_data + 1;
		std::cout << "run : packetopcode_login || "
			<< lh( in_data, sum )
			<< std::endl;
		return true;
	}
}


register_procunit( packetopcode_logout )
{
	bool run( const int in_data )
	{
		int sum = in_data + 2;
		std::cout << "run : packetopcode_logout || "
			<< lh( in_data, sum )
			<< std::endl;
		return true;
	}
}

//----------------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------------
int _tmain(int argc, _TCHAR* argv[])
{
	using namespace cocoon;
	using namespace cocoon::network;

	//-----
	{
		auto* const procunit = g_procframework_manager()->get_procunit( packetopcode_login );
		if ( nullptr == procunit )
		{
			std::cout << "nullptr == procunit" << std::endl;
			return 1;
		}

		if ( false == procunit->run( 1 ) )
		{
			std::cout << "fail || false == procunit->run( 100 )" << std::endl;
			return 1;
		}
	}

	//-----
	{
		auto* const procunit = g_procframework_manager()->get_procunit( packetopcode_logout );
		if ( nullptr == procunit )
		{
			std::cout << "nullptr == procunit" << std::endl;
			return 1;
		}

		if ( false == procunit->run( 100 ) )
		{
			std::cout << "fail || false == procunit->run( 100 )" << std::endl;
			return 1;
		}
	}

	//-----
	std::cout << "succ" << std::endl;

	return 0;
}

