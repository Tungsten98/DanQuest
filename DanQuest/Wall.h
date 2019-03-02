//
//  Wall.h
//  DanQuest
//
//  Created by 17xiangyangt on 7/27/15.
//  Copyright (c) 2015 Tang. All rights reserved.
//

#ifndef __DanQuest__Wall__
#define __DanQuest__Wall__

#include <SFML/Graphics.hpp>
#include <string>
#include <map>

class Wall
{
private:
    sf::Sprite sprite;
    sf::Vector2i position;
    
    std::map<std::string, sf::Color> colourMap;
    
public:
    const static int wallSideSize = 32;
    
    //colours: warm or cool theme
    enum ColourMode
    {
        WARM,
        COOL,
        DEFAULT
    };
    
    ColourMode colourMode;
    
    Wall(sf::Texture& texture, sf::Vector2i pos);
    
    void setColour(ColourMode mode);
    
    void draw (sf::RenderWindow& window, float dt);
};

#endif /* defined(__DanQuest__Wall__) */
