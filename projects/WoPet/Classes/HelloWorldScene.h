#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

class CCAudio : public cocos2d::CCObject
{
public:
    CCAudio() {};
    virtual ~CCAudio() {};

    //static CCAudio *s_sharedAudioEngine = NULL;

    static CCAudio *sharedEngine() {
        static CCAudio s_sharedAudioEngine;
        return &s_sharedAudioEngine;
        /*
        if (s_sharedAudioEngine == NULL) {
            s_sharedAudioEngine = new CCAudio();
        }
        //*/
    };

    void play() { };
    void stop() { };
};

class HelloWorld : public cocos2d::CCLayer
{
public:
    HelloWorld();
    virtual ~HelloWorld();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // on exit scene
    void exitScene();

    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* scene();
    
    // a selector callback
    void menuCloseCallback(CCObject* pSender);

    void sprite_fly_tick(float interval);
    void sprite_fly_tick2(float interval);
    
    // implement the "static node()" method manually
    CREATE_FUNC(HelloWorld);
};

#endif // __HELLOWORLD_SCENE_H__
