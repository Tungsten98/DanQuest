
//
// Project Name: DanQuest
//

#include "Game.h"
#include "GameStateStart.h"

int main()
{
    Game game;
    
    game.pushState(new GameStateStart(&game));
    game.gameLoop();
    
    return 0;
}

/* PROBLEMS:
 * 1. Misalligned highscore box
 * 2. Letters from name keep disappearing each time high score table is opened
 * 3. Name cannot be seen when keying in name
 */