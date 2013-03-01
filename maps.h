#ifndef MAPS_H
#define MAPS_H

#include <string>
#include <map>
#include <fstream>
#include <vector>

#include "allegro5/allegro.h"
#include "allegro5/allegro_image.h"

class mapBase
{
    private:
        std::string name;

    public:
        void setName();
        std::string getName();
        virtual bool loadFromFile(std::string fileName) = 0;

};


class TileMapping
{
    private:
        std::map <unsigned int, ALLEGRO_BITMAP*> tMap;

    public:
        ~TileMapping();
        virtual void loadFromFile(std::string filename);
        ALLEGRO_BITMAP* getImage(unsigned int key);

};


class Tile
{
    private:
    static int dimension;
    unsigned int key;
    unsigned int tileMappingIndex;

    public:
        Tile();
        static void setDimension(int i);
        void setKey(int i);

};


class Screen
{
    private:
        unsigned int widthInTiles;
        unsigned int heightInTiles;
        std::vector<Tile*> tiles;

    public:
        Screen(int width, int height);
        ~Screen();

};


class TileMap : public mapBase
{

};


#endif
