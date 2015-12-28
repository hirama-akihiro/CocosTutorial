#ifndef __COIN_H_
#define __COIN_H_

#include "cocos2d.h"

class Coin : public cocos2d::Node
{
public:
    // マップインデックス
    int mapIndex;
    
private:
    // スプライト
    cocos2d::Sprite* sprite;
    
public:
    // インスタンスを生成する
    static Coin* create(cocos2d::Layer* layer, cocos2d::Vec2 pos);
    
    // 初期化する
    bool init(cocos2d::Layer* layer,cocos2d::Vec2 pos);
    
    // getter
    int getMapIndex(){ return mapIndex; }
    // setter
    void setMapIndex(int mapIndex){ this->mapIndex = mapIndex; }
};

#endif // __COIN_H_