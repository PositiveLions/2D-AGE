#ifndef CHARACTER_FACTORY_H
#define CHARACTER_FACTORY_H

#include <map>


//Creates and manages character objects
template <typename T> class CharacterFactory
{
    private:
        //contains the individual objects referenced by an individual name (string)
        std::map<std::string, T*> objects;

    public:
        ~CharacterFactory();    //cleans up the dynamically allocated objects
        void createCharacter(std::string ID);   //adds a new character object
        void destroyCharacter(std::string ID);  //deletes a character object
        T* getCharacter(std::string ID);  //returns a character by it's ID

};


//Creates a character to be referenced by the specified ID (string)
template <typename T> void CharacterFactory<T>::createCharacter(std::string ID)
{
        objects.insert(std::pair<std::string, T*>(ID, new T(ID)));
}


//frees the memory of the object stored in the value portion of the map
//and deletes the std::pair from the map
template <typename T> void CharacterFactory<T>::destroyCharacter(std::string ID)
{
    //If an object with key 'ID' is found...
    if(objects.count(ID))
    {
        //delete the object from memory
        delete objects[ID];
        //erase it's entry from the map
        objects.erase(ID);
    }
}


//Returns the character object with the specified name
template <typename T> T* CharacterFactory<T>::getCharacter(std::string ID)
{
    return objects[ID];
}


//Destructor - Frees all of the objects this tracks and empties the map.
template <typename T> CharacterFactory<T>::~CharacterFactory()
{
    //for every std::pair in the map
    for(typename std::map<std::string, T*>::iterator x = objects.begin(); x != objects.end(); x++)
    {
        //delete the object contained in the value portion of the std::pair
        delete x->second;
    }

    //empty the entire map of std::pair's
    objects.clear();
}


#endif
