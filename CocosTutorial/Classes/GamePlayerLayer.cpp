#include "GamePlayerLayer.h"

USING_NS_CC;

Scene* GamePlayerLayer::createScene()
{
    // 'scene' はautoreleaseオブジェクト
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = GamePlayerLayer::create();
    
    // レイヤーをシーンの子として追加する。
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GamePlayerLayer::init()
{
    //////////////////////////////
    // 1. 最初に親クラスの初期化を行う
    if ( !Layer::init() ){ return false; }
    
    // 2. 主人公のスプライトを作成する
    auto spriteRunner = Sprite::create("runner.png");
    
    // 3. 主人公の位置を設定する。
    spriteRunner->setPosition(Vec2(80,85));
    
    // 4. 移動アクションを作成する
    auto actionTo = MoveTo::create(2, Vec2(300,85));
    spriteRunner->runAction(actionTo);
    addChild(spriteRunner);
    
    return true;
}

