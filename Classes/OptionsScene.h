#ifndef __OPTIONS_SCENE_H__
#define __OPTIONS_SCENE_H__

#include "cocos2d.h"

USING_NS_CC; //đừng bao giờ quên cái nồi này


class OptionsScene : public cocos2d::CCLayer
{
public:
	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();  

	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::CCScene* scene();

	//touch...
	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);

	//handle menu

	void musicOnClick(CCObject* pSender);
	void musicOffClick(CCObject* pSender);

	void soundOnClick(CCObject* pSender);
	void soundOffClick(CCObject* pSender);

	void resetCampaign(CCObject* pSender);
	
	// implement the "static node()" method manually
	CREATE_FUNC(OptionsScene);


	static float s_musicVolume; //0.0 -> 1.0
	static float s_soundVolume; //0.0 -> 1.0

private:
	CCSize m_sizeTick;

	CCSprite* imgTickMusic;
	CCSprite* imgTickSounds;
	CCSprite* imgUnTickMusic;
	CCSprite* imgUnTickSounds;
};

#endif // __OPTIONS_SCENE_H__
