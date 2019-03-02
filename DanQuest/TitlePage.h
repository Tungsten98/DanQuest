//
//  TitlePage.h
//  DanQuest
//
//  Created by 17xiangyangt on 8/4/15.
//  Copyright (c) 2015 Tang. All rights reserved.
//

#ifndef __DanQuest__TitlePage__
#define __DanQuest__TitlePage__

#include <SFML/Graphics.hpp>

#include "Game.h"

class Game;

class TitlePage
{
private:
    Game* game;
    
    sf::Text title;
    sf::Text warmText;
    sf::Text coolText;
    sf::Text highScoreText;
    
    sf::RectangleShape warmRect;
    sf::RectangleShape coolRect;
    sf::RectangleShape highScoreRect;
    
    inline void resetColours();
    
public:
    bool showHighScores;
    
    TitlePage(Game* game);
    
    void draw(const float dt);
    void updateButton(sf::Vector2f mousePos);
    void transition(sf::Vector2f mousePos);
};

#endif /* defined(__DanQuest__TitlePage__) */
