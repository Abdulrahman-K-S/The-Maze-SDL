/*
 * ===================================================
 * ===================================================
 *                SDL Graphics Wrapper
 *                     Revision 1
 *
 *            (C) 2015  Nick Stones-Havas
 *
 * ===================================================
 *
 *  C library for drawing to the screen.
 *
 * ===================================================
 * ===================================================
 */
#include <stdio.h>
#include "../header/gfx.h"

 /* Used to identify a texture structure in memory */
#define TEX_TAG 0x55AA

/* Error string buffer */
char errstr[256];

/*
 * SDL textures are stored in VRAM, so we need to manage
 * a RAM-persistent copy of the texture's pixel data that we
 * can write to. Allocated textures are stored in a linked
 * list so we can keep track of them all easily.
 */
typedef struct ManagedTexture_ ManagedTexture_;
struct ManagedTexture_ {
    void* pixelData; /* RAM copy of the texture */
    SDL_Texture* texture;
    Uint32 pitch;
    ManagedTexture_* next;
    ManagedTexture_* prev;
    Uint16 magicTag;
};
ManagedTexture_* managedTextures = NULL;

/* SDL Stuff */
SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

unsigned int screenWidth = -1;
unsigned int screenHeight = -1;

/*========================================================
 * Library debug functions
 *========================================================
 */

/**
 * gfxGetError - Get a string describing the last error encountered
 *               by this library.
 *
 * @Return: The error string.
*/
const char* gfxGetError()
{
    return errstr;
}

/**
 * gfxSetError - Set a string describing the last error encountered
 *               by this library.
*/
void gfxSetError(char* str, char showSdlErr)
{
    if (showSdlErr)
    {
        sprintf_s(errstr, "%s: %s", str, SDL_GetError());
    }
    else
    {
        sprintf_s(errstr, "%s", str);
    }
}

/*========================================================
 * GFX management functions
 *========================================================
 */

/**
 * initGFX - Initialize the graphics environment
 *
 * @title:  The title to use for the displayed window
 * @width:  The width of the displayed window in pixels
 * @height: The height of the displayed window in pixels
*/
int initGFX(char* title, unsigned int width, unsigned int height)
{
    if (window || renderer) return 0;

    screenWidth = width;
    screenHeight = height;

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        gfxSetError("Error initializing SDL", 1);
        return 0;
    }

    window = SDL_CreateWindow(title, 50, 50, width, height, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);

    if (!window || !renderer)
    {
        gfxSetError("Could not create SDL window", 1);
        return 0;
    }

    SDL_SetWindowTitle(window, title);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);

    return 1;
}

/**
 * createTexture - Create a texture buffer
 *
 * @width:  The width of the texture buffer
 * @height: The height of the texture buffer
 *
 * Returns: A pointer to the texture pixel buffer
*/
void* createTexture(unsigned int width, unsigned int height)
{
    Uint32* data;
    ManagedTexture_* newmtex;
    if (!width || !height || !renderer)
    {
        gfxSetError("SDL window has not been initialized yet", 0);
        return NULL;
    }

    newmtex = malloc(sizeof(ManagedTexture_));
    if (!newmtex)
    {
        return NULL;
    }
    newmtex->pitch = width * sizeof(Uint32);
    newmtex->next = NULL;
    newmtex->prev = NULL;
    newmtex->magicTag = TEX_TAG;

    newmtex->texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ABGR8888,
        SDL_TEXTUREACCESS_STREAMING, width, height);
    if (!(newmtex->texture))
    {
        free(newmtex);
        gfxSetError("Could not create texture", 1);
        return NULL;
    }

    data = malloc((sizeof(Uint32) * width * height) +
        sizeof(ManagedTexture_*));
    if (!data)
    {
        free(newmtex);
        return NULL;
    }

    /*
     * Hide a pointer to the managed struct before the actual pixel data.
     *
     * This allows the caller to only have to worry about the data they
     * want, while still allowing this library to perform more complicated
     * management tasks given only a reference to the pixel data.
     */
    *((ManagedTexture_**)data) = newmtex;
    newmtex->pixelData = ((ManagedTexture_**)data) + 1;

    /* Insert the item into the linked list */
    if (managedTextures)
    {
        newmtex->next = managedTextures;
        managedTextures->prev = newmtex;
    }
    managedTextures = newmtex;

    return newmtex->pixelData;
}

