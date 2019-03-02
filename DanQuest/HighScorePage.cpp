//
//  HighScorePage.cpp
//  DanQuest
//
//  Created by 17xiangyangt on 8/5/15.
//  Copyright (c) 2015 Tang. All rights reserved.
//

#include "HighScorePage.h"

HighScorePage::HighScorePage(Game* game)
{
    this->game = game;
    this->isExit = false;
    this->drawWarning = false;
    
    //construct the table
    this->table.tableBodyRect.setSize(sf::Vector2f(this->game->gameWidth - 68, this->game->gameHeight - 204));
    this->table.tableBodyRect.setFillColor(sf::Color(255, 255, 255, 200));
    this->table.tableBodyRect.setOutlineColor(sf::Color::Black);
    this->table.tableBodyRect.setOutlineThickness(1.0f);
    this->table.tableTitleRect.setSize(sf::Vector2f(this->table.tableBodyRect.getSize().x, 48));
    this->table.tableTitleRect.setFillColor(sf::Color(255, 225, 200));
    this->table.tableTitleRect.setOutlineColor(sf::Color::Black);
    this->table.tableTitleRect.setOutlineThickness(1.0f);
    this->table.tableSubRect.setSize(this->table.tableTitleRect.getSize());
    this->table.tableSubRect.setFillColor(sf::Color(255, 140, 60));
    this->table.tableSubRect.setOutlineColor(sf::Color::Black);
    this->table.tableSubRect.setOutlineThickness(1.0f);
    
    for (auto& line : this->table.lines)
    {
        line = new sf::RectangleShape(sf::Vector2f(1, 388));
        line->setFillColor(sf::Color::Black);
    }
    
    //define the properties of each table element
    this->table.tableBodyRect.setPosition(sf::Vector2f(34, 34));
    this->table.tableTitleRect.setPosition(this->table.tableBodyRect.getPosition());
    this->table.tableSubRect.setPosition(sf::Vector2f(this->table.tableTitleRect.getPosition().x, this->table.tableTitleRect.getPosition().y + this->table.tableTitleRect.getSize().y));
    
    this->table.lines[0]->setPosition(84, 82);
    this->table.lines[1]->setPosition(180, 82);
    this->table.lines[2]->setPosition(400, 82);
    this->table.lines[3]->setPosition(452, 82);
    this->table.lines[4]->setPosition(548, 82);
    
    this->title.setFont(this->game->fontmgr.getRef("Consolas"));
    this->title.setString("High Scores");
    this->title.setCharacterSize(36);
    this->title.setColor(sf::Color(255, 140, 60));
    this->title.setOrigin(this->title.getGlobalBounds().width * 0.5f, this->title.getGlobalBounds().height * 0.5f);
    this->title.setPosition(this->table.tableTitleRect.getPosition().x + (this->table.tableTitleRect.getSize().x * 0.5f), this->table.tableTitleRect.getPosition().y + (this->table.tableTitleRect.getSize().y * 0.25f));
    
    
    for (sf::Text& subHeading : subHeadings)
    {
        subHeading.setFont(this->game->fontmgr.getRef("Consolas"));
        subHeading.setCharacterSize(20);
        subHeading.setColor(sf::Color(255, 225, 200));
        subHeading.setOrigin(subHeading.getGlobalBounds().width * 0.5f, subHeading.getGlobalBounds().height * 0.5f);
    }
    this->subHeadings[0].setString("Rank");
    this->subHeadings[0].setPosition
    (
        ((this->table.tableBodyRect.getPosition().x + this->table.lines[0]->getPosition().x) / 2.0f) - 22,
        this->table.tableSubRect.getPosition().y + 8
    );
    
    this->subHeadings[1].setString("Name");
    this->subHeadings[1].setPosition
    (
     ((this->table.lines[0]->getPosition().x + this->table.lines[1]->getPosition().x) - 42) / 2.0f,
     this->table.tableSubRect.getPosition().y + 8
     );
    
    this->subHeadings[2].setString("Score");
    this->subHeadings[2].setPosition
    (
     ((this->table.lines[1]->getPosition().x + this->table.lines[2]->getPosition().x) - 54) / 2.0f,
     this->table.tableSubRect.getPosition().y + 8
     );
    
    this->subHeadings[3].setString("Rank");
    this->subHeadings[3].setPosition
    (
     ((this->table.lines[2]->getPosition().x + this->table.lines[3]->getPosition().x) / 2.0f) - 22,
     this->table.tableSubRect.getPosition().y + 8
     );
    
    this->subHeadings[4].setString("Name");
    this->subHeadings[4].setPosition
    (
     ((this->table.lines[3]->getPosition().x + this->table.lines[4]->getPosition().x) - 42) / 2.0f,
     this->table.tableSubRect.getPosition().y + 8
     );
    
    this->subHeadings[5].setString("Score");
    this->subHeadings[5].setPosition
    (
     ((this->table.lines[4]->getPosition().x + (this->table.tableBodyRect.getPosition() + this->table.tableBodyRect.getSize()).x) - 54) / 2.0f,
     this->table.tableSubRect.getPosition().y + 8
     );
    
    //load the scores by reading the file containing them (if the file exists)
    this->loadHighScores("highscores.txt");
    for (int i = 0; i < 10; ++i)
    {
        numberBuffer[i] = i + 1;
    }
    
    //using the sf::Text objects, make the scores and names drawable by assigning them a position and some font properties
    for (int i = 0; i < 10; ++i)
    {
        this->rankNumbers[i].setFont(this->game->fontmgr.getRef("Consolas"));
        this->rankNumbers[i].setString(std::to_string(numberBuffer[i]));
        this->rankNumbers[i].setCharacterSize(32);
        this->rankNumbers[i].setColor(sf::Color(255, 140, 60));
        
        this->winnerNames[i].setFont(this->game->fontmgr.getRef("Consolas"));
        this->winnerNames[i].setString(nameBuffer[i]);
        this->winnerNames[i].setCharacterSize(32);
        this->winnerNames[i].setColor(sf::Color(255, 140, 60));
        this->winnerNames[i].setOrigin(this->winnerNames[i].getGlobalBounds().width * 0.5f, 0);
        
        this->highScores[i].setFont(this->game->fontmgr.getRef("Consolas"));
        this->highScores[i].setString(std::to_string(scoreBuffer[i]));
        this->highScores[i].setCharacterSize(32);
        this->highScores[i].setColor(sf::Color(255, 140, 60));
        this->highScores[i].setOrigin(this->highScores[i].getGlobalBounds().width * 0.5f, 0);
        
        this->gameModes[i].setFont(this->game->fontmgr.getRef("Consolas"));
        this->gameModes[i].setString(modeBuffer[i]);
        this->gameModes[i].setCharacterSize(32);
        this->gameModes[i].setColor(sf::Color(255, 140, 60));
        //getGlobalBounds() does not give an accurate rectangle measure
        this->gameModes[i].setOrigin(sf::Vector2f(this->gameModes[i].getGlobalBounds().width * 0.5f, 0));
        if (this->modeBuffer[i] == "WARM")
        {
            this->gameModes[i].setColor(sf::Color(255, 150, 150));
            this->modeRect[i].setSize(sf::Vector2f(80, 36));
            this->modeRect[i].setFillColor(sf::Color(255, 210, 210));
            this->modeRect[i].setOutlineColor(sf::Color(255, 150, 150));
            this->modeRect[i].setOutlineThickness(1.0f);
            this->modeRect[i].setOrigin(this->modeRect[i].getSize() * 0.5f);
        }
        else if (this->modeBuffer[i] == "COOL")
        {
            this->gameModes[i].setColor(sf::Color(150, 150, 255));
            this->modeRect[i].setSize(sf::Vector2f(80, 36));
            this->modeRect[i].setFillColor(sf::Color(210, 210, 255));
            this->modeRect[i].setOutlineColor(sf::Color(150, 150, 255));
            this->modeRect[i].setOutlineThickness(1.0f);
            this->modeRect[i].setOrigin(this->modeRect[i].getSize() * 0.5f);
        }
    }
    
    //for rank 10, a 2 digit number (note: not exactly * 0.5f for proportioning purposes)
    this->rankNumbers[9].setOrigin(sf::Vector2f(this->rankNumbers[9].getGlobalBounds().width * 0.25f, 0));
    
    //set the positions of each entry (5 on each side)
    for (int i = 0; i < 5; ++i)
    {
        this->rankNumbers[i].setPosition(sf::Vector2f(this->subHeadings[0].getPosition().x + this->subHeadings[0].getGlobalBounds().width * 0.5 - 8, this->subHeadings[0].getPosition().y + (60 * (i + 1))));
        this->rankNumbers[i + 5].setPosition(sf::Vector2f(this->subHeadings[3].getPosition().x + this->subHeadings[3].getGlobalBounds().width * 0.5 - 8, this->subHeadings[3].getPosition().y + (60 * (i + 1))));
        
        this->winnerNames[i].setPosition(sf::Vector2f(this->subHeadings[1].getPosition().x - this->subHeadings[1].getGlobalBounds().width * 0.5 + 40, this->subHeadings[1].getPosition().y + (60 * (i + 1))));
        this->winnerNames[i + 5].setPosition(sf::Vector2f(this->subHeadings[4].getPosition().x - this->subHeadings[4].getGlobalBounds().width * 0.5 + 40, this->subHeadings[4].getPosition().y + (60 * (i + 1))));
        
        this->highScores[i].setPosition(sf::Vector2f(this->subHeadings[2].getPosition().x - this->subHeadings[2].getGlobalBounds().width * 0.5 - 8, this->subHeadings[2].getPosition().y + (60 * (i + 1))));
        this->highScores[i + 5].setPosition(sf::Vector2f(this->subHeadings[5].getPosition().x - this->subHeadings[5].getGlobalBounds().width * 0.5 - 8, this->subHeadings[5].getPosition().y + (60 * (i + 1))));
        
        this->gameModes[i].setPosition(sf::Vector2f(this->subHeadings[2].getPosition().x - this->subHeadings[2].getGlobalBounds().width * 0.5 + 80, this->subHeadings[2].getPosition().y + (60 * (i + 1))));
        this->gameModes[i + 5].setPosition(sf::Vector2f(this->subHeadings[5].getPosition().x - this->subHeadings[5].getGlobalBounds().width * 0.5 + 80, this->subHeadings[5].getPosition().y + (60 * (i + 1))));
        
        this->modeRect[i].setPosition(this->gameModes[i].getPosition().x + 2, this->gameModes[i].getPosition().y + 22);
        this->modeRect[i + 5].setPosition(this->gameModes[i + 5].getPosition().x + 2, this->gameModes[i + 5].getPosition().y + 22);
    }
    
    //construct the back button
    this->backRect.setSize(sf::Vector2f(144, 48));
    this->backRect.setFillColor(sf::Color(255, 200, 150));
    this->backRect.setOutlineColor(sf::Color(255, 140, 60));
    this->backRect.setOutlineThickness(2.0f);
    this->backRect.setOrigin(this->backRect.getSize() * 0.5f);
    this->backRect.setPosition(sf::Vector2f(this->game->gameWidth * 0.3f, this->game->gameHeight * 0.85f));
    
    this->backText.setFont(this->game->fontmgr.getRef("Consolas"));
    this->backText.setString("Back");
    this->backText.setCharacterSize(32);
    this->backText.setColor(sf::Color(255, 140, 60));
    this->backText.setOrigin(this->backText.getGlobalBounds().width * 0.5f, this->backText.getGlobalBounds().height);
    this->backText.setPosition(sf::Vector2f(this->backRect.getPosition()));
    
    //construct the clear scores button
    this->deleteRect.setSize(sf::Vector2f(270, 48));
    this->deleteRect.setFillColor(sf::Color(255, 210, 210));
    this->deleteRect.setOutlineColor(sf::Color(255, 150, 150));
    this->deleteRect.setOutlineThickness(2.0f);
    this->deleteRect.setOrigin(this->deleteRect.getSize() * 0.5f);
    this->deleteRect.setPosition(sf::Vector2f(this->game->gameWidth * 0.7f, this->game->gameHeight * 0.85f));
    
    this->deleteText.setFont(this->game->fontmgr.getRef("Consolas"));
    this->deleteText.setString("Clear Scores");
    this->deleteText.setCharacterSize(32);
    this->deleteText.setColor(sf::Color(255, 150, 150));
    this->deleteText.setOrigin(this->deleteText.getGlobalBounds().width * 0.5, this->deleteText.getGlobalBounds().height);
    this->deleteText.setPosition(sf::Vector2f(this->deleteRect.getPosition()));
    
    //the warning page
    this->warningBox.setSize(sf::Vector2f(this->game->gameWidth, this->game->gameHeight));
    this->warningBox.setFillColor(sf::Color(0, 0, 0, 128));
    this->warningBox.setPosition(sf::Vector2f(0, 0));
    
    this->noticeRect.setSize(sf::Vector2f(this->game->gameWidth * 0.6f, this->game->gameHeight * 0.5f));
    this->noticeRect.setFillColor(sf::Color(255, 200, 150));
    this->noticeRect.setOutlineColor(sf::Color(255, 140, 60));
    this->noticeRect.setOutlineThickness(2.0f);
    this->noticeRect.setOrigin(this->noticeRect.getSize() * 0.5f);
    this->noticeRect.setPosition(this->game->gameWidth * 0.5f, this->game->gameHeight * 0.5f);
    
    this->noticeText.setFont(this->game->fontmgr.getRef("Consolas"));
    this->noticeText.setString("Delete your high scores?");
    this->noticeText.setCharacterSize(32);
    this->noticeText.setColor(sf::Color(255, 140, 60));
    this->noticeText.setOrigin(this->noticeText.getGlobalBounds().width * 0.5, this->noticeText.getGlobalBounds().height);
    this->noticeText.setPosition(this->noticeRect.getPosition().x, this->noticeRect.getPosition().y * 0.75);
    
    this->yesRect.setSize(sf::Vector2f(108, 36));
    this->yesRect.setFillColor(sf::Color(255, 210, 210));
    this->yesRect.setOutlineColor(sf::Color(255, 150, 150));
    this->yesRect.setOutlineThickness(2.0f);
    this->yesRect.setOrigin(this->yesRect.getSize() * 0.5f);
    this->yesRect.setPosition(this->noticeRect.getPosition().x - (this->noticeRect.getSize().x * 0.2f), this->noticeRect.getPosition().y + (this->noticeRect.getSize().y * 0.25f));
    
    this->yesText.setFont(this->game->fontmgr.getRef("Consolas"));
    this->yesText.setString("Yes");
    this->yesText.setCharacterSize(32);
    this->yesText.setColor(sf::Color(255, 150, 150));
    this->yesText.setOrigin(this->yesText.getGlobalBounds().width * 0.5, this->yesText.getGlobalBounds().height + 2);
    this->yesText.setPosition(this->yesRect.getPosition().x, this->yesRect.getPosition().y);
    
    this->noRect.setSize(sf::Vector2f(108, 36));
    this->noRect.setFillColor(sf::Color(210, 210, 255));
    this->noRect.setOutlineColor(sf::Color(150, 150, 255));
    this->noRect.setOutlineThickness(2.0f);
    this->noRect.setOrigin(this->noRect.getSize() * 0.5f);
    this->noRect.setPosition(this->noticeRect.getPosition().x + (this->noticeRect.getSize().x * 0.2f), this->noticeRect.getPosition().y + (this->noticeRect.getSize().y * 0.25f));
    
    this->noText.setFont(this->game->fontmgr.getRef("Consolas"));
    this->noText.setString("No");
    this->noText.setCharacterSize(32);
    this->noText.setColor(sf::Color(150, 150, 255));
    this->noText.setOrigin(this->noText.getGlobalBounds().width * 0.5, this->noText.getGlobalBounds().height + 2);
    this->noText.setPosition(this->noRect.getPosition().x, this->noRect.getPosition().y);
}

