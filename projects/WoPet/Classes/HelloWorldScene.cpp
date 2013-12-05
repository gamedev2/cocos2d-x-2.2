#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
using namespace CocosDenshion;

HelloWorld::HelloWorld()
{
    //
}

HelloWorld::~HelloWorld()
{
    exitScene();
}

CCScene* HelloWorld::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    HelloWorld *layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

CCSprite *spriteTicketMove = NULL;

void HelloWorld::sprite_fly_tick(float interval)
{
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

    if (spriteTicketMove == NULL)
        return;
    if (!spriteTicketMove->isRunning())
        return;

    CCPoint pt = spriteTicketMove->getPosition();
    if (pt.x > origin.x + visibleSize.width)
        pt.x = origin.x;
    else
        pt.x = pt.x + 0.0f;

    spriteTicketMove->setPositionX(pt.x);

    static const float minScale = 1.0f, maxScale = 1.0f;

    static int dir = 1;
    static const float fSetp = 0.003f;
    float scale = spriteTicketMove->getScale();
    if ((scale - maxScale) >= 0.0f) {
        scale = maxScale;
        dir = -dir;
    }
    else if ((scale - minScale) <= 0.0f) {
        scale = minScale;
        dir = -dir;
    }
    if (dir > 0)
        scale += fSetp;
    else
        scale -= fSetp;

    spriteTicketMove->setScale(scale);
}

CCSprite *spriteTicketMove2 = NULL;

