#ifndef DEF_MONSTER
#define DEF_MONSTER


// Includes
#include <string>

using namespace std;

// Classe

class Monster
{
    public:
    unsigned int getId() const;
    unsigned int getPosX() const;
    unsigned int getPosY() const;
    string getName() const;
    string getType() const;
    int getAttack() const;
    int getDefense() const;
    unsigned int getLife() const;
    string getObject() const;

    void setId(const unsigned int &value);
    void setPosX(const unsigned int &value);
    void setPosY(const unsigned int &value);
    void setName(const string &value);
    void setType(const string &value);
    void setAttack(const int &value);
    void setDefense(const int &value);
    void setLife(const unsigned int &value);
    void setObject(const string &value);
    void setMonster(const  unsigned int &id, const  unsigned int &posX, const  unsigned int &posY, const  string &name, const  string &type, const int &attack, const int &defense, const unsigned int &life, const  string &object);


    Monster(unsigned int &id, unsigned int &posX, unsigned int &posY, string &name, string &type, int &attack, int &defense, unsigned int &life, string &object);
    ~Monster();

    private:
    unsigned int id;
    unsigned int posX;
    unsigned int posY;
    string name;
    string type;
    int attack;
    int defense;
    unsigned int life;
    string object;

};

#endif
