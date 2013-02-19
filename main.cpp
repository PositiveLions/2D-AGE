#include "allegro5/allegro.h"
#include "AGE.h"

int main(int argc, char* argv[])
{

    Engine e(800, 600, ALLEGRO_WINDOWED);


    while(e.isRunning)
    {
        e.handleDisplayEvents();

        al_flip_display();
    }



}
