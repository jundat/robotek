#ifndef __SCORES_SCENE_H__
#define __SCORES_SCENE_H__

#include "cocos2d.h"

USING_NS_CC; //đừng bao giờ quên cái nồi này



class ScoresScene : public cocos2d::CCLayerColor
{
public:

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();  

	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::CCScene* scene();

	// implement the "static node()" method manually
	CREATE_FUNC(ScoresScene);
};

#endif // __SCORES_SCENE_H__
