//
//  Ball.h
//  DanQuest
//
//  Created by 17xiangyangt on 7/28/15.
//  Copyright (c) 2015 Tang. All rights reserved.
//

#ifndef __DanQuest__Ball__
#define __DanQuest__Ball__

#include <SFML/Graphics.hpp>
#include <vector>
#include <cstdlib>
#include <cmath>
#include <ctime>

#include "Wall.h"

class Ball
{
private:
    constexpr const static double Pi = 3.14159;
    const static int MIN_WIDTH = 48, MIN_HEIGHT = 48;
    const static int MAX_WIDTH = 800 - 48;
    const static int MAX_HEIGHT = 640 - 48;
    constexpr const static float ballRadius = 16.0f;
    
public:
    //variables
    //number of points held
    int pointsToGive;
    
    //sprite representation of the ball
    sf::Sprite sprite;
    
    //bounding circle for checking clicks
    sf::CircleShape boundingCircle;
    
    sf::Clock lifeTime;
    
    float speed;
    float ballAngle;
    
    //methods
    Ball(sf::Texture& texture, sf::Color& colour, int points, float speed);
    ~Ball();
    
    bool clicked(sf::Vector2f mousePos);
    void move(const int height, const int width, const float dt);
};

#endif /* defined(__DanQuest__Ball__) */
