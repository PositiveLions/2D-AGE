#include "custom_characters.h"

void customPlayer::setImage(std::string filename)
{
    image = al_load_bitmap(filename.c_str());
}


void customPlayer::drawCharacter()
{
    al_draw_bitmap(image, getXCoord(), getYCoord(), 0);
}
