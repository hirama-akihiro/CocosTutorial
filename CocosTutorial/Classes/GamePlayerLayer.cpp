#include "GamePlayerLayer.h"
#include "StatusLayer.h"
#include "Global.h"
#include <SimpleAudioEngine.h>

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
    // 最初に親クラスの初期化を行う
    if ( !Layer::init() ){ return false; }
    
    // スプライトフレームキャッシュを作成する
    SpriteFrameCache* cacher = SpriteFrameCache::getInstance();
    
    // スプライトシート(plistファイル)をSpriteFrameCacheクラスにロードする
    cacher->addSpriteFramesWithFile("running.plist");
    
    // 走るアクションを作成する
    // 画像を配列に読み込む
    Vector<SpriteFrame*> frames;
    for(int i = 0; i < 8; i++){
        std::stringstream ss;
        ss << "runner" << i << ".png";
        frames.pushBack(cacher->getSpriteFrameByName(ss.str()));
    }
    
    // アニメーションを作成する
    Animation* anim = Animation::createWithSpriteFrames(frames, 0.1f);
    // アニメーションアクションを作成する
    Animate* action = Animate::create(anim);
    // 永久に繰り返すアクションを作成する
    RepeatForever* anime = RepeatForever::create(action);
    
    // 物理エンジンを通した主人公を作成する
    spriteRunner = Sprite::create();
    // スプライトのサイズを設定する
    spriteRunner->setContentSize(Size(62, 56));
    // スプライトのサイズを取得する
    Size contentSize = spriteRunner->getContentSize();

    // 走るアクションを実行する
    spriteRunner->runAction(anime);
    // スプライトの位置を設定する
    spriteRunner->setPosition(Vec2(Global::g_runnerStartX, Global::g_groundHeight + contentSize.height * 0.5));
    
    // ランナーをレイヤーに追加する
    addChild(spriteRunner);
    
    // デフォルトのマテリアルを作成する
    PhysicsMaterial material = PHYSICSSHAPE_MATERIAL_DEFAULT;
    // 密度を設定する
    material.density = 1.0f;
    // 反発係数を設定する
    material.restitution = 0.0f;
    // 摩擦係数を設定する
    material.friction = 0.0f;
    
    // 剛体を作成する
    PhysicsBody* body = PhysicsBody::createBox(Size(contentSize.width * 0.5, contentSize.height), material);
    
    // 重さを設定する
    body->setMass(10.0f);
    // 回転させるか
    body->setRotationEnable(false);
    // 重力の影響を受けるか
    body->setGravityEnable(true);
    // 衝突する
    body->setContactTestBitmask(true);
    // 重力の影響を受けるか
    body->setDynamic(true);
    // 撃力を与える
    body->applyImpulse(Vect(1000.0,0.0),Point(0, 0));
    
    // スプライトに剛体を関連付ける
    spriteRunner->setPhysicsBody(body);
    
    // プレイヤーにタグ付け
    spriteRunner->setTag(Global::TagOfSprite::RUNNER_SPRITE);
    
    // update関数が呼ばれるようにする
    scheduleUpdate();
    
    // シングルタッチイベントリスナーを作成する
    auto listener = EventListenerTouchOneByOne::create();
    // スワロータッチモードにするとonTouchBeganメソッドはタッチイベント他では使われない
    listener->onTouchBegan = CC_CALLBACK_2(GamePlayerLayer::onTouchBegan, this);
    // 優先度100でディスパッチャーに登録
    getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
    
    return true;
}

void GamePlayerLayer::update(float dt)
{
    // 親のオブジェクトを取得する
    auto parent = getParent();
    // ステータスレイヤーを取得する
    auto statusLayer = (StatusLayer*)(parent->getChildByTag(Global::TagOfLayer::STATUS_LAYER));
    // ステータスレイヤーで移動距離を更新する
    statusLayer->updateMeter(getEyeX());
    
    // プレイヤーの座標が地面以下に埋まった場合、地面の高さに戻す
    auto pos = spriteRunner->getPosition();
    auto size = spriteRunner->getContentSize();
    if(pos.y - size.height * 0.5 < Global::g_groundHeight){
        spriteRunner->setPosition(Vec2(pos.x, Global::g_groundHeight + size.height * 0.5));
    }
}

// ゲームプレイヤーの移動量を取得
float GamePlayerLayer::getEyeX()
{
    return spriteRunner->getPositionX() - Global::g_runnerStartX;
}

bool GamePlayerLayer::onTouchBegan(Touch *touch, Event *event)
{
    log("PlayScene::ccTouchBegin");
    // 上向きの撃力を与える
    spriteRunner->getPhysicsBody()->applyImpulse(Vect(0, 3000), Point::ZERO);
    
    // オーディオエンジンを取得する
    auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
    // ジャンプ音を鳴らす
    audio->playEffect("jump.mp3");
    
    return true;
}



