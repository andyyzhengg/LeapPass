//
//  PassListener.cpp
//  LeapPass
//
//  Created by Andy Zheng on 3/28/14.
//  Copyright (c) 2014 Andy Zheng. All rights reserved.
//

#include "PassListener.h"

using namespace Leap;

PassListener::PassListener(bool save) : _save(save)
{
    for(int i = 0; i < 4; ++i)
    {
        pins[i] = false;
    }
}

void
PassListener::onInit(const Controller& controller) {}

void
PassListener::onConnect(const Controller& controller)
{
    controller.enableGesture(Gesture::TYPE_SWIPE);
}

void
PassListener::onDisconnect(const Controller& controller){}

void
PassListener::onExit(const Controller& controller) {}

void
PassListener::onFrame(const Controller& controller)
{
    const Frame frame = controller.frame();
    const Frame prevFrame = controller.frame(1);
    if (!frame.hands().isEmpty())
    {
        //Only works on the first hand
        const Hand hand = frame.hands()[0];
        const FingerList fingers = hand.fingers();
        //If the fist is closed we store the last symbol that was shown to the Leap Motion.
        if (fingers.count() <= 1 && !finished)
        {
            //If the last move was not a fist we proceed
            if(!lastMoveFist)
            {
                if(numPins < 4)
                {
                    password+=lastSymbol;
                    std::cout << lastSymbol << std::endl;
                    lastMoveFist = true;
                    pins[numPins++] = true;
                }
            }else
            {
                //Otherwise we check if someone closed their fist/ used one finger to backspace.
                Gesture gesture = frame.gestures()[0];
                if(Gesture::TYPE_SWIPE == gesture.type())
                {
                    SwipeGesture swipe = gesture;
                    if((swipe.direction()[0] < 0.0) && (swipe.state() == Gesture::STATE_START))
                    {
                        if(numPins > 0)
                        {
                            password.pop_back();
                            pins[--numPins] = false;
                            std::cout << password << std::endl;
                        }
                    }
                }
                
            }
        }
        else if(fingers.count() == 5 && !finished)
        {
            //If the hand is opened (five fingers out) then this signals us to terminate and store/check password
            std::cout << "\nPassword is: " << password << std::endl;
            if(_save)
            {
                std::hash<std::string> out; // Password is stored in a text file as a hash.
                std::size_t str_out = out(password);
                std::ofstream outFile;
                outFile.open("pass.txt");
                if(outFile.is_open())
                {
                    outFile << str_out;
                    outFile.close();
                }
                else
                {
                    std::cerr << "Error opening pass.txt" << std::endl;
                }
                finished = true;
            }else
            {
                std::ifstream inFile;
                inFile.open("pass.txt");
                if(inFile.is_open())
                {
                    std::size_t str_in;
                    inFile >> str_in;
                    if(str_in == std::hash<std::string>()(password))
                    {
                        finished = true;
                        std::cout << "Success!" << std::endl;
                    }else
                    {
                        std::cout << "Wrong! Try again." << std::endl;
                        password.clear();
                        for(int i = 0; i < 4; ++i)
                        {
                            pins[i] = false;
                        }
                        numPins = 0;
                    }
                    
                }else
                {
                    finished = true;
                    std::cerr << "Error opening pass.txt" << std::endl;
                }
            }
        }else
        {
            //Get symbol, should only be able to change symbol if it is a valid symbol
            if(lastMoveFist)
            {
                lastSymbol = getSymbol(fingers);
                if(lastSymbol != '\0')
                    lastMoveFist = false;
            }
        }
        
    }
}

void
PassListener::onFocusGained(const Controller& controller) {}

void
PassListener::onFocusLost(const Controller& controller) {}

/* Return a char based on the hand symbol. Based on sign language. */
char
PassListener::getSymbol(const Leap::FingerList& fingers)
{
    char retChar = {};
    float angle = {};
    float avgFingerSpd = 0.0;
    Vector *fingersVector = new Vector[fingers.count()];
    for(int i = 0; i < fingers.count(); ++i)
    {
        fingersVector[i] = fingers[i].direction();
        avgFingerSpd+=fingers[i].tipVelocity()[0];
        avgFingerSpd+=fingers[i].tipVelocity()[1];
        avgFingerSpd+=fingers[i].tipVelocity()[2];
        avgFingerSpd /= 3;
    }
    avgFingerSpd /= fingers.count();
    if(avgFingerSpd < 5.0 && avgFingerSpd > -5.0)
    {
        switch(fingers.count())
        {
                //1 and 5 are used for special signals.
            case 2:
                angle = fingersVector[0].angleTo(fingersVector[1]);
                if(angle <= .75)
                {
                    retChar = '2';
                }
                else if((angle > .75) && (fingers[0].tipPosition().distanceTo(fingers[1].tipPosition()) > 150.0))
                {
                    retChar = 'y';
                }else
                {
                    retChar = 'l';
                }
                std::cout << "angle from 0 to 1: " << angle << " distance between 0 and 1: " << fingers[0].tipPosition().distanceTo(fingers[1].tipPosition()) << std::endl;
                break;
            case 3:
                angle = fingersVector[1].angleTo(fingersVector[2]);
                if((angle > .5) && (fingers[1].tipPosition().distanceTo(fingers[2].tipPosition()) > 100.0))
                {
                    retChar = '7';
                }else
                {
                    retChar = '3';
                }
                std::cout << "angle from 1 to 2: " << angle << " distance between 1 and 2: " << fingers[1].tipPosition().distanceTo(fingers[2].tipPosition()) << std::endl;
                break;
            case 4:
                retChar = '4';
                break;
            default:
                break;
        }
    }
    delete [] fingersVector;
    return retChar;
}
