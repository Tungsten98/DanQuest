//
//  Game.h
//  DanQuest
//
//  Created by 17xiangyangt on 7/27/15.
//  Copyright (c) 2015 Tang. All rights reserved.
//

#ifndef __DanQuest__Game__
#define __DanQuest__Game__

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <stack>
#include <vector>
#include <map>

#include "GameState.h"
#include "TextureManager.h"
#include "FontManager.h"
#include "ResourcePath.hpp"
#include "Wall.h"
#include "TitlePage.h"
#include "BallSpawner.h"
#include "GameOverPage.h"
#include "HighScorePage.h"

class GameState;
class BallSpawner;
class TitlePage;
class GameOverPage;
class HighScorePage;

class Game
{
private:
    std::map<std::string, sf::Color> colourMap;
    
    void loadTextures();
    void loadFonts();
    void loadWalls();
    
public:
    const int gameWidth = 800, gameHeight = 640;
    
    //colours: warm or cool theme
    enum ColourMode
    {
        WARM,
        COOL,
        DEFAULT
    };
    
    ColourMode colourMode;
    void setBackgroundColour(ColourMode mode);
    
    std::stack<GameState*> gameStates;
    sf::RenderWindow window;
    TextureManager texmgr;
    FontManager fontmgr;
    
    TitlePage* titlePage;
    BallSpawner* ballSpawner;
    GameOverPage* gameOverPage;
    HighScorePage* highScorePage;
    
    sf::Sprite background;
    std::vector<Wall> walls;
    
    Game();
    ~Game();
    
    void pushState(GameState* state);
    void popState();
    void changeState(GameState* state);
    GameState* peekState();
    void gameLoop();
};

#endif /* defined(__DanQuest__Game__) */
