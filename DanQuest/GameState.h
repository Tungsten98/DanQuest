//
//  GameState.h
//  DanQuest
//
//  Created by 17xiangyangt on 7/27/15.
//  Copyright (c) 2015 Tang. All rights reserved.
//

#ifndef __DanQuest__GameState__
#define __DanQuest__GameState__

#include "Game.h"

class Game;

class GameState
{
protected:
    Game* game;
    
public:
    
    virtual ~GameState(){}
    
    //abstract methods
    virtual void draw(const float dt) = 0;
    virtual void update(const float dt) = 0;
    virtual void handleInput() = 0;
};

#endif /* defined(__DanQuest__GameState__) */
