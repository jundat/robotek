#include "OptionsScene.h"
#include "MenuScene.h"


float OptionsScene::s_musicVolume = 0.5;
float OptionsScene::s_soundVolume = 0.5;


CCScene* OptionsScene::scene()
{
	// 'scene' is an autorelease object
	CCScene *scene = CCScene::create();

	// 'layer' is an autorelease object
	OptionsScene *layer = OptionsScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

bool OptionsScene::init()
{
	if ( !CCLayer::init())
	{
		return false;
	}

	//touch init...

	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
	this->setTouchEnabled(true);
	
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();

	//MUSIC

	CCSprite* textMusic = CCSprite::create("textMusic.png");
	textMusic->setPosition(ccp(391.5, 640-48));
	this->addChild(textMusic, 0);
	
	imgUnTickMusic = CCSprite::create("imgUnTick.png");
	imgUnTickMusic->setPosition(ccp(391.5, 640-98.5));
	this->addChild(imgUnTickMusic, 0);

	imgTickMusic = CCSprite::create("imgTick.png");
	this->m_sizeTick = CCSize(imgTickMusic->getContentSize());

	imgTickMusic->setAnchorPoint(ccp(0, 0));
	imgTickMusic->setPosition(ccp(108, 640-129));
	imgTickMusic->setTextureRect(CCRect(0, 0, s_musicVolume * imgTickMusic->getContentSize().width, imgTickMusic->getContentSize().height));
	this->addChild(imgTickMusic, 0);


	CCMenuItemImage* musicOn = CCMenuItemImage::create("imgSoundOn.png", "imgSoundOn.png", this, menu_selector(OptionsScene::musicOnClick));
	CCMenuItemImage* musicOff = CCMenuItemImage::create("imgSoundOff.png", "imgSoundOff.png", this, menu_selector(OptionsScene::musicOffClick));
	musicOff->setPosition(ccp(60, 640-98));
	musicOn->setPosition(ccp(721, 640-98));

	//SOUNDS

	CCSprite* textSounds = CCSprite::create("textSounds.png");
	textSounds->setPosition(ccp(391.5, 640-175));
	this->addChild(textSounds, 0);

	imgUnTickSounds = CCSprite::create("imgUnTick.png");
	imgUnTickSounds->setPosition(ccp(391.5, 640-223.5));
	this->addChild(imgUnTickSounds, 0);

	imgTickSounds = CCSprite::create("imgTick.png");
	imgTickSounds->setAnchorPoint(ccp(0, 0));
	imgTickSounds->setPosition(ccp(108, 640-254));
	imgTickSounds->setTextureRect(CCRect(0, 0, s_soundVolume * imgTickSounds->getContentSize().width, imgTickSounds->getContentSize().height));
	this->addChild(imgTickSounds, 0);


	CCMenuItemImage* soundOn = CCMenuItemImage::create("imgSoundOn.png", "imgSoundOn.png", this, menu_selector(OptionsScene::soundOnClick));
	CCMenuItemImage* soundOff = CCMenuItemImage::create("imgSoundOff.png", "imgSoundOff.png", this, menu_selector(OptionsScene::soundOffClick));
	soundOff->setPosition(ccp(60, 640-225));
	soundOn->setPosition(ccp(721, 640-225));

	//RESET CAMPAIGN...

	CCSprite* textResetCampaign = CCSprite::create("textResetCampaign.png");
	textResetCampaign->setPosition(ccp(356, 640-318));
	this->addChild(textResetCampaign, 0);

	CCMenuItemImage* resetCampaign = CCMenuItemImage::create("iconReset.png", "iconReset.png", this, menu_selector(OptionsScene::resetCampaign));
	resetCampaign->setPosition(ccp(541, 640-315.5));

	//
	// create menu, it's an autorelease object
	CCMenu* pMenu = CCMenu::create(musicOn, musicOff, soundOn, soundOff, resetCampaign, NULL);
	pMenu->setPosition(CCPointZero);
	this->addChild(pMenu, 1);

	return true;
}

bool OptionsScene::ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent )
{
	return true;
}

void OptionsScene::ccTouchEnded( CCTouch *pTouch, CCEvent *pEvent )
{
	CCRect rectmusic = imgUnTickMusic->boundingBox();
	if(rectmusic.containsPoint(pTouch->getLocation()))
	{
		//565, 63
		//ccp(108, 129)
		float w = pTouch->getLocation().x - 108;
		w=(w<=0)?0:w;

		w=(w>=m_sizeTick.width)?m_sizeTick.width:w;

		imgTickMusic->setTextureRect(CCRect(0, 0, w, 63));
		s_musicVolume = w/m_sizeTick.width;
	}

	CCRect rectsounds = imgUnTickSounds->boundingBox();
	if(rectsounds.containsPoint(pTouch->getLocation()))
	{
		//565, 63
		//ccp(108, 254)
		float w = pTouch->getLocation().x - 108;
		w=(w<=0)?0:w;w=(w<=0)?0:w;

		w=(w>=m_sizeTick.width)?m_sizeTick.width:w;

		imgTickSounds->setTextureRect(CCRect(0, 0, w, 63));
		s_soundVolume = w/m_sizeTick.width;
	}
}

void OptionsScene::ccTouchMoved( CCTouch *pTouch, CCEvent *pEvent )
{
	CCRect rectmusic = imgUnTickMusic->boundingBox();
	if(rectmusic.containsPoint(pTouch->getLocation()))
	{
		//565, 63
		//ccp(108, 129)
		float w = pTouch->getLocation().x - 108;
		w=(w<=0)?0:w;
		
		w=(w>=m_sizeTick.width)?m_sizeTick.width:w;

		imgTickMusic->setTextureRect(CCRect(0, 0, w, 63));
		s_musicVolume = w/m_sizeTick.width;
	}

	CCRect rectsounds = imgUnTickSounds->boundingBox();
	if(rectsounds.containsPoint(pTouch->getLocation()))
	{
		//565, 63
		//ccp(108, 254)
		float w = pTouch->getLocation().x - 108;
		w=(w<=0)?0:w;w=(w<=0)?0:w;

		w=(w>=m_sizeTick.width)?m_sizeTick.width:w;

		imgTickSounds->setTextureRect(CCRect(0, 0, w, 63));
		s_soundVolume = w/m_sizeTick.width;
	}
}

//handle button.......

void OptionsScene::musicOnClick( CCObject* pSender )
{
	imgTickMusic->setTextureRect(CCRect(0, 0, imgUnTickMusic->getContentSize().width, imgTickMusic->getContentSize().height));
	s_musicVolume = 1.0;
}

void OptionsScene::musicOffClick( CCObject* pSender )
{
	imgTickMusic->setTextureRect(CCRect(0, 0, 0, imgTickMusic->getContentSize().height));
	s_musicVolume = 0.0;
}

void OptionsScene::soundOnClick( CCObject* pSender )
{
	imgTickSounds->setTextureRect(CCRect(0, 0, imgUnTickSounds->getContentSize().width, imgTickSounds->getContentSize().height));
	s_soundVolume = 1.0;
}

void OptionsScene::soundOffClick( CCObject* pSender )
{
	imgTickSounds->setTextureRect(CCRect(0, 0, 0, imgTickSounds->getContentSize().height));
	s_soundVolume = 0.0;
}

void OptionsScene::resetCampaign( CCObject* pSender )
{

}







