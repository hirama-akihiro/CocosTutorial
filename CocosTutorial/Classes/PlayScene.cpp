#include "PlayScene.h"
#include "BackGroundLayer.h"
#include "GamePlayerLayer.h"
#include "GameOverLayer.h"
#include "StatusLayer.h"
#include "Global.h"

USING_NS_CC;

Scene* PlayScene::createScene()
{
    // 物理空間の付いたシーンを作成する
    Scene* scene = Scene::createWithPhysics();
    
    // 物理空間を取り出す
    PhysicsWorld* world = scene->getPhysicsWorld();
    
    // 重力を設置する
    world->setGravity(Vec2(0, -350));
    
    // デバッグの為にオブジェクトの衝突判定領域を表示する
    world->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    
    // 'layer'はautoreleaseオブジェクト
    Layer* layer = PlayScene::create();
    
    // レイヤーをシーンのことして追加する
    scene->addChild(layer);
    
    // シーンを返す
    return scene;
}

// on "init" you need to initialize your instance
bool PlayScene::init()
{
    //////////////////////////////
    // 1. 最初に親クラスの初期化を行う
    if ( !Layer::init() ){ return false; }
    getEventDispatcher()->removeAllEventListeners();
    
    // 物理エンジンを初期化する
    initPhysics();
    
    // 背景レイヤーを作成する
    auto backgroundLayer = BackGroundLayer::create();
    backgroundLayer->setTag(Global::TagOfLayer::BACKGROUND_LAYER);
    addChild(backgroundLayer);
    
    // ゲームプレイヤーレイヤーを作成する
    auto gameplayerLayer = GamePlayerLayer::create();
    gameplayerLayer->setTag(Global::TagOfLayer::GAMEPLAY_LAYER);
    addChild(gameplayerLayer);
    
    // ステータスレイヤーを作成する
    auto statusLayer = StatusLayer::create();
    statusLayer->setTag(Global::TagOfLayer::STATUS_LAYER);
    addChild(statusLayer);
    
    // フレーム毎にupdate関数を呼び出す
    scheduleUpdate();
    
    return true;
}

bool PlayScene::initPhysics()
{
    // 床を作成する
    Node* wallBottom = Node::create();
    // 床をシーンに追加する
    addChild(wallBottom);
    
    // アンカーポイントを左下にする
    wallBottom->setAnchorPoint(Vec2::ZERO);
    // 位置を(0,0)にする
    wallBottom->setPosition(Vec2::ZERO);
    // 左右方向に大きなサイズにする
    wallBottom->setContentSize(Size(480, Global::g_groundHeight));
    
    // デフォルトのマテリアルを作成する
    PhysicsMaterial material = PHYSICSBODY_MATERIAL_DEFAULT;
    // 密度を設定する
    material.density = 1.0f;
    // 反発係数を設定する
    material.restitution = 0.0f;
    // 摩擦係数を設定する
    material.friction = 0.0f;
    // 剛体を作成する
    PhysicsBody* body = PhysicsBody::createBox(wallBottom->getContentSize());
    // 重力の影響を受けない
    body->setDynamic(false);
    // 衝突する
    body->setContactTestBitmask(true);
    
    // スプライトに剛体を関連付ける
    wallBottom->setPhysicsBody(body);
    
    // プレイヤーとオブジェクトとの衝突判定を作成してディスパッチャーに追加する
    auto collisionCoinListener = EventListenerPhysicsContact::create();
    collisionCoinListener->onContactBegin = CC_CALLBACK_1(PlayScene::onCollisionBegin, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(collisionCoinListener, this);

    return true;
}

void PlayScene::update(float dt)
{
    // ゲームプレイヤーを取得する
    GamePlayerLayer* gameplayLayer = (GamePlayerLayer*)this->getChildByTag(Global::TagOfLayer::GAMEPLAY_LAYER);
    // 最初からの移動量を取得する
    float eyeX = gameplayLayer->getEyeX();
    // 位置を設定する
    gameplayLayer->setPosition(-eyeX, 0);
    
    // 背景レイヤーを取得する
    BackGroundLayer* backgroundLayer = (BackGroundLayer*)this->getChildByTag(Global::TagOfLayer::BACKGROUND_LAYER);
    // 位置を設定する
    backgroundLayer->setPosition(-eyeX, 0);
    
    // 不要になったスプライトを背景レイヤーから削除します
    for (int i = 0; i < shapesToRemove.size(); ++i) {
        // 形状を取得する
        auto node = shapesToRemove.at(i);
        // 背景レイヤーを取得する
        backgroundLayer->removeChild(node);
    }
    // 消すオブジェクトのリストクリアする
    shapesToRemove.clear();
}

bool PlayScene::onCollisionBegin(PhysicsContact &contact)
{
    // 1つ目の衝突形状を取得する
    auto shapeA = contact.getShapeA();
    auto nodeA = shapeA->getBody()->getNode();

    // 2つ目の衝突形状を取得する
    auto shapeB = contact.getShapeB();
    auto nodeB = shapeB->getBody()->getNode();
    
    log("contact a = %d b = %d", nodeA->getTag(), nodeB->getTag());
    
    if(nodeA->getTag() < 0 || nodeB->getTag() < 0){ return true; }
    
    // 衝突したオブジェクトがコインなら削除リストに追加する
    if(nodeA->getTag() == Global::TagOfSprite::COIN_SPRITE){
        shapesToRemove.pushBack(nodeA);
        // ステータスレイヤーを取得する
        auto statusLayer = (StatusLayer*)getChildByTag(Global::TagOfLayer::STATUS_LAYER);
        // ステータスレイヤーでコインの数を更新する
        statusLayer->addCoin(1);
    }else if(nodeB->getTag() == Global::TagOfSprite::COIN_SPRITE){
        shapesToRemove.pushBack(nodeB);
        // ステータスレイヤーを取得する
        auto statusLayer = (StatusLayer*)getChildByTag(Global::TagOfLayer::STATUS_LAYER);
        // ステータスレイヤーでコインの数を更新する
        statusLayer->addCoin(1);
    }else if(nodeA->getTag() == Global::TagOfSprite::ROCK_SPRITE
             || nodeB->getTag() == Global::TagOfSprite::ROCK_SPRITE){
        log("==game over");
        // ディレクタを取得する
        auto director = Director::getInstance();
        // 停止する
        director->pause();
        // ゲームオーバレイヤーを作成する
        auto gameOverLayer = GameOverLayer::create();
        // ゲームオーバレイヤーをシーンに追加する
        addChild(gameOverLayer);
    }
    
    return true;
}



