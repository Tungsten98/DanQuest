//
//  FontManager.h
//  DanQuest
//
//  Created by 17xiangyangt on 8/3/15.
//  Copyright (c) 2015 Tang. All rights reserved.
//

#ifndef __DanQuest__FontManager__
#define __DanQuest__FontManager__

#include <SFML/Graphics.hpp>
#include <string>
#include <map>

class FontManager
{
private:
    std::map<std::string, sf::Font> fonts;
    
public:
    FontManager(){}
    void loadFont(const std::string& name, const std::string& filename);
    
    //returns a reference to the font on the map
    sf::Font& getRef(const std::string& fontname);
};

#endif /* defined(__DanQuest__FontManager__) */
