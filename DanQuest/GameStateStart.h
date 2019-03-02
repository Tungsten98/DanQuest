//
//  GameStateStart.h
//  DanQuest
//
//  Created by 17xiangyangt on 7/27/15.
//  Copyright (c) 2015 Tang. All rights reserved.
//

#ifndef __DanQuest__GameStateStart__
#define __DanQuest__GameStateStart__

#include <SFML/Graphics.hpp>

#include "GameState.h"
#include "GameStatePlaying.h"
#include "GameStateScores.h"

class GameStateStart : public GameState
{
private:
    sf::View view;
    void loadGame();
    void loadHighScores();
    
public:
    GameStateStart(Game* game);
    void draw(const float dt);
    void update(const float dt);
    void handleInput();
};

#endif /* defined(__DanQuest__GameStateStart__) */
