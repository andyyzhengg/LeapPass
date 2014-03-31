//
//  SDL_GUI.cpp
//  LeapPassGui
//
//  Created by Andy Zheng on 3/29/14.
//  Copyright (c) 2014 Andy Zheng. All rights reserved.
//

#include "SDL_GUI.h"
#include <iostream>
#include <string>

void
SDL_GUI::init()
{
    SDL_Init(SDL_INIT_EVERYTHING);
    IMG_Init(IMG_INIT_PNG);
    win = SDL_CreateWindow("Leap Pass Gui", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    SDL_SetRenderDrawColor( ren, 0xFF, 0xFF, 0xFF, 0xFF );
    TTF_Init();
}

void
SDL_GUI::loadImageTexture(char c)
{
    std::string fileName = " .png";
    fileName[0] = c;
    imageTexture = IMG_LoadTexture(ren, fileName.c_str());
}

void
SDL_GUI::loadTTexture(bool save)
{
    font = TTF_OpenFont(font_name, 144);
    SDL_Surface *s = TTF_RenderText_Shaded(font, save ? "Save" : "Load" , {0,0,0}, {255,255,255});
    fontTexture = SDL_CreateTextureFromSurface(ren, s);
    SDL_FreeSurface(s);
    TTF_CloseFont(font);
}

void
SDL_GUI::clean()
{
    /*
    for(int i = 0; i < 4; ++i)
        SDL_DestroyTexture(imageTexture[i].tex);
     */
    SDL_DestroyTexture(imageTexture);
    SDL_DestroyTexture(fontTexture);
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}