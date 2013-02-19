#ifndef AGE_H
#define AGE_H

#include <cstdio>
#include <iostream>

#include "allegro5/allegro.h"
#include "allegro5/allegro_image.h"
#include "allegro5/allegro_font.h"
#include "allegro5/allegro_ttf.h"

class Engine
{
private:
    ALLEGRO_DISPLAY* screen;
    int screenWidth;
    int screenHeight;
    ALLEGRO_EVENT_QUEUE* displayEvents;

public:
    bool isRunning;

    Engine(int w, int h, int dispFlags);
    ~Engine();
    void handleDisplayEvents();

};



#endif
