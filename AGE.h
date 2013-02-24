#ifndef AGE_H
#define AGE_H

#include <cstdio>
#include <iostream>

#include "allegro5/allegro.h"
#include "allegro5/allegro_image.h"
#include "allegro5/allegro_font.h"
#include "allegro5/allegro_ttf.h"


/*
    This class is a base class for the game engine.  It handles the main game
    loop toggle switch, contains information about the display, as well as
    functions to manipulate the display.  This class also handles event
    processing. To use this class, create a derived class with a constructor
    that passes the necessary values to Engine's constructor and defines the
    following virtual methods:

        void keyboardInput(KEYBOARD_EVENT_TYPE kbdEventType, int keyCode)
            This function handles keyboard input, kbdEventType specifies whether
            the key was pressed or released (KEY_DOWN or KEY_UP) and keyCode
            specifies which key was pressed.  For keyCode's see the Allegro API
            manual (Keyboard Routines -> Key codes).
*/
class Engine
{
protected:
    ALLEGRO_DISPLAY* screen;    //Primary surface
    int screenWidth;
    int screenHeight;
    ALLEGRO_EVENT_QUEUE* displayEvents;     //Display / Window events
    ALLEGRO_EVENT_QUEUE* keyboardEvents;    //Keyboard input events

public:
    Engine(int w, int h, int dispFlags);
    ~Engine();

    enum KEYBOARD_EVENT_TYPE {KEY_DOWN, KEY_UP};

    bool isRunning;     //Use this for the main game loop

    //Event handling functions
    void handleDisplayEvents();
    void handleKeyboardEvents();
    virtual void keyboardInput(KEYBOARD_EVENT_TYPE kbdEventType, int keyCode) = 0;

};

#endif
