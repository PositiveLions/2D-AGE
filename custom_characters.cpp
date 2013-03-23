#include "custom_characters.h"

//Sets the image of the character
//TODO: make this private, it should only be used by update()
//TODO: or remove this, since the overloaded version is the only one that
//      should be used.
void customPlayer::setImage(std::string filename)
{
    image = al_load_bitmap(filename.c_str());
}

//draws the character at it's current position on the screen
void customPlayer::drawCharacter()
{
    al_draw_bitmap(image, getXCoord(), getYCoord(), 0);
}

//Sets the image of the character
//TODO: make this private, it should only be used by update()
void customPlayer::setImage(ALLEGRO_BITMAP* image)
{
    this->image = image;
}


//Updates necessary information about the character, all character-based logic
//  should go here.
void customPlayer::update(TileMap& tileMap)
{
    //call the parent-class's update function
    PlayerCharacter::update();

    std::string animationToUse = "";

    //Set lastDirection
    if(xVelocity > 0)
    {
        lastDirection = RIGHT;
    }
    else if(xVelocity < 0)
    {
        lastDirection = LEFT;
    }

    if(yVelocity > 0)
    {
        lastDirection = DOWN;
    }
    else if(yVelocity < 0)
    {
        lastDirection = UP;
    }



    //determines which animation should be used
    //(names are contained in the *.chr file
    if(xVelocity == 0 && yVelocity == 0 && lastDirection == DOWN)
    {
        animationToUse = "standing_down";
    }
    else if(xVelocity == 0 && yVelocity == 0 && lastDirection == UP)
    {
        animationToUse = "standing_up";
    }
    else if(xVelocity == 0 && yVelocity == 0 && lastDirection == LEFT)
    {
        animationToUse = "standing_left";
    }
    else if(xVelocity == 0 && yVelocity == 0 && lastDirection == RIGHT)
    {
        animationToUse = "standing_right";
    }

    else if(yVelocity > 0)
    {
        animationToUse = "walking_down";
    }
    else if(yVelocity < 0)
    {
        animationToUse = "walking_up";
    }
    else if(xVelocity > 0)
    {
        animationToUse = "walking_right";
    }
    else if(xVelocity < 0)
    {
        animationToUse = "walking_left";
    }



    //get the next image
    image = animations.getImage(animationToUse);


    int height = al_get_bitmap_height(image);
    int width = al_get_bitmap_width(image);
    int screenWidth = tileMap.getScreenWidthPx();
    int screenHeight = tileMap.getScreenHeightPx();

    //if player walks off edge of screen and theres another screen in that
    //  direction, change screens, otherwise prevent player from walking off
    //  screen in that direction.
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
            xCoord = (((0.5 * width) * -1) + 1);
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
            yCoord = (((0.5 * height) * -1) + 1);
        }
        else
        {
            yCoord = (screenHeight - ((0.5 * height) + 1));
        }
    }

}

