#include "CampaignScene.h"
#include "MenuScene.h"
#include "CampaignData.h"


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
	m_sprCampaign->setPosition(ccp(m_sprCampaign->getContentSize().width/2, visibleSize.height - m_sprCampaign->getContentSize().height/2));
	m_sprCampaign->setBlendFunc(blendLinearDodge);
	//map
	createMap(m_sprCampaign);
	this->addChild(m_sprCampaign, 0);

	//init current point border
	m_sprPointBorder = CCSprite::create("imgPointBorder.png");
	m_sprPointBorder->setPosition(ccp(-100, -100));
	m_sprCampaign->addChild(m_sprPointBorder, 0);

	CCAction* zoomInOut = CCRepeatForever::create(CCSequence::create(
		CCScaleBy::create(0.5, 1.2, 1.2),
		CCScaleBy::create(0.5, 1.2, 1.2)->reverse(),
		NULL));
	m_sprPointBorder->runAction(zoomInOut);

	this->scheduleUpdate();
	return true;
}

CCSprite* CampaignScene::createMap(CCSprite* sprCampaign)
{
	int len = (sizeof(g_campaignData)/sizeof(*g_campaignData));
	CCSize size = sprCampaign->getContentSize();

	ccBlendFunc blendLinearDodge = ccBlendFunc();
	blendLinearDodge.src = GL_ONE;
	blendLinearDodge.dst = GL_ONE;

	for (int i = 0; i < len; ++i)
	{
		CCSprite* point = CCSprite::create("imgPointBlue.png");
		point->setPosition(ccp(g_campaignData[i][0], size.height - g_campaignData[i][1]));
		point->setBlendFunc(blendLinearDodge);
		sprCampaign->addChild(point, 0, i); //tag = i
	}
	
	return sprCampaign;
}

bool CampaignScene::ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent )
{
	return true;
}

void CampaignScene::ccTouchEnded( CCTouch *pTouch, CCEvent *pEvent )
{
	int len = (sizeof(g_campaignData)/sizeof(*g_campaignData));

	for (int i = 0; i < len; ++i)
	{
		CCNode* node = m_sprCampaign->getChildByTag(i);
		if(node->boundingBox().containsPoint(m_sprCampaign->convertToNodeSpace(pTouch->getLocation())))
		{
			m_sprPointBorder->setPosition(node->getPosition());
		}
	}
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
