#include "AboutScene.h"
#include "MenuScene.h"


CCScene* AboutScene::scene()
{
	// 'scene' is an autorelease object
	CCScene *scene = CCScene::create();

	// 'layer' is an autorelease object
	AboutScene *layer = AboutScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool AboutScene::init()
{
	if ( !CCLayerColor::initWithColor(ccc4(0, 0, 0, 0)))
	{
		return false;
	}

	//background...

	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();

	CCSprite* pSprite = CCSprite::create("imgAboutText.png");
	pSprite->setPosition(ccp(30 + pSprite->getContentSize().width/2, visibleSize.height - 30 - pSprite->getContentSize().height/2));
	this->addChild(pSprite, 0);

	return true;
}
