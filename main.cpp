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
    myEngine e(800, 600, ALLEGRO_WINDOWED);

    //Create a tileMapping and populate it with data from "test.tmap"
    TileMapping testMapping;
    testMapping.loadFromFile("test.tmap");

    //Create a map named "Test Map" from the file "test.map"
    //TileMap myMap("Test Map", "test2.map");
    //Set myMap's tileMapping (tileset) to testMapping's
    e.myMap.setTileMapping(&testMapping);
    e.myMap.loadFromFile("test2.map");



    //CharacterFactory<customPlayer> customPFactory;
    e.customPFactory.createCharacter("player1");
    e.customPFactory.getCharacter("player1")->setImage("test3.png");
    //e.customPFactory.getCharacter("player1")->getID();



    //Main game loop
    while(e.isRunning)
    {
        //Event processing
        e.handleDisplayEvents();
        e.handleKeyboardEvents();



        e.myMap.DrawMap(e.getDisplay());

        e.customPFactory.getCharacter("player1")->update();
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
                    isRunning = false;
                    break;

                case ALLEGRO_KEY_RIGHT:
                    //myMap.changeScreen(TileMap::RIGHT);
                    customPFactory.getCharacter("player1")->setXVelocity(1);
                    break;

                case ALLEGRO_KEY_LEFT:
                    //myMap.changeScreen(TileMap::LEFT);
                    customPFactory.getCharacter("player1")->setXVelocity(-1);
                    break;

                case ALLEGRO_KEY_UP:
                    //myMap.changeScreen(TileMap::UP);
                    customPFactory.getCharacter("player1")->setYVelocity(-1);
                    break;

                case ALLEGRO_KEY_DOWN:
                    //myMap.changeScreen(TileMap::DOWN);
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
                    if(customPFactory.getCharacter("player1")->getYVelocity() < 0)
                    {
                        customPFactory.getCharacter("player1")->setYVelocity(0);
                    }
                    break;
                case ALLEGRO_KEY_DOWN:
                    if(customPFactory.getCharacter("player1")->getYVelocity() > 0)
                    {
                        customPFactory.getCharacter("player1")->setYVelocity(0);
                    }
                    break;
                case ALLEGRO_KEY_LEFT:
                    if(customPFactory.getCharacter("player1")->getXVelocity() < 0)
                    {
                        customPFactory.getCharacter("player1")->setXVelocity(0);
                    }
                    break;
                case ALLEGRO_KEY_RIGHT:
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
