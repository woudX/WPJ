#include "WPJInstantAction.h"

USING_NS_WPJ

///	WPJInstantAction
//////////////////////////////////////////////////////////////////////////

WPJInstantAction *WPJInstantAction::CreateNewObject()
{
	WPJInstantAction *pRet = new WPJInstantAction();
	pRet->AutoRelease();

	return pRet;
}

WPJInstantAction::WPJInstantAction()
	:m_bIsDone(false)
	,m_fElapsed(0.0f)
{
	m_fDuration = 0.0f;
}

WPJObject *WPJInstantAction::DupCopy(WPJZone *zone)
{
	WPJInstantAction *pRet = NULL;
	WPJZone *pNewZone = NULL;

	if (zone && zone->m_pCopyZone)
	{
		pRet = (WPJInstantAction *)zone->m_pCopyZone;
	}
	else
	{
		pRet = WPJInstantAction::CreateNewObject();
		zone = pNewZone = new WPJZone(pRet);
	}

	WPJFiniteAction::DupCopy(zone);

	ptr_safe_del(pNewZone);
	return pRet;
}

WPJInstantAction *WPJInstantAction::Copy()
{
	return (WPJInstantAction *)DupCopy(0);
}

void WPJInstantAction::StartWithTarget(WPJNode *target)
{
	WPJFiniteAction::StartWithTarget(target);

	m_fElapsed = 0.0f;
	m_bIsDone = false;
}

void WPJInstantAction::Step(float dt)
{
	UN_USED_PARAM(dt);
	if (!IsDone())
	{
		Update(1.0);
		m_bIsDone = true;
	}
}

void WPJInstantAction::Update(float dt)
{
	UN_USED_PARAM(dt);
}

bool WPJInstantAction::IsDone()
{
	return m_bIsDone;
}

WPJInstantAction::~WPJInstantAction()
{

}

/// WPJPlaceBy
//////////////////////////////////////////////////////////////////////////

WPJPlaceBy::WPJPlaceBy()
{

}

WPJPlaceBy::WPJPlaceBy(WPJPoint &point)
	:m_obDeltaPos(point)
{

}

WPJPlaceBy *WPJPlaceBy::Create(WPJPoint& position)
{
	WPJPlaceBy *pRet = new WPJPlaceBy(position);
	pRet->AutoRelease();

	return pRet;
}

WPJObject *WPJPlaceBy::DupCopy(WPJZone *zone)
{
	WPJPlaceBy *pRet = NULL;
	WPJZone *pNewZone = NULL;

	if (zone && zone->m_pCopyZone)
	{
		pRet = (WPJPlaceBy *)zone->m_pCopyZone;
	}
	else
	{
		pRet = WPJPlaceBy::Create(m_obDeltaPos);
		zone = pNewZone = new WPJZone(pRet);
	}

	WPJInstantAction::DupCopy(zone);
	ptr_safe_del(zone);

	return pRet;
}

WPJPlaceBy *WPJPlaceBy::Copy()
{
	return (WPJPlaceBy *)DupCopy(0);
}

WPJFiniteAction *WPJPlaceBy::Reverse()
{
	return WPJPlaceBy::Create(-m_obDeltaPos);
}

void WPJPlaceBy::Update(float dt)
{
	UN_USED_PARAM(dt);
	m_pTarget->SetPosition(m_obEndPos);
}

void WPJPlaceBy::StartWithTarget(WPJNode *target)
{
	WPJInstantAction::StartWithTarget(target);

	m_obStartPos = m_pTarget->GetPosition();
	m_obEndPos = m_obStartPos + m_obDeltaPos;
}

/// WPJCallFunc
//////////////////////////////////////////////////////////////////////////

WPJCallFunc::WPJCallFunc()
	:m_pSelectTarget(NULL)
	,m_pCallFunc(0)
{

}

WPJCallFunc::~WPJCallFunc()
{
	WPJ_SAFE_RELEASE(m_pSelectTarget);
}

void WPJCallFunc::Init(WPJNode *pSelectTarget, SEL_CALLFUNC pCallFunc)
{
	WPJ_SAFE_RELEASE(m_pSelectTarget);

	m_pSelectTarget = pSelectTarget;
	m_pCallFunc = pCallFunc;

	WPJ_SAFE_RETAIN(m_pSelectTarget);
}