void HelloWorld::sprite_fly_tick2(float interval)
{
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

    if (spriteTicketMove2 == NULL)
        return;
    if (!spriteTicketMove2->isRunning())
        return;

    CCPoint pt = spriteTicketMove2->getPosition();
    if (pt.x > origin.x + visibleSize.width)
        pt.x = origin.x;
    else
        pt.x = pt.x + 0.0f;

    spriteTicketMove2->setPositionX(pt.x);

    static const float minScale = 1.0f, maxScale = 1.0f;

    static int dir = 1;
    static const float fSetp = 0.003f;
    float scale = spriteTicketMove2->getScale();
    if ((scale - maxScale) >= 0.0f) {
        scale = maxScale;
        dir = -dir;
    }
    else if ((scale - minScale) <= 0.0f) {
        scale = minScale;
        dir = -dir;
    }
    if (dir > 0)
        scale += fSetp;
    else
        scale -= fSetp;

    spriteTicketMove2->setScale(scale);
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
                                        "CloseNormal.png",
                                        "CloseSelected.png",
                                        this,
                                        menu_selector(HelloWorld::menuCloseCallback));
    
    if (pCloseItem != NULL)
    {
        pCloseItem->setPosition(ccp(origin.x + visibleSize.width - pCloseItem->getContentSize().width/2 ,
                                origin.y + pCloseItem->getContentSize().height/2));

        // create menu, it's an autorelease object
        CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
        if (pMenu != NULL)
        {
            pMenu->setPosition(CCPointZero);
            this->addChild(pMenu, 1);
        }
    }

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    CCLabelTTF* pLabel = CCLabelTTF::create("Hello World", "Arial", 24);
    
    if (pLabel != NULL)
    {
        // position the label on the center of the screen
        pLabel->setPosition(ccp(origin.x + visibleSize.width/2,
                                origin.y + visibleSize.height - pLabel->getContentSize().height));

        // add the label as a child to this layer
        this->addChild(pLabel, 1);
    }

    // add "HelloWorld" splash screen"
    //CCSprite* pSprite = CCSprite::create("HelloWorld.png");
    CCSprite* pSprite = CCSprite::create("assets/bg/wow_bg2s.png");
    if (pSprite != NULL)
    {
        // position the sprite on the center of the screen
        pSprite->setPosition(ccp(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

        CCRect recBG = pSprite->getTextureRect();
        float fWidth  = (int)(recBG.getMaxX() - recBG.getMinX());
        float fHeight = (int)(recBG.getMaxY() - recBG.getMinY());
        fWidth = pSprite->getContentSize().width;
        fHeight = pSprite->getContentSize().height;

        pSprite->setScaleX(1024.0 / fWidth);
        pSprite->setScaleY(640.0 / fHeight);

        // add the sprite as a child to this layer
        this->addChild(pSprite, 0);
    }

    // 载入 Sprite Sheet
    CCSpriteFrameCache *frameCache = CCSpriteFrameCache::sharedSpriteFrameCache();
    if (frameCache != NULL)
    {
        frameCache->addSpriteFramesWithFile("pngs/Wop-Onyxian0.plist", "pngs/Wop-Onyxian0.png");

        // 构造一个帧动画序列 Onyxian Whelpling_01.png -> Onyxian Whelpling_12.png
        CCArray *framesArray = CCArray::create();
        CCString frameName;
        for (int i = 0; i < 12; ++i)
        {
            frameName.initWithFormat("pngs/Onyxian Whelpling_%02d.png", i + 1);
            CCSpriteFrame *frame = frameCache->spriteFrameByName(frameName.getCString());
            if (frame != NULL)
                framesArray->addObject(frame);
        }

        // 创建 CCSprite 对象
        CCSpriteFrame *firstFrame = (CCSpriteFrame *)framesArray->objectAtIndex(0);
        if (firstFrame != NULL)
        {   
            CCSprite *sprite = CCSprite::createWithSpriteFrame(firstFrame);
            if (sprite != NULL)
            {
                // 在 CCSprite 之上播放动画（用 1.2 秒播放完 12 帧）
                CCAnimation *animation = CCAnimation::createWithSpriteFrames(framesArray, 1.2f / (float)12);
                if (animation != NULL)
                {
                    sprite->runAction(CCRepeatForever::create(CCAnimate::create(animation)));
                    sprite->setPosition(ccp(150, visibleSize.height/2 + origin.y + 100));

                    spriteTicketMove = sprite;
                    
                    CCDirector::sharedDirector()->getScheduler()->scheduleSelector((SEL_SCHEDULE)&HelloWorld::sprite_fly_tick, (CCObject *)this, 0.0f, false);
                    //sprite->setScale(1.5);

                    // add the sprite as a child to this layer
                    this->addChild(sprite, 1000);
                }
            }
        }
    }

    // 载入 Sprite Sheet
    CCSpriteFrameCache *frameCache2 = CCSpriteFrameCache::sharedSpriteFrameCache();
    if (frameCache2 != NULL)
    {
        frameCache2->addSpriteFramesWithFile("pngs/WopetNew0.plist", "pngs/WopetNew0.png");

        // 构造一个帧动画序列 Onyxian Whelpling_01.png -> Onyxian Whelpling_12.png
        CCArray *framesArray = CCArray::create();
        CCString frameName;
        for (int i = 0; i < 12; ++i)
        {
            frameName.initWithFormat("pngs/Onyxian Whelpling_1_%02d.png", i + 1);
            CCSpriteFrame *frame = frameCache->spriteFrameByName(frameName.getCString());
            if (frame != NULL)
                framesArray->addObject(frame);
        }

        // 创建 CCSprite 对象
        CCSpriteFrame *firstFrame = (CCSpriteFrame *)framesArray->objectAtIndex(0);
        if (firstFrame != NULL)
        {   
            CCSprite *sprite = CCSprite::createWithSpriteFrame(firstFrame);
            if (sprite != NULL)
            {
                // 在 CCSprite 之上播放动画（用 1.2 秒播放完 12 帧）
                CCAnimation *animation = CCAnimation::createWithSpriteFrames(framesArray, 1.6f / (float)24);
                if (animation != NULL)
                {
                    sprite->runAction(CCRepeatForever::create(CCAnimate::create(animation)));
                    sprite->setPosition(ccp(150, visibleSize.height/2 + origin.y - 120));

                    spriteTicketMove2 = sprite;

                    CCDirector::sharedDirector()->getScheduler()->scheduleSelector((SEL_SCHEDULE)&HelloWorld::sprite_fly_tick2, (CCObject *)this, 0.0f, false);
                    //sprite->setScale(1.5);

                    // add the sprite as a child to this layer
                    this->addChild(sprite, 1000);
                }
            }
        }
    }

    // 播放背景音乐
    //CCComAudio* pAudio = (CCComAudio*)(pNode->getComponent("Audio"));
    //pAudio->playBackgroundMusic(pAudio->getFile(), pAudio->getIsLoop());

    SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(0.05f);
    SimpleAudioEngine::sharedEngine()->setEffectsVolume(0.1f);

    // play background music, preload effect
    //SimpleAudioEngine::sharedEngine()->playBackgroundMusic("music/++_12-String Tek.mp3", true);
    SimpleAudioEngine::sharedEngine()->playBackgroundMusic("music/33-Will to Survive.mp3", true);
    SimpleAudioEngine::sharedEngine()->preloadEffect("effect1.mp3");

    CCAudio *pAudio = CCAudio::sharedEngine();
    if (pAudio != NULL) {
        pAudio->play();
    }

    int nEffectId = SimpleAudioEngine::sharedEngine()->playEffect("effect1.mp3");
    SimpleAudioEngine::sharedEngine()->stopEffect(nEffectId);

    /*
    // 停止
    CCScheduler::sharedScheduler()->unscheduleSelector(schedule_selector(CDataInitNetModule::updateTimer), this);
    // 若CDataInitNetModule先释放掉，会导致cocos2d-x 刷新crash

    // 延迟调用
    CCDelayTime *delayAction = CCDelayTime::actionWithDuration(0.1f);
    CCCallFunc *callSelectorAction = CCCallFunc::actionWithTarget(this,
                                    callfunc_selector(CDataInitNetModule::informDelegateSuccess));
    // run the action
    this->runAction(CCSequence::actions(delayAction,
                                        callSelectorAction,
                                        NULL));
    // 若该类所在Node未加入场景中，该方法不能触发
    //*/

    return true;
}

void HelloWorld::exitScene()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)

    CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.", "Alert");

#else
    // Stop playing background music and all playing sound effects
    SimpleAudioEngine::sharedEngine()->stopAll();

    CCDirector::sharedDirector()->end();

  #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
  #endif

#endif
}

void HelloWorld::menuCloseCallback(CCObject* pSender)
{
    exitScene();
}
