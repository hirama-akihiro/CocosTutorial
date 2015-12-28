#include "BackGroundLayer.h"
#include "GamePlayerLayer.h"
#include "Global.h"

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
//    auto spriteBG = Sprite::create("PlayBG.png");
//    spriteBG->setPosition(centerPos);
//    addChild(spriteBG);
    
    // タイルマップ0をロードする
    map00 = TMXTiledMap::create("map00.tmx");
    // タイルマップ1をロードする
    map01 = TMXTiledMap::create("map01.tmx");
    
    // タイルマップの幅を取得する
    Size contentSize = map00->getContentSize();
    // タイルマップの幅を覚えておく
    mapWidth = contentSize.width;
    log("%f",mapWidth);
    
    // タイルマップ0の位置を(0,0)に設定する
    map00->setPosition(0, 0);
    // タイルマップ1の位置をタイルマップ0の右隣に設定する
    map01->setPosition(mapWidth, 0);
    
    // レイヤーに追加する
    addChild(map00);
    addChild(map01);
    
    // フレーム毎にupdate関数を呼び出す
    scheduleUpdate();
    
    return true;
}

void BackGroundLayer::update(float dt)
{
    // ゲームプレイヤーを取得する
    Node* parent = getParent();
    GamePlayerLayer* gameplayerLayer = (GamePlayerLayer*)parent->getChildByTag(Global::TagOfLayer::GAMEPLAY_LAYER);
    
    // 最初からの移動量を取得する
    float eyeX = gameplayerLayer->getEyeX();
    // 位置をチェックして再ロードする
    checkAndReload(eyeX);
}

bool BackGroundLayer::checkAndReload(float eyeX)
{
    // どちらのマップを使うか決める
    int newMapIndex = (int)(eyeX / mapWidth);
    if(mapIndex == newMapIndex){return false;}
    
    if(newMapIndex % 2 == 0){
        // マップが偶数番目ならマップ1をマップ0の右に位置付ける
        map01->setPositionX(mapWidth * (newMapIndex + 1));
    }else{
        // そうでないならマップ0をマップ1の右に位置付ける
        map00->setPositionX(mapWidth * (newMapIndex + 1));
    }
    
    // １つ目のマップを覚えておく
    mapIndex = newMapIndex;
    
    return true;
}


