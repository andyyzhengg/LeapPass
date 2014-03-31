/* Credits to all mentors and tutorials I used for this project. 
 * SDL code adapted from SDL tutorials from TwinkleBear.
 * Leap Motion code adapted from examples in SDK and tutorials.
 */
#include "Leap.h"
#include "MenuListener.h"
#include "PassListener.h"
#include "SDL_GUI.h"
#include <iostream>

using namespace Leap;

/* SDL code is from Twinklebear tutorials */
int
main()
{
    //Get save or load from Menu Listener
    SDL_GUI *g = new SDL_GUI{};
    g->init();
    MenuListener mlistener;
    Controller controller;
    
    
    g->loadTTexture(false);
    int w, h;
    //SDL_QueryTexture(g->fontTexture, NULL, NULL, &w, &h);
    SDL_RenderClear(g->ren);
    SDL_QueryTexture(g->fontTexture, NULL, NULL, &w, &h);
    SDL_Rect dst = {g->SCREEN_WIDTH / 2 - w / 2, g->SCREEN_HEIGHT / 2 - w / 2,w,h};
	SDL_RenderCopy(g->ren, g->fontTexture, NULL, &dst);
    SDL_RenderPresent(g->ren);
    controller.addListener(mlistener);
    bool save = false;
    std::cout << "Swipe left to save and right to load and click to select" << std::endl;
    //Wait till menu get's a selection
    SDL_Event e;
    while(!mlistener.finished)
    {
        g->loadTTexture(mlistener.selected);
        int w, h;
        SDL_QueryTexture(g->fontTexture, NULL, NULL, &w, &h);
        SDL_RenderClear(g->ren);
        SDL_QueryTexture(g->fontTexture, NULL, NULL, &w, &h);
        SDL_Rect dst = {g->SCREEN_WIDTH / 2 - w / 2, g->SCREEN_HEIGHT / 2 - h / 2,w,h};
        SDL_RenderCopy(g->ren, g->fontTexture, NULL, &dst);
        SDL_RenderPresent(g->ren);
        while(SDL_PollEvent(&e))
        {
            if(e.type == SDL_QUIT)
                mlistener.finished = true;
            if(e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE)
                mlistener.finished = true;
            if(mlistener.finished == true)
            {
                controller.removeListener(mlistener);
                g->clean();
                delete g;
                return 0;
            }
        }
    }
    save = mlistener.save;
    /* Change the gui a bit since we want a new menu */
    SDL_SetRenderDrawColor(g->ren, 0x00, 0x00, 0x00, 0x00 );
    g->font = TTF_OpenFont(g->font_name, 144);
    SDL_Surface *s = TTF_RenderText_Shaded(g->font, save ? "Save" : "Load" , {255,255,255}, {0,0,0});
    g->fontTexture = SDL_CreateTextureFromSurface(g->ren, s);
    SDL_FreeSurface(s);
    TTF_CloseFont(g->font);
    //SDL_QueryTexture(g->fontTexture, NULL, NULL, &w, &h);
    SDL_RenderClear(g->ren);
    SDL_QueryTexture(g->fontTexture, NULL, NULL, &w, &h);
    dst = {g->SCREEN_WIDTH / 2 - w / 2, g->SCREEN_HEIGHT / 2 - h / 2,w,h};
	SDL_RenderCopy(g->ren, g->fontTexture, NULL, &dst);
    SDL_RenderPresent(g->ren);
    controller.removeListener(mlistener);
    //Pass the save bool to the password listener
    
    PassListener listener(save);
    controller.addListener(listener);
    bool first = true;
    //SDL_Texture *oldFrame = nullptr;
    while(!listener.finished)
    {
        if(listener.lastSymbol != '\0')
        {
            g->loadImageTexture(listener.lastSymbol);
            if(first)
            {
                SDL_SetRenderDrawColor(g->ren, 240, 250, 250, 0x00 );
                first = false;
            }
        }
        if(g->numPins < listener.numPins)
        {
            //adding a new image
            int w, h;
            //SDL_QueryTexture(g->imageTexture, NULL, NULL, &w, &h);
            SDL_RenderClear(g->ren);
            SDL_QueryTexture(g->imageTexture, NULL, NULL, &w, &h);
            SDL_Rect dst = {((g->SCREEN_WIDTH - 180*4)/5)*(g->numPins+1) + g->numPins*180, g->SCREEN_HEIGHT / 2 - h / 2,w,h};
            SDL_RenderCopy(g->ren, g->imageTexture, NULL, &dst);
            /*
            for(int i = 0; i < g->numPins; ++i)
            {
                SDL_QueryTexture(g->imageTexture[i].tex, NULL, NULL, &w, &h);
                g-> dstArr[i].dst = {((g->SCREEN_WIDTH - 180*4)/5)*(g->numPins) + (g->numPins-1)*180, g->SCREEN_HEIGHT / 2 - h / 2,w,h};
                SDL_RenderCopy(g->ren, g->imageTexture[i].tex, NULL, &(g->dstArr[i].dst));
            }
             */
            SDL_RenderPresent(g->ren);
            for(int i = g->numPins; i < 4; ++i)
            {
                g->pins[i] = listener.pins[i];
            }
            g->numPins = listener.numPins;
        }else if(g->numPins > listener.numPins)
        {
            //deleting newly added image
            int w, h;
            //SDL_QueryTexture(g->imageTexture, NULL, NULL, &w, &h);
            SDL_RenderClear(g->ren);
            SDL_QueryTexture(g->imageTexture, NULL, NULL, &w, &h);
            g->numPins = listener.numPins;
            SDL_Rect dst = {((g->SCREEN_WIDTH - 180*4)/5)*(g->numPins+1) + g->numPins*180, g->SCREEN_HEIGHT / 2 - h / 2,w,h};
            SDL_RenderCopy(g->ren, g->imageTexture, NULL, &dst);
/*
            for(int i = 0; i < g->numPins; ++i)
            {
                SDL_QueryTexture(g->imageTexture[i].tex, NULL, NULL, &w, &h);
                g->numPins = listener.numPins;
                g-> dstArr[i].dst = {((g->SCREEN_WIDTH - 180*4)/5)*(g->numPins+1) + g->numPins*180, g->SCREEN_HEIGHT / 2 - h / 2,w,h};
                SDL_RenderCopy(g->ren, g->imageTexture[i].tex, NULL, &(g->dstArr[i].dst));
            }
 */
            SDL_RenderPresent(g->ren);
            for(int i = 0; i < listener.numPins; ++i)
            {
                g->pins[i] = listener.pins[i];
            }

        }
        while(SDL_PollEvent(&e))
        {
            if(e.type == SDL_QUIT)
                listener.finished = true;
            if(e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE)
                listener.finished = true;
        }
    }
    controller.removeListener(listener);
    SDL_SetRenderDrawColor(g->ren, 0x00, 0x00, 0x00, 0x00 );
    g->font = TTF_OpenFont(g->font_name, 120);
    s = TTF_RenderText_Shaded(g->font, "Success! Esc to exit." , {255,255,255}, {0,0,0});
    g->fontTexture = SDL_CreateTextureFromSurface(g->ren, s);
    SDL_FreeSurface(s);
    TTF_CloseFont(g->font);
    //SDL_QueryTexture(g->fontTexture, NULL, NULL, &w, &h);
    SDL_RenderClear(g->ren);
    SDL_QueryTexture(g->fontTexture, NULL, NULL, &w, &h);
    dst = {g->SCREEN_WIDTH / 2 - w / 2, g->SCREEN_HEIGHT / 2 - h / 2,w,h};
	SDL_RenderCopy(g->ren, g->fontTexture, NULL, &dst);
    SDL_RenderPresent(g->ren);
    bool quit = false;
    while(!quit)
    {
        while(SDL_PollEvent(&e))
        {
            if(e.type == SDL_QUIT)
                quit = true;
            if(e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE)
                quit = true;
        }
    }
    g->clean();
    delete g;
    return 0;
}
