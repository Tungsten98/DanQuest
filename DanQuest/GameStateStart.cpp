//
//  GameStateStart.cpp
//  DanQuest
//
//  Created by 17xiangyangt on 7/27/15.
//  Copyright (c) 2015 Tang. All rights reserved.
//

#include "GameStateStart.h"

GameStateStart::GameStateStart(Game* game)
{
    this->game = game;
    
    //set initial view and center equal and relative to the window respectively
    sf::Vector2f pos = sf::Vector2f(this->game->window.getSize());
    this->view.setSize(pos);
    pos *= 0.5f;
    this->view.setCenter(pos);
    this->game->window.setView(this->view);
    
    this->game->colourMode = Game::ColourMode::DEFAULT;
    this->game->setBackgroundColour(this->game->colourMode);
    for (auto& wall : this->game->walls)
    {
        wall.colourMode = Wall::ColourMode::DEFAULT;
        wall.setColour(wall.colourMode);
    }
    
    this->game->titlePage = new TitlePage(this->game);
    
}

void GameStateStart::loadGame()
{
    this->game->pushState(new GameStatePlaying(this->game));
    return;
}

void GameStateStart::loadHighScores()
{
    this->game->pushState(new GameStateScores(this->game));
    return;
}

void GameStateStart::draw(const float dt)
{
    this->game->window.clear(sf::Color::Black);
    
    this->game->window.draw(this->game->background);
    
    for (auto wall : this->game->walls)
    {
        wall.draw(this->game->window, dt);
    }
    
    this->game->titlePage->draw(dt);
    
    return;
}

void GameStateStart::update(const float dt)
{
    
}

void GameStateStart::handleInput()
{
    sf::Event event;
    
    while (this->game->window.pollEvent(event))
    {
        switch (event.type)
        {
            case sf::Event::Closed:
                this->game->window.close();
                break;
                
            case sf::Event::MouseMoved:
            {
                sf::Vector2f mousePos = sf::Vector2f(this->game->window.mapPixelToCoords(sf::Mouse::getPosition(this->game->window), this->view));
                this->game->titlePage->updateButton(mousePos);
            }
                break;
                
            case sf::Event::MouseButtonPressed:
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    sf::Vector2f mousePos = sf::Vector2f(this->game->window.mapPixelToCoords(sf::Mouse::getPosition(this->game->window), this->view));
                    this->game->titlePage->transition(mousePos);
                }
                
                if (this->game->colourMode != Game::ColourMode::DEFAULT)
                {
                    this->loadGame();
                }
                
                else if (this->game->titlePage->showHighScores)
                {
                    this->loadHighScores();
                }
            }
                break;
                
            default:
                break;
        }
    }
}