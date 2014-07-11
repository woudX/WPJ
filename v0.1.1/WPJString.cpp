#include "WPJString.h"
#include "WPJGarbageCollection.h"

USING_NS_WPJ

HString::HString():m_obStr(""),hashCode(0)
{
	
}

HString *HString::CreateNewObject()
{
	HString *pRet = new HString();
	pRet->Retain();
	WPJGC::GetSharedInst()->AddPtr(pRet);

	return pRet;
}

HString::HString(std::string orgi)
{
	m_obStr = orgi;
	hashCode = Hash(orgi);
}

HString::HString(HString const *orgi)
{
	m_obStr = orgi->m_obStr;
	hashCode = orgi->hashCode;
}

HString &HString::operator= (const HString &rhs)
{
	m_obStr = rhs.m_obStr;
	hashCode = rhs.hashCode;
	return *this;
}

bool HString::operator== (const HString &rhs) 
{
	return this->EqualWith(&rhs);
}

bool HString::operator!= (const HString &rhs) 
{
	return !(this->EqualWith(&rhs));
}

bool HString::operator< (const HString &rhs) const
{
	bool bRet = false;
	if (m_obStr.compare(rhs.m_obStr) < 0)
		bRet = true;

	return bRet;
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
	return m_obStr.c_str();
}

bool HString::InitWithFormatAndValist(const char *format, va_list ap)
{
	bool bRet = false;
	char *pBuf = (char*) malloc(MAX_STRING_LEN);

	if (pBuf != NULL)
	{
		vsnprintf(pBuf, MAX_STRING_LEN, format, ap);
		m_obStr = pBuf;
		free(pBuf);
		bRet = true;
	}

	return bRet;
}

bool HString::InitWithFormat(const char *format, ... )
{
	bool bRet = false;
	va_list ap;
	va_start(ap, format);
	bRet = InitWithFormatAndValist(format, ap);
	va_end(ap);

	return bRet;
}

HString *HString::CreatePointerWithFormat(const char *format, ...)
{
	HString *pRet = HString::CreateNewObject();
	va_list ap;
	va_start(ap, format);
	pRet->InitWithFormatAndValist(format, ap);
	va_end(ap);

	return pRet;
}

HString HString::CreateWithFormat(const char *format, ...)
{
	HString pRet;
	va_list ap;
	va_start(ap, format);
	pRet.InitWithFormatAndValist(format, ap);
	va_end(ap);

	return pRet;
}