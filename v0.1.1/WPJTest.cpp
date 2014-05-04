#include "WPJTest.h"
#include "WPJGarbageCollection.h"

USING_NS_WPJ

WPJNodeTest *WPJNodeTest::CreateNewObject()
{
	WPJNodeTest *t_pNodeTest = new WPJNodeTest();
	t_pNodeTest->Retain();
	WPJGC::GetSharedInst()->AddPtr(t_pNodeTest);

	return t_pNodeTest;
}

void WPJNodeTest::GetSharedPtr(WPJNodeTest* &object)
{
	object = this;
	object->Retain();
}

U_INT WPJNodeTest::GetSize()
{
	return sizeof(this);
}

WPJNodeTest *WPJNodeTest::GetCopiedPtr()
{
	return DupCopy();
}

WPJNodeTest *WPJNodeTest::DupCopy()
{
	return NULL;
}

void WPJNodeTest::TestFuncA(float dt)
{
	WPJLOG("[%s] Test Info ... Come from TestFuncA , dt = %f\n" , _D_NOW_TIME__, dt);
}

void WPJNodeTest::TestFuncB(float dt)
{
	WPJLOG("[%s] Test Info ... Come from TestFuncB , dt = %f\n" , _D_NOW_TIME__, dt);
}

void WPJNodeTest::Update(float dt)
{
	WPJLOG("[%s] Test Info ... Come from Update , dt = %f\n" , _D_NOW_TIME__, dt);
}

void WPJNodeTest::OnEnterTransitionDidFinish()
{
	WPJNode::OnEnterTransitionDidFinish();

	WPJLOG("[%s] Admission gorgeous effect ! Great !\n", _D_NOW_TIME__);
}