#include "PlayScene.h"
#include "BackGroundLayer.h"
#include "GamePlayerLayer.h"
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
    
    // 物理エンジンを初期化する
    initPhysics();
    
    // 2. 3つのレイヤーを追加する
    auto backgroundLayer = BackGroundLayer::create();
    addChild(backgroundLayer);
    auto gameplayerLayer = GamePlayerLayer::create();
    addChild(gameplayerLayer);
    auto statusLayer = StatusLayer::create();
    addChild(statusLayer);
    
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
    material.restitution = 1.0f;
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
    
    return true;
}




