#include "allegro5/allegro.h"
#include "AGE.h"
#include "maps.h"


/*
    Derive a class from the Engine class.  Constructor must match the one below.
    This class also defines the pure-virtual function keyboardInput - necessary
    for handling keyboard input.
*/
class myEngine : public Engine
{
    private:
        void keyboardInput(KEYBOARD_EVENT_TYPE kbdEventType, int keyCode);
    public:
        myEngine(int w, int h, int dispType) : Engine(w, h, dispType) {}
};


//Test harness for AGE development
int main(int argc, char* argv[])
{

    //Initialize AGE
    myEngine e(800, 600, ALLEGRO_WINDOWED);

    TileMapping testMapping;
    testMapping.loadFromFile("test.tmap");

    Screen s(25, 18);

    //Main game loop
    while(e.isRunning)
    {
        //Event processing
        e.handleDisplayEvents();
        e.handleKeyboardEvents();

        al_draw_bitmap(testMapping.getImage(0), 200, 200, 0);

        //Blit the primary surface to the monitor
        al_flip_display();
    }



}


//This is where you put your keyboard input code
void myEngine::keyboardInput(KEYBOARD_EVENT_TYPE kbdEventType, int keyCode)
{

    switch(kbdEventType)
    {
        case KEY_DOWN:
            switch(keyCode)
            {
                case ALLEGRO_KEY_ESCAPE:
                    isRunning = false;
                    break;

                default:
                    break;
            }
            break;

        case KEY_UP:
            switch(keyCode)
            {

                default:
                    break;
            }
            break;

        default:
            break;
    }

}
