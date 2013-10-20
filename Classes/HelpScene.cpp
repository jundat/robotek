#include "HelpScene.h"
#include "MenuScene.h"


CCScene* HelpScene::scene()
{
	// 'scene' is an autorelease object
	CCScene *scene = CCScene::create();

	// 'layer' is an autorelease object
	HelpScene *layer = HelpScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool HelpScene::init()
{
	if ( !CCLayerColor::initWithColor(ccc4(0, 0, 0, 0)))
	{
		return false;
	}

	//touch init...

	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
	this->setTouchEnabled(true);

	//background...

	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();

	//content help...

	m_sprHelp = CCSprite::create("imgHelp.png");
	m_sprHelp->setPosition(ccp(m_sprHelp->getContentSize().width/2, - START_HELP_Y + visibleSize.height - m_sprHelp->getContentSize().height / 2));
	this->addChild(m_sprHelp, 0);

	//back button...

	this->scheduleUpdate();
	return true;
}

bool HelpScene::ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent )
{
	return true;
}

void HelpScene::ccTouchEnded( CCTouch *pTouch, CCEvent *pEvent )
{

}

void HelpScene::ccTouchMoved( CCTouch *pTouch, CCEvent *pEvent )
{
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	CCPoint delta  = pTouch->getDelta();
	
	float SCALE_MOVE = 2;

	float time = abs(delta.y) / 25;
	CCActionInterval* moveby = CCMoveBy::create(time, ccp(0, SCALE_MOVE * delta.y));
	m_sprHelp->runAction(CCEaseSineOut::create(moveby));
}

void HelpScene::update( float delta )
{
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	float newy = m_sprHelp->getPositionY();

	if(newy > START_HELP_Y + m_sprHelp->getContentSize().height / 2)  //in top
	{
		newy = START_HELP_Y + m_sprHelp->getContentSize().height / 2;
	}

	if(newy < visibleSize.height - START_HELP_Y - m_sprHelp->getContentSize().height / 2) //in bottom
	{
		newy = visibleSize.height - START_HELP_Y - m_sprHelp->getContentSize().height / 2;
	}

	m_sprHelp->setPositionY(newy);
}
