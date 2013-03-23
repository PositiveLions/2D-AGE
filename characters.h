#ifndef CHARACTERS_H
#define CHARACTERS_H

#include <string>

#include "character_factory.h"


class PlayerCharacter
{
  private:
      std::string ID;

  protected:
      int xCoord;
      int yCoord;
      int xVelocity;
      int yVelocity;

  public:

      PlayerCharacter(std::string ID);

      std::string getID();
      void setXCoord(int X);
      int getXCoord();
      void setYCoord(int Y);
      int getYCoord();
      void setXVelocity(int velocity);
      void setYVelocity(int velocity);
      int getXVelocity();
      int getYVelocity();
      void update();


};


#endif
