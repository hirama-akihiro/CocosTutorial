#ifndef __PLAY_SCENE_H__
#define __PLAY_SCENE_H__

#include "cocos2d.h"

class PlayScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    
    virtual bool init();
    virtual void update(float dt);
    virtual bool initPhysics();
    
    virtual bool onCollisionBegin(cocos2d::PhysicsContact &contact);
    
    // 削除するスプライト
    cocos2d::Vector<Node*> shapesToRemove;
    
    // implement the "static create()" method manually
    CREATE_FUNC(PlayScene);
};

#endif // __PLAY_SCENE_H__
