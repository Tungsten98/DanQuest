//
//  GameOverPage.h
//  DanQuest
//
//  Created by 17xiangyangt on 8/5/15.
//  Copyright (c) 2015 Tang. All rights reserved.
//

#ifndef __DanQuest__GameOverPage__
#define __DanQuest__GameOverPage__

#include <SFML/Graphics.hpp>
#include <string>
#include <fstream>
#include <cctype>

#include "Game.h"

class Game;

class GameOverPage
{
private:
    Game* game;
    
    int finalScore;
    bool clickedInBox;
    bool toGame;
    bool toHighScores;
    
    sf::Text gameOverText;
    sf::Text finalScoreText;
    
    sf::Text warmText;
    sf::Text coolText;
    sf::Text mainMenuText;
    sf::RectangleShape warmRect;
    sf::RectangleShape coolRect;
    sf::RectangleShape mainMenuRect;
    
    inline void resetColours();
    std::string finalScoreString();
    
    sf::RectangleShape hsWrapperBox;
    sf::RectangleShape newHsRect;
    sf::RectangleShape textRect;
    sf::RectangleShape okRect;
    sf::RectangleShape clearNameRect;
    
    sf::Text congratsText;
    sf::Text newHsText;
    sf::Text enterNameText;
    std::string currentInput;
    sf::Text currentText;
    sf::Text okText;
    sf::Text clearNameText;
    
public:
    GameOverPage(Game* game, int score);
    
    void draw(const float dt);
    void updateButton(sf::Vector2f mousePos);
    void transition(sf::Vector2f mousePos);
    
    int getFinalScore() {return finalScore;}
    void setCurrentText(std::string& newText) {currentText.setString(newText);}
    std::string getCurrentText() {return currentInput;} //temporary
    //TO DO: create a new method that updates the current input internally, using the character from an external source (the GameStateOver page)
    void updateNameString (const sf::Uint32 unicodeKey);
    
    bool newHighScore;
    bool isClicked() {return clickedInBox;}
    bool continuePlay() {return toGame;}
    bool showHighScores() {return toHighScores;}
};

#endif /* defined(__DanQuest__GameOverPage__) */
