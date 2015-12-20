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
    
    // 2. スプライトフレームキャッシュを作成する
    SpriteFrameCache* cacher = SpriteFrameCache::getInstance();
    
    // 3. plistを読み込む
    cacher->addSpriteFramesWithFile("running.plist");
    Sprite* spriteRunner = Sprite::create();
    
    // 4. 主人公の位置を設定する
    spriteRunner->setPosition(Vec2(80,85));
    
    // 5. 移動アクションを作成する
    // 画像を入れつに読み込む
    Vector<SpriteFrame*> frames;
    for(int i = 0; i < 8; i++){
        std::stringstream ss;
        ss << "runner" << i << ".png";
        frames.pushBack(cacher->getSpriteFrameByName(ss.str()));
    }
    
    // 6. アニメーションを作成する
    Animation* anim = Animation::createWithSpriteFrames(frames, 0.1f);
    
    // 7. アニメーションアクションを作成する
    Animate* action = Animate::create(anim);
    
    // 8. 永久に繰り返すアクションを作成する
    RepeatForever* anime = RepeatForever::create(action);
    
    // アクションを実行する
    spriteRunner->runAction(anime);
    
    addChild(spriteRunner);
    
    /*
    // 2. 主人公のスプライトを作成する
    auto spriteRunner = Sprite::create("runner.png");
    
    // 3. 主人公の位置を設定する。
    spriteRunner->setPosition(Vec2(80,85));
    
    // 4. 移動アクションを作成する
    auto actionTo = MoveTo::create(2, Vec2(300,85));
    spriteRunner->runAction(actionTo);
    addChild(spriteRunner);
     */
    
    return true;
}

