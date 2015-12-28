#ifndef __ROCK_H_
#define __ROCK_H_

#include "cocos2d.h"

class Rock : public cocos2d::Node
{
public:
    // マップインデックス
    int mapIndex;
    
private:
    // スプライト
    cocos2d::Sprite* sprite;
    
public:
    // インスタンスを生成する
    static Rock* create(cocos2d::Layer* layer, float posX);
    
    // 初期化する
    bool init(cocos2d::Layer* layer,float posX);
    
    // getter
    int getMapIndex(){ return mapIndex; }
    // setter
    void setMapIndex(int mapIndex){ this->mapIndex = mapIndex; }
};

#endif // __COIN_H_