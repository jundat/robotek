#include "SplashScene.h"
#include "MenuScene.h"


USING_NS_CC;

CCScene* SplashScene::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    SplashScene *layer = SplashScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool SplashScene::init()
{
	//////////////////////////////
	// 1. super init first
	if( !CCLayerColor::init()) //initWithColor(ccc4(255, 255, 255, 255)) ) //RGBA
	{
		return false;
	}
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize(); //gốc tọa độ ở góc dưới, bên trái

    // add "Image" splash screen"
    CCSprite* pSprite = CCSprite::create("imgVendor.png");

    // position the sprite on the center of the screen
    pSprite->setPosition(ccp(visibleSize.width/2, visibleSize.height/2));

    // add the sprite as a child to this layer
    this->addChild(pSprite, 0);

	//sequence
	CCFiniteTimeAction*  actionLogo = CCSequence::create(
		CCFadeIn::create(1.0), //fadein
		CCDelayTime::create(1.0), //delay
		CCFadeOut::create(0.5), //fadeout
		CCCallFuncN::create( this, callfuncN_selector(SplashScene::closeCallback1) ),
		NULL);
    
	pSprite->runAction(actionLogo);

    return true;
}


void SplashScene::closeCallback1(CCNode* sender)
{
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize(); //gốc tọa độ ở góc dưới, bên trái

	// add "Image" splash screen"
	CCSprite* pSprite = CCSprite::create("imgProduct.png");

	// position the sprite on the center of the screen
	pSprite->setPosition(ccp(visibleSize.width/2, visibleSize.height/2));

	// add the sprite as a child to this layer
	this->addChild(pSprite, 0);

	//sequence
	CCFiniteTimeAction*  actionLogo = CCSequence::create(
		CCFadeIn::create(0.5), //fadein
		CCDelayTime::create(1.0), //delay
		CCFadeOut::create(1.0), //fadeout
		CCCallFuncN::create( this, callfuncN_selector(SplashScene::closeCallback2) ),
		NULL);

	pSprite->runAction(actionLogo);
}

void SplashScene::closeCallback2(CCNode* sender)
{
	CCTransitionScene* transScene = CCTransitionFade::create(1.0, MenuScene::scene());
	CCDirector::sharedDirector()->replaceScene(transScene);
}