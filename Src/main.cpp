#include "Game.h"

Game *game = nullptr;

int main(int argc, char *argv[])
{
    const int FPS = 60;
    const int FRAME_DELAY = 1000 / FPS; // Target time per frame in milliseconds
    Uint32 frameStart;
    int frameTime;

    // Initialize game
    game = new Game();
    game->init("GameWindow", 800, 640, false);

    // Game loop with frame rate control
    while (game->running())
    {
        frameStart = SDL_GetTicks(); // Get start time of frame

        // Game loop components
        game->handleEvents();
        game->update();
        game->render();

        // Calculate frame time and delay if necessary
        frameTime = SDL_GetTicks() - frameStart;
        if (FRAME_DELAY > frameTime)
        {
            SDL_Delay(FRAME_DELAY - frameTime);
        }
    }

	game->clean();
	delete game;
	game = nullptr;
	return 0;
}