#include "allegro5/allegro.h"
#include "AGE.h"
#include "maps.h"
#include "characters.h"

//debug
#include "custom_characters.h"


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

        TileMap myMap;
        CharacterFactory<customPlayer> customPFactory;
};


//Test harness for AGE development
int main(int argc, char* argv[])
{

    //Initialize AGE
    myEngine e(800, 576, ALLEGRO_WINDOWED);

    //Create a tileMapping and populate it with data from "test.tmap"
    TileMapping testMapping;
    testMapping.loadFromFile("test.tmap");

    //Create a map named "Test Map" from the file "test2.map"
    e.myMap.loadFromFile("test2.map");
    //Set myMap's tileMapping (tileset) to testMapping's
    e.myMap.setTileMapping(&testMapping);

    //Create, load, and initialize a character through the character factory
    e.customPFactory.createCharacter("player1");
    e.customPFactory.getCharacter("player1")->animations.loadFromFile("main_character.chr");
    e.customPFactory.getCharacter("player1")->setXCoord(384);
    e.customPFactory.getCharacter("player1")->setYCoord(272);


    //Main game loop
    while(e.isRunning)
    {
        //Event processing
        e.handleDisplayEvents();
        e.handleKeyboardEvents();

        //Logic
        e.customPFactory.getCharacter("player1")->update(e.myMap);

        //Drawing
        e.myMap.DrawMap(e.getDisplay());
        e.customPFactory.getCharacter("player1")->drawCharacter();

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
                    isRunning = false;  //quit
                    break;

                case ALLEGRO_KEY_RIGHT:
                    //Positive velocity on X-axis
                    customPFactory.getCharacter("player1")->setXVelocity(1);
                    break;

                case ALLEGRO_KEY_LEFT:
                    //Negative velocity on X-axis
                    customPFactory.getCharacter("player1")->setXVelocity(-1);
                    break;

                case ALLEGRO_KEY_UP:
                    //Negative velocity on Y-axis
                    customPFactory.getCharacter("player1")->setYVelocity(-1);
                    break;

                case ALLEGRO_KEY_DOWN:
                    //Positive velocity on Y-axis
                    customPFactory.getCharacter("player1")->setYVelocity(1);
                    break;

                default:
                    break;
            }
            break;

        //Key released event
        case KEY_UP:
            switch(keyCode)
            {
                case ALLEGRO_KEY_UP:
                    //Clear velocity on Y-axis if velocity on Y axis is negative
                    if(customPFactory.getCharacter("player1")->getYVelocity() < 0)
                    {
                        customPFactory.getCharacter("player1")->setYVelocity(0);
                    }
                    break;
                case ALLEGRO_KEY_DOWN:
                    //Clear velocity on Y-axis if velocity on Y axis is positive
                    if(customPFactory.getCharacter("player1")->getYVelocity() > 0)
                    {
                        customPFactory.getCharacter("player1")->setYVelocity(0);
                    }
                    break;
                case ALLEGRO_KEY_LEFT:
                    //Clear velocity on X-axis if velocity on X-axis is negative
                    if(customPFactory.getCharacter("player1")->getXVelocity() < 0)
                    {
                        customPFactory.getCharacter("player1")->setXVelocity(0);
                    }
                    break;
                case ALLEGRO_KEY_RIGHT:
                    //Clear velocity on X-axis if velocity on X-axis is positive
                    if(customPFactory.getCharacter("player1")->getXVelocity() > 0)
                    {
                        customPFactory.getCharacter("player1")->setXVelocity(0);
                    }
                    break;

                default:
                    break;
            }
            break;

        default:
            break;
    }

}
