#include "WPJString.h"

USING_NS_WPJ

HString::HString():str(""),hashCode(0)
{
	
}

HString::HString(std::string orgi)
{
	str = orgi;
	hashCode = Hash(orgi);
}

HString::HString(HString const *orgi)
{
	str = orgi->str;
	hashCode = orgi->hashCode;
}

HString &HString::operator= (const HString &rhs)
{
	str = rhs.str;
	hashCode = rhs.hashCode;
	return *this;
}

bool HString::EqualWith(HString const *rhs)
{
	return hashCode == rhs->hashCode;
}

U_INT HString::Hash(std::string _str)
{
	// Times33 Algorithm
	U_INT t_uHashCode = 0;
	int t_iLength = _str.length();

	for (int idx = 0; idx < t_iLength; ++idx)
	{
		t_uHashCode = t_uHashCode * 33 + _str[idx];
	}

	return t_uHashCode;
}


const char *HString::c_str()
{
	return str.c_str();
}