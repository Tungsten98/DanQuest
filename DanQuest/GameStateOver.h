//
//  GameStateOver.h
//  DanQuest
//
//  Created by 17xiangyangt on 8/4/15.
//  Copyright (c) 2015 Tang. All rights reserved.
//

#ifndef __DanQuest__GameStateOver__
#define __DanQuest__GameStateOver__

#include <SFML/Graphics.hpp>

#include "GameState.h"
#include "GameStateStart.h"
#include "GameStatePlaying.h"

class GameStateOver : public GameState
{
private:
    sf::View view;
    void reloadGame();
    void returnToMain();
    void gotoHighScores();
    
    sf::Clock interactClock;
    
    //add an interface that pops up for the user to enter his/her name (3 characters) when s/he achieves a new high score
    
public:
    GameStateOver(Game* game, const int score);
    
    void draw(const float dt);
    void update(const float dt);
    void handleInput();
};

#endif /* defined(__DanQuest__GameStateOver__) */
