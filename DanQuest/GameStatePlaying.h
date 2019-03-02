//
//  GameStatePlaying.h
//  DanQuest
//
//  Created by 17xiangyangt on 7/27/15.
//  Copyright (c) 2015 Tang. All rights reserved.
//

#ifndef __DanQuest__GameStatePlaying__
#define __DanQuest__GameStatePlaying__

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include "GameState.h"
#include "GameStateOver.h"

class GameStatePlaying : public GameState
{
private:
    sf::View gameView;
    void endGame();
    
public:
    GameStatePlaying(Game* game);
    
    void draw(const float dt);
    void update(const float dt);
    void handleInput();
};

#endif /* defined(__DanQuest__GameStatePlaying__) */
