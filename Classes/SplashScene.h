#ifndef __SPLASH_SCENE_H__
#define __SPLASH_SCENE_H__

#include "cocos2d.h"

class SplashScene : public cocos2d::CCLayerColor
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* scene();
    
    // a selector callback
    void closeCallback1(CCNode* sender);

	// a selector callback
	void closeCallback2(CCNode* sender);

    // implement the "static node()" method manually
    CREATE_FUNC(SplashScene);
};

#endif // __SPLASH_SCENE_H__
