#ifndef DEF_TREASURE
#define DEF_TREASURE


// Includes
#include <string>

using namespace std;

// Classe

class Treasure
{
    public:
    unsigned int getId() const;
    unsigned int getPosX() const;
    unsigned int getPosY() const;
    string getName() const;
    string getType() const;
    string getFeature() const;
    string getObject() const;

    void setId(const unsigned int &value);
    void setPosX(const unsigned int &value);
    void setPosY(const unsigned int &value);
    void setName(const string &value);
    void setType(const string &value);
    void setFeature(const string &value);
    void setObject(const string &value);
    void setTreasure(const  unsigned int &id, const  unsigned int &posX, const  unsigned int &posY, const  string &name, const  string &type, const  string &feature, const  string &object);


    Treasure(unsigned int &id, unsigned int &posX, unsigned int &posY, string &name, string &type, string &feature, string &object);
    ~Treasure();

    private:
    unsigned int id;
    unsigned int posX;
    unsigned int posY;
    string name;
    string type;
    string feature;
    string object;

};

#endif
