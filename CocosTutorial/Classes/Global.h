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
    
    // Spriteタグ設定
    enum TagOfSprite{
        RUNNER_SPRITE = 0,
        COIN_SPRITE = 1,
        ROCK_SPRITE = 2
    };
};

#endif
