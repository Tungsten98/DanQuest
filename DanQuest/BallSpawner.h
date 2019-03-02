//
//  BallSpawner.h
//  DanQuest
//
//  Created by 17xiangyangt on 7/28/15.
//  Copyright (c) 2015 Tang. All rights reserved.
//

#ifndef __DanQuest__BallSpawner__
#define __DanQuest__BallSpawner__

#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <cmath>
#include <ctime>
#include <vector>
#include <map>
#include <string>

#include "Ball.h"
#include "Game.h"

class Game;

class BallSpawner
{
private:
    const int MAX_BALL_NUM = 40;
    int warmSpawned, coolSpawned;
    
    float mainLifeSpans[6];
    const float otherLifeSpan = 15.0f;
    float spawnRate;
    
    //to assist with the spawning algorithm
    int pass = 1;
    
    std::map<std::string, sf::Color> colourMap;
    Game* game;
    
    sf::Clock spawnClock;
    
    //check if the player has lost
    bool lost;
    
    //For time limit
    int minutes;
    float seconds;
    sf::Clock gameTimeClock;
    std::string changeTimeString();
    
public:
    
    enum ColourMode
    {
        WARM,
        COOL
    };
    ColourMode activeMode;
    
    struct Colours
    {
        enum WarmColours
        {
            YELLOW = 1,
            YELLOW_ORANGE,
            ORANGE,
            ORANGE_VERMILLION,
            VERMILLION,
            RED
        };
        enum CoolColours
        {
            LIME = 1,
            GREEN,
            TURQUOISE,
            CYAN,
            AZURE,
            BLUE
        };
    };
    
    Colours::WarmColours warmColours;
    Colours::CoolColours coolColours;
    
    std::vector<Ball*> balls;
    
    //keep track of the score
    int score = 0;
    
    //Text to print the score onto the background
    sf::Text scoreText;
    sf::Text timeText;
    
    BallSpawner(Game* game);
    ~BallSpawner();
    
    void spawnBall();
    void drawEntities();
    void deleteBalls();
    void moveBalls(const float dt);
    void clickBall(sf::Vector2f mousePos);
    void updateTime();
    bool hasLost();
};

#endif /* defined(__DanQuest__BallSpawner__) */
