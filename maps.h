#ifndef MAPS_H
#define MAPS_H

#include <string>

class mapBase
{
    private:
        std::string name;

    public:
        void setName();
        std::string getName();
        virtual bool loadFromFile(std::string fileName) = 0;

};


class Tile
{
    private:


    public:


};


class Screen
{
    private:


    public:


};


class TileMap : public mapBase
{

};


#endif
