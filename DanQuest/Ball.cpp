//
//  Ball.cpp
//  DanQuest
//
//  Created by 17xiangyangt on 7/28/15.
//  Copyright (c) 2015 Tang. All rights reserved.
//

#include "Ball.h"

Ball::Ball(sf::Texture& texture, sf::Color& colour, int points, float speed)
{
    this->sprite.setTexture(texture);
    this->sprite.setColor(colour);
    this->boundingCircle.setRadius(ballRadius);
    this->pointsToGive = points;
    this->speed = speed;
    
    this->sprite.setOrigin(float(this->sprite.getTextureRect().width) * 0.5f, float(this->sprite.getTextureRect().height) * 0.5f);
    
    //initialise an angle
    do
    {
        //change the angle and convert to radians (cmath works with radians)
        this->ballAngle = (std::rand() % 360) * Pi / 180;
        
    } while (std::abs(std::cos(this->ballAngle)) < 0.3f || std::abs(std::cos(this->ballAngle)) > 0.8f);
    
    //initialise a spawning position
    do
    {
        this->sprite.setPosition(sf::Vector2f(std::rand() % MAX_WIDTH, std::rand() % MAX_HEIGHT));
        
    } while (this->sprite.getPosition().x < MIN_WIDTH || this->sprite.getPosition().x > MAX_WIDTH ||
             this->sprite.getPosition().y < MIN_HEIGHT || this->sprite.getPosition().y > MAX_HEIGHT);
    
    this->boundingCircle.setPosition(this->sprite.getPosition());
    this->lifeTime.restart();
}

Ball::~Ball(){}

bool Ball::clicked(sf::Vector2f mousePos)
{
    if (mousePos.x > this->boundingCircle.getPosition().x - ballRadius &&
        mousePos.x < this->boundingCircle.getPosition().x + ballRadius &&
        mousePos.y > this->boundingCircle.getPosition().y - ballRadius &&
        mousePos.y < this->boundingCircle.getPosition().y + ballRadius)
    {
        return true;
    }
    else
        return false;
}

void Ball::move(const int width, const int height, const float dt)
{
    //check collisions against the walls
    if (this->boundingCircle.getPosition().x - ballRadius <= Wall::wallSideSize) //problem
    {
        ballAngle = Pi - ballAngle;
        this->sprite.setPosition(float(this->sprite.getPosition().x) + 0.1f, float(this->sprite.getPosition().y));
    }
    else if (this->boundingCircle.getPosition().x + ballRadius >= width - Wall::wallSideSize) //problem
    {
        ballAngle = Pi - ballAngle;
        this->sprite.setPosition(float(this->sprite.getPosition().x) - 0.1f, float(this->sprite.getPosition().y));
    }
    if (this->boundingCircle.getPosition().y - ballRadius <= Wall::wallSideSize)
    {
        ballAngle = -ballAngle;
        this->sprite.setPosition(float(this->sprite.getPosition().x), float(this->sprite.getPosition().y) + 0.1f);
    }
    else if (this->boundingCircle.getPosition().y + ballRadius >= height - Wall::wallSideSize)
    {
        ballAngle = -ballAngle;
        this->sprite.setPosition(float(this->sprite.getPosition().x), float(this->sprite.getPosition().y) - 0.1f);
    }
    
    this->sprite.move(std::cos(ballAngle) * this->speed * dt, std::sin(ballAngle) * this->speed * dt);
    this->boundingCircle.setPosition(this->sprite.getPosition());
}