HighScorePage::HighScorePage(Game* game, std::string& newName, int newScore)
{
    *this = *new HighScorePage(game);
    this->addEntry(newName, newScore);
    
    this->backText.setString("OK");
    this->backText.setPosition(this->backText.getPosition().x + 16, this->backText.getPosition().y);
    
    //reset the scoreboard properties to update to the new high scores
    for (int i = 0; i < 10; ++i)
    {
        this->rankNumbers[i].setString(std::to_string(numberBuffer[i]));
        this->winnerNames[i].setString(nameBuffer[i]);
        this->winnerNames[i].setOrigin(this->winnerNames[i].getGlobalBounds().width * 0.5f, 0);
        this->highScores[i].setString(std::to_string(scoreBuffer[i]));
        this->highScores[i].setOrigin(this->highScores[i].getGlobalBounds().width * 0.5f, 0);
        this->gameModes[i].setString(modeBuffer[i]);
        this->gameModes[i].setOrigin(sf::Vector2f(this->gameModes[i].getGlobalBounds().width * 0.5f, 0));
        
        if (this->modeBuffer[i] == "WARM")
        {
            this->gameModes[i].setColor(sf::Color(255, 150, 150));
            this->modeRect[i].setSize(sf::Vector2f(80, 36));
            this->modeRect[i].setFillColor(sf::Color(255, 210, 210));
            this->modeRect[i].setOutlineColor(sf::Color(255, 150, 150));
            this->modeRect[i].setOutlineThickness(1.0f);
            this->modeRect[i].setOrigin(this->modeRect[i].getSize() * 0.5f);
        }
        else if (this->modeBuffer[i] == "COOL")
        {
            this->gameModes[i].setColor(sf::Color(150, 150, 255));
            this->modeRect[i].setSize(sf::Vector2f(80, 36));
            this->modeRect[i].setFillColor(sf::Color(210, 210, 255));
            this->modeRect[i].setOutlineColor(sf::Color(150, 150, 255));
            this->modeRect[i].setOutlineThickness(1.0f);
            this->modeRect[i].setOrigin(this->modeRect[i].getSize() * 0.5f);
        }
        
        //reset the positions of each entry due to formatting (improve later)
        for (int i = 0; i < 5; ++i)
        {
            this->rankNumbers[i].setPosition(sf::Vector2f(this->subHeadings[0].getPosition().x + this->subHeadings[0].getGlobalBounds().width * 0.5 - 8, this->subHeadings[0].getPosition().y + (60 * (i + 1))));
            this->rankNumbers[i + 5].setPosition(sf::Vector2f(this->subHeadings[3].getPosition().x + this->subHeadings[3].getGlobalBounds().width * 0.5 - 8, this->subHeadings[3].getPosition().y + (60 * (i + 1))));
            
            this->winnerNames[i].setPosition(sf::Vector2f(this->subHeadings[1].getPosition().x - this->subHeadings[1].getGlobalBounds().width * 0.5 + 40, this->subHeadings[1].getPosition().y + (60 * (i + 1))));
            this->winnerNames[i + 5].setPosition(sf::Vector2f(this->subHeadings[4].getPosition().x - this->subHeadings[4].getGlobalBounds().width * 0.5 + 40, this->subHeadings[4].getPosition().y + (60 * (i + 1))));
            
            this->highScores[i].setPosition(sf::Vector2f(this->subHeadings[2].getPosition().x - this->subHeadings[2].getGlobalBounds().width * 0.5 - 8, this->subHeadings[2].getPosition().y + (60 * (i + 1))));
            this->highScores[i + 5].setPosition(sf::Vector2f(this->subHeadings[5].getPosition().x - this->subHeadings[5].getGlobalBounds().width * 0.5 - 8, this->subHeadings[5].getPosition().y + (60 * (i + 1))));
            
            this->gameModes[i].setPosition(sf::Vector2f(this->subHeadings[2].getPosition().x - this->subHeadings[2].getGlobalBounds().width * 0.5 + 80, this->subHeadings[2].getPosition().y + (60 * (i + 1))));
            this->gameModes[i + 5].setPosition(sf::Vector2f(this->subHeadings[5].getPosition().x - this->subHeadings[5].getGlobalBounds().width * 0.5 + 80, this->subHeadings[5].getPosition().y + (60 * (i + 1))));
            
            this->modeRect[i].setPosition(this->gameModes[i].getPosition().x + 2, this->gameModes[i].getPosition().y + 22);
            this->modeRect[i + 5].setPosition(this->gameModes[i + 5].getPosition().x + 2, this->gameModes[i + 5].getPosition().y + 22); //check root cause of modeRect dislocation and fix later
        }
    }
}

