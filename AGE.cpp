#include "AGE.h"

/*
    Constructor for the engine class.  This initializes Allegro, redirects
    stderr and stdout streams to "AGE.log", creates a display with the specified
    width, height, and display flags, and initializes the event handling system.
*/
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

    //Initialize Allegro 5
    std::cout << "Initializing Allegro 5...";
    if(!al_init())
    {
        std::cerr << "Error: Can't Initialize Allegro 5.\n";
        isRunning = false;
    }
    else
    {
        std::cout << "Success!\n";
    }

    //Initialize Allegro's Image add-ons
    std::cout << "Initializing Allegro 5 Image Add-on...";
    if(!al_init_image_addon())
    {
        std::cerr << "Error: Can't initialize Allegro image add-on.\n";
        isRunning = false;
    }
    else
    {
        std::cout << "Success!\n";
    }

    //Initialize Allegro's Font and TTF add-ons
    std::cout << "Initializing Allegro 5 Font Add-ons...";
    al_init_font_addon();
    if(!al_init_ttf_addon())
    {
        std::cerr << "Error: Can't initialize Allegro font add-ons.\n";
        isRunning = false;
    }
    else
    {
        std::cout << "Success!\n";
    }

    //Initialize Allegro's keyboard routines
    std::cout << "Initializing Allegro 5 Keyboard Support...";
    if(!al_install_keyboard())
    {
        std::cerr << "Error: Can't initialize Allegro keyboard support.\n";
        isRunning = false;
    }
    else
    {
        std::cout << "Success!\n";
    }

    //Initialize Allegro's mouse routines
    std::cout << "Initializing Allegro 5 Mouse Support...";
    if(!al_install_mouse())
    {
        std::cerr << "Error: Can't initialize Allegro mouse support.\n";
        isRunning = false;
    }
    else
    {
        std::cout << "Success!\n";
    }

    //Initialize Allegro's joystick routines
    std::cout << "Initializing Allegro 5 Joystick Support...";
    if(!al_install_joystick())
    {
        std::cerr << "Error: Can't initialize Allegro joystick support.\n";
        isRunning = false;
    }
    else
    {
        std::cout << "Success!\n";
    }

    //Create the display using the values passed to the constructor
    std::cout << "Creating screen...";
    al_set_new_display_flags(dispFlags);
    screen = al_create_display(screenWidth, screenHeight);
    if(screen == NULL)
    {
        std::cerr << "Error: Failed to create 'screen'.\n";
        isRunning = false;
    }
    else
    {
        std::cout << "Success!\n";
    }

    //Create each individual event queues (individual for flexibility in design)
    std::cout << "Creating event queues...";
    displayEvents = al_create_event_queue();
    keyboardEvents = al_create_event_queue();

    //Attach event sources to their corresponding event queues
    //TODO:
    al_register_event_source(displayEvents, al_get_display_event_source(screen));
    al_register_event_source(keyboardEvents, al_get_keyboard_event_source());
    std::cout << "Done!\n";

}

/*
    Destructor for the Engine class.  Performs necessary clean-up for the game
    engine.  Currently only unregisters event sources from their corresponding
    event queues and destroys the queues.  Also releases the primary surface.
*/
Engine::~Engine()
{

    std::cout << "Shutting down (A)llegro (G)ame (E)ngine...\n";
    std::cout << "==========================================\n";

    //Unregister event sources and destroy event queues
    std::cout << "Destroying event queues...";
    al_unregister_event_source(displayEvents, al_get_display_event_source(screen));
    al_unregister_event_source(keyboardEvents, al_get_keyboard_event_source());

    al_destroy_event_queue(displayEvents);
    al_destroy_event_queue(keyboardEvents);
    std::cout << "Done!\n";

    //Release the primary surface
    al_destroy_display(screen);
}


/*
    Handles processing of display events.  Currently this only enables the
    program to terminate gracefully when the window is closed via the X button

    TODO: Possibly make this a virtual function so that users can over-ride it's
        default behavior
*/
void Engine::handleDisplayEvents()
{

    ALLEGRO_EVENT tempEvent;

    while(al_get_next_event(displayEvents, &tempEvent))
    {
        if(tempEvent.type == ALLEGRO_EVENT_DISPLAY_CLOSE) isRunning = false;
    }

}


/*
    Handles processing of keyboard events.  This function processes keyboard
    events and passes the type of event (key pressed or key released) and which
    key was pressed to the keyboardInput(...) function.  The keyboardInput(...)
    function is virtual, should be overloaded, and is where you will put your
    input code for the keyboard.
*/
void Engine::handleKeyboardEvents()
{

    ALLEGRO_EVENT tempEvent;

    while(al_get_next_event(keyboardEvents, &tempEvent))
    {
        switch(tempEvent.type)
        {
            case ALLEGRO_EVENT_KEY_DOWN:
                keyboardInput(KEY_DOWN, tempEvent.keyboard.keycode);
                break;

            case ALLEGRO_EVENT_KEY_UP:
                keyboardInput(KEY_UP, tempEvent.keyboard.keycode);
                break;

            default:
                break;
        }

    }

}
