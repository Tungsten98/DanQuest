//
//  TitlePage.cpp
//  DanQuest
//
//  Created by 17xiangyangt on 8/4/15.
//  Copyright (c) 2015 Tang. All rights reserved.
//

#include "TitlePage.h"

TitlePage::TitlePage(Game* game)
{
    this->game = game;
    this->showHighScores = false;
    
    this->warmRect.setSize(sf::Vector2f(240, 120));
    this->warmRect.setFillColor(sf::Color(255, 170, 170));
    this->warmRect.setOutlineColor(sf::Color(255, 120, 120));
    this->warmRect.setOutlineThickness(2.0f);
    this->warmRect.setOrigin(this->warmRect.getSize() * 0.5f);
    this->warmRect.setPosition(sf::Vector2f(this->game->gameWidth * 0.25f, this->game->gameHeight * 0.75f - 80));
    
    this->coolRect.setSize(sf::Vector2f(240, 120));
    this->coolRect.setFillColor(sf::Color(170, 170, 255));
    this->coolRect.setOutlineColor(sf::Color(120, 120, 255));
    this->coolRect.setOutlineThickness(2.0f);
    this->coolRect.setOrigin(this->coolRect.getSize() * 0.5f);
    this->coolRect.setPosition(sf::Vector2f(this->game->gameWidth * 0.75f, this->game->gameHeight * 0.75f - 80));
    
    this->highScoreRect.setSize(sf::Vector2f(640, 80));
    this->highScoreRect.setFillColor(sf::Color(255, 200, 150));
    this->highScoreRect.setOutlineColor(sf::Color(255, 140, 60));
    this->highScoreRect.setOutlineThickness(2.0f);
    this->highScoreRect.setOrigin(this->highScoreRect.getSize() * 0.5f);
    this->highScoreRect.setPosition(sf::Vector2f(this->game->gameWidth * 0.5f, this->game->gameHeight * 0.75f + 48));
    
    this->title.setFont(this->game->fontmgr.getRef("Consolas"));
    this->title.setString("DanQuest");
    this->title.setCharacterSize(120);
    this->title.setColor(sf::Color(255, 140, 60));
    this->title.setOrigin(sf::Vector2f(this->title.getGlobalBounds().width, this->title.getGlobalBounds().height) * 0.5f);
    this->title.setPosition(sf::Vector2f(this->game->gameWidth * 0.5f, this->game->gameHeight * 0.5f - 140));
    
    this->warmText.setFont(this->game->fontmgr.getRef("Consolas"));
    this->warmText.setString("Warm Mode");
    this->warmText.setCharacterSize(40);
    this->warmText.setColor(sf::Color(255, 120, 120));
    this->warmText.setOrigin(sf::Vector2f(this->warmText.getGlobalBounds().width, this->warmText.getGlobalBounds().height) * 0.5f);
    this->warmText.setPosition(sf::Vector2f(this->game->gameWidth * 0.25f, (this->game->gameHeight * 0.75f) - 96));
    
    this->coolText.setFont(this->game->fontmgr.getRef("Consolas"));
    this->coolText.setString("Cool Mode");
    this->coolText.setCharacterSize(40);
    this->coolText.setColor(sf::Color(120, 120, 255));
    this->coolText.setOrigin(sf::Vector2f(this->warmText.getGlobalBounds().width, this->warmText.getGlobalBounds().height) * 0.5f);
    this->coolText.setPosition(sf::Vector2f(this->game->gameWidth * 0.75f, (this->game->gameHeight * 0.75f) - 96));
    
    this->highScoreText.setFont(this->game->fontmgr.getRef("Consolas"));
    this->highScoreText.setString("High Scores");
    this->highScoreText.setCharacterSize(40);
    this->highScoreText.setColor(sf::Color(255, 140, 60));
    this->highScoreText.setOrigin(sf::Vector2f(this->warmText.getGlobalBounds().width, this->warmText.getGlobalBounds().height) * 0.5f);
    this->highScoreText.setPosition(sf::Vector2f(this->game->gameWidth * 0.5f, (this->game->gameHeight * 0.75f) + 32));
}

inline void TitlePage::resetColours()
{
    this->warmRect.setFillColor(sf::Color(255, 170, 170));
    this->warmRect.setOutlineColor(sf::Color(255, 120, 120));
    this->warmText.setColor(sf::Color(255, 120, 120));
    
    this->coolRect.setFillColor(sf::Color(170, 170, 255));
    this->coolRect.setOutlineColor(sf::Color(120, 120, 255));
    this->coolText.setColor(sf::Color(120, 120, 255));
    
    this->highScoreRect.setFillColor(sf::Color(255, 200, 150));
    this->highScoreRect.setOutlineColor(sf::Color(255, 140, 60));
    this->highScoreText.setColor(sf::Color(255, 140, 60));
}

