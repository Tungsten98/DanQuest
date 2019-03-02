//
//  GameOverPage.cpp
//  DanQuest
//
//  Created by 17xiangyangt on 8/5/15.
//  Copyright (c) 2015 Tang. All rights reserved.
//

#include "GameOverPage.h"

GameOverPage::GameOverPage(Game* game, int score)
{
    this->game = game;
    this->finalScore = score;
    this->clickedInBox = false;
    this->toGame = false;
    
    //make the constructor read the highscore file to determine the appropriate flag to set for newHighScore
    this->newHighScore = false;
    std::ifstream file;
    file.open("highscores.txt", std::ios::in);
    
    if (file.is_open())
    {
        std::string tempBuffer[10];
        int bufferCount = 0;
        
        std::string line;
        while (std::getline(file, line))
        {
            if (bufferCount < 10)
            {
                tempBuffer[bufferCount] = line;
                ++bufferCount;
            }
        }
        
        for (int i = 0; i < 10; ++i)
        {
            int startIndex = (tempBuffer[i].find(":") + 1);
            int endIndex = (tempBuffer[i].find("("));
            std::string scoreCopyString = tempBuffer[i].substr(startIndex, endIndex - startIndex);
            int scoreCopy = std::stoi(scoreCopyString);
            
            if (score > scoreCopy)
            {
                this->newHighScore = true;
                break;
            }
        }
    }
    file.close();
    
    this->toHighScores = false;
    
    this->gameOverText.setFont(this->game->fontmgr.getRef("Consolas"));
    this->gameOverText.setString("Game Over");
    this->gameOverText.setCharacterSize(120);
    
    if (this->game->colourMode == Game::ColourMode::WARM)
        this->gameOverText.setColor(sf::Color(255, 120, 120));
    else if (this->game->colourMode == Game::ColourMode::COOL)
        this->gameOverText.setColor(sf::Color(120, 120, 255));
    
    this->gameOverText.setOrigin(sf::Vector2f(this->gameOverText.getGlobalBounds().width, this->gameOverText.getGlobalBounds().height) * 0.5f);
    this->gameOverText.setPosition(sf::Vector2f(this->game->gameWidth * 0.5f, this->game->gameHeight * 0.5f - 200));
    
    this->finalScoreText.setFont(this->game->fontmgr.getRef("Consolas"));
    this->finalScoreText.setString(finalScoreString());
    this->finalScoreText.setCharacterSize(40);
    
    if (this->game->colourMode == Game::ColourMode::WARM)
        this->finalScoreText.setColor(sf::Color(255, 120, 120));
    else if (this->game->colourMode == Game::ColourMode::COOL)
        this->finalScoreText.setColor(sf::Color(120, 120, 255));
    
    this->finalScoreText.setOrigin(sf::Vector2f(this->finalScoreText.getGlobalBounds().width, this->finalScoreText.getGlobalBounds().height) * 0.5f);
    this->finalScoreText.setPosition(sf::Vector2f(this->game->gameWidth * 0.5f, this->game->gameHeight * 0.5f - 60));
    
    
    this->warmRect.setSize(sf::Vector2f(240, 120));
    this->warmRect.setFillColor(sf::Color(255, 170, 170));
    this->warmRect.setOutlineColor(sf::Color(255, 120, 120));
    this->warmRect.setOutlineThickness(2.0f);
    this->warmRect.setOrigin(this->warmRect.getSize() * 0.5f);
    
    if (this->game->colourMode == Game::ColourMode::WARM)
        this->warmRect.setPosition(sf::Vector2f(this->game->gameWidth * 0.25f, this->game->gameHeight * 0.75f - 80));
    else if (this->game->colourMode == Game::ColourMode::COOL)
        this->warmRect.setPosition(sf::Vector2f(this->game->gameWidth * 0.75f, this->game->gameHeight * 0.75f - 80));
    
    
    this->coolRect.setSize(sf::Vector2f(240, 120));
    this->coolRect.setFillColor(sf::Color(170, 170, 255));
    this->coolRect.setOutlineColor(sf::Color(120, 120, 255));
    this->coolRect.setOutlineThickness(2.0f);
    this->coolRect.setOrigin(this->coolRect.getSize() * 0.5f);
    
    if (this->game->colourMode == Game::ColourMode::COOL)
        this->coolRect.setPosition(sf::Vector2f(this->game->gameWidth * 0.25f, this->game->gameHeight * 0.75f - 80));
    else if (this->game->colourMode == Game::ColourMode::WARM)
        this->coolRect.setPosition(sf::Vector2f(this->game->gameWidth * 0.75f, this->game->gameHeight * 0.75f - 80));
    
    
    this->mainMenuRect.setSize(sf::Vector2f(640, 80));
    this->mainMenuRect.setFillColor(sf::Color(255, 200, 150));
    this->mainMenuRect.setOutlineColor(sf::Color(255, 140, 60));
    this->mainMenuRect.setOutlineThickness(2.0f);
    this->mainMenuRect.setOrigin(this->mainMenuRect.getSize() * 0.5f);
    this->mainMenuRect.setPosition(sf::Vector2f(this->game->gameWidth * 0.5f, this->game->gameHeight * 0.75f + 48));
    
    
    this->warmText.setFont(this->game->fontmgr.getRef("Consolas"));
    
    if (this->game->colourMode == Game::ColourMode::WARM)
        this->warmText.setString("Play again");
    else
        this->warmText.setString(" Play in\nWarm Mode");
    
    this->warmText.setCharacterSize(40);
    this->warmText.setColor(sf::Color(255, 120, 120));
    this->warmText.setOrigin(sf::Vector2f(this->warmText.getGlobalBounds().width, this->warmText.getGlobalBounds().height) * 0.5f);
    
    if (this->game->colourMode == Game::ColourMode::WARM)
        this->warmText.setPosition(sf::Vector2f(this->game->gameWidth * 0.25f, (this->game->gameHeight * 0.75f) - 96));
    else if (this->game->colourMode == Game::ColourMode::COOL)
        this->warmText.setPosition(sf::Vector2f(this->game->gameWidth * 0.75f, (this->game->gameHeight * 0.75f) - 96));
    
    
    this->coolText.setFont(this->game->fontmgr.getRef("Consolas"));
    
    if (this->game->colourMode == Game::ColourMode::COOL)
        this->coolText.setString("Play again");
    else
        this->coolText.setString(" Play in\nCool Mode");
    
    this->coolText.setCharacterSize(40);
    this->coolText.setColor(sf::Color(120, 120, 255));
    this->coolText.setOrigin(sf::Vector2f(this->coolText.getGlobalBounds().width, this->coolText.getGlobalBounds().height) * 0.5f);
    
    if (this->game->colourMode == Game::ColourMode::COOL)
        this->coolText.setPosition(sf::Vector2f(this->game->gameWidth * 0.25f, (this->game->gameHeight * 0.75f) - 96));
    else if (this->game->colourMode == Game::ColourMode::WARM)
        this->coolText.setPosition(sf::Vector2f(this->game->gameWidth * 0.75f, (this->game->gameHeight * 0.75f) - 96));
    
    
    this->mainMenuText.setFont(this->game->fontmgr.getRef("Consolas"));
    this->mainMenuText.setString("Main Menu");
    this->mainMenuText.setCharacterSize(40);
    this->mainMenuText.setColor(sf::Color(255, 140, 60));
    this->mainMenuText.setOrigin(sf::Vector2f(this->mainMenuText.getGlobalBounds().width, this->mainMenuText.getGlobalBounds().height) * 0.5f);
    this->mainMenuText.setPosition(sf::Vector2f(this->game->gameWidth * 0.5f, (this->game->gameHeight * 0.75f) + 32));
    
    
    //high score window
    this->hsWrapperBox.setSize(sf::Vector2f(this->game->gameWidth, this->game->gameHeight));
    this->hsWrapperBox.setFillColor(sf::Color(0, 0, 0, 128));
    this->hsWrapperBox.setPosition(0, 0);
    
    this->newHsRect.setSize(sf::Vector2f(this->game->gameWidth * 0.8f, this->game->gameHeight * 0.6f));
    if (this->game->colourMode == Game::ColourMode::WARM)
    {
        this->newHsRect.setFillColor(sf::Color(255, 210, 210));
        this->newHsRect.setOutlineColor(sf::Color(255, 150, 150));
    }
    else if (this->game->colourMode == Game::ColourMode::COOL)
    {
        this->newHsRect.setFillColor(sf::Color(210, 210, 255));
        this->newHsRect.setOutlineColor(sf::Color(150, 150, 210));
    }
    this->newHsRect.setOutlineThickness(2.0f);
    this->newHsRect.setOrigin(this->newHsRect.getSize() * 0.5f);
    this->newHsRect.setPosition(this->game->gameWidth * 0.5f, this->game->gameHeight * 0.5f);
    
    this->congratsText.setFont(this->game->fontmgr.getRef("Consolas"));
    this->congratsText.setString("\t\tCongratulations,\nyou've achieved a new High Score!");
    this->congratsText.setCharacterSize(32);
    this->congratsText.setColor(this->newHsRect.getOutlineColor());
    this->congratsText.setOrigin(this->congratsText.getGlobalBounds().width * 0.5f, this->congratsText.getGlobalBounds().height * 0.5f);
    this->congratsText.setPosition(this->newHsRect.getPosition().x, this->newHsRect.getPosition().y - (this->newHsRect.getSize().y * 0.3f));
    
    this->newHsText.setFont(this->game->fontmgr.getRef("Consolas"));
    this->newHsText.setString("Your Score: " + std::to_string(this->finalScore));
    this->newHsText.setCharacterSize(28);
    this->newHsText.setColor(this->newHsRect.getOutlineColor());
    this->newHsText.setOrigin(this->newHsText.getGlobalBounds().width * 0.5f, this->newHsText.getGlobalBounds().height * 0.5f);
    this->newHsText.setPosition(this->newHsRect.getPosition().x, this->newHsRect.getPosition().y - (this->newHsRect.getSize().y * 0.1f));
    
    this->enterNameText.setFont(this->game->fontmgr.getRef("Consolas"));
    this->enterNameText.setString("Enter your name: ");
    this->enterNameText.setCharacterSize(24);
    this->enterNameText.setColor(this->newHsRect.getOutlineColor());
    this->enterNameText.setOrigin(this->enterNameText.getGlobalBounds().width * 0.5f, this->enterNameText.getGlobalBounds().height * 0.5f);
    this->enterNameText.setPosition(this->newHsRect.getPosition().x + 12, this->newHsRect.getPosition().y + (this->newHsRect.getSize().y * 0.1));
    
    
    this->textRect.setSize(sf::Vector2f(this->newHsRect.getSize().x * 0.6f, 36));
    this->textRect.setFillColor(sf::Color::White);
    this->textRect.setOutlineColor(this->newHsRect.getOutlineColor());
    this->textRect.setOutlineThickness(2.0f);
    this->textRect.setOrigin(this->textRect.getSize().x * 0.5f, this->textRect.getSize().y * 0.5f);
    this->textRect.setPosition(this->newHsRect.getPosition().x, this->newHsRect.getPosition().y + (this->newHsRect.getSize().y * 0.25f));
    
    this->currentInput = "---";
    this->currentText.setFont(this->game->fontmgr.getRef("Consolas"));
    this->currentText.setString(this->currentInput);
    this->currentText.setCharacterSize(32);
    this->currentText.setColor(this->textRect.getOutlineColor());
    this->currentText.setOrigin(this->currentText.getGlobalBounds().width * 0.5f, this->currentText.getGlobalBounds().height * 7.5f);
    this->currentText.setPosition(this->textRect.getPosition().x, this->textRect.getPosition().y);
    
    this->okRect.setSize(sf::Vector2f(108, 36));
    this->okRect.setFillColor(sf::Color(255, 200, 150));
    this->okRect.setOutlineColor(sf::Color(255, 140, 60));
    this->okRect.setOutlineThickness(2.0f);
    this->okRect.setOrigin(this->okRect.getSize() * 0.5f);
    this->okRect.setPosition(this->newHsRect.getPosition().x - (this->newHsRect.getPosition().x * 0.3f), this->newHsRect.getPosition().y + (this->newHsRect.getSize().y * 0.4f));
    
    this->okText.setFont(this->game->fontmgr.getRef("Consolas"));
    this->okText.setString("OK");
    this->okText.setCharacterSize(32);
    this->okText.setColor(this->okRect.getOutlineColor());
    this->okText.setOrigin(this->okText.getGlobalBounds().width * 0.5f, this->okText.getGlobalBounds().height);
    this->okText.setPosition(this->okRect.getPosition().x, this->okRect.getPosition().y - 2);
    
    //clear name box
    this->clearNameRect.setSize(sf::Vector2f(108, 36));
    this->clearNameRect.setFillColor(sf::Color(255, 170, 170));
    this->clearNameRect.setOutlineColor(sf::Color(255, 120, 120));
    this->clearNameRect.setOutlineThickness(2.0f);
    this->clearNameRect.setOrigin(this->clearNameRect.getSize() * 0.5f);
    this->clearNameRect.setPosition(this->newHsRect.getPosition().x + (this->newHsRect.getPosition().x * 0.3f), this->newHsRect.getPosition().y + (this->newHsRect.getSize().y * 0.4f));
    
    this->clearNameText.setFont(this->game->fontmgr.getRef("Consolas"));
    this->clearNameText.setString("Clear");
    this->clearNameText.setCharacterSize(32);
    this->clearNameText.setColor(this->okRect.getOutlineColor());
    this->clearNameText.setOrigin(this->clearNameText.getGlobalBounds().width * 0.5f, this->clearNameText.getGlobalBounds().height);
    this->clearNameText.setPosition(this->clearNameRect.getPosition().x, this->clearNameRect.getPosition().y);
}

