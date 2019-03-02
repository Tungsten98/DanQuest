//
//  TextureManager.cpp
//  DanQuest
//
//  Created by 17xiangyangt on 7/27/15.
//  Copyright (c) 2015 Tang. All rights reserved.
//

#include "TextureManager.h"

void TextureManager::loadTexture(const std::string& name, const std::string& filename)
{
    //load the texture
    sf::Texture tex;
    tex.loadFromFile(filename);
    
    //add it to the texture dictionary
    this->textures[name] = tex;
    
    return;
}

sf::Texture& TextureManager::getRef(const std::string& texname)
{
    return this->textures.at(texname);
}