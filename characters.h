#ifndef CHARACTERS_H
#define CHARACTERS_H

#include <string>
#include <map>

#include "character_factory.h"


class PlayerCharacter
{
  private:
      std::string ID;
      int xCoord;
      int yCoord;
      int xVelocity;
      int yVelocity;

  public:

      PlayerCharacter(std::string ID);
      PlayerCharacter(const PlayerCharacter&);

      void getID();
      void setXCoord(int X);
      void setYCoord(int Y);
      void setXVelocity(int velocity);
      void setYVelocity(int velocity);


};


#endif
