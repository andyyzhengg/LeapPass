//
//  PassListener.h
//  LeapPass
//
//  Created by Andy Zheng on 3/28/14.
//  Copyright (c) 2014 Andy Zheng. All rights reserved.
//

#ifndef __LeapPass__PassListener__
#define __LeapPass__PassListener__

#include "Leap.h"
#include "SDL_GUI.h"
#include <functional>
#include <cmath>
#include <string>
#include <fstream>
#include <iostream>

class PassListener : public Leap::Listener
{
public:
    PassListener(bool save);
    virtual void onInit(const Leap::Controller&);
    virtual void onConnect(const Leap::Controller&);
    virtual void onDisconnect(const Leap::Controller&);
    virtual void onExit(const Leap::Controller&);
    virtual void onFrame(const Leap::Controller&);
    virtual void onFocusGained(const Leap::Controller&);
    virtual void onFocusLost(const Leap::Controller&);
    char getSymbol(const Leap::FingerList&);
    char lastSymbol = '\0';
    char numPins = 0;
    bool pins[4];
    bool lastMoveFist = true;
    bool finished = false;
    bool _save = false;
    std::string password {};
};

#endif /* defined(__LeapPass__PassListener__) */