HighScorePage::~HighScorePage()
{
    for (auto line : this->table.lines)
    {
        delete line;
    }
}

void HighScorePage::addEntry(std::string& newName, int newScore)
{
    //find the score's position in relation to the other scores
    int pos = 1;
    for (int score : this->scoreBuffer)
    {
        if (newScore < score)
        {
            ++pos;
        }
    }
    
    //push back all records behind the new score's position & overwrite the previous 10th place record
    for (int i = 9; i > pos - 1; --i)
    {
        scoreBuffer[i] = scoreBuffer[i - 1];
        nameBuffer[i] = nameBuffer[i - 1];
        modeBuffer[i] = modeBuffer[i - 1];
    }
    
    //insert the new high score at the appropriate position
    this->scoreBuffer[pos - 1] = newScore;
    this->nameBuffer[pos - 1] = newName;
    if (this->game->colourMode == Game::ColourMode::WARM)
    {
        this->modeBuffer[pos - 1] = "WARM";
    }
    else if (this->game->colourMode == Game::ColourMode::COOL)
    {
        this->modeBuffer[pos - 1] = "COOL";
    }
}

void HighScorePage::draw(const float dt)
{
    this->game->window.draw(this->table.tableBodyRect);
    this->game->window.draw(this->table.tableTitleRect);
    this->game->window.draw(this->table.tableSubRect);
    for (auto& line : this->table.lines)
    {
        this->game->window.draw(*line);
    }
    
    this->game->window.draw(this->title);
    for (sf::Text& subHeading : this->subHeadings)
    {
        this->game->window.draw(subHeading);
    }
    
    for (int i = 0; i < 10; ++i)
    {
        this->game->window.draw(this->modeRect[i]);
        this->game->window.draw(this->rankNumbers[i]);
        this->game->window.draw(this->winnerNames[i]);
        this->game->window.draw(this->highScores[i]);
        this->game->window.draw(this->gameModes[i]);
    }
    
    this->game->window.draw(this->backRect);
    this->game->window.draw(this->deleteRect);
    this->game->window.draw(this->backText);
    this->game->window.draw(this->deleteText);
    
    if (this->drawWarning)
    {
        this->game->window.draw(this->warningBox);
        this->game->window.draw(this->noticeRect);
        this->game->window.draw(this->noticeText);
        this->game->window.draw(this->yesRect);
        this->game->window.draw(this->yesText);
        this->game->window.draw(this->noRect);
        this->game->window.draw(this->noText);
    }
}

