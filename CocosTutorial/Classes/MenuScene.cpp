#include "MenuScene.h"

USING_NS_CC;

Scene* MenuScene::createScene()
{
    // 'scene' はautoreleaseオブジェクト
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = MenuScene::create();
    
    // レイヤーをシーンの子として追加する。
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool MenuScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() ){ return false; }
    
    // 2.画面サイズを取得する
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    // 3.中心を計算する
    auto centerPos = visibleSize / 2;
    
    // 4. 背景画像を選択し、位置と中心を設定する
    auto spriteBG = Sprite::create("helloBG.png");
    spriteBG->setPosition(centerPos);
    this->addChild(spriteBG);
    
    // 5.メニューのフォントサイズ
    MenuItemFont::setFontSize(60);
    
    // 6. メニューを作成しonPlayイベントコールバック関数を設定する
    auto menuItemPlay = MenuItemImage::create("start_n.png",
                                              "start_s.png",
                                              CC_CALLBACK_1(MenuScene::onPlay, this));
    
    auto menu = Menu::create(menuItemPlay, NULL);
    this->addChild(menu);
    
    return true;
    
    
    
    
    /*
    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.
    
    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(MenuScene::menuCloseCallback, this));
    
    closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));
    
    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
    
    /////////////////////////////
    // 3. add your codes below...
    
    // add a label shows "Hello World"
    // create and initialize a label
    
    auto label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);
    
    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));
    
    // add the label as a child to this layer
    this->addChild(label, 1);
    
    // add "MenuScene" splash screen"
    auto sprite = Sprite::create("HelloWorld.png");
    
    // position the sprite on the center of the screen
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    
    // add the sprite as a child to this layer
    this->addChild(sprite, 0);
    
    return true;
     */
}


void MenuScene::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

// メニュー項目が押された場合のコールバック関数
void MenuScene::onPlay(Ref* pSender)
{
    log("==onPlay clicked");
}
