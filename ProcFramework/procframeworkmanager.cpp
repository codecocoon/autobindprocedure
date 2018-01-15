/*
* I take no responsibility for this code and any problems you might get if using it.
* published at https://github.com/codecocoon/autobindprocedure.git
* codecocoon@gmail.com
*/

#include "stdafx.h"
#include "procframeworkmanager.h"


namespace cocoon {
namespace network {

procframework_manager* create_procunit( const int in_pk, procunit* const in_procunit )
{
	if ( nullptr == in_procunit )
	{
		std::cout << "fail || nullptr == in_procunit" << std::endl;
		return nullptr;
	}

	g_procframework_manager()->set_procunit( in_pk, in_procunit );
	return g_procframework_manager();
}

} // namespace network
} // namespace cocoon