WPJObject *WPJCallFunc::DupCopy(WPJZone *zone)
{
	WPJCallFunc *pRet = NULL;
	WPJZone *pNewZone = NULL;

	if (zone && zone->m_pCopyZone)
	{
		pRet = (WPJCallFunc *)zone->m_pCopyZone;
	}
	else
	{
		pRet = WPJCallFunc::Create();
		zone = pNewZone = new WPJZone(pRet);
	}

	WPJInstantAction::DupCopy(zone);
	pRet->Init(m_pSelectTarget, m_pCallFunc);
	ptr_safe_del(pNewZone);

	return pRet;
}

WPJCallFunc *WPJCallFunc::Copy()
{
	return (WPJCallFunc *)DupCopy(0);
}

void WPJCallFunc::Update(float dt)
{
	UN_USED_PARAM(dt);
	Execute();
}

void WPJCallFunc::Execute()
{
	if (m_pCallFunc)
	{
		(m_pSelectTarget->*m_pCallFunc)();
	}
}

void WPJCallFunc::StartWithTarget(WPJNode *target)
{
	WPJInstantAction::StartWithTarget(target);
}

WPJFiniteAction *WPJCallFunc::Reverse()
{
	WPJLOG("[%s] There is no reverse about WPJCallFunc!\n", _D_NOW_TIME__);
	ASSERT(0);
	return 0;
}

WPJCallFunc *WPJCallFunc::Create(WPJNode *pSelectTarget, SEL_CALLFUNC pCallFunc)
{
	WPJCallFunc *pRet = new WPJCallFunc();
	pRet->AutoRelease();
	pRet->Init(pSelectTarget, pCallFunc);

	return pRet;
}

WPJCallFunc *WPJCallFunc::Create()
{
	WPJCallFunc *pRet = new WPJCallFunc();
	pRet->AutoRelease();

	return pRet;
}

/// WPJCallFuncO
//////////////////////////////////////////////////////////////////////////
WPJCallFuncO::WPJCallFuncO()
{

}

WPJCallFuncO::~WPJCallFuncO()
{
	WPJ_SAFE_RELEASE(m_pObject);
}

void WPJCallFuncO::Init(WPJNode *pSelectTarget, SEL_CALLFUNCO pCallFuncO, WPJObject *pObject)
{
	WPJ_SAFE_RELEASE(m_pSelectTarget);
	WPJ_SAFE_RELEASE(m_pObject);

	m_pSelectTarget = pSelectTarget;
	m_pCallFuncO = pCallFuncO;
	m_pObject = pObject;

	WPJ_SAFE_RETAIN(m_pObject);
	WPJ_SAFE_RETAIN(m_pSelectTarget);
}

WPJCallFuncO *WPJCallFuncO::Create()
{
	WPJCallFuncO *pRet = new WPJCallFuncO();

	if (pRet)
		pRet->AutoRelease();

	return pRet;
}

WPJCallFuncO *WPJCallFuncO::Create(WPJNode *pSelectTarget, SEL_CALLFUNCO pCallFuncO, WPJObject *pObject)
{
	WPJCallFuncO *pRet = new WPJCallFuncO();

	if (pRet)
	{
		pRet->Init(pSelectTarget, pCallFuncO, pObject);
		pRet->AutoRelease();
	}

	return pRet;
}

WPJObject *WPJCallFuncO::DupCopy(WPJZone *zone)
{
	WPJCallFuncO *pRet = NULL;
	WPJZone *pNewZone = NULL;

	if (zone && zone->m_pCopyZone)
	{
		pRet = (WPJCallFuncO *)zone->m_pCopyZone;
	}
	else
	{
		pRet = WPJCallFuncO::Create();
		zone = pNewZone = new WPJZone(pRet);
	}

	WPJCallFunc::DupCopy(zone);
	pRet->Init(m_pSelectTarget, m_pCallFuncO, m_pObject);
	ptr_safe_del(pNewZone);

	return pRet;
}

WPJCallFuncO *WPJCallFuncO::Copy()
{
	return (WPJCallFuncO *)DupCopy(0);
}

