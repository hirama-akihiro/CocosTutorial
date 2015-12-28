#ifndef __BACKGROUND_LAYER_H__
#define __BACKGROUND_LAYER_H__

#include "cocos2d.h"

class BackGroundLayer : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    
    virtual bool init();
    virtual void update(float dt);
    
    // 背景マップ1
    cocos2d::TMXTiledMap* map00;
    // 背景マップ2
    cocos2d::TMXTiledMap* map01;
    // マップの幅
    float mapWidth;
    // 表示中のマップのインデックス
    int mapIndex;
    
    bool checkAndReload(float eyeX);
    
    // implement the "static create()" method manually
    CREATE_FUNC(BackGroundLayer);
};

#endif // __BACKGROUND_LAYER_H__