std::string GameOverPage::finalScoreString()
{
    std::string str;
    
    str = "Your final score: " + std::to_string(this->finalScore);
    
    return str;
}

inline void GameOverPage::resetColours()
{
    this->warmRect.setFillColor(sf::Color(255, 170, 170));
    this->warmRect.setOutlineColor(sf::Color(255, 120, 120));
    this->warmText.setColor(sf::Color(255, 120, 120));
    
    this->coolRect.setFillColor(sf::Color(170, 170, 255));
    this->coolRect.setOutlineColor(sf::Color(120, 120, 255));
    this->coolText.setColor(sf::Color(120, 120, 255));
    
    this->mainMenuRect.setFillColor(sf::Color(255, 200, 150));
    this->mainMenuRect.setOutlineColor(sf::Color(255, 140, 60));
    this->mainMenuText.setColor(sf::Color(255, 140, 60));
    
    if (newHighScore)
    {
        this->okRect.setFillColor(sf::Color(255, 200, 150));
        this->okRect.setOutlineColor(sf::Color(255, 140, 60));
        this->okText.setColor(this->okRect.getOutlineColor());
        
        this->clearNameRect.setFillColor(sf::Color(255, 170, 170));
        this->clearNameRect.setOutlineColor(sf::Color(255, 120, 120));
        this->clearNameText.setColor(this->clearNameRect.getOutlineColor());
    }
}

