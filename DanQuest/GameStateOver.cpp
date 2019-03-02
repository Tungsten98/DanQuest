//
//  GameStateOver.cpp
//  DanQuest
//
//  Created by 17xiangyangt on 8/4/15.
//  Copyright (c) 2015 Tang. All rights reserved.
//

#include "GameStateOver.h"

GameStateOver::GameStateOver(Game* game, const int score)
{
    this->game = game;
    sf::Vector2f pos = sf::Vector2f(this->game->window.getSize());
    this->view.setSize(pos);
    pos *= 0.5f;
    this->view.setCenter(pos);
    this->game->window.setView(this->view);
    
    this->game->gameOverPage = new GameOverPage(this->game, score);
    this->interactClock.restart();
}

void GameStateOver::reloadGame()
{
    this->game->pushState(new GameStatePlaying(this->game));
    return;
}

void GameStateOver::returnToMain()
{
    this->game->pushState(new GameStateStart(this->game));
    return;
}

void GameStateOver::gotoHighScores()
{
    int finalScore = this->game->gameOverPage->getFinalScore();
    std::string currentText = this->game->gameOverPage->getCurrentText();
    this->game->pushState(new GameStateScores(this->game, currentText, finalScore));
}

void GameStateOver::draw(const float dt)
{
    this->game->window.clear(sf::Color::Black);
    
    this->game->window.draw(this->game->background);
    
    for (auto wall : this->game->walls)
    {
        wall.draw(this->game->window, dt);
    }
    
    this->game->gameOverPage->draw(dt);
    
    return;
}

void GameStateOver::update(const float dt)
{
    
}

void GameStateOver::handleInput()
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
                this->game->gameOverPage->updateButton(mousePos);
            }
                break;
                
            case sf::Event::MouseButtonPressed:
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    sf::Vector2f mousePos = sf::Vector2f(this->game->window.mapPixelToCoords(sf::Mouse::getPosition(this->game->window), this->view));
                    this->game->gameOverPage->transition(mousePos);
                }
                if (this->game->gameOverPage->isClicked() && this->interactClock.getElapsedTime().asSeconds() >= 0.5f)
                {
                    if (this->game->gameOverPage->continuePlay())
                    {
                        this->reloadGame();
                    }
                    else if (this->game->gameOverPage->showHighScores())
                    {
                        this->gotoHighScores();
                    }
                    else
                    {
                        this->returnToMain();
                    }
                }
            }
                break;
                
            case sf::Event::TextEntered:
            {
                if (this->game->gameOverPage->newHighScore)
                {
                    this->game->gameOverPage->updateNameString(event.text.unicode);
                }
            }
                break;
                
            default:
                break;
        }
    }
}