inline void HighScorePage::resetColours()
{
    this->backRect.setFillColor(sf::Color(255, 200, 150));
    this->backRect.setOutlineColor(sf::Color(255, 140, 60));
    this->backText.setColor(sf::Color(255, 140, 60));
    
    this->deleteRect.setFillColor(sf::Color(255, 210, 210));
    this->deleteRect.setOutlineColor(sf::Color(255, 150, 150));
    this->deleteText.setColor(sf::Color(255, 150, 150));
    
    this->yesRect.setFillColor(sf::Color(255, 210, 210));
    this->yesRect.setOutlineColor(sf::Color(255, 150, 150));
    this->yesText.setColor(sf::Color(255, 150, 150));
    
    this->noRect.setFillColor(sf::Color(210, 210, 255));
    this->noRect.setOutlineColor(sf::Color(150, 150, 255));
    this->noText.setColor(sf::Color(150, 150, 255));
}

void HighScorePage::updateButton(sf::Vector2f mousePos)
{
    //change the colour of the buttons when the mouse cursor is inside the boxes
    if (this->drawWarning)
    {
        if (mousePos.x > this->yesRect.getPosition().x - (this->yesRect.getSize().x * 0.5f) &&
            mousePos.x < this->yesRect.getPosition().x + (this->yesRect.getSize().x * 0.5f) &&
            mousePos.y > this->yesRect.getPosition().y - (this->yesRect.getSize().y * 0.5f)&&
            mousePos.y < this->yesRect.getPosition().y + (this->yesRect.getSize().y * 0.5f))
        {
            //invert the colours
            this->yesRect.setFillColor(sf::Color(255, 150, 150));
            this->yesRect.setOutlineColor(sf::Color(255, 210, 210));
            this->yesText.setColor(this->yesRect.getOutlineColor());
        }
        else if (mousePos.x > this->noRect.getPosition().x - (this->noRect.getSize().x * 0.5f) &&
                 mousePos.x < this->noRect.getPosition().x + (this->noRect.getSize().x * 0.5f) &&
                 mousePos.y > this->noRect.getPosition().y - (this->noRect.getSize().y * 0.5f) &&
                 mousePos.y < this->noRect.getPosition().y + (this->noRect.getSize().y * 0.5f))
        {
            //invert the colours
            this->noRect.setFillColor(sf::Color(150, 150, 255));
            this->noRect.setOutlineColor(sf::Color(210, 210, 255));
            this->noText.setColor(this->noRect.getOutlineColor());
        }
        else
        {
            //reset the colours
            this->resetColours();
        }
    }
    else
    {
        if (mousePos.x > this->backRect.getPosition().x - (this->backRect.getSize().x * 0.5f) &&
            mousePos.x < this->backRect.getPosition().x + (this->backRect.getSize().x * 0.5f) &&
            mousePos.y > this->backRect.getPosition().y - (this->backRect.getSize().y * 0.5f)&&
            mousePos.y < this->backRect.getPosition().y + (this->backRect.getSize().y * 0.5f))
        {
            //invert the colours
            this->backRect.setFillColor(sf::Color(255, 140, 60));
            this->backRect.setOutlineColor(sf::Color(255, 200, 150));
            this->backText.setColor(this->backRect.getOutlineColor());
        }
        else if (mousePos.x > this->deleteRect.getPosition().x - (this->deleteRect.getSize().x * 0.5f) &&
                 mousePos.x < this->deleteRect.getPosition().x + (this->deleteRect.getSize().x * 0.5f) &&
                 mousePos.y > this->deleteRect.getPosition().y - (this->deleteRect.getSize().y * 0.5f) &&
                 mousePos.y < this->deleteRect.getPosition().y + (this->deleteRect.getSize().y * 0.5f))
        {
            //invert the colours
            this->deleteRect.setFillColor(sf::Color(255, 150, 150));
            this->deleteRect.setOutlineColor(sf::Color(255, 210, 210));
            this->deleteText.setColor(this->deleteRect.getOutlineColor());
        }
        else
        {
            //reset the colours
            this->resetColours();
        }
    }
}

