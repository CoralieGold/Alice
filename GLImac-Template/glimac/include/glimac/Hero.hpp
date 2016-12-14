#ifndef DEF_HERO
#define DEF_HERO


// Includes
#include <string>
#include <iostream>
#include "Treasure.hpp"
#include "FreeflyCamera.hpp"

#define LIFE_MAX 100

using namespace std;
using namespace glimac;

// Classe

class Hero
{
    public:
    unsigned int getPosX() const;
    unsigned int getPosY() const;
    int getOrientation() const;
    string getName() const;
    int getAttack() const;
    int getDefense() const;
    unsigned int getLife() const;
    FreeflyCamera getCamera() const;
    // get inventory

    void setPosX(const unsigned int &value);
    void setPosY(const unsigned int &value);
    void setOrientation(const int &value);
    void setAttack(const int &value);
    void setDefense(const int &value);
    void setLife(const unsigned int &value);
    void setName(const string &value);
    void setCamera(const FreeflyCamera &value);
    // set inventory
    void setHero(const  unsigned int &posX, const  unsigned int &posY, const  string &name, const int &attack, const int &defense, const unsigned int &life, const FreeflyCamera &camera);


    void down();
    void up();
    void left();
    void right();
    void rotateUp();
    void rotateDown();


    void applyTreasure(Treasure &treasure);


    Hero(unsigned int &posX, unsigned int &posY, string &name, int &attack, int &defense, unsigned int &life, FreeflyCamera camera);
    ~Hero();

    private:
    unsigned int posX;
    unsigned int posY;
    int orientation;
    string name;
    int attack;
    int defense;
    unsigned int life;
    int* inventory;
    FreeflyCamera camera;


};

#endif