void GameOverPage::updateNameString(const sf::Uint32 unicodeKey)
{
    //Instantiate a char variable named character based on unicodeKey
    if (unicodeKey > 64 && unicodeKey < 128) //continue if the character is an alphabet or the backspace key
    {
        if (unicodeKey < 91 || (unicodeKey > 96 && unicodeKey < 123)) //blacklist the non-alphabet characters
        {
            char input = static_cast<char>(unicodeKey);
            if (unicodeKey > 96 && unicodeKey < 123)
                input = std::toupper(input); //convert lowercase to uppercase
            
            //iterate over currentInput and replace '-' with the alphabet
            for (auto iterator = this->currentInput.begin(); iterator != this->currentInput.end(); ++iterator)
            {
                if (*iterator == '-')
                {
                    *iterator = input;
                    break;
                }
            }
        }
    }
    this->currentText.setString(currentInput);
    this->currentText.setOrigin(this->currentText.getGlobalBounds().width * 0.5f, this->currentText.getGlobalBounds().height + 2);
}

void GameOverPage::draw(const float dt)
{
    this->game->window.draw(gameOverText);
    this->game->window.draw(finalScoreText);
    this->game->window.draw(warmRect);
    this->game->window.draw(coolRect);
    this->game->window.draw(mainMenuRect);
    this->game->window.draw(warmText);
    this->game->window.draw(coolText);
    this->game->window.draw(mainMenuText);
    
    if (this->newHighScore)
    {
        this->game->window.draw(hsWrapperBox);
        this->game->window.draw(newHsRect);
        this->game->window.draw(congratsText);
        this->game->window.draw(newHsText);
        this->game->window.draw(enterNameText);
        this->game->window.draw(textRect);
        this->game->window.draw(currentText);
        this->game->window.draw(okRect);
        this->game->window.draw(okText);
        this->game->window.draw(clearNameRect);
        this->game->window.draw(clearNameText);
    }
    
    return;
}

