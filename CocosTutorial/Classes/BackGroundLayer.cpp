#include "BackGroundLayer.h"

USING_NS_CC;

Scene* BackGroundLayer::createScene()
{
    // 'scene' はautoreleaseオブジェクト
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = BackGroundLayer::create();
    
    // レイヤーをシーンの子として追加する。
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool BackGroundLayer::init()
{
    //////////////////////////////
    // 1. 最初に親クラスの初期化を行う
    if ( !Layer::init() ){ return false; }
    
    // 2. 画面サイズを取得する
    Size visibleSize = Director::getInstance()->getVisibleSize();
    
    // 3. 中心を計算する
    Vec2 centerPos = visibleSize / 2;
    
    // 4. 背景画像を作成し、位置と中心を設定する。
    auto spriteBG = Sprite::create("PlayBG.png");
    spriteBG->setPosition(centerPos);
    addChild(spriteBG);
    
    return true;
}

