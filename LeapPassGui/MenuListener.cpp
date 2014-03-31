//
//  MenuListener.cpp
//  LeapPass
//
//  Created by Andy Zheng on 3/29/14.
//  Copyright (c) 2014 Andy Zheng. All rights reserved.
//

#include "MenuListener.h"

using namespace Leap;

void
MenuListener::onInit(const Controller& controller) {}

void
MenuListener::onConnect(const Controller& controller)
{
    controller.enableGesture(Gesture::TYPE_SCREEN_TAP);
    controller.enableGesture(Gesture::TYPE_SWIPE);
}

void
MenuListener::onDisconnect(const Controller& controller) {}

void
MenuListener::onExit(const Controller& controller) {}

/* A menu for choosing to save a new password or to load an old password and check with hand gestures */
void
MenuListener::onFrame(const Controller& controller)
{
    const Frame frame = controller.frame();
    const Frame prevFrame = controller.frame(1);
    Gesture gesture = frame.gestures()[0];
    
    switch (gesture.type())
    {
        case Gesture::TYPE_SWIPE:
        {
            SwipeGesture swipe = gesture;
            //Swipe right to Load
            if(swipe.direction()[0] > 0.0)
            {
                if(swipe.state() == Gesture::STATE_START)
                {
                    std::cout << "Load" << std::endl;
                    selected = false;
                }
            }
            else
            {
                //Swipe left to save
                if(swipe.state() == Gesture::STATE_START)
                {
                    std::cout << "Save" << std::endl;
                    selected = true;
                }
            }
            break;
        }
        case Gesture::TYPE_SCREEN_TAP:
        {
            ScreenTapGesture screentap = gesture;
            save = selected;
            save ? std::cout << "Save selected" << std::endl : std::cout << " Load selected" << std::endl;
            finished = true;
            break;
        }
        default:
            break;
    }
}

void
MenuListener::onFocusGained(const Controller& controller) {}

void
MenuListener::onFocusLost(const Controller& controller) {}
