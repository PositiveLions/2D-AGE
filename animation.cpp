#include "animation.h"


Animation::Animation(std::vector<ALLEGRO_BITMAP*> imgs)
{
    images = imgs;
    currentIndex = 0;
}


void Animation::setCurrentIndex(unsigned int i)
{
    if(i < images.size())
    {
        currentIndex = i;
    }
}



//ADD SUPPORT FOR REWIND MODE ( 0 increased to max then decreased to 0)
//INSTEAD OF NORMAL ( 0 increased to max, then set to 0)
ALLEGRO_BITMAP* Animation::getNextFrame()
{
    int tempIndex = currentIndex;

    if(currentIndex == (images.size() - 1))
    {
        currentIndex = 0;
    }
    else
    {
        currentIndex++;
    }

    return images[tempIndex];
}



Animation::~Animation()
{
    for(std::vector<ALLEGRO_BITMAP*>::iterator i = images.begin(); i != images.end(); i++)
    {
        al_destroy_bitmap(*i);
    }

    images.clear();
}



CharacterAnimations::CharacterAnimations()
{

}


ALLEGRO_BITMAP* CharacterAnimations::getImage(std::string animationName)
{
    return animations[animationName]->getNextFrame();
}


void CharacterAnimations::loadFromFile(std::string filename)
{

    std::string filenameToLoad = "";
    unsigned int numberOfAnimations = 0;

    std::string animationName = "";
    unsigned int numberOfFrames = 0;

    unsigned int frameXCoord = 0;
    unsigned int frameYCoord = 0;
    unsigned int frameWidth = 0;
    unsigned int frameHeight = 0;
    int frameXOffset = 0;
    int frameYOffset = 0;

    std::vector<ALLEGRO_BITMAP*> tempFrames;
    Animation* tempAnimation;

    std::ifstream file;
    file.open(filename.c_str());

    if(!file.fail())
    {

        file >> filenameToLoad;
        parentImage = al_load_bitmap(filenameToLoad.c_str());

        file >> numberOfAnimations;

        for(unsigned int x = 0; x < numberOfAnimations; x++)
        {

            file >> animationName;
            file >> numberOfFrames;

            tempFrames.clear();
            tempFrames.resize(numberOfFrames);

            for(unsigned int y = 0; y < numberOfFrames; y++)
            {
                //pull data
                file >> frameXCoord;
                file >> frameYCoord;
                file >> frameWidth;
                file >> frameHeight;
                file >> frameXOffset;
                file >> frameYOffset;

                tempFrames[y] = al_create_sub_bitmap(parentImage, frameXCoord, frameYCoord, frameWidth, frameHeight);

            }

            tempAnimation = new Animation(tempFrames);

            animations.insert(std::pair<std::string, Animation*>(animationName, tempAnimation));

        }

    }


    file.close();
}



CharacterAnimations::~CharacterAnimations()
{

    for(std::map<std::string, Animation*>::iterator i = animations.begin(); i != animations.end(); i++)
    {
        delete i->second;
    }


    animations.clear();
}
