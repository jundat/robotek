#include "MenuScene.h"
#include "Global.h"
#include "Random.h"

#include "HelpScene.h"
#include "AboutScene.h"
#include "OptionsScene.h"
#include "ScoresScene.h"
#include "CampaignScene.h"

USING_NS_CC;


CCScene* MenuScene::scene()
{
	CCScene *scene = CCScene::create();
	MenuScene *layer = MenuScene::create();
	scene->addChild(layer);
	return scene;
}

bool MenuScene::init()
{
	if ( !CCLayerColor::init() )
	{
		return false;
	}

	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize(); //gốc tọa độ ở góc dưới, bên trái

	ccBlendFunc blendLinearDodge = ccBlendFunc();
	blendLinearDodge.src = GL_ONE;
	blendLinearDodge.dst = GL_ONE;

	//background moving...

	m_sprBlend = CCSprite::create("imgBlendMenu.png");
	m_sprBlend->setPosition(ccp(visibleSize.width/2, visibleSize.height/2));
	this->addChild(m_sprBlend, 0, 100);
	m_sprBlend->setBlendFunc(blendLinearDodge);

	m_sprBlendCopy = CCSprite::create("imgBlendMenu.png");
	m_sprBlendCopy->setPosition(ccp(- visibleSize.width/2 , visibleSize.height/2));
	this->addChild(m_sprBlendCopy, 0, 200);
	m_sprBlend->setBlendFunc(blendLinearDodge);

	CCSprite* bg = CCSprite::create("imgBgMenu.png");
	bg->setPosition(ccp(visibleSize.width/2, visibleSize.height/2));
	this->addChild(bg, 0);
	bg->setBlendFunc(blendLinearDodge);

	//moving triangle...

	CCSprite* sprTriangle = CCSprite::create("imgTriangle.png");
	sprTriangle->setPosition(ccp(200, 200));
	sprTriangle->setBlendFunc(blendLinearDodge);
	//this->addChild(sprTriangle);

	for (int i = 0; i < MAX_CURRENT_TRIANGLE; ++i)
	{
		CCSprite* sprNew = CCSprite::create("imgTriangle.png"); //Global::duplicateSprite(sprTriangle);
		
		sprNew->setBlendFunc(blendLinearDodge);

		//random scale
		float scalex = (float) (RANDOM(10) / 20.0 + 0.15);
		float scaley = (float) (RANDOM(10) / 20.0 + 0.15);
		sprNew->setScaleX(scalex);
		sprNew->setScaleY(scaley);

		//random rotate
		float rota = (float) (RANDOM(180));
		sprNew->setRotation(rota);
		
		//random begin position
		int sx = RANDOM(visibleSize.width);
		int sy = RANDOM(visibleSize.height);

		//random destination position
		int dx = sx + RANDOM(visibleSize.width / 5);
		int dy = visibleSize.height + 30;

		int time = (dy - sy) / 32;
		
		sprNew->setPosition(ccp(sx, sy));

		CCAction* sequen = CCSequence::create(
			CCMoveTo::create(time, ccp(dx, dy)), 
			CCCallFuncN::create(sprNew, callfuncN_selector(MenuScene::deleteTriangle)),
			NULL);

		this->addChild(sprNew);
		sprNew->runAction(sequen);
	}

	//menubar moving...

	m_sprWaveTop = CCSprite::create("imgWaveTop.png");
	m_sprWaveTopCopy = CCSprite::create("imgWaveTop.png");
	m_sprWaveBottom = CCSprite::create("imgWaveBottom.png");
	m_sprWaveBottomCopy = CCSprite::create("imgWaveBottom.png");

	m_sprWaveTop->setPosition(ccp(visibleSize.width - m_sprWaveTop->getContentSize().width/2, visibleSize.height/2));
	m_sprWaveTopCopy->setPosition(ccp(visibleSize.width - m_sprWaveTopCopy->getContentSize().width/2, visibleSize.height/2 + visibleSize.height));
	m_sprWaveBottom->setPosition(ccp(visibleSize.width - m_sprWaveBottom->getContentSize().width/2, visibleSize.height/2));
	m_sprWaveBottomCopy->setPosition(ccp(visibleSize.width - m_sprWaveBottomCopy->getContentSize().width/2, -visibleSize.height/2));

	//sprWaveTop->setBlendFunc(someBlend);
	m_sprWaveBottom->setBlendFunc(blendLinearDodge);
	m_sprWaveBottomCopy->setBlendFunc(blendLinearDodge);

	this->addChild(m_sprWaveBottom, 0, 400);
	this->addChild(m_sprWaveBottomCopy, 0, 401);
	this->addChild(m_sprWaveTop, 0, 300);
	this->addChild(m_sprWaveTopCopy, 0, 301);


	//vender small...
	CCSprite* sprVenderSmall = CCSprite::create("imgVenderSmall.png");
	sprVenderSmall->setPosition(ccp(visibleSize.width - sprVenderSmall->getContentSize().width/2, sprVenderSmall->getContentSize().height/2));
	this->addChild(sprVenderSmall);


	//menu item...

	m_itemStart = CCMenuItemImage::create("itemStart.png", "itemStart.png", this, menu_selector(MenuScene::startClicked));
	m_itemScores = CCMenuItemImage::create("itemScores.png", "itemScores.png", this, menu_selector(MenuScene::scoresClicked));
	m_itemOptions = CCMenuItemImage::create("itemOptions.png", "itemOptions.png", this, menu_selector(MenuScene::optionsClicked));
	m_itemAbout = CCMenuItemImage::create("itemAbout.png", "itemAbout.png", this, menu_selector(MenuScene::aboutClicked));
	m_itemHelp = CCMenuItemImage::create("itemHelp.png", "itemHelp.png", this, menu_selector(MenuScene::helpClicked));

	m_itemStart->setPosition(ccp(visibleSize.width - m_itemStart->getContentSize().width/2, visibleSize.height - 20 - m_itemStart->getContentSize().height/2));
	m_itemScores->setPosition(ccp(visibleSize.width - m_itemScores->getContentSize().width/2, visibleSize.height - 100 - m_itemScores->getContentSize().height/2));
	m_itemOptions->setPosition(ccp(visibleSize.width - m_itemOptions->getContentSize().width/2, visibleSize.height - 180 - m_itemOptions->getContentSize().height/2));
	m_itemAbout->setPosition(ccp(visibleSize.width - m_itemAbout->getContentSize().width/2, visibleSize.height - 260 - m_itemAbout->getContentSize().height/2));
	m_itemHelp->setPosition(ccp(visibleSize.width - m_itemHelp->getContentSize().width/2, visibleSize.height - 340 - m_itemHelp->getContentSize().height/2));

	m_repeatFadeInOut = CCRepeatForever::create(CCSequence::create(
		CCFadeIn::create(0.5f), 
		CCFadeOut::create(0.5f),
		NULL));
	m_repeatFadeInOut->retain();
	
	m_currentItem = m_itemStart;
	m_itemStart->runAction(m_repeatFadeInOut);

	// create menu, it's an autorelease object
	CCMenu* pMenu = CCMenu::create(m_itemStart, m_itemScores, m_itemOptions, m_itemAbout, m_itemHelp, NULL);
	pMenu->setPosition(CCPointZero);
	this->addChild(pMenu, 1);

	m_buffer = CCSprite::create("imgFade.png");
	m_buffer->setScaleX(1136);
	m_buffer->setScaleY(640);
	m_buffer->setPosition(ccp(visibleSize.width/2, visibleSize.height/2));
	m_buffer->setOpacity(0);
	this->addChild(m_buffer, 10);

	this->scheduleUpdate();
	return true;
}

