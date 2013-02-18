#include "AGE.h"

Engine::Engine()
{
    bool isRunning = true;

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



}
