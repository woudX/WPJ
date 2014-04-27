#ifndef _H_WPJTEST
#define _H_WPJTEST

#include "WPJNode.h"

NS_WPJ_BEGIN

class WPJNodeTest : public WPJNode
{
public:

	/// Factory Method
	static WPJNodeTest *CreateNewObject();
	
	/// Inherited Methods
	virtual U_INT GetSize();
	virtual void GetSharedPtr(WPJNodeTest* &object);
	virtual WPJNodeTest *GetCopiedPtr();
	virtual WPJNodeTest *DupCopy();

	void TestFuncA(float dt);
	void TestFuncB(float dt);
	virtual void Update(float dt);
};


NS_WPJ_END

#endif