#include "CampaignScene.h"
#include "MenuScene.h"


CCScene* CampaignScene::scene()
{
	CCScene *scene = CCScene::create();
	CampaignScene *layer = CampaignScene::create();
	scene->addChild(layer);
	return scene;
}

// on "init" you need to initialize your instance
bool CampaignScene::init()
{
	if ( !CCLayerColor::initWithColor(ccc4(0, 0, 0, 0)))
	{
		return false;
	}

	//touch init...

	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
	this->setTouchEnabled(true);

	ccBlendFunc blendLinearDodge = ccBlendFunc();
	blendLinearDodge.src = GL_ONE;
	blendLinearDodge.dst = GL_ONE;

	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();

	//background...

	m_sprBlend = CCSprite::create("imgBlendCampaign.png");
	m_sprBlend->setPosition(ccp(visibleSize.width/2, visibleSize.height/2));
	this->addChild(m_sprBlend, 0, 100);
	m_sprBlend->setBlendFunc(blendLinearDodge);

	m_sprBlendCopy = CCSprite::create("imgBlendCampaign.png");
	m_sprBlendCopy->setPosition(ccp(- visibleSize.width/2 , visibleSize.height/2));
	this->addChild(m_sprBlendCopy, 0, 200);
	m_sprBlend->setBlendFunc(blendLinearDodge);


	//content campaign...

	m_sprCampaign = CCSprite::create("imgCampaign.png");
	m_sprCampaign->setPosition(ccp(m_sprCampaign->getContentSize().width/2, - MARGIN_Y + visibleSize.height - m_sprCampaign->getContentSize().height / 2));
	this->addChild(m_sprCampaign, 0);
	m_sprCampaign->setBlendFunc(blendLinearDodge);

	//back button...

	this->scheduleUpdate();
	return true;
}

bool CampaignScene::ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent )
{
	return true;
}

void CampaignScene::ccTouchEnded( CCTouch *pTouch, CCEvent *pEvent )
{

}

void CampaignScene::ccTouchMoved( CCTouch *pTouch, CCEvent *pEvent )
{
	CCPoint delta  = pTouch->getDelta();	
	float time = abs(delta.y) / 25;
	CCActionInterval* moveby = CCMoveBy::create(time, delta);
	m_sprCampaign->runAction(CCEaseSineOut::create(moveby));
}

void CampaignScene::update( float delta )
{
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	
	float newy = m_sprCampaign->getPositionY();
	if(newy > MARGIN_Y + m_sprCampaign->getContentSize().height / 2)  //in top
	{
		newy = MARGIN_Y + m_sprCampaign->getContentSize().height / 2;
	}

	if(newy < visibleSize.height - MARGIN_Y - m_sprCampaign->getContentSize().height / 2) //in bottom
	{
		newy = visibleSize.height - MARGIN_Y - m_sprCampaign->getContentSize().height / 2;
	}
	m_sprCampaign->setPositionY(newy);

	//...

	float newx = m_sprCampaign->getPositionX();
	if(newx > MARGIN_X + m_sprCampaign->getContentSize().width / 2)  //in top
	{
		newx = MARGIN_X + m_sprCampaign->getContentSize().width / 2;
	}

	if(newx < visibleSize.width - MARGIN_X - m_sprCampaign->getContentSize().width / 2) //in bottom
	{
		newx = visibleSize.width - MARGIN_X - m_sprCampaign->getContentSize().width / 2;
	}
	m_sprCampaign->setPositionX(newx);
	

	//background moving...


	float moveBg = delta * 10.0;
	m_sprBlend->setPositionX(m_sprBlend->getPositionX() + moveBg);

	if(m_sprBlend->getPositionX() >= visibleSize.width + visibleSize.width/2) 
	{
		m_sprBlend->setPositionX(- visibleSize.width/2);
	}

	//move follow
	if(m_sprBlend->getPositionX() >= visibleSize.width/2) 
	{
		m_sprBlendCopy->setPositionX(m_sprBlend->getPositionX() - visibleSize.width);
	}
	else
	{
		m_sprBlendCopy->setPositionX(m_sprBlend->getPositionX() + visibleSize.width);
	}
}
