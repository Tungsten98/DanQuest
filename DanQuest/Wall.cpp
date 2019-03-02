//
//  Wall.cpp
//  DanQuest
//
//  Created by 17xiangyangt on 7/27/15.
//  Copyright (c) 2015 Tang. All rights reserved.
//

#include "Wall.h"

Wall::Wall(sf::Texture& texture, sf::Vector2i pos)
{
    this->sprite.setTexture(texture);
    
    this->colourMap.emplace("warm", sf::Color(255, 150, 150));
    this->colourMap.emplace("cool", sf::Color(150, 150, 255));
    this->colourMap.emplace("default", sf::Color(255, 140, 60));
    
    //set the default colour
    this->colourMode = ColourMode::DEFAULT;
    this->setColour(colourMode);
    
    this->position = pos;
    this->sprite.setPosition(sf::Vector2f(pos));
}

void Wall::setColour(ColourMode mode)
{
    if (mode == ColourMode::WARM)
    {
        this->sprite.setColor(this->colourMap.at("warm"));
    }
    else if (mode == ColourMode::COOL)
    {
        this->sprite.setColor(this->colourMap.at("cool"));
    }
    else
    {
        this->sprite.setColor(this->colourMap.at("default"));
    }
    
    return;
}

void Wall::draw(sf::RenderWindow& window, float dt)
{
    if (this->sprite.getTexture() != nullptr)
        window.draw(this->sprite);
    
    return;
}