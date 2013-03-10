#include "characters.h"


PlayerCharacter::PlayerCharacter(std::string ID)
{
    this->ID = ID;
    xCoord = 0;
    yCoord = 0;
    xVelocity = 0;
    yVelocity = 0;
}


std::string PlayerCharacter::getID()
{
    return ID;
}

void PlayerCharacter::setXCoord(int X)
{
    xCoord = X;
}

int PlayerCharacter::getXCoord()
{
    return xCoord;
}

void PlayerCharacter::setYCoord(int Y)
{
    yCoord = Y;
}

int PlayerCharacter::getYCoord()
{
    return yCoord;
}

void PlayerCharacter::setXVelocity(int velocity)
{
    xVelocity = velocity;
}

void PlayerCharacter::setYVelocity(int velocity)
{
    yVelocity = velocity;
}

int PlayerCharacter::getXVelocity()
{
    return xVelocity;
}

int PlayerCharacter::getYVelocity()
{
    return yVelocity;
}

void PlayerCharacter::update()
{
    xCoord += xVelocity;
    yCoord += yVelocity;
}
