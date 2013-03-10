#include "custom_characters.h"

void customPlayer::setImage(std::string filename)
{
    image = al_load_bitmap(filename.c_str());
}


void customPlayer::drawCharacter()
{
    al_draw_bitmap(image, getXCoord(), getYCoord(), 0);
}



void customPlayer::update(TileMap& tileMap)
{
    PlayerCharacter::update();

    int height = al_get_bitmap_height(image);
    int width = al_get_bitmap_width(image);
    int screenWidth = tileMap.getScreenWidthPx();
    int screenHeight = tileMap.getScreenHeightPx();

    if((xCoord + (0.5 * width))  <= 0)
    {
        if(tileMap.changeScreen(TileMap::LEFT))
        {
            xCoord = screenWidth - ((0.5 * width) + 1);
        }
        else
        {
            xCoord = (0 - (0.5 * width));
        }
    }
    else if((xCoord + (0.5 * width)) >= screenWidth)
    {
        if(tileMap.changeScreen(TileMap::RIGHT))
        {
            xCoord = ((0.5 * width) + 1);
        }
        else
        {
            xCoord = screenWidth - (0.5 * width + 1);
        }
    }


    if((yCoord + (0.5 * height)) <= 0)
    {
        if(tileMap.changeScreen(TileMap::UP))
        {
            yCoord = screenHeight - ((0.5 * height) + 1);
        }
        else
        {
            yCoord = (0 - (0.5 * height));
        }
    }
    else if((yCoord + (0.5 * height)) >= screenHeight)
    {
        if(tileMap.changeScreen(TileMap::DOWN))
        {
            yCoord = ((0.5 * height) - 1);
        }
        else
        {
            yCoord = (screenHeight - ((0.5 * height) + 1));
        }
    }

}