/**
 * destroyTexture - Free a texture buffer from memory
 *
 * @texture: A pointer to the texture to be destroyed
 *
 * Returns: 1 if the operation was successful, 0 otherwise.
*/
int destroyTexture(void* ptr)
{
    /* Recover the memory management structure before freeing anything */
    ManagedTexture_* mtex = *(((ManagedTexture_**)ptr) - 1);

    /* Don't do anything if it's not actually a managed structure */
    if (mtex->magicTag != TEX_TAG)
    {
        gfxSetError("Not a valid texture pointer", 0);
        return 0;
    }

    /* Prevent this structure from being somehow sent here again */
    mtex->magicTag = 0;

    /* Actual cleanup */
    free(((ManagedTexture_**)ptr) - 1);

    SDL_DestroyTexture(mtex->texture);

    if (mtex->prev) mtex->prev->next = mtex->next;
    if (mtex->next) mtex->next->prev = mtex->prev;
    if (managedTextures == mtex) managedTextures = mtex->next;
    free(mtex);

    return 1;
}

/**
 * displayFullscreenTexture - Draw a texture to the window's entire
 *                            rendering area.
 *
 * @texture: A pointer to the texture to be drawm.
 *
 * Returns: 1 if the operation was successful, 0 otherwise.
*/
void displayFullscreenTexture(void* texture)
{
    ManagedTexture_* mtex;

    if (!window || !renderer)
    {
        gfxSetError("SDL window has not been initialized yet", 0);
        return;
    }

    /* Recover the managed texture structure */
    mtex = *(((ManagedTexture_**)texture) - 1);

    /* Don't do anything if it's not actually a managed texture */
    if (mtex->magicTag != TEX_TAG)
    {
        gfxSetError("Not a valid texture pointer", 0);
        return;
    }

    SDL_UpdateTexture(mtex->texture, NULL, mtex->pixelData, mtex->pitch);

    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, mtex->texture, NULL, NULL);
    SDL_RenderPresent(renderer);
}

/**
 * destroyGFX - Terminate the graphics environment and free all allocated resources
*/
void destroyGFX() {
    /* Destroy all allocated textures */
    while (managedTextures) destroyTexture(managedTextures->pixelData);

    /* Clean everything else up */
    if (window && renderer) {
        SDL_DestroyRenderer(renderer);
        renderer = NULL;
        SDL_DestroyWindow(window);
        window = NULL;

        SDL_Quit();
    }
}


/*========================================================
 * Drawing functions
 *========================================================
 */

/**
 * setDrawColor - Set the current drawing color for primitives
 *
 * @r: The red channel of the color.
 * @g: The green channel of the color.
 * @b: The blue channel of the color.
 * @a: The alpha (blending) channel of the color.
*/
void setDrawColor(int r, int g, int b, int a)
{
    SDL_SetRenderDrawColor(renderer, r, g, b, a);
}

/**
 * drawLine - Draw a line between two points on the screen
 *
 * @x1: The starting point's x component.
 * @y1: The starting point's y component.
 * @x2: The finishing point's x component.
 * @y2: The finishing point's y component.
*/
void drawLine(int x1, int y1, int x2, int y2)
{
    int xOffset = 0;
    int yOffset = 0;

    if (x2 - x1 > 0) xOffset = -1;
    if (y2 - y1 > 0) yOffset = -1;

    SDL_RenderDrawLine(renderer, x1, y1, x2 + xOffset, y2 + yOffset);
}

/**
 * fillRect - Draw a filled rectangle to the screen
 *
 * @x: The x component of the top-left corner of the rectangle.
 * @y: The y component of the top-left corner of the rectangle.
 * @w: The width of the rectangle.
 * @h: The height of the rectangle.
*/
void fillRect(int x, int y, int w, int h)
{
    SDL_Rect rect;
    rect.x = x;
    rect.y = y;
    rect.w = w;
    rect.h = h;
    SDL_RenderFillRect(renderer, &rect);
}

/**
 * drawRect - Draw the outline of a rectangle to the screen
 *
 * @x: The x component of the top-left corner of the rectangle.
 * @y: The y component of the top-left corner of the rectangle.
 * @w: The width of the rectangle.
 * @h: The height of the rectangle.
*/
void drawRect(int x, int y, int w, int h)
{
    SDL_Rect rect;
    rect.x = x;
    rect.y = y;
    rect.w = w;
    rect.h = h;
    SDL_RenderDrawRect(renderer, &rect);
}


/**
 * presentRenderer - Refresh the primitive objects on the screen
*/
void presentRenderer()
{
    SDL_RenderPresent(renderer);
}

/**
 * clearRenderer - Clear the primitive objects on the screen
*/
void clearRenderer()
{
    SDL_RenderClear(renderer);
}
