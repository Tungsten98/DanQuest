//
//  BallSpawner.cpp
//  DanQuest
//
//  Created by 17xiangyangt on 7/28/15.
//  Copyright (c) 2015 Tang. All rights reserved.
//

#include "BallSpawner.h"

BallSpawner::BallSpawner(Game* game)
{
    this->game = game;
    
    if (this->game->colourMode == Game::ColourMode::WARM)
    {
        this->activeMode = BallSpawner::ColourMode::WARM;
    }
    else if (this->game->colourMode == Game::ColourMode::COOL)
    {
        this->activeMode = BallSpawner::ColourMode::COOL;
    }
    
    //initialise the colourMap
    //
    //warm colours
    colourMap["red"] = sf::Color(255, 0, 0);
    colourMap["vermillion"] = sf::Color(255, 61, 0);
    colourMap["vermillion-orange"] = sf::Color(255, 101, 0);
    colourMap["orange"] = sf::Color(255, 146, 0);
    colourMap["yellow-orange"] = sf::Color(255, 181, 0);
    colourMap["yellow"] = sf::Color(255, 255, 0);
    
    //cool colours
    colourMap["lime"] = sf::Color(191, 255, 0);
    colourMap["green"] = sf::Color(0, 255, 0);
    colourMap["turquoise"] = sf::Color(0, 255, 191);
    colourMap["cyan"] = sf::Color(0, 255, 255);
    colourMap["azure"] = sf::Color(0, 191, 255);
    colourMap["blue"] = sf::Color(0, 0, 255);
    
    this->spawnRate = 3.0f;
    
    //initialise life spans
    mainLifeSpans[0] = 15.0f;
    mainLifeSpans[1] = 13.0f;
    mainLifeSpans[2] = 10.0f;
    mainLifeSpans[3] = 8.0f;
    mainLifeSpans[4] = 4.0f;
    mainLifeSpans[5] = 2.0f;
    
    this->score = 0;
    this->lost = false;
    
    this->scoreText.setFont(this->game->fontmgr.getRef("Consolas"));
    if (this->activeMode == BallSpawner::ColourMode::WARM)
        this->scoreText.setColor(sf::Color(255, 0, 0, 128));
    else if (this->activeMode == BallSpawner::ColourMode::COOL)
        this->scoreText.setColor(sf::Color(0, 0, 255, 128));
    this->scoreText.setString(std::to_string(score));
    this->scoreText.setCharacterSize(250);
    this->scoreText.setOrigin(this->scoreText.getGlobalBounds().width * 0.5f, this->scoreText.getGlobalBounds().height * 0.5f);
    this->scoreText.setPosition(sf::Vector2f(this->game->gameWidth * 0.5f - 12, this->game->gameHeight * 0.5f - 140));
    
    this->timeText.setFont(this->game->fontmgr.getRef("Consolas"));
    if (this->activeMode == BallSpawner::ColourMode::WARM)
        this->timeText.setColor(sf::Color(255, 0, 0, 128));
    else if (this->activeMode == BallSpawner::ColourMode::COOL)
        this->timeText.setColor(sf::Color(0, 0, 255, 128));
    this->timeText.setString(changeTimeString());
    this->timeText.setCharacterSize(50);
    this->timeText.setOrigin(this->timeText.getGlobalBounds().width * 0.5f, this->timeText.getGlobalBounds().height * 0.5f);
    this->timeText.setPosition(sf::Vector2f(this->game->gameWidth * 0.5f - 12, this->game->gameHeight * 0.5f + 100));
    
    this->minutes = 2;
    this->seconds = 0.0f;
    
    this->warmSpawned = 0;
    this->coolSpawned = 0;
    this->pass = 1;
    
    this->gameTimeClock.restart();
    this->spawnClock.restart();
}

BallSpawner::~BallSpawner()
{
    while (!balls.empty())
    {
        if (balls.back() != nullptr)
            delete balls.back();
        
        balls.pop_back();
    }
}

std::string BallSpawner::changeTimeString()
{
    std::string str;
    if (seconds < 10)
    {
        str = "Time left: " + std::to_string(this->minutes) + " : 0" + std::to_string((int)this->seconds);
    }
    else
    {
        str = "Time left: " + std::to_string(this->minutes) + " : " + std::to_string((int)this->seconds);
    }
    
    return str;
}

void BallSpawner::drawEntities()
{
    this->game->window.draw(this->scoreText);
    this->game->window.draw(this->timeText);
    if (!balls.empty())
    {
        for (auto ball : this->balls)
        {
            this->game->window.draw(ball->sprite);
        }
    }
}