void MenuScene::update(float delta) 
{
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();

	//background moving...


	float moveBg = delta * 30;
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

	//menu bar moving...

	int moveBar = (int)(delta * 160);
	m_sprWaveTop->setPositionY(m_sprWaveTop->getPositionY() - moveBar);
	m_sprWaveBottom->setPositionY(m_sprWaveBottom->getPositionY() + moveBar);

	if (m_sprWaveTop->getPositionY() <= - visibleSize.height/2)
	{
		m_sprWaveTop->setPositionY(visibleSize.height/2 + visibleSize.height);
	}

	if (m_sprWaveTop->getPositionY() <= visibleSize.height/2)
	{
		m_sprWaveTopCopy->setPositionY(m_sprWaveTop->getPositionY() + visibleSize.height);
	} 
	else
	{
		m_sprWaveTopCopy->setPositionY(m_sprWaveTop->getPositionY() - visibleSize.height);
	}
	
	// bottom

	if (m_sprWaveBottom->getPositionY() >= visibleSize.height/2 + visibleSize.height)
	{
		m_sprWaveBottom->setPositionY(- visibleSize.height/2);
	}

	if (m_sprWaveBottom->getPositionY() >= visibleSize.height/2)
	{
		m_sprWaveBottomCopy->setPositionY(m_sprWaveBottom->getPositionY() - visibleSize.height);
	}
	else
	{
		m_sprWaveBottomCopy->setPositionY(m_sprWaveBottom->getPositionY() + visibleSize.height);
	}
}

void MenuScene::deleteTriangle(CCNode* pSender)
{
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize(); //gốc tọa độ ở góc dưới, bên trái
	
	ccBlendFunc blendLinearDodge = ccBlendFunc();
	blendLinearDodge.src = GL_ONE;
	blendLinearDodge.dst = GL_ONE;

	//////////////////////////////////////////////////////////////////////////
	CCSprite* sprNew = (CCSprite*) pSender;

	//random scale
	float scalex = (float) (RANDOM(10) / 20.0 + 0.15);
	float scaley = (float) (RANDOM(10) / 20.0 + 0.15);
	sprNew->setScaleX(scalex);
	sprNew->setScaleY(scaley);

	//random rotate
	float rota = (float) (RANDOM(180));
	sprNew->setRotation(rota);

	//random begin position
	int sx = RANDOM(visibleSize.width);
	int sy = -30;

	//random destination position
	int dx = sx + RANDOM(visibleSize.width / 5);
	int dy = visibleSize.height;

	int time = (dy - sy) / 32;

	sprNew->setPosition(ccp(sx, sy));

	CCAction* sequen = CCSequence::create(
		CCMoveTo::create(time, ccp(dx, dy)), 
		CCCallFuncN::create(sprNew, callfuncN_selector(MenuScene::deleteTriangle)),
		NULL);

	sprNew->runAction(sequen);
}


