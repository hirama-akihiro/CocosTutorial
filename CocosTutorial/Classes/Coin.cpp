#include "Coin.h"
#include "Global.h"

USING_NS_CC;

Coin* Coin::create(Layer *layer, Vec2 pos)
{
    Coin* pRet = new Coin();
    
    if(pRet && pRet->init(layer, pos)){
        pRet->autorelease();
        return pRet;
    }else{
        delete pRet;
        return pRet = NULL;
    }
}

bool Coin::init(Layer *layer, Vec2 pos)
{
    if(!Node::init()){ return false; }
    
    // スプライトを作成する
    sprite = Sprite::create("coin0.png");
    // タグを設定する
    sprite->setTag(Global::TagOfSprite::COIN_SPRITE);
    // スプライトのサイズを取得する
    Size contentSize = sprite->getContentSize();
    // スプライトの位置を設定する
    sprite->setPosition(pos);
    
    // アニメーションを作成する
    Vector<SpriteFrame*> animFrames;
    // スプライトフレームキャッシュを作成する
    SpriteFrameCache* cache = SpriteFrameCache::getInstance();
    
    // コインの回転アクションを作成する
    // 画像を配列に取り込む
    for(int i = 0; i < 8; ++i){
        std::stringstream ss;
        ss << "coin" << i << ".png";
        auto frame = cache->getSpriteFrameByName(ss.str());
        animFrames.pushBack(frame);
    }
    
    // アニメーションを作成する
    auto animation = Animation::createWithSpriteFrames(animFrames, 0.1f);
    // 永久に繰り返すアクションを作成する
    auto action = RepeatForever::create(Animate::create(animation));
    // アクションを実行するようにする
    sprite->runAction(action);
    
    // デフォルトのマテリアルを作成する
    auto material = PHYSICSBODY_MATERIAL_DEFAULT;
    // 密度を設定する
    material.density = 0.0f;
    // 反発係数を設定する
    material.restitution = 0.0f;
    // 摩擦係数を設定する
    material.friction = 0.0f;
    
    // 半径を計算する
    float radius = 0.95f * contentSize.width * 0.5f;
    // 円の剛体を作成する
    auto body = PhysicsBody::createCircle(radius, material);
    // 質量を設定する
    body->setMass(0.00000000000000001);
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