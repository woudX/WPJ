#ifndef _H_WPJSCENE
#define _H_WPJSCENE

#include "WPJStdafx.h"
#include "WPJMacros.h"
#include "WPJNode.h"

NS_WPJ_BEGIN

/**
 * WPJScene is used as a container, it can contain all kinds of layer, we can look it as a act in a movie.
 * As the WPJDirector is a movie script, WPJScene is a act and WPJLayer is stage stratified in act, WPJNode
 * is actor/props in WPJLayer. 
 
 +	WPJDirector					---- Movie Script
	-	WPJScene_1				---- Act
		-	WPJLayer_A			---- Stage Stratified
			*	WPJNode_I		----	 Actor/Props
			*	WPJNode_II
			*	WPJNode_III
			...
		+	WPJLayer_B
		...
	+	WPJScene_2
	+	WPJScene_3
	...

 * Of course the hierarchical relationships is not fixed, user can set 
 * the relationships as they want, for example:

 +	WPJDirector					
	-	WPJScene_1				
		-	WPJLayer_A			---- WPJLayerA is consisted of many WPJLayers, that's ok
			-	WPJLayer_I		
				*	WPJNode_1
				*	WPJNode_2
				...
			+	WPJLayer_II
			...
	+	WPJScene_2
	+	WPJScene_3
	...
 */

class WPJScene : public WPJNode
{
public:
	static WPJScene *CreateNewObject();

	virtual bool Init();

	~WPJScene();
protected:
	WPJScene();


};

NS_WPJ_END

#endif