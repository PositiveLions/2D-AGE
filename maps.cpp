#include "maps.h"
#include <iostream>

//Sets the default Tile dimension
int Tile::dimension = 32;

Tile::Tile()
{
    key = 0;
    tileMappingIndex = 0;

}

void Tile::setDimension(int i)
{
    dimension = i;
}


TileMapping::~TileMapping()
{
    for(unsigned int x = 0; x < tMap.size(); x++)
    {
        al_destroy_bitmap(tMap[x]);
    }
}


//TODO: get path of tmap file and prefix it to filenames, so that filenames in
//      the tmap file are relative to the tmap file itself.
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

    }

    //close the file stream
    file.close();

}


ALLEGRO_BITMAP* TileMapping::getImage(unsigned int key)
{
    return tMap[key];
}


Screen::Screen(int width, int height)
{
    widthInTiles = width;
    heightInTiles = height;

    tiles.resize(width * height);

    for(unsigned int x = 0; x < ((widthInTiles * heightInTiles) - 1); x++)
    {
        tiles[x] = new Tile;
    }

}

Screen::~Screen()
{
    //Delete the Tile*'s from memory
    for(unsigned int x = 0; x < ((widthInTiles * heightInTiles) - 1); x++)
    {
        delete tiles[x];
    }
}