void TitlePage::draw(const float dt)
{
    this->game->window.draw(title);
    this->game->window.draw(warmRect);
    this->game->window.draw(coolRect);
    this->game->window.draw(warmText);
    this->game->window.draw(coolText);
    this->game->window.draw(highScoreRect);
    this->game->window.draw(highScoreText);
    
    return;
}

void TitlePage::updateButton(sf::Vector2f mousePos)
{
    if (mousePos.x > this->warmRect.getPosition().x - (this->warmRect.getSize().x * 0.5f) &&
        mousePos.x < this->warmRect.getPosition().x + (this->warmRect.getSize().x * 0.5f) &&
        mousePos.y > this->warmRect.getPosition().y - (this->warmRect.getSize().y * 0.5f) &&
        mousePos.y < this->warmRect.getPosition().y + (this->warmRect.getSize().y * 0.5f))
    {
        //invert the colours
        this->warmRect.setFillColor(sf::Color(255, 120, 120));
        this->warmRect.setOutlineColor(sf::Color(255, 170, 170));
        this->warmText.setColor(this->warmRect.getOutlineColor());
        
    }
    else if (mousePos.x > this->coolRect.getPosition().x - (this->coolRect.getSize().x * 0.5f) &&
             mousePos.x < this->coolRect.getPosition().x + (this->coolRect.getSize().x * 0.5f) &&
             mousePos.y > this->coolRect.getPosition().y - (this->coolRect.getSize().y * 0.5f) &&
             mousePos.y < this->coolRect.getPosition().y + (this->coolRect.getSize().y * 0.5f))
    {
        //invert the colours
        this->coolRect.setFillColor(sf::Color(120, 120, 255));
        this->coolRect.setOutlineColor(sf::Color(170, 170, 255));
        this->coolText.setColor(this->coolRect.getOutlineColor());
    }
    else if (mousePos.x > this->highScoreRect.getPosition().x - (this->highScoreRect.getSize().x * 0.5f) &&
             mousePos.x < this->highScoreRect.getPosition().x + (this->highScoreRect.getSize().x * 0.5f) &&
             mousePos.y > this->highScoreRect.getPosition().y - (this->highScoreRect.getSize().y * 0.5f) &&
             mousePos.y < this->highScoreRect.getPosition().y + (this->highScoreRect.getSize().y * 0.5f))
    {
        //invert the colours
        this->highScoreRect.setFillColor(sf::Color(255, 140, 60));
        this->highScoreRect.setOutlineColor(sf::Color(255, 200, 50));
        this->highScoreText.setColor(this->highScoreRect.getOutlineColor());
    }
    else
    {
        this->resetColours();
    }
    
    return;
}

void TitlePage::transition(sf::Vector2f mousePos)
{
    if (mousePos.x > this->warmRect.getPosition().x - (this->warmRect.getSize().x * 0.5f) &&
        mousePos.x < this->warmRect.getPosition().x + (this->warmRect.getSize().x * 0.5f) &&
        mousePos.y > this->warmRect.getPosition().y - (this->warmRect.getSize().y * 0.5f) &&
        mousePos.y < this->warmRect.getPosition().y + (this->warmRect.getSize().y * 0.5f))
    {
        this->game->colourMode = Game::ColourMode::WARM;
    }
    else if (mousePos.x > this->coolRect.getPosition().x - (this->coolRect.getSize().x * 0.5f) &&
             mousePos.x < this->coolRect.getPosition().x + (this->coolRect.getSize().x * 0.5f) &&
             mousePos.y > this->coolRect.getPosition().y - (this->coolRect.getSize().y * 0.5f) &&
             mousePos.y < this->coolRect.getPosition().y + (this->coolRect.getSize().y * 0.5f))
    {
        this->game->colourMode = Game::ColourMode::COOL;
    }
    else if (mousePos.x > this->highScoreRect.getPosition().x - (this->highScoreRect.getSize().x * 0.5f) &&
             mousePos.x < this->highScoreRect.getPosition().x + (this->highScoreRect.getSize().x * 0.5f) &&
             mousePos.y > this->highScoreRect.getPosition().y - (this->highScoreRect.getSize().y * 0.5f) &&
             mousePos.y < this->highScoreRect.getPosition().y + (this->highScoreRect.getSize().y * 0.5f))
    {
        this->showHighScores = true;
    }
    
    return;
}