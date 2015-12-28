#include "GameOverLayer.h"
#include "PlayScene.h"

USING_NS_CC;

bool GameOverLayer::init()
{
    log("isOKOK");
    if(!LayerColor::initWithColor(Color4B(0, 0, 0, 180))){ return false; }
    log("isOk");
    // ディレクタを取得する
    auto director = Director::getInstance();
    // ウィンドウのサイズを取得する
    auto windowSize = director->getWinSize();
    // 中心位置を計算する
    auto centerPos = Vec2(windowSize.width * 0.5, windowSize.height * 0.5);
    // リスタートメニューを項目作成する
    auto menuItemRestart = MenuItemSprite::create(Sprite::create("restart_n.png"),
                                                  Sprite::create("restart_s.png"),
                                                  CC_CALLBACK_1(GameOverLayer::onRestart,this));
    
    //　リスタートメニューを作成する
    auto menu = Menu::create(menuItemRestart, NULL);
    // メニューの位置を設定する
    menu->setPosition(centerPos);
    // メニューをレイヤーに追加する
    addChild(menu);
    
    return true;
}

void GameOverLayer::onRestart(Ref* pSender)
{
    // プレイシーンを作成する
    auto playScene = PlayScene::createScene();
    // ディレクタを取得する
    auto director = Director::getInstance();
    // 再開する
    director->resume();
    // シーンを変更する
    director->replaceScene(playScene);
}