void BallSpawner::spawnBall()
{
    std::srand(static_cast<unsigned int>(std::time(NULL)));
    
    std::map<Colours::WarmColours, std::string> warmMap;
    std::map<Colours::CoolColours, std::string> coolMap;
    
    //match the enums with the respective strings
    warmMap[Colours::WarmColours::RED] = "red";
    warmMap[Colours::WarmColours::VERMILLION] = "vermillion";
    warmMap[Colours::WarmColours::ORANGE_VERMILLION] = "vermillion-orange";
    warmMap[Colours::WarmColours::ORANGE] = "orange";
    warmMap[Colours::WarmColours::YELLOW_ORANGE] = "yellow-orange";
    warmMap[Colours::WarmColours::YELLOW] = "yellow";
    
    coolMap[Colours::CoolColours::LIME] = "lime";
    coolMap[Colours::CoolColours::GREEN] = "green";
    coolMap[Colours::CoolColours::TURQUOISE] = "turquoise";
    coolMap[Colours::CoolColours::CYAN] = "cyan";
    coolMap[Colours::CoolColours::AZURE] = "azure";
    coolMap[Colours::CoolColours::BLUE] = "blue";
    
    switch (this->pass)
    {
        case 1:
        {
            spawnRate = 3.0f;
            if (this->game->colourMode == Game::ColourMode::WARM)
            {
                if (spawnClock.getElapsedTime().asSeconds() >= spawnRate)
                {
                    this->balls.push_back(new Ball(this->game->texmgr.getRef("ball"), this->colourMap.at(warmMap.at(Colours::WarmColours::YELLOW)), 1, 200.0f));
                    this->spawnClock.restart();
                    ++this->pass;
                }
            }
            else if (this->game->colourMode == Game::ColourMode::COOL)
            {
                if (spawnClock.getElapsedTime().asSeconds() >= spawnRate)
                {
                    this->balls.push_back(new Ball(this->game->texmgr.getRef("ball"), this->colourMap.at(coolMap.at(Colours::CoolColours::LIME)), 1, 200.0f));
                    this->spawnClock.restart();
                    ++this->pass;
                }
            }
        }
            break;
     
        case 2:
        {
            spawnRate = 2.5f;
            if (warmSpawned + coolSpawned < 2)
            {
                if (this->game->colourMode == Game::ColourMode::WARM)
                {
                    if (spawnClock.getElapsedTime().asSeconds() >= spawnRate)
                    {
                        this->balls.push_back(new Ball(this->game->texmgr.getRef("ball"), this->colourMap.at(warmMap.at(Colours::WarmColours::YELLOW)), 1, 200.0f));
     
                        ++warmSpawned;
                        this->spawnClock.restart();
                    }
                }
                else if (this->game->colourMode == Game::ColourMode::COOL)
                {
                    if (spawnClock.getElapsedTime().asSeconds() >= spawnRate)
                    {
                        this->balls.push_back(new Ball(this->game->texmgr.getRef("ball"), this->colourMap.at(coolMap.at(Colours::CoolColours::LIME)), 1, 200.0f));
     
                        ++coolSpawned;
                        this->spawnClock.restart();
                    }
                }
            }
     
            else if (warmSpawned + coolSpawned >= 2)
            {
                //reset the counters
                warmSpawned = 0;
                coolSpawned = 0;
                ++this->pass;
            }
        }
            break;
            
        case 3: // 1st 'bomb'
        {
            spawnRate = 2.5f;
            if (this->game->colourMode == Game::ColourMode::WARM)
            {
                if (spawnClock.getElapsedTime().asSeconds() >= spawnRate)
                {
                    this->balls.push_back(new Ball(this->game->texmgr.getRef("ball"), this->colourMap.at(coolMap.at(static_cast<Colours::CoolColours>(rand() % 6 + 1))), 0, 480.0f));
                    
                    this->spawnClock.restart();
                    ++this->pass;
                }
            }
            else if (this->game->colourMode == Game::ColourMode::COOL)
            {
                if (spawnClock.getElapsedTime().asSeconds() >= spawnRate)
                {
                    this->balls.push_back(new Ball(this->game->texmgr.getRef("ball"), this->colourMap.at(warmMap.at(static_cast<Colours::WarmColours>(rand() % 6 + 1))), 0, 480.0f));
                    
                    this->spawnClock.restart();
                    ++this->pass;
                }
            }
        }
            break;
            
        case 4:
        {
            spawnRate = 2.0f;
            if (warmSpawned + coolSpawned < 5)
            {
                if (this->game->colourMode == Game::ColourMode::WARM)
                {
                    if (spawnClock.getElapsedTime().asSeconds() >= spawnRate)
                    {
                        if (coolSpawned == 1)
                        {
                            if (spawnClock.getElapsedTime().asSeconds() >= spawnRate)
                            {
                                this->balls.push_back(new Ball(this->game->texmgr.getRef("ball"), this->colourMap.at(warmMap.at(Colours::WarmColours::YELLOW)), 1, 200.0f));
                                
                                ++warmSpawned;
                                this->spawnClock.restart();
                            }
                        }
                        else if (warmSpawned == 4)
                        {
                            if (spawnClock.getElapsedTime().asSeconds() >= spawnRate)
                            {
                                this->balls.push_back(new Ball(this->game->texmgr.getRef("ball"), this->colourMap.at(coolMap.at(static_cast<Colours::CoolColours>(rand() % 6 + 1))), 0, 480.0f));

                                ++coolSpawned;
                                this->spawnClock.restart();
                            }
                        }
                        else
                        {
                            //In a 50% chance
                            if (std::rand() % 100 < 50)
                            {
                                this->balls.push_back(new Ball(this->game->texmgr.getRef("ball"), this->colourMap.at(warmMap.at(Colours::WarmColours::YELLOW)), 1, 200.0f));
                                ++warmSpawned;
                            }
                            else
                            {
                                this->balls.push_back(new Ball(this->game->texmgr.getRef("ball"), this->colourMap.at(coolMap.at(static_cast<Colours::CoolColours>(rand() % 6 + 1))), 0, 480.0f));
                                ++coolSpawned;
                            }
                            this->spawnClock.restart();
                        }
                    }
                }
                
                else if (this->game->colourMode == Game::ColourMode::COOL)
                {
                    if (spawnClock.getElapsedTime().asSeconds() >= spawnRate)
                    {
                        if (warmSpawned == 1)
                        {
                            this->balls.push_back(new Ball(this->game->texmgr.getRef("ball"), this->colourMap.at(coolMap.at(Colours::CoolColours::LIME)), 1, 200.0f));
                            ++coolSpawned;
                            this->spawnClock.restart();
                        }
                        else if (coolSpawned == 4)
                        {
                            this->balls.push_back(new Ball(this->game->texmgr.getRef("ball"), this->colourMap.at(warmMap.at(static_cast<Colours::WarmColours>(rand() % 6 + 1))), 0, 480.0f));
                            ++warmSpawned;
                            this->spawnClock.restart();
                        }
                        else
                        {
                            //In a 50% chance
                            if (std::rand() % 100 < 50)
                            {
                                this->balls.push_back(new Ball(this->game->texmgr.getRef("ball"), this->colourMap.at(coolMap.at(Colours::CoolColours::LIME)), 1, 200.0f));
                                ++coolSpawned;
                            }
                            else
                            {
                                this->balls.push_back(new Ball(this->game->texmgr.getRef("ball"), this->colourMap.at(warmMap.at(static_cast<Colours::WarmColours>(rand() % 6 + 1))), 0, 480.0f));
                                ++warmSpawned;
                            }
                            this->spawnClock.restart();
                        }
                    }
                }
            }
            
            else if (warmSpawned + coolSpawned >= 5)
            {
                //reset the counters
                warmSpawned = 0;
                coolSpawned = 0;
                ++this->pass;
            }
        }
            break;
            
        case 5:
        {
            spawnRate = 1.8f;
            if (warmSpawned + coolSpawned < 5)
            {
                if (this->game->colourMode == Game::ColourMode::WARM)
                {
                    if (spawnClock.getElapsedTime().asSeconds() >= spawnRate)
                    {
                        if (coolSpawned == 2)
                        {
                            int twoPointCount = 0;
                            for (auto ball : balls)
                            {
                                if (ball->pointsToGive == 2)
                                    ++twoPointCount;
                            }
                            
                            if (twoPointCount == 1) //if a two point ball already exists
                            {
                                this->balls.push_back(new Ball(this->game->texmgr.getRef("ball"), this->colourMap.at(warmMap.at(Colours::WarmColours::YELLOW)), 1, 200.0f));
                            }
                            else
                            {
                                this->balls.push_back(new Ball(this->game->texmgr.getRef("ball"), this->colourMap.at(warmMap.at(Colours::WarmColours::YELLOW_ORANGE)), 2, 320.0f));
                            }
                            ++warmSpawned;
                            this->spawnClock.restart();
                        }
                        else if (warmSpawned == 3)
                        {
                            this->balls.push_back(new Ball(this->game->texmgr.getRef("ball"), this->colourMap.at(coolMap.at(static_cast<Colours::CoolColours>(rand() % 6 + 1))), 0, 480.0f));
                            ++coolSpawned;
                            this->spawnClock.restart();
                        }
                        else
                        {
                            //In a 50% chance
                            if (std::rand() % 100 < 50)
                            {
                                int twoPointCount = 0;
                                for (auto ball : balls)
                                {
                                    if (ball->pointsToGive == 2)
                                        ++twoPointCount;
                                }
                                
                                if (twoPointCount == 1)
                                {
                                    this->balls.push_back(new Ball(this->game->texmgr.getRef("ball"), this->colourMap.at(warmMap.at(Colours::WarmColours::YELLOW)), 1, 200.0f));
                                }
                                else
                                {
                                    this->balls.push_back(new Ball(this->game->texmgr.getRef("ball"), this->colourMap.at(warmMap.at(Colours::WarmColours::YELLOW_ORANGE)), 2, 320.0f));
                                }
                                ++warmSpawned;
                            }
                            else
                            {
                                this->balls.push_back(new Ball(this->game->texmgr.getRef("ball"), this->colourMap.at(coolMap.at(static_cast<Colours::CoolColours>(rand() % 6 + 1))), 0, 480.0f));
                                ++coolSpawned;
                            }
                            this->spawnClock.restart();
                        }
                    }
                }
                
                else if (this->game->colourMode == Game::ColourMode::COOL)
                {
                    if (spawnClock.getElapsedTime().asSeconds() >= spawnRate)
                    {
                        if (warmSpawned == 2)
                        {
                            int twoPointCount = 0;
                            for (auto ball : balls)
                            {
                                if (ball->pointsToGive == 2)
                                    ++twoPointCount;
                            }
                            
                            if (twoPointCount == 1)
                            {
                                this->balls.push_back(new Ball(this->game->texmgr.getRef("ball"), this->colourMap.at(coolMap.at(Colours::CoolColours::LIME)), 1, 200.0f));
                            }
                            else
                            {
                                this->balls.push_back(new Ball(this->game->texmgr.getRef("ball"), this->colourMap.at(coolMap.at(Colours::CoolColours::GREEN)), 2, 320.0f));
                            }
                            
                            ++coolSpawned;
                            this->spawnClock.restart();
                        }
                        else if (coolSpawned == 3)
                        {
                            if (spawnClock.getElapsedTime().asSeconds() >= spawnRate)
                            {
                                this->balls.push_back(new Ball(this->game->texmgr.getRef("ball"), this->colourMap.at(warmMap.at(static_cast<Colours::WarmColours>(rand() % 6 + 1))), 0, 480.0f));
                                
                                ++warmSpawned;
                                this->spawnClock.restart();
                            }
                        }
                        else
                        {
                            //In a 50% chance
                            if (std::rand() % 100 < 50)
                            {
                                int twoPointCount = 0;
                                for (auto ball : balls)
                                {
                                    if (ball->pointsToGive == 2)
                                        ++twoPointCount;
                                }
                                
                                if (twoPointCount == 1)
                                {
                                    this->balls.push_back(new Ball(this->game->texmgr.getRef("ball"), this->colourMap.at(coolMap.at(Colours::CoolColours::LIME)), 1, 200.0f));
                                }
                                else
                                {
                                    this->balls.push_back(new Ball(this->game->texmgr.getRef("ball"), this->colourMap.at(coolMap.at(Colours::CoolColours::GREEN)), 2, 320.0f));
                                }
                                
                                ++coolSpawned;
                            }
                            else
                            {
                                this->balls.push_back(new Ball(this->game->texmgr.getRef("ball"), this->colourMap.at(warmMap.at(static_cast<Colours::WarmColours>(rand() % 6 + 1))), 0, 480.0f));
                                ++warmSpawned;
                            }
                            this->spawnClock.restart();
                        }
                    }
                }
            }
            
            if (warmSpawned + coolSpawned >= 5)
            {
                //reset the counters
                warmSpawned = 0;
                coolSpawned = 0;
                ++this->pass;
            }
        }
            break;
            
        case 6:
        {
            spawnRate = 1.5f;
            if (warmSpawned + coolSpawned < 8)
            {
                if (this->game->colourMode == Game::ColourMode::WARM)
                {
                    if (spawnClock.getElapsedTime().asSeconds() >= spawnRate)
                    {
                        if (coolSpawned == 2)
                        {
                            int genNum = rand() % 99;
                            if (genNum < 33)
                            {
                                this->balls.push_back(new Ball(this->game->texmgr.getRef("ball"), this->colourMap.at(warmMap.at(Colours::WarmColours::YELLOW)), 1, 200.0f));
                            }
                            else if (genNum >= 33 && genNum < 66)
                            {
                                this->balls.push_back(new Ball(this->game->texmgr.getRef("ball"), this->colourMap.at(warmMap.at(Colours::WarmColours::YELLOW_ORANGE)), 2, 320.0f));
                            }
                            else
                            {
                                this->balls.push_back(new Ball(this->game->texmgr.getRef("ball"), this->colourMap.at(warmMap.at(Colours::WarmColours::ORANGE)), 3, 400.0f));
                            }
                            ++warmSpawned;
                            this->spawnClock.restart();
                        }
                        else if (warmSpawned == 6)
                        {
                            if (spawnClock.getElapsedTime().asSeconds() >= spawnRate)
                            {
                                this->balls.push_back(new Ball(this->game->texmgr.getRef("ball"), this->colourMap.at(coolMap.at(static_cast<Colours::CoolColours>(rand() % 6 + 1))), 0, 480.0f));
                                ++coolSpawned;
                                this->spawnClock.restart();
                            }
                        }
                        else
                        {
                            //In a 50% chance
                            if (std::rand() % 100 < 50)
                            {
                                int genNum = rand() % 99;
                                if (genNum < 33)
                                {
                                    this->balls.push_back(new Ball(this->game->texmgr.getRef("ball"), this->colourMap.at(warmMap.at(Colours::WarmColours::YELLOW)), 1, 200.0f));
                                }
                                else if (genNum >= 33 && genNum < 66)
                                {
                                    this->balls.push_back(new Ball(this->game->texmgr.getRef("ball"), this->colourMap.at(warmMap.at(Colours::WarmColours::YELLOW_ORANGE)), 2, 320.0f));
                                }
                                else
                                {
                                    this->balls.push_back(new Ball(this->game->texmgr.getRef("ball"), this->colourMap.at(warmMap.at(Colours::WarmColours::ORANGE)), 3, 400.0f));
                                }
                                
                                ++warmSpawned;
                            }
                            else
                            {
                                this->balls.push_back(new Ball(this->game->texmgr.getRef("ball"), this->colourMap.at(coolMap.at(static_cast<Colours::CoolColours>(rand() % 6 + 1))), 0, 480.0f));
                                
                                ++coolSpawned;
                            }
                            this->spawnClock.restart();
                        }
                    }
                }
                
                
                else if (this->game->colourMode == Game::ColourMode::COOL)
                {
                    if (spawnClock.getElapsedTime().asSeconds() >= spawnRate)
                    {
                        if (warmSpawned == 2)
                        {
                            int genNum = rand() % 99;
                            if (genNum < 33)
                            {
                                this->balls.push_back(new Ball(this->game->texmgr.getRef("ball"), this->colourMap.at(coolMap.at(Colours::CoolColours::LIME)), 1, 200.0f));
                            }
                            else if (genNum >= 33 && genNum < 66)
                            {
                                this->balls.push_back(new Ball(this->game->texmgr.getRef("ball"), this->colourMap.at(coolMap.at(Colours::CoolColours::GREEN)), 2, 320.0f));
                            }
                            else
                            {
                                this->balls.push_back(new Ball(this->game->texmgr.getRef("ball"), this->colourMap.at(coolMap.at(Colours::CoolColours::TURQUOISE)), 3, 400.0f));
                            }
                            ++coolSpawned;
                            this->spawnClock.restart();
                        }
                        else if (coolSpawned == 6)
                        {
                            this->balls.push_back(new Ball(this->game->texmgr.getRef("ball"), this->colourMap.at(warmMap.at(static_cast<Colours::WarmColours>(rand() % 6 + 1))), 0, 480.0f));
                            
                            ++warmSpawned;
                            this->spawnClock.restart();
                        }
                        else
                        {
                            if (spawnClock.getElapsedTime().asSeconds() >= spawnRate)
                            {
                                //In a 50% chance
                                if (std::rand() % 100 < 50)
                                {
                                    int genNum = rand() % 99;
                                    if (genNum < 33)
                                    {
                                        this->balls.push_back(new Ball(this->game->texmgr.getRef("ball"), this->colourMap.at(coolMap.at(Colours::CoolColours::LIME)), 1, 200.0f));
                                    }
                                    else if (genNum >= 33 && genNum < 66)
                                    {
                                        this->balls.push_back(new Ball(this->game->texmgr.getRef("ball"), this->colourMap.at(coolMap.at(Colours::CoolColours::GREEN)), 2, 320.0f));
                                    }
                                    else
                                    {
                                        this->balls.push_back(new Ball(this->game->texmgr.getRef("ball"), this->colourMap.at(coolMap.at(Colours::CoolColours::TURQUOISE)), 3, 400.0f));
                                    }
                                    ++coolSpawned;
                                }
                                else
                                {
                                    this->balls.push_back(new Ball(this->game->texmgr.getRef("ball"), this->colourMap.at(warmMap.at(static_cast<Colours::WarmColours>(rand() % 6 + 1))), 0, 480.0f));
                                    
                                    ++warmSpawned;
                                }
                                this->spawnClock.restart();
                            }
                        }
                    }
                }
            }
            
            if (warmSpawned + coolSpawned >= 8)
            {
                //reset the counters
                warmSpawned = 0;
                coolSpawned = 0;
                ++this->pass;
            }
        }
            break;
            
        case 7:
        {
            spawnRate = 1.3f;
            if (warmSpawned + coolSpawned < 10)
            {
                if (this->game->colourMode == Game::ColourMode::WARM)
                {
                    if (spawnClock.getElapsedTime().asSeconds() >= spawnRate)
                    {
                        if (coolSpawned == 3)
                        {
                            int genNum = rand() % 99;
                            if (genNum < 33)
                            {
                                this->balls.push_back(new Ball(this->game->texmgr.getRef("ball"), this->colourMap.at(warmMap.at(Colours::WarmColours::YELLOW)), 1, 200.0f));
                            }
                            else if (genNum >= 33 && genNum < 66)
                            {
                                this->balls.push_back(new Ball(this->game->texmgr.getRef("ball"), this->colourMap.at(warmMap.at(Colours::WarmColours::YELLOW_ORANGE)), 2, 320.0f));
                            }
                            else
                            {
                                this->balls.push_back(new Ball(this->game->texmgr.getRef("ball"), this->colourMap.at(warmMap.at(Colours::WarmColours::ORANGE)), 3, 400.0f));
                            }
                            ++warmSpawned;
                            this->spawnClock.restart();
                        }
                        else if (warmSpawned == 7)
                        {
                            this->balls.push_back(new Ball(this->game->texmgr.getRef("ball"), this->colourMap.at(coolMap.at(static_cast<Colours::CoolColours>(rand() % 6 + 1))), 0, 480.0f));
                            
                            ++coolSpawned;
                            this->spawnClock.restart();
                        }
                        else
                        {
                            if (spawnClock.getElapsedTime().asSeconds() >= spawnRate)
                            {
                                //In a 50% chance
                                if (std::rand() % 100 < 50)
                                {
                                    int genNum = rand() % 99;
                                    if (genNum < 33)
                                    {
                                        this->balls.push_back(new Ball(this->game->texmgr.getRef("ball"), this->colourMap.at(warmMap.at(Colours::WarmColours::YELLOW)), 1, 200.0f));
                                    }
                                    else if (genNum >= 33 && genNum < 66)
                                    {
                                        this->balls.push_back(new Ball(this->game->texmgr.getRef("ball"), this->colourMap.at(warmMap.at(Colours::WarmColours::YELLOW_ORANGE)), 2, 320.0f));
                                    }
                                    else
                                    {
                                        this->balls.push_back(new Ball(this->game->texmgr.getRef("ball"), this->colourMap.at(warmMap.at(Colours::WarmColours::ORANGE)), 3, 400.0f));
                                    }
                                    ++warmSpawned;
                                }
                                else
                                {
                                    this->balls.push_back(new Ball(this->game->texmgr.getRef("ball"), this->colourMap.at(coolMap.at(static_cast<Colours::CoolColours>(rand() % 6 + 1))), 0, 480.0f));
                                    ++coolSpawned;
                                }
                                this->spawnClock.restart();
                            }
                        }
                    }
                }
                
                else if (this->game->colourMode == Game::ColourMode::COOL)
                {
                    if (spawnClock.getElapsedTime().asSeconds() >= spawnRate)
                    {
                        if (warmSpawned == 3)
                        {
                            int genNum = rand() % 99;
                            if (genNum < 33)
                            {
                                this->balls.push_back(new Ball(this->game->texmgr.getRef("ball"), this->colourMap.at(coolMap.at(Colours::CoolColours::LIME)), 1, 200.0f));
                            }
                            else if (genNum >= 33 && genNum < 66)
                            {
                                this->balls.push_back(new Ball(this->game->texmgr.getRef("ball"), this->colourMap.at(coolMap.at(Colours::CoolColours::GREEN)), 2, 320.0f));
                            }
                            else
                            {
                                this->balls.push_back(new Ball(this->game->texmgr.getRef("ball"), this->colourMap.at(coolMap.at(Colours::CoolColours::TURQUOISE)), 3, 400.0f));
                            }
                            ++coolSpawned;
                            this->spawnClock.restart();
                        }
                        else if (coolSpawned == 7)
                        {
                            this->balls.push_back(new Ball(this->game->texmgr.getRef("ball"), this->colourMap.at(warmMap.at(static_cast<Colours::WarmColours>(rand() % 6 + 1))), 0, 480.0f));
                            ++warmSpawned;
                            this->spawnClock.restart();
                        }
                        else
                        {
                            //In a 50% chance
                            if (std::rand() % 100 < 50)
                            {
                                int genNum = rand() % 99;
                                if (genNum < 33)
                                {
                                    this->balls.push_back(new Ball(this->game->texmgr.getRef("ball"), this->colourMap.at(coolMap.at(Colours::CoolColours::LIME)), 1, 200.0f));
                                }
                                else if (genNum >= 33 && genNum < 66)
                                {
                                    this->balls.push_back(new Ball(this->game->texmgr.getRef("ball"), this->colourMap.at(coolMap.at(Colours::CoolColours::GREEN)), 2, 320.0f));
                                }
                                else
                                {
                                    this->balls.push_back(new Ball(this->game->texmgr.getRef("ball"), this->colourMap.at(coolMap.at(Colours::CoolColours::TURQUOISE)), 3, 400.0f));
                                }
                                ++coolSpawned;
                            }
                            else
                            {
                                this->balls.push_back(new Ball(this->game->texmgr.getRef("ball"), this->colourMap.at(warmMap.at(static_cast<Colours::WarmColours>(rand() % 6 + 1))), 0, 480.0f));
                                ++warmSpawned;
                            }
                            this->spawnClock.restart();
                        }
                    }
                }
            }
            
            if (warmSpawned + coolSpawned >= 10)
            {
                //reset the counters
                warmSpawned = 0;
                coolSpawned = 0;
                ++this->pass;
            }
        }
            break;
            
        case 8:
        {
            spawnRate = 1.0f;
            if (warmSpawned + coolSpawned < 15)
            {
                if (this->game->colourMode == Game::ColourMode::WARM)
                {
                    if (spawnClock.getElapsedTime().asSeconds() >= spawnRate)
                    {
                        if (coolSpawned == 4)
                        {
                            int genNum = rand() % 100;
                            if (genNum < 20)
                            {
                                this->balls.push_back(new Ball(this->game->texmgr.getRef("ball"), this->colourMap.at(warmMap.at(Colours::WarmColours::YELLOW)), 1, 200.0f));
                            }
                            else if (genNum >= 20 && genNum < 40)
                            {
                                this->balls.push_back(new Ball(this->game->texmgr.getRef("ball"), this->colourMap.at(warmMap.at(Colours::WarmColours::YELLOW_ORANGE)), 2, 320.0f));
                            }
                            else if (genNum >= 40 && genNum < 60)
                            {
                                this->balls.push_back(new Ball(this->game->texmgr.getRef("ball"), this->colourMap.at(warmMap.at(Colours::WarmColours::ORANGE)), 3, 400.0f));
                            }
                            else if (genNum >= 60 && genNum < 80)
                            {
                                this->balls.push_back(new Ball(this->game->texmgr.getRef("ball"), this->colourMap.at(warmMap.at(Colours::WarmColours::ORANGE_VERMILLION)), 4, 480.0f));
                            }
                            else
                            {
                                this->balls.push_back(new Ball(this->game->texmgr.getRef("ball"), this->colourMap.at(warmMap.at(Colours::WarmColours::VERMILLION)), 5, 600.0f));
                            }
                            ++warmSpawned;
                            this->spawnClock.restart();
                        }
                        
                        else if (warmSpawned == 11)
                        {
                            this->balls.push_back(new Ball(this->game->texmgr.getRef("ball"), this->colourMap.at(coolMap.at(static_cast<Colours::CoolColours>(rand() % 6 + 1))), 0, 480.0f));
                            ++coolSpawned;
                            this->spawnClock.restart();
                        }
                        else
                        {
                            //In a 50% chance
                            if (std::rand() % 100 < 50)
                            {
                                int genNum = rand() % 100;
                                if (genNum < 20)
                                {
                                    this->balls.push_back(new Ball(this->game->texmgr.getRef("ball"), this->colourMap.at(warmMap.at(Colours::WarmColours::YELLOW)), 1, 200.0f));
                                }
                                else if (genNum >= 20 && genNum < 40)
                                {
                                    this->balls.push_back(new Ball(this->game->texmgr.getRef("ball"), this->colourMap.at(warmMap.at(Colours::WarmColours::YELLOW_ORANGE)), 2, 320.0f));
                                }
                                else if (genNum >= 40 && genNum < 60)
                                {
                                    this->balls.push_back(new Ball(this->game->texmgr.getRef("ball"), this->colourMap.at(warmMap.at(Colours::WarmColours::ORANGE)), 3, 400.0f));
                                }
                                else if (genNum >= 60 && genNum < 80)
                                {
                                    this->balls.push_back(new Ball(this->game->texmgr.getRef("ball"), this->colourMap.at(warmMap.at(Colours::WarmColours::ORANGE_VERMILLION)), 4, 480.0f));
                                }
                                else
                                {
                                    this->balls.push_back(new Ball(this->game->texmgr.getRef("ball"), this->colourMap.at(warmMap.at(Colours::WarmColours::VERMILLION)), 5, 600.0f));
                                }
                                ++warmSpawned;
                            }
                            else
                            {
                                this->balls.push_back(new Ball(this->game->texmgr.getRef("ball"), this->colourMap.at(coolMap.at(static_cast<Colours::CoolColours>(rand() % 6 + 1))), 0, 480.0f));
                                ++coolSpawned;
                            }
                            this->spawnClock.restart();
                        }
                    }
                }
                
                else if (this->game->colourMode == Game::ColourMode::COOL)
                {
                    if (spawnClock.getElapsedTime().asSeconds() >= spawnRate)
                    {
                        if (warmSpawned == 4)
                        {
                            int genNum = rand() % 100;
                            if (genNum < 20)
                            {
                                this->balls.push_back(new Ball(this->game->texmgr.getRef("ball"), this->colourMap.at(coolMap.at(Colours::CoolColours::LIME)), 1, 200.0f));
                            }
                            else if (genNum >= 20 && genNum < 40)
                            {
                                this->balls.push_back(new Ball(this->game->texmgr.getRef("ball"), this->colourMap.at(coolMap.at(Colours::CoolColours::GREEN)), 2, 320.0f));
                            }
                            else if (genNum >= 40 && genNum < 60)
                            {
                                this->balls.push_back(new Ball(this->game->texmgr.getRef("ball"), this->colourMap.at(coolMap.at(Colours::CoolColours::TURQUOISE)), 3, 400.0f));
                            }
                            else if (genNum >= 60 && genNum < 80)
                            {
                                this->balls.push_back(new Ball(this->game->texmgr.getRef("ball"), this->colourMap.at(coolMap.at(Colours::CoolColours::CYAN)), 4, 480.0f));
                            }
                            else
                            {
                                this->balls.push_back(new Ball(this->game->texmgr.getRef("ball"), this->colourMap.at(coolMap.at(Colours::CoolColours::AZURE)), 5, 600.0f));
                            }
                            ++coolSpawned;
                            this->spawnClock.restart();
                        }
                        else if (coolSpawned == 11)
                        {
                            this->balls.push_back(new Ball(this->game->texmgr.getRef("ball"), this->colourMap.at(warmMap.at(static_cast<Colours::WarmColours>(rand() % 6 + 1))), 0, 480.0f));
                            ++warmSpawned;
                            this->spawnClock.restart();
                        }
                        else
                        {
                            //In a 50% chance
                            if (std::rand() % 100 < 50)
                            {
                                int genNum = rand() % 100;
                                if (genNum < 20)
                                {
                                    this->balls.push_back(new Ball(this->game->texmgr.getRef("ball"), this->colourMap.at(coolMap.at(Colours::CoolColours::LIME)), 1, 200.0f));
                                }
                                else if (genNum >= 20 && genNum < 40)
                                {
                                    this->balls.push_back(new Ball(this->game->texmgr.getRef("ball"), this->colourMap.at(coolMap.at(Colours::CoolColours::GREEN)), 2, 320.0f));
                                }
                                else if (genNum >= 40 && genNum < 60)
                                {
                                    this->balls.push_back(new Ball(this->game->texmgr.getRef("ball"), this->colourMap.at(coolMap.at(Colours::CoolColours::TURQUOISE)), 3, 400.0f));
                                }
                                else if (genNum >= 60 && genNum < 80)
                                {
                                    this->balls.push_back(new Ball(this->game->texmgr.getRef("ball"), this->colourMap.at(coolMap.at(Colours::CoolColours::CYAN)), 4, 480.0f));
                                }
                                else
                                {
                                    this->balls.push_back(new Ball(this->game->texmgr.getRef("ball"), this->colourMap.at(coolMap.at(Colours::CoolColours::AZURE)), 5, 600.0f));
                                }
                                ++coolSpawned;
                            }
                            else
                            {
                                this->balls.push_back(new Ball(this->game->texmgr.getRef("ball"), this->colourMap.at(warmMap.at(static_cast<Colours::WarmColours>(rand() % 6 + 1))), 0, 480.0f));
                                ++warmSpawned;
                            }
                            this->spawnClock.restart();
                        }
                    }
                }
            }
            
            if (warmSpawned + coolSpawned >= 15)
            {
                //reset the counters
                warmSpawned = 0;
                coolSpawned = 0;
                ++this->pass;
            }
        }
            break;
        
        default: //from 9th pass onwards
        {
            spawnRate = 0.5f;
            
            //perform a check to see if the number of balls exceeds the maximum
            if (spawnClock.getElapsedTime().asSeconds() >= spawnRate && balls.size() < MAX_BALL_NUM)
            {
                if (this->game->colourMode == Game::ColourMode::WARM)
                {
                    int warmBallCount = 0;
                    for (auto ball : balls)
                    {
                        if (ball->pointsToGive > 0)
                            ++warmBallCount;
                    }
                    warmSpawned = warmBallCount;
                    coolSpawned = balls.size() - warmBallCount;
                    
                    if (coolSpawned >= MAX_BALL_NUM / 2) //half of the balls generate points
                    {
                        int genNum = rand() % 120;
                        if (genNum < 20)
                        {
                            this->balls.push_back(new Ball(this->game->texmgr.getRef("ball"), this->colourMap.at(warmMap.at(Colours::WarmColours::YELLOW)), 1, 200.0f));
                        }
                        else if (genNum >= 20 && genNum < 40)
                        {
                            this->balls.push_back(new Ball(this->game->texmgr.getRef("ball"), this->colourMap.at(warmMap.at(Colours::WarmColours::YELLOW_ORANGE)), 2, 320.0f));
                        }
                        else if (genNum >= 40 && genNum < 60)
                        {
                            this->balls.push_back(new Ball(this->game->texmgr.getRef("ball"), this->colourMap.at(warmMap.at(Colours::WarmColours::ORANGE)), 3, 400.0f));
                        }
                        else if (genNum >= 60 && genNum < 80)
                        {
                            this->balls.push_back(new Ball(this->game->texmgr.getRef("ball"), this->colourMap.at(warmMap.at(Colours::WarmColours::ORANGE_VERMILLION)), 4, 480.0f));
                        }
                        else if (genNum >= 80 && genNum < 100)
                        {
                            this->balls.push_back(new Ball(this->game->texmgr.getRef("ball"), this->colourMap.at(warmMap.at(Colours::WarmColours::VERMILLION)), 5, 600.0f));
                        }
                        else if (genNum >= 100 && genNum < 120)
                        {
                            this->balls.push_back(new Ball(this->game->texmgr.getRef("ball"), this->colourMap.at(warmMap.at(Colours::WarmColours::RED)), 6, 680.0f));
                        }
                    }
                    else if (warmSpawned >= MAX_BALL_NUM / 2)
                    {
                        this->balls.push_back(new Ball(this->game->texmgr.getRef("ball"), this->colourMap.at(coolMap.at(static_cast<Colours::CoolColours>(rand() % 6 + 1))), 0, 480.0f));
                    }
                    else
                    {
                        if (std::rand() % 100 < 50)
                        {
                            int genNum = rand() % 120;
                            if (genNum < 20)
                            {
                                this->balls.push_back(new Ball(this->game->texmgr.getRef("ball"), this->colourMap.at(warmMap.at(Colours::WarmColours::YELLOW)), 1, 200.0f));
                            }
                            else if (genNum >= 20 && genNum < 40)
                            {
                                this->balls.push_back(new Ball(this->game->texmgr.getRef("ball"), this->colourMap.at(warmMap.at(Colours::WarmColours::YELLOW_ORANGE)), 2, 320.0f));
                            }
                            else if (genNum >= 40 && genNum < 60)
                            {
                                this->balls.push_back(new Ball(this->game->texmgr.getRef("ball"), this->colourMap.at(warmMap.at(Colours::WarmColours::ORANGE)), 3, 400.0f));
                            }
                            else if (genNum >= 60 && genNum < 80)
                            {
                                this->balls.push_back(new Ball(this->game->texmgr.getRef("ball"), this->colourMap.at(warmMap.at(Colours::WarmColours::ORANGE_VERMILLION)), 4, 480.0f));
                            }
                            else if (genNum >= 80 && genNum < 100)
                            {
                                this->balls.push_back(new Ball(this->game->texmgr.getRef("ball"), this->colourMap.at(warmMap.at(Colours::WarmColours::VERMILLION)), 5, 600.0f));
                            }
                            else if (genNum >= 100 && genNum < 120)
                            {
                                this->balls.push_back(new Ball(this->game->texmgr.getRef("ball"), this->colourMap.at(warmMap.at(Colours::WarmColours::RED)), 6, 680.0f));
                            }
                        }
                        else
                        {
                            this->balls.push_back(new Ball(this->game->texmgr.getRef("ball"), this->colourMap.at(coolMap.at(static_cast<Colours::CoolColours>(rand() % 6 + 1))), 0, 480.0f));
                        }
                    }
                }
                
                else if (this->game->colourMode == Game::ColourMode::COOL)
                {
                    int coolBallCount = 0;
                    for (auto ball : balls)
                    {
                        if (ball->pointsToGive > 0)
                            ++coolBallCount;
                    }
                    coolSpawned = coolBallCount;
                    warmSpawned = balls.size() - coolBallCount;
                    
                    if (warmSpawned >= MAX_BALL_NUM / 2)
                    {
                        int genNum = rand() % 120;
                        if (genNum < 20)
                        {
                            this->balls.push_back(new Ball(this->game->texmgr.getRef("ball"), this->colourMap.at(coolMap.at(Colours::CoolColours::LIME)), 1, 200.0f));
                        }
                        else if (genNum >= 20 && genNum < 40)
                        {
                            this->balls.push_back(new Ball(this->game->texmgr.getRef("ball"), this->colourMap.at(coolMap.at(Colours::CoolColours::GREEN)), 2, 320.0f));
                        }
                        else if (genNum >= 40 && genNum < 60)
                        {
                            this->balls.push_back(new Ball(this->game->texmgr.getRef("ball"), this->colourMap.at(coolMap.at(Colours::CoolColours::TURQUOISE)), 3, 400.0f));
                        }
                        else if (genNum >= 60 && genNum < 80)
                        {
                            this->balls.push_back(new Ball(this->game->texmgr.getRef("ball"), this->colourMap.at(coolMap.at(Colours::CoolColours::CYAN)), 4, 480.0f));
                        }
                        else if (genNum >= 80 && genNum < 100)
                        {
                            this->balls.push_back(new Ball(this->game->texmgr.getRef("ball"), this->colourMap.at(coolMap.at(Colours::CoolColours::AZURE)), 5, 600.0f));
                        }
                        else if (genNum >= 100 && genNum < 120)
                        {
                            this->balls.push_back(new Ball(this->game->texmgr.getRef("ball"), this->colourMap.at(coolMap.at(Colours::CoolColours::BLUE)), 6, 680.0f));
                        }
                    }
                    else if (coolSpawned >= MAX_BALL_NUM / 2)
                    {
                        this->balls.push_back(new Ball(this->game->texmgr.getRef("ball"), this->colourMap.at(warmMap.at(static_cast<Colours::WarmColours>(rand() % 6 + 1))), 0, 480.0f));
                    }
                    else
                    {
                        if (std::rand() % 100 < 50)
                        {
                            
                            int genNum = rand() % 120;
                            if (genNum < 20)
                            {
                                this->balls.push_back(new Ball(this->game->texmgr.getRef("ball"), this->colourMap.at(coolMap.at(Colours::CoolColours::LIME)), 1, 200.0f));
                            }
                            else if (genNum >= 20 && genNum < 40)
                            {
                                this->balls.push_back(new Ball(this->game->texmgr.getRef("ball"), this->colourMap.at(coolMap.at(Colours::CoolColours::GREEN)), 2, 320.0f));
                            }
                            else if (genNum >= 40 && genNum < 60)
                            {
                                this->balls.push_back(new Ball(this->game->texmgr.getRef("ball"), this->colourMap.at(coolMap.at(Colours::CoolColours::TURQUOISE)), 3, 400.0f));
                            }
                            else if (genNum >= 60 && genNum < 80)
                            {
                                this->balls.push_back(new Ball(this->game->texmgr.getRef("ball"), this->colourMap.at(coolMap.at(Colours::CoolColours::CYAN)), 4, 480.0f));
                            }
                            else if (genNum >= 80 && genNum < 100)
                            {
                                this->balls.push_back(new Ball(this->game->texmgr.getRef("ball"), this->colourMap.at(coolMap.at(Colours::CoolColours::AZURE)), 5, 600.0f));
                            }
                            else if (genNum >= 100 && genNum < 120)
                            {
                                this->balls.push_back(new Ball(this->game->texmgr.getRef("ball"), this->colourMap.at(coolMap.at(Colours::CoolColours::BLUE)), 6, 680.0f));
                            }
                        }
                        else
                        {
                            this->balls.push_back(new Ball(this->game->texmgr.getRef("ball"), this->colourMap.at(warmMap.at(static_cast<Colours::WarmColours>(rand() % 6 + 1))), 0, 480.0f));
                        }
                    }
                }
                spawnClock.restart();
                
                //counter reset
                this->warmSpawned = 0;
                this->coolSpawned = 0;
            }
        }
            break;
    }
    return;
}