#pragma region ADD NEW LAYER


void MenuScene::addStartLayer( CCNode* pSender )
{
	m_currentItem->setOpacity(255);
	m_currentItem = m_itemStart;
	m_repeatFadeInOut->startWithTarget(m_itemStart);

	for (int i = 900; i >= 500; i -= 100)
	{
		CCNode* scene = this->getChildByTag(i);
		if(scene != NULL)
		{
			scene->removeFromParent();
		}
	}

	CCDirector::sharedDirector()->replaceScene(CampaignScene::scene());
}

void MenuScene::addScoresLayer( CCNode* pSender )
{
	m_currentItem->setOpacity(255);
	m_currentItem = m_itemScores;
	m_repeatFadeInOut->startWithTarget(m_itemScores);

	for (int i = 900; i >= 500; i -= 100)
	{
		CCNode* scene = this->getChildByTag(i);
		if(scene != NULL)
		{
			scene->removeFromParent();
		}
	}

	CCNode* about = ScoresScene::create();
	this->addChild(about, 2, 600);
}

void MenuScene::addOptionsLayer( CCNode* pSender )
{
	m_currentItem->setOpacity(255);
	m_currentItem = m_itemOptions;
	m_repeatFadeInOut->startWithTarget(m_itemOptions);

	for (int i = 900; i >= 500; i -= 100)
	{
		CCNode* scene = this->getChildByTag(i);
		if(scene != NULL)
		{
			scene->removeFromParent();
		}
	}

	CCNode* option = OptionsScene::create();
	this->addChild(option, 3, 700);
}

void MenuScene::addAboutLayer( CCNode* pSender )
{
	m_currentItem->setOpacity(255);
	m_currentItem = m_itemAbout;
	m_repeatFadeInOut->startWithTarget(m_itemAbout);

	for (int i = 900; i >= 500; i -= 100)
	{
		CCNode* scene = this->getChildByTag(i);
		if(scene != NULL)
		{
			scene->removeFromParent();
		}
	}

	CCNode* about = AboutScene::create();
	this->addChild(about, 2, 800);
}

void MenuScene::addHelpLayer( CCNode* pSender )
{	
	m_currentItem->setOpacity(255);
	m_currentItem = m_itemHelp;
	m_repeatFadeInOut->startWithTarget(m_itemHelp);

	for (int i = 900; i >= 500; i -= 100)
	{
		CCNode* scene = this->getChildByTag(i);
		if(scene != NULL)
		{
			scene->removeFromParent();
		}
	}

	CCNode* help = HelpScene::create();
	this->addChild(help, 2, 900);
}


#pragma endregion


#pragma region MENU ITEM HANDLER


//500
void MenuScene::startClicked(CCObject* pSender)
{
	CCAction* fadeInOut = CCSequence::create(
		CCFadeIn::create(0.5f), 
		CCCallFuncN::create(this, callfuncN_selector(MenuScene::addStartLayer)),
		CCFadeOut::create(0.5f),
		NULL);
	m_buffer->runAction(fadeInOut);
}

//600
void MenuScene::scoresClicked( CCObject* pSender )
{
	CCAction* fadeInOut = CCSequence::create(
		CCFadeIn::create(0.5f), 
		CCCallFuncN::create(this, callfuncN_selector(MenuScene::addScoresLayer)),
		CCFadeOut::create(0.5f),
		NULL);
	m_buffer->runAction(fadeInOut);
}

//700
void MenuScene::optionsClicked( CCObject* pSender )
{
	CCAction* fadeInOut = CCSequence::create(
		CCFadeIn::create(0.5f), 
		CCCallFuncN::create(this, callfuncN_selector(MenuScene::addOptionsLayer)),
		CCFadeOut::create(0.5f),
		NULL);
	m_buffer->runAction(fadeInOut);
}

//800
void MenuScene::aboutClicked( CCObject* pSender )
{
	CCAction* fadeInOut = CCSequence::create(
		CCFadeIn::create(0.5f), 
		CCCallFuncN::create(this, callfuncN_selector(MenuScene::addAboutLayer)),
		CCFadeOut::create(0.5f),
		NULL);
	m_buffer->runAction(fadeInOut);
}

//900
void MenuScene::helpClicked( CCObject* pSender )
{
	CCAction* fadeInOut = CCSequence::create(
		CCFadeIn::create(0.5f), 
		CCCallFuncN::create(this, callfuncN_selector(MenuScene::addHelpLayer)),
		CCFadeOut::create(0.5f),
		NULL);
	m_buffer->runAction(fadeInOut);
}


#pragma endregion