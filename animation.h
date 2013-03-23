#ifndef ANIMATION_H
#define ANIMATION_H

#include "allegro5/allegro.h"
#include "allegro5/allegro_image.h"

#include <string>
#include <vector>
#include <map>
#include <fstream>


//Animation class - A single series of pictures that make up a single animation
//  (eg. 3 pictures for walking down is one Animation)
class Animation
{
    private:
        std::vector<ALLEGRO_BITMAP*> images;    //collection of images
        unsigned int currentIndex;              //The index of the current image

    public:
        Animation(std::vector<ALLEGRO_BITMAP*> imgs);
        ~Animation();

        void setCurrentIndex(unsigned int i);   //Sets currentIndex
        ALLEGRO_BITMAP* getNextFrame();         //Returns the next image

};


//CharacterAnimations class - This is to be inherited by animated character
//  classes.  Contains multiple animations.  Loads animations from a *.chr file.
//  To use: in a character's update() function, use:
//  image = getImage("animation_name");
class CharacterAnimations
{
    private:
        std::map<std::string,Animation*> animations;
        ALLEGRO_BITMAP* parentImage;    //the spritesheet for all animations


    public:
        CharacterAnimations();
        ~CharacterAnimations();

        void loadFromFile(std::string filename);    //loads *.chr files

        //gets the next image of an animation based on the name of the animation
        ALLEGRO_BITMAP* getImage(std::string animationName);


};


#endif
