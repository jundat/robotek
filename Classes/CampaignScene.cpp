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

	//Current Point Border

	//init current point border
	m_sprPointBorder = CCSprite::create("imgPointBorder.png");
	m_sprPointBorder->setPosition(ccp(-100, -100));
	m_sprCampaign->addChild(m_sprPointBorder, 0);

	CCAction* zoomInOut = CCRepeatForever::create(CCSequence::create(
		CCScaleBy::create(0.4f, 1.2f, 1.2f),
		CCScaleBy::create(0.4f, 1.2f, 1.2f)->reverse(),
		NULL));
	m_sprPointBorder->runAction(zoomInOut);

	//Current Infor Dialog

	m_sprDialogPoint = CCSprite::create("dialogPoint.png");
	m_sprDialogPoint->setScale(1.0f);
	m_sprDialogPoint->setPosition(ccp(-1, -1));
	m_sprDialogPoint->setOpacity(DIALOG_OPACITY);
	m_sprCampaign->addChild(m_sprDialogPoint, 0);

	m_sprDialogLine = CCSprite::create("dialogLine.png");
	m_sprDialogLine->setScale(1.0f);
	m_sprDialogLine->setPosition(ccp(-1, -1));
	m_sprDialogLine->setOpacity(DIALOG_OPACITY);
	m_sprCampaign->addChild(m_sprDialogLine, 0);


	//TITLE....

	m_labelBoxTitle =CCLabelBMFont::create("CHOOSE CITY" , "fonts/Calibri_44.fnt");
	m_labelBoxTitle->setScale(SCALE_FONT_TITLE);
	m_labelBoxTitle->setPosition(ccp(-100, -100));
	m_labelBoxTitle->setColor(ccc3(80, 230, 255));
	m_sprCampaign->addChild(m_labelBoxTitle, 1);

	m_labelBoxContent =CCLabelBMFont::create("...content..." , "fonts/Calibri_44.fnt");
	m_labelBoxContent->setScale(SCALE_FONT_CONTENT);
	m_labelBoxContent->setPosition(ccp(-100, -100));
	m_labelBoxContent->setColor(ccc3(18, 169, 220));
	m_sprCampaign->addChild(m_labelBoxContent, 1);


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
	bool hasPoint = false;

	for (int i = 0; i < len; ++i)
	{
		CCNode* node = m_sprCampaign->getChildByTag(i);
		if(node->boundingBox().containsPoint(m_sprCampaign->convertToNodeSpace(pTouch->getLocation())))
		{
			CCPoint p = node->getPosition();
			char* title = g_campaignContent[i][0];
			char* content = g_campaignContent[i][1];
			setDialog(p, title, content);

			hasPoint = true;
			break;
		}
	}

	if(hasPoint == false)
	{
		setDialog(ccp(-100, -100), "", "");
	}
}

void CampaignScene::ccTouchMoved( CCTouch *pTouch, CCEvent *pEvent )
{
	CCPoint delta  = pTouch->getDelta();	
	float time = abs(delta.y) / 25;
	CCActionInterval* moveby = CCMoveBy::create(time, delta);
	m_sprCampaign->runAction(CCEaseSineOut::create(moveby));
}

void CampaignScene::setDialog(CCPoint p, char* title, char* content)
{
	//hightlight point

	m_sprPointBorder->setPosition(p);

	//info box

	//string...

	m_labelBoxTitle->setString(title);
	m_labelBoxContent->setString(content);

	float margin_left_dialog = 30; //khoảng cách từ điểm được chọn tới box
	float margin_line_top = 30; //khoảng cách từ đầu box đến line
	float margin_left_text = 10;
	float wTitle = 2 * margin_left_text + SCALE_FONT_TITLE * m_labelBoxTitle->getContentSize().width;
	float wContent = 2 * margin_left_text + SCALE_FONT_CONTENT * m_labelBoxContent->getContentSize().width;
	float w = (wTitle > wContent) ? wTitle : wContent;
	float h = margin_line_top + SCALE_FONT_TITLE *  m_labelBoxTitle->getContentSize().height + 
		SCALE_FONT_CONTENT * m_labelBoxContent->getContentSize().height;


	m_sprDialogPoint->setScaleX(w);
	m_sprDialogPoint->setScaleY(h);

	m_sprDialogLine->setScaleX(w);

	CCPoint dp = ccp(p.x + margin_left_dialog + w/2, p.y);
	CCPoint lp = ccp(dp.x, dp.y + h/2 - margin_line_top);
	m_sprDialogPoint->setPosition(dp);
	m_sprDialogLine->setPosition(lp);

	//position string

	m_labelBoxTitle->setPosition(ccp(lp.x - w/2 + wTitle/2, lp.y + 12));
	m_labelBoxContent->setPosition(ccp(dp.x - w/2 + wContent/2, dp.y));
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
