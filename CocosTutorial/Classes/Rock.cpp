#include "Rock.h"
#include "Global.h"

USING_NS_CC;

Rock* Rock::create(Layer *layer, float posX)
{
    Rock* pRet = new Rock();
    
    if(pRet && pRet->init(layer, posX)){
        pRet->autorelease();
        return pRet;
    }else{
        delete pRet;
        return pRet = NULL;
    }
}

bool Rock::init(Layer *layer, float posX)
{
    if(!Node::init()){ return false; }
    
    // スプライトを作成する
    sprite = Sprite::create("rock.png");
    // タグを設定する
    sprite->setTag(Global::TagOfSprite::ROCK_SPRITE);
    // スプライトのサイズを取得する
    Size contentSize = sprite->getContentSize();
    // スプライトの位置を設定する
    sprite->setPosition(posX, contentSize.height * 0.5 + Global::g_groundHeight);
    
    // デフォルトのマテリアルを作成する
    auto material = PHYSICSBODY_MATERIAL_DEFAULT;
    // 密度を設定する
    material.density = 1.0f;
    // 反発係数を設定する
    material.restitution = 0.0f;
    // 摩擦係数を設定する
    material.friction = 0.0f;
    
    // 剛体を作成する
    auto body = PhysicsBody::createBox(contentSize, material);
    // 回転させない
    body->setRotationEnable(false);
    // 重力の影響を受けない
    body->setGravityEnable(false);
    // 衝突を検知する
    body->setContactTestBitmask(true);
    // 動く
    body->setDynamic(true);
    
    // スプライトに剛体を関連付ける
    sprite->setPhysicsBody(body);
    
    // レイヤーにスプライトを追加する
    layer->addChild(sprite, 1);
    
    return true;
}