void HighScorePage::transition(sf::Vector2f mousePos)
{
    //depending on the user's previous mode, redirect them back to the previous mode
    if (this->drawWarning)
    {
        if (mousePos.x > this->yesRect.getPosition().x - (this->yesRect.getSize().x * 0.5f) &&
            mousePos.x < this->yesRect.getPosition().x + (this->yesRect.getSize().x * 0.5f) &&
            mousePos.y > this->yesRect.getPosition().y - (this->yesRect.getSize().y * 0.5f)&&
            mousePos.y < this->yesRect.getPosition().y + (this->yesRect.getSize().y * 0.5f))
        {
            this->clearScores("highscores.txt");
            this->drawWarning = false;
        }
        else if (mousePos.x > this->noRect.getPosition().x - (this->noRect.getSize().x * 0.5f) &&
                 mousePos.x < this->noRect.getPosition().x + (this->noRect.getSize().x * 0.5f) &&
                 mousePos.y > this->noRect.getPosition().y - (this->noRect.getSize().y * 0.5f) &&
                 mousePos.y < this->noRect.getPosition().y + (this->noRect.getSize().y * 0.5f))
        {
            this->drawWarning = false;
        }
    }
    else
    {
        if (mousePos.x > this->backRect.getPosition().x - (this->backRect.getSize().x * 0.5f) &&
            mousePos.x < this->backRect.getPosition().x + (this->backRect.getSize().x * 0.5f) &&
            mousePos.y > this->backRect.getPosition().y - (this->backRect.getSize().y * 0.5f)&&
            mousePos.y < this->backRect.getPosition().y + (this->backRect.getSize().y * 0.5f))
        {
            this->saveHighScores("highscores.txt");
            this->isExit = true;
            
        }
        //delete the high score board
        else if (mousePos.x > this->deleteRect.getPosition().x - (this->deleteRect.getSize().x * 0.5f) &&
                 mousePos.x < this->deleteRect.getPosition().x + (this->deleteRect.getSize().x * 0.5f) &&
                 mousePos.y > this->deleteRect.getPosition().y - (this->deleteRect.getSize().y * 0.5f) &&
                 mousePos.y < this->deleteRect.getPosition().y + (this->deleteRect.getSize().y * 0.5f))
        {
            this->drawWarning = true;
        }
    }
}