void WPJCallFuncO::Execute()
{
	if (m_pCallFuncO)
	{
		(m_pSelectTarget->*m_pCallFuncO)(m_pObject);
	}
}

/// WPJCallFuncN
//////////////////////////////////////////////////////////////////////////

WPJCallFuncN::WPJCallFuncN()
{

}

void WPJCallFuncN::Init(WPJNode *pSelectTarget, SEL_CALLFUNCN pCallFuncN)
{
	WPJ_SAFE_RELEASE(m_pSelectTarget);

	m_pSelectTarget = pSelectTarget;
	m_pCallFuncN = pCallFuncN;

	WPJ_SAFE_RETAIN(m_pSelectTarget);

}

WPJCallFuncN *WPJCallFuncN::Create()
{
	WPJCallFuncN *pRet = new WPJCallFuncN();

	if (pRet)
		pRet->AutoRelease();

	return pRet;
}

WPJCallFuncN *WPJCallFuncN::Create(WPJNode *pSelectTarget, SEL_CALLFUNCN pCallFunc)
{
	WPJCallFuncN *pRet = new WPJCallFuncN();

	if (pRet)
	{
		pRet->Init(pSelectTarget, pCallFunc);
		pRet->AutoRelease();
	}

	return pRet;
}

WPJObject *WPJCallFuncN::DupCopy(WPJZone *zone)
{
	WPJCallFuncN *pRet = NULL;
	WPJZone *pNewZone = NULL;

	if (zone && zone->m_pCopyZone)
	{
		pRet = (WPJCallFuncN *)zone->m_pCopyZone;
	}
	else
	{
		pRet = WPJCallFuncN::Create();
		zone = pNewZone = new WPJZone(pRet);
	}

	WPJCallFunc::DupCopy(zone);
	pRet->Init(m_pSelectTarget, m_pCallFuncN);
	ptr_safe_del(pNewZone);

	return pRet;
}

void WPJCallFuncN::Execute()
{
	if (m_pCallFuncN)
	{
		(m_pSelectTarget->*m_pCallFuncN)(m_pTarget);
	}
}

/// WPJCallFuncND
//////////////////////////////////////////////////////////////////////////

WPJCallFuncND::WPJCallFuncND()
{

}

void WPJCallFuncND::Init(WPJNode *pSelectTarget, SEL_CALLFUNCND pCallFuncND, void *pData)
{
	WPJ_SAFE_RELEASE(m_pSelectTarget);
	m_pSelectTarget = pSelectTarget;
	m_pCallFuncND = pCallFuncND;
	m_pData = pData;
	WPJ_SAFE_RETAIN(m_pSelectTarget);
}

WPJCallFuncND *WPJCallFuncND::Create()
{
	WPJCallFuncND *pRet = new WPJCallFuncND();
	
	if (pRet)
		pRet->AutoRelease();

	return pRet;
}

WPJCallFuncND *WPJCallFuncND::Create(WPJNode *pSelectTarget, SEL_CALLFUNCND pCallFuncND, void *pData)
{
	WPJCallFuncND *pRet = new WPJCallFuncND();

	if (pRet)
	{
		pRet->Init(pSelectTarget, pCallFuncND, pData);
		pRet->AutoRelease();
	}

	return pRet;
}

WPJObject *WPJCallFuncND::DupCopy(WPJZone *zone)
{
	WPJCallFuncND *pRet = NULL;
	WPJZone *pNewZone = NULL;

	if (zone && zone->m_pCopyZone)
	{
		pRet = (WPJCallFuncND *)zone->m_pCopyZone;
	}
	else
	{
		pRet = WPJCallFuncND::Create();
		zone = pNewZone = new WPJZone(pRet);
	}

	WPJCallFuncN::DupCopy(zone);
	pRet->Init(m_pSelectTarget, m_pCallFuncND, m_pData);
	ptr_safe_del(pNewZone);

	return pRet;
}

WPJCallFuncND *WPJCallFuncND::Copy()
{
	return (WPJCallFuncND *)DupCopy(0);
}

void WPJCallFuncND::Execute()
{
	if (m_pCallFuncND)
	{
		(m_pSelectTarget->*m_pCallFuncND)(m_pTarget, m_pData);
	}
}

WPJCallFuncND::~WPJCallFuncND()
{
	m_pData = NULL;
}
