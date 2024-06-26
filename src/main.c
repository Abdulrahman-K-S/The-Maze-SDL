#include <stdio.h>
#include <stdlib.h>

#include "../header/config.h"
#include "../header/raycaster.h"
#include "../header/renderer.h"
#include "../header/player.h"
#include "../header/map.h"

const short MAP[MAP_GRID_HEIGHT][MAP_GRID_WIDTH] = {
    {B,B,B,B,B,B,B,B,B,B},
    {B,0,0,0,0,0,0,0,0,B},
    {B,0,0,R,R,0,0,0,0,B},
    {B,0,0,R,0,0,0,0,0,B},
    {B,0,0,0,0,0,0,0,0,B},
    {B,0,0,0,0,0,R,0,0,B},
    {B,0,0,0,0,R,R,0,0,B},
    {B,0,0,0,0,0,0,0,0,B},
    {B,0,0,0,0,0,0,0,0,B},
    {B,B,B,B,B,B,B,B,B,B}
};


/* Program globals */
Uint32* screenBuffer = NULL;

const Uint32 COLORS[4] = {
    RGBtoABGR(255, 108, 80), // Red
    RGBtoABGR(0, 255, 0), // Green
    RGBtoABGR(66, 52, 248), // Blue
    RGBtoABGR(228, 232, 238) // Off White
};

/* Program toggles */
char gameIsRunning = TRUE;
char showMap = FALSE;

void render()
{
    if (showMap)
    {
        clearRenderer();
        renderMap();
    }
    else
    {
        /* Draw projected scene */
        renderProjectedScene();
    }
}

void consumeSDLEvents()
{
    SDL_Event event;
    char keyIsDown;

    while (SDL_PollEvent(&event))
    {
        keyIsDown = (event.type == SDL_KEYDOWN);
        switch (event.type)
        {
        case SDL_KEYUP:
        case SDL_KEYDOWN:
            switch (event.key.keysym.sym)
            {
            case SDLK_UP:
            case SDLK_w:
                movingForward = keyIsDown;
                break;
            case SDLK_DOWN:
            case SDLK_s:
                movingBack = keyIsDown;
                break;
            case SDLK_LEFT:
            case SDLK_a:
                turningLeft = keyIsDown;
                break;
            case SDLK_RIGHT:
            case SDLK_d:
                turningRight = keyIsDown;
                break;
            case SDLK_LSHIFT:
            case SDLK_RSHIFT:
                playerIsRunning = keyIsDown;
                break;
            case SDLK_ESCAPE:
                gameIsRunning = FALSE;
                break;
            case SDLK_m:
                if (keyIsDown) showMap = !showMap;
                break;
            case SDLK_LEFTBRACKET:
                if (keyIsDown && distFromViewplane - 20.0f > 100.0f) distFromViewplane -= 20.0f;
                break;
            case SDLK_RIGHTBRACKET:
                if (keyIsDown) distFromViewplane += 20.0f;
                break;
            default:
                break;
            }
            break;
        case SDL_QUIT:
            gameIsRunning = FALSE;
            break;
        default:
            break;
        }
    }
}

void runGame()
{
    long gameTicks = 0;
    long time;

    do
    {
        time = SDL_GetTicks();

        /* Handle SDL key events */
        consumeSDLEvents();

        /* Update the player */
        updatePlayer();

        /* Update the raycaster */
        updateRaycaster();

        /* Render a frame */
        render();

        /* Fixed delay before next frame */
        SDL_Delay(10);

        /* Print FPS every 500 frames */
        if (!(gameTicks++ % 500))
            fprintf(stderr, "FPS: %.2f\n", 1000.0f / (float)(SDL_GetTicks() - time));
    } while (gameIsRunning);
}

int setupWindow()
{
    int x, y;

    if (!initGFX("Raycaster", WINDOW_WIDTH, WINDOW_HEIGHT)) return FALSE;

    screenBuffer = createTexture(WINDOW_WIDTH, WINDOW_HEIGHT);

    if (!screenBuffer) return FALSE;

    /* Make the texture initially gray */
    for (x = 0; x < WINDOW_WIDTH; x++)
    {
        for (y = 0; y < WINDOW_HEIGHT; y++)
        {
            screenBuffer[(WINDOW_WIDTH * y) + x] = 0xFFAAAAAA;
        }
    }

    return TRUE;
}

int main() 
{
    if (!setupWindow())
    {
        fprintf(stderr, "Could not initialize raycaster!\n");
        return EXIT_FAILURE;
    }
    initPlayer();
    initRaycaster();
    runGame();

    destroyGFX();
    return EXIT_SUCCESS;
}
