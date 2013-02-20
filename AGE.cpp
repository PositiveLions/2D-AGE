#include "AGE.h"

Engine::Engine(int w, int h, int dispFlags)
{

    bool isRunning = true;

    screenWidth = w;
    screenHeight = h;

    //Re-direct stderr and stdout to AGE.log file
    freopen("AGE.log", "w", stderr);
    freopen("AGE.log", "w", stdout);

    std::cout << "Initializing (A)llegro (G)ame (E)ngine...\n";
    std::cout << "=========================================\n";

    std::cout << "Initializing Allegro 5...";
    if(!al_init())
    {
        std::cerr << "Error: Can't Initialize Allegro 5.\n";
    }
    else
    {
        std::cout << "Success!\n";
    }

    std::cout << "Initializing Allegro 5 Image Add-on...";
    if(!al_init_image_addon())
    {
        std::cerr << "Error: Can't initialize Allegro image add-on.\n";
    }
    else
    {
        std::cout << "Success!\n";
    }

    std::cout << "Initializing Allegro 5 Font Add-ons...";
    al_init_font_addon();
    if(!al_init_ttf_addon())
    {
        std::cerr << "Error: Can't initialize Allegro font add-ons.\n";
    }
    else
    {
        std::cout << "Success!\n";
    }

    std::cout << "Initializing Allegro 5 Keyboard Support...";
    if(!al_install_keyboard())
    {
        std::cerr << "Error: Can't initialize Allegro keyboard support.\n";
    }
    else
    {
        std::cout << "Success!\n";
    }

    std::cout << "Initializing Allegro 5 Mouse Support...";
    if(!al_install_mouse())
    {
        std::cerr << "Error: Can't initialize Allegro mouse support.\n";
    }
    else
    {
        std::cout << "Success!\n";
    }

    std::cout << "Initializing Allegro 5 Joystick Support...";
    if(!al_install_joystick())
    {
        std::cerr << "Error: Can't initialize Allegro joystick support.\n";
    }
    else
    {
        std::cout << "Success!\n";
    }


    std::cout << "Creating screen...";
    al_set_new_display_flags(dispFlags);
    screen = al_create_display(screenWidth, screenHeight);
    if(screen == NULL)
    {
        std::cerr << "Error: Failed to create 'screen'.\n";
    }
    else
    {
        std::cout << "Success!\n";
    }

    std::cout << "Creating event queues...";
    displayEvents = al_create_event_queue();

    al_register_event_source(displayEvents, al_get_display_event_source(screen));
    std::cout << "Done!\n";

}

Engine::~Engine()
{

    std::cout << "Shutting down (A)llegro (G)ame (E)ngine...\n";
    std::cout << "==========================================\n";

    //clean-up
    std::cout << "Destroying event queues...";
    al_unregister_event_source(displayEvents, al_get_display_event_source(screen));

    al_destroy_event_queue(displayEvents);
    std::cout << "Done!\n";


    al_destroy_display(screen);
}


void Engine::handleDisplayEvents()
{
    ALLEGRO_EVENT tempEvent;

    while(al_get_next_event(displayEvents, &tempEvent))
    {
        if(tempEvent.type == ALLEGRO_EVENT_DISPLAY_CLOSE) isRunning = false;
    }

}
