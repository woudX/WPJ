#include "WPJString.h"

USING_NS_WPJ

WPJString::WPJString():str(""),hashCode(0)
{

}

WPJString::WPJString(std::string orgi)
{
	str = orgi;
	hashCode = Hash(orgi);
}

WPJString::WPJString(const WPJString const *orgi)
{
	str = orgi->str;
	hashCode = orgi->hashCode;
}

bool WPJString::EqualWith(const WPJString const *rhs)
{
	return hashCode == rhs->hashCode;
}

U_INT WPJString::Hash(std::string _str)
{
	return 0;
}
