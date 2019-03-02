//
//  GameStateScores.cpp
//  DanQuest
//
//  Created by 17xiangyangt on 8/9/15.
//  Copyright (c) 2015 Tang. All rights reserved.
//

#include "GameStateScores.h"

GameStateScores::GameStateScores(Game* game)
{
    this->game = game;
    sf::Vector2f pos = sf::Vector2f(this->game->window.getSize());
    this->view.setSize(pos);
    pos *= 0.5f;
    this->view.setCenter(pos);
    this->game->window.setView(this->view);
    
    this->game->setBackgroundColour(this->game->colourMode);
    for (auto& wall : this->game->walls)
    {
        wall.setColour(wall.colourMode);
    }
    
    this->game->highScorePage = new HighScorePage(this->game);
}

GameStateScores::GameStateScores(Game* game, std::string& newName, int newScore)
{
    this->game = game;
    sf::Vector2f pos = sf::Vector2f(this->game->window.getSize());
    this->view.setSize(pos);
    pos *= 0.5f;
    this->view.setCenter(pos);
    this->game->window.setView(this->view);
    
    this->game->setBackgroundColour(this->game->colourMode);
    for (auto& wall : this->game->walls)
    {
        wall.setColour(wall.colourMode);
    }
    
    this->game->highScorePage = new HighScorePage(this->game, newName, newScore);
}

void GameStateScores::goBack()
{
    this->game->pushState(new GameStateStart(this->game));
    return;
}

void GameStateScores::draw(const float dt)
{
    this->game->window.clear();
    this->game->window.draw(this->game->background);
    for (auto& wall : this->game->walls)
    {
        wall.draw(this->game->window, dt);
    }
    this->game->highScorePage->draw(dt);
    return;
}

void GameStateScores::update(const float dt)
{
    if (this->game->highScorePage->isExit == true)
        this->goBack();
}

void GameStateScores::handleInput()
{
    sf::Event event;
    while (this->game->window.pollEvent(event))
    {
        switch (event.type)
        {
            case sf::Event::Closed:
            {
                this->game->window.close();
            }
                break;
                
            case sf::Event::MouseMoved:
            {
                sf::Vector2f mousePos = sf::Vector2f(this->game->window.mapPixelToCoords(sf::Mouse::getPosition(this->game->window), this->view));
                this->game->highScorePage->updateButton(mousePos);
            }
                break;
                
            case sf::Event::MouseButtonPressed:
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    sf::Vector2f mousePos = sf::Vector2f(this->game->window.mapPixelToCoords(sf::Mouse::getPosition(this->game->window), this->view));
                    this->game->highScorePage->transition(mousePos);
                }
            }
                break;
                
            default:
                break;
        }
    }
}