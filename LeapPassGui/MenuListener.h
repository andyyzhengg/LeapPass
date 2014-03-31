//
//  MenuListener.h
//  LeapPass
//
//  Created by Andy Zheng on 3/29/14.
//  Copyright (c) 2014 Andy Zheng. All rights reserved.
//

#ifndef __LeapPass__MenuListener__
#define __LeapPass__MenuListener__

#include "Leap.h"
#include "SDL_GUI.h"
#include <iostream>

class MenuListener : public Leap::Listener
{
public:
    virtual void onInit(const Leap::Controller&);
    virtual void onConnect(const Leap::Controller&);
    virtual void onDisconnect(const Leap::Controller&);
    virtual void onExit(const Leap::Controller&);
    virtual void onFrame(const Leap::Controller&);
    virtual void onFocusGained(const Leap::Controller&);
    virtual void onFocusLost(const Leap::Controller&);
    bool save = false, finished = false, selected = false;
};

#endif /* defined(__LeapPass__MenuListener__) */
