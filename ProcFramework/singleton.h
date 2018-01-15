/*
* I take no responsibility for this code and any problems you might get if using it.
* published at https://github.com/codecocoon/autobindprocedure.git
* codecocoon@gmail.com
*/

#ifndef __singleton_h__
#define __singleton_h__


namespace cocoon {

template<typename T>
class singleton
{

protected:

	singleton( void ) {}
	virtual ~singleton( void ) {}


private:

	static inline T& get( void )
	{
		static T m_instance;
		return m_instance;

	}


public:

	static inline T* get_instance( void )
	{
		return &T::get();
	}
};

} // namespace cocoon


#endif  