#ifndef DEF_SCENEOPENGL
#define DEF_SCENEOPENGL


// Includes

#define GLEW_STATIC
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <GL/glew.h>
#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>
#include <SDL/SDL.h>

#include <stdlib.h>
#include <time.h>

#include "Treasure.hpp"
#include "Monster.hpp"
#include "Hero.hpp"
#include "Cube.hpp"
#include "Sphere.hpp"
#include "Object.hpp"
#include "Image.hpp"

#define MONSTERS_SPEED 50

#define WALL 1
#define CORRIDOR 2
#define ENTER 3
#define EXIT 4
#define DOOR 5

using namespace std;

// Classe

class SceneOpenGL
{
    public:

    SceneOpenGL();
    ~SceneOpenGL();

    int** getGrid() const;
    void setGrid(int** &value);

    bool readLevel(const char* filepath);
    bool readDungeon(const char* imagepath);
    //void rotateLevel();

    bool hasObstacle(int posX, int posY);
    bool canMove(int orientation, int posX, int posY, int action);

    

    vector<Treasure> getTreasures();
    vector<Monster*> getMonsters();

    bool isTreasure(int posX, int posY);
    bool isMonster(int posX, int posY);

    Treasure& getTreasure(int posX, int posY);
    //Monster getMonster(int posX, int posY);

    void deleteTreasure(int posX, int posY);
    void deleteMonster(unsigned int id);

    GLuint createVboCube(Cube &cube);
    GLuint createVboSphere(Sphere &sphere);
    GLuint createVboObject(Object &object);

    void createVao(GLuint vbo);

    GLuint createTexture(const char* imagePath);

    bool monsterSeeHero(Monster m, Hero a);
    bool monsterNextToHero(Monster m, Hero a);

    void choosePath(Monster &m);

    // Héro attaque le monstre
    unsigned int attack(Hero &h, Monster &m);

    // Monstre attaque le héro
    unsigned int isAttacked(Monster &m, Hero &h);

    int** grid;
    int sizeX;
    int sizeY;

    private:
    vector<Treasure> treasures;
    vector<Monster*> monsters;


};

#endif
