#ifndef __STATUS_LAYER_H__
#define __STATUS_LAYER_H__

#include "cocos2d.h"

class StatusLayer : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    
    virtual bool init();
    
    // コイン数のラベル
    cocos2d::Label* labelCoin;
    // プレイヤー移動距離のラベル
    cocos2d::Label* labelMeter;
    // コインの数
    int coins;
    
    void updateMeter(float px);
    void addCoin(int num);
    
    // implement the "static create()" method manually
    CREATE_FUNC(StatusLayer);
};

#endif // __STATUS_LAYER_H__
