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
        //this is defined below main()
        void keyboardInput(KEYBOARD_EVENT_TYPE kbdEventType, int keyCode);

    public:
        myEngine(int w, int h, int dispType) : Engine(w, h, dispType) {}
};


//Test harness for AGE development
int main(int argc, char* argv[])
{

    //Initialize AGE
    myEngine e(800, 600, ALLEGRO_WINDOWED);

    //Create a tileMapping and populate it with data from "test.tmap"
    TileMapping testMapping;
    testMapping.loadFromFile("test.tmap");

    //Create a map named "Test Map" from the file "test.map"
    TileMap myMap("Test Map", "test2.map");
    //Set myMap's tileMapping (tileset) to testMapping's
    myMap.setTileMapping(&testMapping);



    //Main game loop
    while(e.isRunning)
    {
        //Event processing
        e.handleDisplayEvents();
        e.handleKeyboardEvents();



        myMap.DrawMap(e.getDisplay());


        //Blit the primary surface to the monitor
        al_flip_display();
    }




}



//This is where you put your keyboard input code
void myEngine::keyboardInput(KEYBOARD_EVENT_TYPE kbdEventType, int keyCode)
{

    switch(kbdEventType)
    {
        //Key pressed event
        case KEY_DOWN:
            switch(keyCode)
            {
                case ALLEGRO_KEY_ESCAPE:
                    isRunning = false;
                    break;

                case ALLEGRO_KEY_RIGHT:
                    //myMap.changeScreen(TileMap::RIGHT);
                    break;

                default:
                    break;
            }
            break;

        //Key released event
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
