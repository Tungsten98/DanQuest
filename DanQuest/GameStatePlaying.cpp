//
//  GameStatePlaying.cpp
//  DanQuest
//
//  Created by 17xiangyangt on 7/27/15.
//  Copyright (c) 2015 Tang. All rights reserved.
//

#include "GameStatePlaying.h"

GameStatePlaying::GameStatePlaying(Game* game)
{
    this->game = game;
    
    sf::Vector2f pos = sf::Vector2f(this->game->window.getSize());
    this->gameView.setSize(pos);
    
    pos *= 0.5f;
    this->gameView.setCenter(pos);
    
    this->game->window.setView(this->gameView);
    
    this->game->ballSpawner = new BallSpawner(this->game);
}

void GameStatePlaying::endGame()
{
    //make the program sleep for 2 seconds to make the player realise s/he lost
    //TO DO: Fix the sleep system so that the player can close the app even during the sleep period
    sf::sleep(sf::seconds(2.0f));
    this->game->pushState(new GameStateOver(this->game, this->game->ballSpawner->score));
    return;
}

void GameStatePlaying::draw(const float dt)
{
    this->game->window.clear(sf::Color::Black);
    this->game->window.draw(this->game->background);
    for (auto wall : this->game->walls)
    {
        wall.draw(this->game->window, dt);
    }
    this->game->ballSpawner->drawEntities();
    
    return;
}

void GameStatePlaying::update(const float dt)
{
    this->game->setBackgroundColour(this->game->colourMode);
    for (auto& wall : this->game->walls)
    {
        if (this->game->colourMode == Game::ColourMode::WARM)
            wall.colourMode = Wall::ColourMode::WARM;
        else if (this->game->colourMode == Game::ColourMode::COOL)
            wall.colourMode = Wall::ColourMode::COOL;
        
        wall.setColour(wall.colourMode);
    }
    
    this->game->ballSpawner->spawnBall();
    this->game->ballSpawner->deleteBalls();
    this->game->ballSpawner->moveBalls(dt);
    this->game->ballSpawner->updateTime();
    
    if (this->game->ballSpawner->hasLost())
        this->endGame();
        
    return;
}

void GameStatePlaying::handleInput()
{
    sf::Event event;
    
    while (this->game->window.pollEvent(event))
    {
        switch (event.type)
        {
            case sf::Event::Closed:
                this->game->window.close();
                break;
                
            case sf::Event::MouseButtonPressed:
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    sf::Vector2f mousePos = sf::Vector2f(this->game->window.mapPixelToCoords(sf::Mouse::getPosition(this->game->window), this->gameView));
                    this->game->ballSpawner->clickBall(mousePos);
                }
            }
                break;
                
            default:
                break;
        }
    }
}