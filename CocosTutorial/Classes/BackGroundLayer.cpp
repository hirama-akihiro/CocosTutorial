#include "BackGroundLayer.h"
#include "GamePlayerLayer.h"
#include "Global.h"
#include "Coin.h"
#include "Rock.h"

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
    // 最初に親クラスの初期化を行う
    if ( !Layer::init() ){ return false; }
    
    // 画面サイズを取得する
    Size visibleSize = Director::getInstance()->getVisibleSize();
    
    // 中心を計算する
    Vec2 centerPos = visibleSize / 2;
    
    // タイルマップ0をロードする
    map00 = TMXTiledMap::create("map00.tmx");
    // タイルマップ1をロードする
    map01 = TMXTiledMap::create("map01.tmx");
    
    // タイルマップの幅を取得する
    Size contentSize = map00->getContentSize();
    // タイルマップの幅を覚えておく
    mapWidth = contentSize.width;
    
    // タイルマップ0の位置を(0,0)に設定する
    map00->setPosition(0, 0);
    // タイルマップ1の位置をタイルマップ0の右隣に設定する
    map01->setPosition(mapWidth, 0);
    
    // スプライトフレームキャッシュを作成する
    SpriteFrameCache* spriteFrameCache = SpriteFrameCache::getInstance();
    // スプライトシート(plistファイル)をSpriteFrameCacheクラスにロードする
    spriteFrameCache->addSpriteFramesWithFile("background.plist");
    
    // マップ0,1からオブジェクトをロードする
    loadObjects(map00, 0);
    loadObjects(map01, 1);
    
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
        // マップ1のオブジェクトをロードする
        loadObjects(map01, newMapIndex + 1);
    }else{
        // そうでないならマップ0をマップ1の右に位置付ける
        map00->setPositionX(mapWidth * (newMapIndex + 1));
        // マップ0のオブジェクトをロードする
        loadObjects(map00, newMapIndex + 1);
    }
    
    // 不要になったオブジェクトを削除する
    removeObjects(newMapIndex + 1);
    
    // １つ目のマップを覚えておく
    mapIndex = newMapIndex;
    
    return true;
}

void BackGroundLayer::loadObjects(TMXTiledMap *map, int mapIndex)
{
    // コインのオブジェクトグループを取得する
    TMXObjectGroup* coinGroup = map->getObjectGroup("coin");
    // コインオブジェクトの配列を取得する
    ValueVector coinArray = coinGroup->getObjects();
    // コインオブジェクトをリストに追加する
    for(int i = 0; i < coinArray.size(); ++i){
        // オブジェクトを取得する
        Value object = coinArray.at(i);
        // objectに設定されているプロパティなどを取得
        ValueMap objectInfo = object.asValueMap();
        // コインオブジェクトを作成する
        Coin* coin = Coin::create(this,
                                  Vec2(objectInfo.at("x").asFloat() + mapWidth * mapIndex,
                                       objectInfo.at("y").asFloat()));
        // コインオブジェクトのマップインデックスを設定する
        coin->setMapIndex(mapIndex);
        // コインオブジェクトをリストに追加する
        objects.pushBack(coin);
    }
    
    // 岩のオブジェクトグループを取得する
    TMXObjectGroup* rockGroup = map->getObjectGroup("rock");
    // 岩オブジェクトの配列を取得する
    ValueVector rockArray = rockGroup->getObjects();
    // 岩オブジェクトをリストに追加する
    for(int i = 0; i < rockArray.size(); ++i){
        // オブジェクトを取得する
        Value object = rockArray.at(i);
        // objectに設定されているプロパティなどを取得
        ValueMap objectInfo = object.asValueMap();
        // コインオブジェクトを作成する
        Rock* rock = Rock::create(this,objectInfo.at("x").asFloat() + mapWidth * mapIndex);
        // コインオブジェクトのマップインデックスを設定する
        rock->setMapIndex(mapIndex);
        // コインオブジェクトをリストに追加する
        objects.pushBack(rock);
    }
}

void BackGroundLayer::removeObjects(int mapIndex)
{
    for(int i = 0; i < objects.size(); ++i){
        // 削除するオブジェクトを取得する
        Node* obj = objects.at(i);
        if(obj->getTag() == Global::TagOfSprite::COIN_SPRITE){
            // コインの場合
            Coin* coin = (Coin*)obj;
            if(coin->getMapIndex() == mapIndex){
                coin->removeFromParent();
            }
        }else if(obj->getTag() == Global::TagOfSprite::ROCK_SPRITE){
            // 岩の場合
            Rock* rock = (Rock*)obj;
            if(rock->getMapIndex() == mapIndex){
                rock->removeFromParent();
            }
        }
    }
}
