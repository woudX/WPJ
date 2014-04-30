#ifndef _H_WPJSTRING
#define _H_WPJSTRING

#include "WPJMacros.h"
#include "WPJStdafx.h"
#include "WPJObject.h"

NS_WPJ_BEGIN

/**
	HString are designed to improve string compare
*/

class HString : public WPJObject
{
public:
	std::string str;
	U_INT hashCode;

	HString();
	HString(std::string orgi);
	HString(const HString *orgi);
	HString &operator= (const HString &rhs);

	const char *c_str();
	U_INT Hash(std::string _str);
	bool EqualWith(const HString *rhs);
};

NS_WPJ_END

#endif // !_H_WPJSTRING
