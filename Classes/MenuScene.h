#ifndef __MENU_SCENE_H__
#define __MENU_SCENE_H__

#include "cocos2d.h"

USING_NS_CC; //đừng bao giờ quên cái nồi này


#define MAX_CURRENT_TRIANGLE  40



class MenuScene : public cocos2d::CCLayerColor
{
public:
	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();  
	

	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::CCScene* scene();

	virtual void update(float delta); 


	void resetPosition(CCNode* pSender);

	void deleteTriangle(CCNode* pSender);

	// a selector callback
	void startClicked(CCObject* pSender);
	void scoresClicked(CCObject* pSender);
	void optionsClicked(CCObject* pSender);
	void aboutClicked(CCObject* pSender);
	void helpClicked(CCObject* pSender);


	// implement the "static node()" method manually
	CREATE_FUNC(MenuScene);

private:
	CCSprite* m_sprBlend;
	CCSprite* m_sprBlendCopy;

	CCSprite* m_sprWaveTop;
	CCSprite* m_sprWaveTopCopy;
	CCSprite* m_sprWaveBottom;
	CCSprite* m_sprWaveBottomCopy;

};

#endif // __MENU_SCENE_H__
