#include "maps.h"
#include <iostream>

//Sets the default Tile dimension
int Tile::dimension = 32;

//Sets the name of any map (or inherited map) object
void mapBase::setName(std::string mapName)
{
    name = mapName;
}


/*
    Loads a *.tmap file into the std::map.
*/
//TODO: get path of tmap file and prefix it to filenames, so that filenames in
//      the tmap file are relative to the tmap file itself. Also, add extension
//      checking (only allow *.tmap files)
void TileMapping::loadFromFile(std::string filename)
{

    unsigned int key = 0;
    std::string val = "";
    ALLEGRO_BITMAP* tempBitmap = NULL;

    //open file
    std::ifstream file;
    file.open(filename.c_str());

    //if file opened properly...
    if(!file.fail())
    {

        //load data from file
        while(!file.eof())
        {
            file >> key >> val;

            tempBitmap = al_load_bitmap(val.c_str());

            tMap.insert(std::pair<unsigned int, ALLEGRO_BITMAP*>(key, tempBitmap));
        }

        //close the file stream
        file.close();

    }

}

//Returns the image in the TileMapping object that is associated with the
//specified key.
ALLEGRO_BITMAP* TileMapping::getImage(unsigned int key)
{
    return tMap[key];
}

//Cleans up after TileMapping objects
TileMapping::~TileMapping()
{
    //Free's the memory allocated by each image object
    //( allocated in TileMapping::loadFromFile() )
    for(unsigned int x = 0; x < tMap.size(); x++)
    {
        al_destroy_bitmap(tMap[x]);
    }
}


//Sets the key of created tiles to a default of 0
Tile::Tile()
{
    key = 0;
}

//Sets a tiles dimension (only square tiles)
void Tile::setDimension(int i)
{
    dimension = i;
}

//Sets a tiles key to the specified value
void Tile::setKey(int i)
{
    key = i;
}


//Creates a Screen object with the specified width and height in tiles.
Screen::Screen(int width, int height)
{
    widthInTiles = width;
    heightInTiles = height;

    tiles.resize(width * height);

    // x < (width * height)  is probably faster than x <= (width * height) - 1
    for(unsigned int x = 0; x <= ((widthInTiles * heightInTiles) - 1); x++)
    {
        tiles[x] = new Tile;
    }

}

//Returns a Screen's Tile object at the specified number
Tile* Screen::getTile(int i)
{
    return tiles[i];
}

//Cleans up after Screen objects
Screen::~Screen()
{
    //Delete the Tile*'s from memory
    //( allocated in Screen's constructor )
    // x < (width * height)  is probably faster than x <= (width * height) - 1
    for(unsigned int x = 0; x <= ((widthInTiles * heightInTiles) - 1); x++)
    {
        delete tiles[x];
    }
}


TileMap::TileMap()
{
    name = "";
    currentScreen = 0;
    widthInScreens = 0;
    heightInScreens = 0;
    screenWidthInTiles = 0;
    screenHeightInTiles = 0;
    tileDimension = 0;
}


//Creates a TileMap object with the specified name from the specified file
//NOTE: calls loadFromFile(filename)
TileMap::TileMap(std::string mapName, std::string filename)
{
    name = mapName;

    TileMap::loadFromFile(filename);
}


//Loads a tilemap from a *.map file - gets called from the constructor
//TODO: possibly make this private?
//TODO: add code to check file extension and only allow *.map files to be loaded
bool TileMap::loadFromFile(std::string filename)
{
    bool hasFailed = false;

    unsigned int sn;
    unsigned int sxy;
    unsigned int sk;

    std::ifstream file;
    file.open(filename.c_str());

    if(file.fail())
    {
        hasFailed = true;
    }
    else
    {
        //header
        file >> widthInScreens >> heightInScreens;
        file >> screenWidthInTiles >> screenHeightInTiles;
        file >> tileDimension;

        //populate screens
        screens.resize(widthInScreens * heightInScreens);

        // x < (width * height)  is probably faster than x <= (width * height) - 1
        for(unsigned int x = 0; x <= ((widthInScreens * heightInScreens) - 1); x++)
        {
            screens[x] = new Screen(screenWidthInTiles, screenHeightInTiles);
        }

        while(!file.eof())
        {
            //body
            file >> sn >> sxy >> sk;

            screens[sn]->getTile(sxy)->setKey(sk);

        }

    }

    file.close();

    loadedScreen = al_create_bitmap((screenWidthInTiles * tileDimension), (screenHeightInTiles * tileDimension));
    needsUpdate = true;
    currentScreen = 0;

    return (!hasFailed);

}

//Sets a TileMap's TileMapping (tileset) to the specified (user created)
//TileMapping object (don't forget to de-reference passed objects)
//eg. setTileMapping(&tileMapObject)
void TileMap::setTileMapping(TileMapping* tMap)
{
    this->tMap = tMap;
}

//Draw the map to the specified display
void TileMap::DrawMap(ALLEGRO_DISPLAY* display)
{

    unsigned int tileKey;

    if(needsUpdate)
    {

        al_set_target_bitmap(loadedScreen);

        al_clear_to_color(al_map_rgb(0, 0, 0));

        //for every row
        for(unsigned int y = 0; y <= (screenHeightInTiles - 1); y++)
        {
            //each tile
            for(unsigned int x = 0; x <= (screenWidthInTiles - 1); x++)
            {
                tileKey = screens[currentScreen]->getTile((screenWidthInTiles * y) + x)->getKey();

                al_draw_bitmap(tMap->getImage(tileKey), (x * tileDimension), (y * tileDimension), 0);
            }

        }

        al_set_target_backbuffer(display);
        needsUpdate = false;

    }

    al_draw_bitmap(loadedScreen, 0, 0, 0);

}

//Changes necessary data so that DrawMap() will draw the next screen
void TileMap::changeScreen(DIRECTION direction)
{
    bool hasFailed = false;

    switch(direction)
    {
    case UP:
        if(currentScreen >= widthInScreens)
        {
            currentScreen -= widthInScreens;
        }
        else
        {
            hasFailed = true;
        }
        break;

    case DOWN:
        if(currentScreen <= (((widthInScreens * heightInScreens) - 1) - widthInScreens))
        {
            currentScreen += widthInScreens;
        }
        else
        {
            hasFailed = true;
        }
        break;

    case LEFT:
        if((currentScreen % widthInScreens) != 0)
        {
            currentScreen--;
        }
        else
        {
            hasFailed = true;
        }
        break;

    case RIGHT:
        if(((currentScreen + 1) % widthInScreens) != 0)
        {
            currentScreen++;
        }
        else
        {
            hasFailed = true;
        }
        break;
    }

    //if this hasn't failed tell it to update on next draw
    if(!hasFailed)
    {
        needsUpdate = true;
    }

}

//Cleans up after TileMap objects
TileMap::~TileMap()
{
    //Frees Screen objects
    //( allocated in TileMap::loadFromFile() )
    // x < (width * height)  is probably faster than x <= (width * height) - 1
    for(unsigned int x = 0; x <= ((widthInScreens * heightInScreens) - 1); x++)
    {
        delete screens[x];
    }

    //Destroys the ALLEGRO_BITMAP of the currently loaded screen
    al_destroy_bitmap(loadedScreen);
}
