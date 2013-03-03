#ifndef MAPS_H
#define MAPS_H

#include <string>
#include <map>
#include <fstream>
#include <vector>

#include "allegro5/allegro.h"
#include "allegro5/allegro_image.h"


/*
    Base class for different types of derived map classes.
*/
class mapBase
{
    protected:
        std::string name;

    public:
        void setName(std::string mapName);
        std::string getName();
        virtual bool loadFromFile(std::string fileName) = 0;

};


/*
    TileMapping class - Loads a tileset from a file and populates a std::map
    with pair<int key, ALLEGRO_IMAGE* tile>
*/
class TileMapping
{
    private:
        std::map <unsigned int, ALLEGRO_BITMAP*> tMap;

    public:
        ~TileMapping();
        virtual void loadFromFile(std::string filename);
        ALLEGRO_BITMAP* getImage(unsigned int key);

};


/*
    Tile class - The basic building blocks of Screen's.  Holds a key that will
    associated with a TileMapping when a TileMap is loaded.
*/
class Tile
{
    private:
    static int dimension;
    unsigned int key;

    public:
        Tile();
        static void setDimension(int i);
        void setKey(int i);
        int getKey()
        {
            return key;
        }

};


/*
    Screen class - Basic building block of TileMaps.  Contains a vector of
    Tile's.
*/

//TODO: Screen won't be an appropriate name after more maps are added, as this
//      class is made specifically for TileMap's.  Keep a generic Screen object
//      and inherit a TileScreen class from it with TileMap screen specific
//      portions contained in it.
class Screen
{
    private:
        unsigned int widthInTiles;
        unsigned int heightInTiles;
        std::vector<Tile*> tiles;

    public:
        Screen(int width, int height);
        ~Screen();
        Tile* getTile(int i);

};


/*
    TileMap class - inherits from mapBase - Holds the necessary data for loading
    and displaying tile maps.
*/
class TileMap : public mapBase
{
    private:
        unsigned int widthInScreens;
        unsigned int heightInScreens;
        unsigned int screenWidthInTiles;
        unsigned int screenHeightInTiles;
        unsigned int tileDimension;

        TileMapping* tMap;
        std::vector<Screen*> screens;
        bool loadFromFile(std::string filename);

    public:
        TileMap(std::string mapName, std::string filename);
        ~TileMap();
        void setTileMapping(TileMapping* tMap);
        //TODO: since screens and tiles are in a one dimensional vector I should
        //      make static functions to get screens above, below, to the left,
        //      and to the right of the current screen - simple math but it
        //      shouldn't be the end-users responsibility to compute these
        //      values
        void DrawMap(unsigned int screenNum);


};


#endif