void BallSpawner::clickBall(sf::Vector2f mousePos)
{
    //backwards iteration, to make sure that the ball drawn in front gets deleted first
    for (int i = 0; i < balls.size(); ++i)
    {
        if (balls[i] != nullptr)
        {
            if (balls[i]->clicked(mousePos))
            {
                if (balls[i]->pointsToGive > 0)
                {
                    this->score += balls[i]->pointsToGive;
                    this->seconds += (balls[i]->pointsToGive * 2 - 2); //formula for time awarded (e.g. 1 point = 0 seconds, 2 points = 2 seconds, 3 points = 4 seconds, etc.)
                    if (this->seconds >= 60)
                    {
                        ++this->minutes;
                        this->seconds -= 60;
                    }
                    
                    delete balls[i];
                    this->balls.erase(balls.begin() + i);
                }
                else
                {
                    this->lost = true;
                }
            }
        }
    }
    
    this->scoreText.setString(std::to_string(score));
    this->scoreText.setCharacterSize(250);
    this->scoreText.setOrigin(this->scoreText.getGlobalBounds().width * 0.5f, this->scoreText.getGlobalBounds().height * 0.5f);
    this->scoreText.setPosition(sf::Vector2f(this->game->gameWidth * 0.5f - 12, this->game->gameHeight * 0.5f - 140));
    
    this->timeText.setString(changeTimeString());
    this->timeText.setCharacterSize(50);
    this->timeText.setOrigin(this->timeText.getGlobalBounds().width * 0.5f, this->timeText.getGlobalBounds().height * 0.5f);
    this->timeText.setPosition(sf::Vector2f(this->game->gameWidth * 0.5f - 12, this->game->gameHeight * 0.5f + 100));
    
    //reset the spawn timer to control ball spawn rate
    if (this->pass > 8 && spawnClock.getElapsedTime().asSeconds() > spawnRate)
        spawnClock.restart();
    
    return;
}

