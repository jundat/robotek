#ifndef __HELP_SCENE_H__
#define __HELP_SCENE_H__

#include "cocos2d.h"

USING_NS_CC; //đừng bao giờ quên cái nồi này

#define START_HELP_Y 0



class HelpScene : public cocos2d::CCLayerColor
{
public:

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();  

	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::CCScene* scene();

	// a selector callback
	void back2Menu(CCObject* pSender);

	virtual void update(float delta);

	//touch...

	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);

	// implement the "static node()" method manually
	CREATE_FUNC(HelpScene);

private:
	CCSprite* m_sprHelp;
};

#endif // __HELLOWORLD_SCENE_H__
