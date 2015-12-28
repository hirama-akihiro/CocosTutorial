#include "StatusLayer.h"

USING_NS_CC;

Scene* StatusLayer::createScene()
{
    // 'scene' はautoreleaseオブジェクト
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = StatusLayer::create();
    
    // レイヤーをシーンの子として追加する。
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool StatusLayer::init()
{
    //////////////////////////////
    // 1. 最初に親クラスの初期化を行う
    if ( !Layer::init() ){ return false; }
    
    // 2. 画面サイズを取得する
    Size visibleSize = Director::getInstance()->getVisibleSize();
    
    // 3. ラベルを作成する
    labelCoin = Label::createWithSystemFont("Coins:0", "Helvetica", 20);
    labelCoin->setColor(Color3B::BLACK);
    labelCoin->setPosition(Vec2(70, visibleSize.height - 20));
    addChild(labelCoin);
    
    labelMeter = Label::createWithSystemFont("0M", "Helvetica", 20);
    labelMeter->setPosition(Vec2(visibleSize.width - 70, visibleSize.height - 20));
    addChild(labelMeter);
    
    coins = 0;
    
    return true;
}

void StatusLayer::updateMeter(float px)
{
    std::stringstream ss;
    ss << (int)(px / 10) << "M";
    labelMeter->setString(ss.str());
}

void StatusLayer::addCoin(int num)
{
    // コインの数を加算する
    coins += num;
    // コイン数のラベルを更新する
    std::stringstream ss;
    ss << "Coins:" << coins;
    labelCoin->setString(ss.str());
}


