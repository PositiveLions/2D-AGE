#include "characters.h"


PlayerCharacter::PlayerCharacter(std::string ID)
{
    this->ID = ID;
    xCoord = 0;
    yCoord = 0;
    xVelocity = 0;
    yVelocity = 0;
}

PlayerCharacter::PlayerCharacter(const PlayerCharacter& p)
{
    ID = p.ID;
    xCoord = p.xCoord;
    yCoord = p.yCoord;
    xVelocity = p.xVelocity;
    yVelocity = p.yVelocity;
}
