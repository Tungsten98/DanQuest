//
//  GameStateScores.h
//  DanQuest
//
//  Created by 17xiangyangt on 8/9/15.
//  Copyright (c) 2015 Tang. All rights reserved.
//

#ifndef __DanQuest__GameStateScores__
#define __DanQuest__GameStateScores__

#include <SFML/Graphics.hpp>
#include <string>

#include "GameState.h"
#include "GameStateStart.h"

class GameStateScores : public GameState
{
private:
    sf::View view;
    void goBack();
    
public:
    GameStateScores(Game* game);
    GameStateScores(Game* game, std::string& newName, int newScore);
    
    void draw(const float dt);
    void update(const float dt);
    void handleInput();
};

#endif /* defined(__DanQuest__GameStateScores__) */
