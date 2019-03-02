//
//  Game.cpp
//  DanQuest
//
//  Created by 17xiangyangt on 7/27/15.
//  Copyright (c) 2015 Tang. All rights reserved.
//

#include "Game.h"

Game::Game()
{
    this->loadTextures();
    this->loadFonts();
    this->window.create(sf::VideoMode(gameWidth, gameHeight), "DanQuest", sf::Style::Titlebar | sf::Style::Close);
    this->window.setFramerateLimit(60);
    
    this->background.setTexture(texmgr.getRef("background"));
    
    this->colourMap.emplace("warm", sf::Color(255, 210, 210));
    this->colourMap.emplace("cool", sf::Color(210, 210, 255));
    this->colourMap.emplace("default", sf::Color(255, 200, 150));
    this->colourMode = ColourMode::DEFAULT;
    this->setBackgroundColour(colourMode);
    
    //Set up wall perimeters
    loadWalls();
}

Game::~Game()
{
    delete titlePage;
    delete ballSpawner;
    delete gameOverPage;
    
    while (!this->gameStates.empty())
    {
        popState();
    }
}

void Game::loadTextures()
{
    texmgr.loadTexture("background", resourcePath() + "DanQuestBackground.png");
    texmgr.loadTexture("wall", resourcePath() + "DanQuestWall.png");
    texmgr.loadTexture("ball", resourcePath() + "DanQuestBall.png");
}

void Game::loadFonts()
{
    fontmgr.loadFont("Consolas", resourcePath() + "Consolas.ttf");
}

void Game::loadWalls()
{
    for (int i = 0; i < gameWidth; i += Wall::wallSideSize)
    {
        this->walls.push_back(Wall(texmgr.getRef("wall"), sf::Vector2i(i, 0)));
    }
    for (int i = 0; i < gameWidth; i += Wall::wallSideSize)
    {
        this->walls.push_back(Wall(texmgr.getRef("wall"), sf::Vector2i(i, gameHeight - Wall::wallSideSize)));
    }
    for (int i = Wall::wallSideSize; i < gameHeight - Wall::wallSideSize; i += Wall::wallSideSize)
    {
        this->walls.push_back(Wall(texmgr.getRef("wall"), sf::Vector2i(0, i)));
    }
    for (int i = Wall::wallSideSize; i < gameHeight - Wall::wallSideSize; i += Wall::wallSideSize)
    {
        this->walls.push_back(Wall(texmgr.getRef("wall"), sf::Vector2i(gameWidth - Wall::wallSideSize, i)));
    }
    
    return;
}

void Game::setBackgroundColour(ColourMode mode)
{
    if (mode == ColourMode::WARM)
    {
        this->background.setColor(this->colourMap.at("warm"));
    }
    else if (mode == ColourMode::COOL)
    {
        this->background.setColor(this->colourMap.at("cool"));
    }
    else
    {
        this->background.setColor(this->colourMap.at("default"));
    }
}

void Game::pushState(GameState* state)
{
    this->gameStates.push(state);
    return;
}

void Game::popState()
{
    delete this->gameStates.top();
    this->gameStates.pop();
    return;
}

void Game::changeState(GameState* state)
{
    if (!this->gameStates.empty())
        popState();
    
    pushState(state);
    return;
}

GameState* Game::peekState()
{
    if (this->gameStates.empty())
        return nullptr;
    else
        return this->gameStates.top();
}

void Game::gameLoop()
{
    sf::Clock clock;
    
    while (this->window.isOpen())
    {
        //keep everything flowing at a smooth rate
        sf::Time elapsed = clock.restart();
        float dt = elapsed.asSeconds();
        
        if (peekState() == nullptr)
            continue;
        
        peekState()->handleInput();
        peekState()->update(dt);
        
        this->window.clear(sf::Color::Black);
        peekState()->draw(dt);
        this->window.display();
    }
}