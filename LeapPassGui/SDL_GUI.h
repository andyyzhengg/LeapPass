//
//  SDL_GUI.h
//  LeapPassGui
//
//  Created by Andy Zheng on 3/29/14.
//  Copyright (c) 2014 Andy Zheng. All rights reserved.
//

#ifndef __LeapPassGui__SDL_GUI__
#define __LeapPassGui__SDL_GUI__

#include <SDL2/SDL.h>
#include <SDL2_ttf/SDL_ttf.h>
#include <SDL2_image/SDL_image.h>

/*
struct imageWrapper
{
    SDL_Texture *tex = nullptr;
};

struct rectWrapper
{
    SDL_Rect dst;
};
*/

class SDL_GUI
{
public:
    const int SCREEN_WIDTH = 960;
    const int SCREEN_HEIGHT = 800;
    const char *font_name = "Snoutlike.ttf"; // Googled for ttf files
    int centerX, centerY;
    SDL_Window *win = nullptr;
    SDL_Renderer *ren = nullptr;
    TTF_Font *font = nullptr;
    SDL_Texture *imageTexture = nullptr;
    //imageWrapper imageTexture[4];
    //rectWrapper dstArr[4];
    SDL_Texture *fontTexture = nullptr;
    bool pins[4]; // array of images
    char numPins = 0;
    void init();
    void loadImageTexture(char c);
    void loadTTexture(bool save);
    void clean();
    bool save = false;
};
#endif /* defined(__LeapPassGui__SDL_GUI__) */
