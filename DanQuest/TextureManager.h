//
//  TextureManager.h
//  DanQuest
//
//  Created by 17xiangyangt on 7/27/15.
//  Copyright (c) 2015 Tang. All rights reserved.
//

#ifndef __DanQuest__TextureManager__
#define __DanQuest__TextureManager__

#include <SFML/Graphics.hpp>
#include <string>
#include <map>

class TextureManager
{
private:
    //dictionary of textures
    std::map<std::string, sf::Texture> textures;
    
public:
    //constructor
    TextureManager(){}
    
    //load a texture from a file
    void loadTexture(const std::string& name, const std::string& filename);
    
    //get a reference to a texture in the dictionary
    sf::Texture& getRef(const std::string& texname);
};

#endif /* defined(__DanQuest__TextureManager__) */