void HighScorePage::loadHighScores(const std::string& filename)
{
    /* Instantiate a file reader object, to read from the high score file (in text mode)
     * Extract information from the file
     * Assign the extracted information to the appropriate buffers
     */
    std::ifstream file;
    file.open(filename, std::ios::in);
    
    std::string tempBuffer[10];
    int bufferCount = 0;
    
    if (file.is_open())
    {
        std::string line;
        while (std::getline(file, line))
        {
            if (bufferCount < 10)
            {
                tempBuffer[bufferCount] = line;
                ++bufferCount;
            }
        }
        
        for (int i = 0; i < bufferCount; ++i)
        {
            //read and split according to needs
            int index = 0;
            int stringExtStart = 0;
            
            
            while (index < tempBuffer[i].length())
            {
                if (tempBuffer[i][index] == '.')
                    break;
                
                ++index;
            }
            std::string numTemp = tempBuffer[i].substr(stringExtStart, index - stringExtStart);
            if (numTemp != "")
                this->numberBuffer[i] = std::stoi(numTemp);
            
            ++index;
            stringExtStart = index;
            
            
            while (index < tempBuffer[i].length())
            {
                if (tempBuffer[i][index] == ':')
                    break;
                
                ++index;
            }
            std::string nameTemp = tempBuffer[i].substr(stringExtStart, index - stringExtStart);
            
            if (nameTemp != "---" && nameTemp != "--" && nameTemp != "-" && nameTemp != "") //possibilities elimination
                this->nameBuffer[i] = nameTemp;
            else
                this->nameBuffer[i] = "---";
            
            ++index;
            stringExtStart = index;
            
            
            while (index < tempBuffer[i].length())
            {
                if (tempBuffer[i][index] == '(')
                    break;
                
                ++index;
            }
            std::string scoreTemp = tempBuffer[i].substr(stringExtStart, index - stringExtStart);
            if (scoreTemp != "")
                this->scoreBuffer[i] = std::stoi(scoreTemp);
            else
                this->scoreBuffer[i] = 0;
            
            ++index;
            stringExtStart = index;
            
            
            while (index < tempBuffer[i].length())
            {
                if (tempBuffer[i][index] == ')')
                    break;
                
                ++index;
            }
            std::string modeTemp = tempBuffer[i].substr(stringExtStart, index - stringExtStart);
            std::string faults[5] {"----", "---", "--", "-", ""};
            int faultCounter = 0;
            for (std::string& fault : faults)
            {
                if (modeTemp == fault)
                    ++faultCounter;
            }
            
            if (faultCounter == 0)
                this->modeBuffer[i] = modeTemp;
            else
                this->modeBuffer[i] = "----";
            
            ++index;
            stringExtStart = index;
        }
    }
    file.close();
}

void HighScorePage::saveHighScores(const std::string& filename)
{
    /* Instantiate a file writer object, to write to the high score file (in text mode)
     * Record all information in the page object to the file
     */
    std::ofstream file;
    file.open(filename, std::ios::out);
    
    if (file.is_open())
    {
        for (int i = 0; i < 10; ++i)
        {
            file << std::to_string(numberBuffer[i]) << "." << nameBuffer[i] << ":" << std::to_string(scoreBuffer[i]) << "(" << modeBuffer[i] << ")" << std::endl;
        }
    }
    
    file.close();
}

void HighScorePage::clearScores(const std::string& filename)
{
    //clear the contents on the scoreboard
    for (int i = 0; i < 10; ++i)
    {
        this->nameBuffer[i] = "---";
        this->modeBuffer[i] = "----";
        this->scoreBuffer[i] = 0;
        
        this->winnerNames[i].setString(nameBuffer[i]);
        this->gameModes[i].setString(modeBuffer[i]);
        this->gameModes[i].setColor(sf::Color(255, 140, 60));
        this->highScores[i].setString(std::to_string(scoreBuffer[i]));
        
        this->modeRect[i].setSize(sf::Vector2f(0, 0));
    }
}