//
//  FontManager.cpp
//  DanQuest
//
//  Created by 17xiangyangt on 8/3/15.
//  Copyright (c) 2015 Tang. All rights reserved.
//

#include "FontManager.h"

void FontManager::loadFont(const std::string& name, const std::string &filename)
{
    sf::Font font;
    font.loadFromFile(filename);
    
    this->fonts[name] = font;
    
    return;
}

sf::Font& FontManager::getRef(const std::string& fontname)
{
    return this->fonts.at(fontname);
}