void GameOverPage::updateButton(sf::Vector2f mousePos)
{
    if (newHighScore)
    {
        if (mousePos.x > this->okRect.getPosition().x - (this->okRect.getSize().x * 0.5f) &&
            mousePos.x < this->okRect.getPosition().x + (this->okRect.getSize().x * 0.5f) &&
            mousePos.y > this->okRect.getPosition().y - (this->okRect.getSize().y * 0.5f) &&
            mousePos.y < this->okRect.getPosition().y + (this->okRect.getSize().y * 0.5f))
        {
            this->okRect.setFillColor(sf::Color(255, 140, 60));
            this->okRect.setOutlineColor(sf::Color(255, 200, 150));
            this->okText.setColor(this->okRect.getOutlineColor());
        }
        else if (mousePos.x > this->clearNameRect.getPosition().x - (this->clearNameRect.getSize().x * 0.5f) &&
                 mousePos.x < this->clearNameRect.getPosition().x + (this->clearNameRect.getSize().x * 0.5f) &&
                 mousePos.y > this->clearNameRect.getPosition().y - (this->clearNameRect.getSize().y * 0.5f) &&
                 mousePos.y < this->clearNameRect.getPosition().y + (this->clearNameRect.getSize().y * 0.5f))
        {
            this->clearNameRect.setFillColor(sf::Color(255, 120, 120));
            this->clearNameRect.setOutlineColor(sf::Color(255, 170, 170));
            this->clearNameText.setColor(this->clearNameRect.getOutlineColor());
        }
        else
        {
            this->resetColours();
        }
    }
    else
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
        else if (mousePos.x > this->mainMenuRect.getPosition().x - (this->mainMenuRect.getSize().x * 0.5f) &&
                 mousePos.x < this->mainMenuRect.getPosition().x + (this->mainMenuRect.getSize().x * 0.5f) &&
                 mousePos.y > this->mainMenuRect.getPosition().y - (this->mainMenuRect.getSize().y * 0.5f) &&
                 mousePos.y < this->mainMenuRect.getPosition().y + (this->mainMenuRect.getSize().y * 0.5f))
        {
            //invert the colours
            this->mainMenuRect.setFillColor(sf::Color(255, 140, 60));
            this->mainMenuRect.setOutlineColor(sf::Color(255, 200, 150));
            this->mainMenuText.setColor(this->mainMenuRect.getOutlineColor());
        }
        else
        {
            this->resetColours();
        }
    }
    
    return;
}

