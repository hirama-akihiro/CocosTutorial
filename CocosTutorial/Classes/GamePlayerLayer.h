#ifndef __GAMEPLAYER_LAYER_H__
#define __GAMEPLAYER_LAYER_H__

#include "cocos2d.h"

class GamePlayerLayer : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    
    virtual bool init();
    virtual void update(float dt);
    virtual bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
    
    float getEyeX();
    
    cocos2d::Sprite* spriteRunner;
    
    
    
    // implement the "static create()" method manually
    CREATE_FUNC(GamePlayerLayer);
};

#endif // __GAMEPLAYER_LAYER_H__
