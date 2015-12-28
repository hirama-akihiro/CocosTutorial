#ifndef __GLOBAL_H_
#define __GLOBAL_H_

class Global
{
public:
    // 地面の高さ
    static const float g_groundHeight;
    // プレイヤーの最初のX座標
    static const float g_runnerStartX;
    
    // レイヤータグ設定
    enum TagOfLayer{
        BACKGROUND_LAYER = 0,
        GAMEPLAY_LAYER = 1,
        STATUS_LAYER = 2
    };
};

#endif