void GameOverPage::transition(sf::Vector2f mousePos)
{
    if (newHighScore)
    {
        if (mousePos.x > this->okRect.getPosition().x - (this->okRect.getSize().x * 0.5f) &&
            mousePos.x < this->okRect.getPosition().x + (this->okRect.getSize().x * 0.5f) &&
            mousePos.y > this->okRect.getPosition().y - (this->okRect.getSize().y * 0.5f) &&
            mousePos.y < this->okRect.getPosition().y + (this->okRect.getSize().y * 0.5f))
        {
            bool hasDash = false;
            for (auto iterator = currentInput.begin(); iterator != currentInput.end(); ++iterator)
            {
                if (*iterator == '-')
                {
                    hasDash = true;
                    break;
                }
            }
            if (!hasDash)
            {
                this->clickedInBox = true;
                this->toHighScores = true;
            }
        }
        else if (mousePos.x > this->clearNameRect.getPosition().x - (this->clearNameRect.getSize().x * 0.5f) &&
                 mousePos.x < this->clearNameRect.getPosition().x + (this->clearNameRect.getSize().x * 0.5f) &&
                 mousePos.y > this->clearNameRect.getPosition().y - (this->clearNameRect.getSize().y * 0.5f) &&
                 mousePos.y < this->clearNameRect.getPosition().y + (this->clearNameRect.getSize().y * 0.5f))
        {
            currentInput = "---";
            currentText.setString(currentInput);
        }
    }
    else
    {
        if (mousePos.x > this->warmRect.getPosition().x - (this->warmRect.getSize().x * 0.5f) &&
            mousePos.x < this->warmRect.getPosition().x + (this->warmRect.getSize().x * 0.5f) &&
            mousePos.y > this->warmRect.getPosition().y - (this->warmRect.getSize().y * 0.5f) &&
            mousePos.y < this->warmRect.getPosition().y + (this->warmRect.getSize().y * 0.5f))
        {
            this->clickedInBox = true;
            this->game->colourMode = Game::ColourMode::WARM;
            this->toGame = true;
        }
        else if (mousePos.x > this->coolRect.getPosition().x - (this->coolRect.getSize().x * 0.5f) &&
                 mousePos.x < this->coolRect.getPosition().x + (this->coolRect.getSize().x * 0.5f) &&
                 mousePos.y > this->coolRect.getPosition().y - (this->coolRect.getSize().y * 0.5f) &&
                 mousePos.y < this->coolRect.getPosition().y + (this->coolRect.getSize().y * 0.5f))
        {
            this->clickedInBox = true;
            this->game->colourMode = Game::ColourMode::COOL;
            this->toGame = true;
        }
        else if (mousePos.x > this->mainMenuRect.getPosition().x - (this->mainMenuRect.getSize().x * 0.5f) &&
                 mousePos.x < this->mainMenuRect.getPosition().x + (this->mainMenuRect.getSize().x * 0.5f) &&
                 mousePos.y > this->mainMenuRect.getPosition().y - (this->mainMenuRect.getSize().y * 0.5f) &&
                 mousePos.y < this->mainMenuRect.getPosition().y + (this->mainMenuRect.getSize().y * 0.5f))
        {
            this->clickedInBox = true;
            this->game->colourMode = Game::ColourMode::DEFAULT;
        }
    }
    
    return;
}