void BallSpawner::moveBalls(const float dt)
{
    for (auto ball : this->balls)
    {
        ball->move(this->game->gameWidth, this->game->gameHeight, dt);
    }
}

void BallSpawner::deleteBalls()
{
    for (int i = 0; i < balls.size(); ++i)
    {
        if (balls[i]->pointsToGive > 0)
        {
            if (balls[i]->lifeTime.getElapsedTime().asSeconds() >= this->mainLifeSpans[balls[i]->pointsToGive - 1])
            {
                delete balls[i];
                this->balls.erase(balls.begin() + i);
            }
        }
        else
        {
            if (balls[i]->lifeTime.getElapsedTime().asSeconds() >= this->otherLifeSpan)
            {
                delete balls[i];
                this->balls.erase(balls.begin() + i);
            }
        }
    }
    
    //reset the spawn timer to control ball spawn rate
    if (this->pass > 8 && spawnClock.getElapsedTime().asSeconds() > spawnRate)
        spawnClock.restart();
    
    return;
}

void BallSpawner::updateTime()
{
    //subtract one second away from the time remaining each second
    if (gameTimeClock.getElapsedTime().asSeconds() >= 1.0f)
    {
        --this->seconds;
        gameTimeClock.restart();
        
        if (this->minutes > 0 && this->seconds < 0.0f)
        {
            this->seconds = 59.0f;
            --this->minutes;
        }
    }
    
    //update the lost flag if both minutes and seconds hit 0
    if (this->minutes <= 0.0f && this->seconds < 0.0f)
        lost = true;
    
    this->timeText.setString(changeTimeString());
    this->timeText.setCharacterSize(50);
    this->timeText.setOrigin(this->timeText.getGlobalBounds().width * 0.5f, this->timeText.getGlobalBounds().height * 0.5f);
    this->timeText.setPosition(sf::Vector2f(this->game->gameWidth * 0.5f - 12, this->game->gameHeight * 0.5f + 100));
    
    return;
}

bool BallSpawner::hasLost()
{
    return lost;
}