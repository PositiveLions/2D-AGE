#ifndef CUSTOM_CHARACTERS_H
#define CUSTOM_CHARACTERS_H

#include "allegro5/allegro.h"
#include "allegro5/allegro_image.h"

#include "characters.h"
#include "maps.h"

#include "animation.h"



//Class for a test character - Animation system will probably be merged into
//  PlayerCharacter class.
class customPlayer : public PlayerCharacter
{
    private:
        ALLEGRO_BITMAP* image;


    public:
        //debug - make private and use accessors - used in update()
        enum DIRECTION {UP, DOWN, LEFT, RIGHT};
        DIRECTION lastDirection;



        customPlayer(std::string ID) : PlayerCharacter(ID) {}
        void setImage(std::string filename);
        void setImage(ALLEGRO_BITMAP* image);
        void drawCharacter();
        CharacterAnimations animations;
        void update(TileMap& tileMap);

};


#endif
