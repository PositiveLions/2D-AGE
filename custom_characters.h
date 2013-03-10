#ifndef CUSTOM_CHARACTERS_H
#define CUSTOM_CHARACTERS_H

#include "allegro5/allegro.h"
#include "allegro5/allegro_image.h"

#include "characters.h"

class customPlayer : public PlayerCharacter
{
    private:
        ALLEGRO_BITMAP* image;

    public:
        customPlayer(std::string ID) : PlayerCharacter(ID) {}
        void setImage(std::string filename);
        void drawCharacter();

};


#endif
