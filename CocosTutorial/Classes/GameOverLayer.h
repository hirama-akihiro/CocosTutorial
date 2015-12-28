#ifndef __GameOverLayer_H_
#define __GameOverLayer_H_

#include "cocos2d.h"

class GameOverLayer : public cocos2d::LayerColor
{
public:
    virtual bool init();
    
    CREATE_FUNC(GameOverLayer);
    
private:
    void onRestart(Ref* pSender);
};

#endif
