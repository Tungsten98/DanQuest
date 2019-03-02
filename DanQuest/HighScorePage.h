//
//  HighScorePage.h
//  DanQuest
//
//  Created by 17xiangyangt on 8/5/15.
//  Copyright (c) 2015 Tang. All rights reserved.
//

#ifndef __DanQuest__HighScorePage__
#define __DanQuest__HighScorePage__

#include <SFML/Graphics.hpp>
#include <fstream>
#include <utility>
#include <string>
#include <vector>

#include "Game.h"

class Game;

class HighScorePage
{
private:
    Game* game;
    
    int prevGameScore;
    
    int numberBuffer[10];
    std::string nameBuffer[10];
    std::string modeBuffer[10];
    int scoreBuffer[10];
    
    sf::Text title;
    sf::Text subHeadings[6]; //number, name, score, number, name, score
    sf::Text rankNumbers[10];
    sf::Text gameModes[10];
    sf::Text winnerNames[10];
    sf::Text highScores[10];
    
    struct Table
    {
        sf::RectangleShape tableTitleRect;
        sf::RectangleShape tableBodyRect;
        sf::RectangleShape tableSubRect;
        sf::RectangleShape* lines[5];
    };
    Table table;
    
    sf::RectangleShape modeRect[10]; //to contain the mode texts
    
    sf::RectangleShape backRect;
    sf::Text backText;
    
    sf::RectangleShape deleteRect;
    sf::Text deleteText;
    
    //for the warning sign (when clearing scores)
    sf::RectangleShape warningBox;
    sf::RectangleShape noticeRect;
    sf::RectangleShape yesRect;
    sf::RectangleShape noRect;
    
    sf::Text noticeText;
    sf::Text yesText;
    sf::Text noText;
    
    inline void resetColours();
    void addEntry(std::string& newName, int newScore);
    
public:
    bool drawWarning;
    bool isExit;
    
    HighScorePage(Game* game);
    HighScorePage(Game* game, std::string& newName, int newScore);
    ~HighScorePage();
    
    void draw(const float dt);
    void updateButton(sf::Vector2f mousePos);
    void transition(sf::Vector2f mousePos);
    
    void loadHighScores(const std::string& filename);
    void saveHighScores(const std::string& filename);
    void clearScores(const std::string& filename);
};

#endif /* defined(__DanQuest__HighScorePage__) */
