#ifndef DEF_TREASURE
#define DEF_TREASURE


// Includes
#include <string>
#include <iostream>


#define TREASURE_LIFE 1
#define TREASURE_DEFENSE 3
#define TREASURE_ATTACK 2
#define TREASURE_LEVEL 4


using namespace std;

// Classe

class Treasure
{
    public:
    unsigned int getId() const;
    unsigned int getPosX() const;
    unsigned int getPosY() const;
    string getName() const;
    int getType() const;
    int getFeature() const;
    string getObject() const;

    void setId(const unsigned int &value);
    void setPosX(const unsigned int &value);
    void setPosY(const unsigned int &value);
    void setName(const string &value);
    void setType(const int &value);
    void setFeature(const int &value);
    void setObject(const string &value);
    void setTreasure(const  unsigned int &id, const  unsigned int &posX, const  unsigned int &posY, const  string &name, const  int &type, const  int &feature, const  string &object);


    Treasure(unsigned int &id, unsigned int &posX, unsigned int &posY, string &name, int &type, int &feature, string &object);
    ~Treasure();

    private:
    unsigned int id;
    unsigned int posX;
    unsigned int posY;
    string name;
    int type;
    int feature;
    string object;

};

#endif
