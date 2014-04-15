#ifndef _H_WPJSTRING
#define _H_WPJSTRING

#include "WPJMacros.h"
#include "WPJStdafx.h"
#include "WPJObject.h"

NS_WPJ_BEGIN

class WPJString : public WPJObject
{
public:
	std::string str;
	U_INT hashCode;

	WPJString();
	WPJString(std::string orgi);
	WPJString(const WPJString *orgi);
	U_INT Hash(std::string _str);
	bool EqualWith(const WPJString *rhs);
};

NS_WPJ_END

#endif // !_H_WPJSTRING
