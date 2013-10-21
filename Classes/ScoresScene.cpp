#include "ScoresScene.h"
#include "MenuScene.h"




CCScene* ScoresScene::scene()
{
	CCScene *scene = CCScene::create();
	ScoresScene *layer = ScoresScene::create();
	scene->addChild(layer);
	return scene;
}


bool ScoresScene::init()
{
	if ( !CCLayerColor::initWithColor(ccc4(0, 0, 0, 0)))
	{
		return false;
	}

	//background...

	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();

	CCSprite* pSprite = CCSprite::create("hallOfFame.png");
	pSprite->setPosition(ccp(30 + pSprite->getContentSize().width/2, visibleSize.height - 30 - pSprite->getContentSize().height/2));
	this->addChild(pSprite, 0);

	for (int i = 0; i < 10; ++i)
	{
		CCSprite* newSpr = CCSprite::create("point.png");
		newSpr->setScaleX(740);
		newSpr->setPosition(ccp(400, 640 - (140 + 50 * i)));
		this->addChild(newSpr, 0);
	}
	

	return true;
}
