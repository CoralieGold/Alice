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
#include <GL/gl.h>
#include <SDL/SDL.h>

#include "Treasure.hpp"
#include "Monster.hpp"
#include "Hero.hpp"
#include "Cube.hpp"
#include "Sphere.hpp"

using namespace std;

// Classe

// 0 : personnage
// 1 : mur
// 2 : couloir
// 3 : entree
// 4 : sortie
// 5 : porte
// 6 : eau
// 7 : monstre
// 8 : tresor

class SceneOpenGL
{
    public:

    SceneOpenGL();
    ~SceneOpenGL();

    int** getGrid() const;
    void setGrid(int** &value);

    bool readLevel();
    bool readDungeon(string image);
    //void rotateLevel();

    bool canMove(int orientation, int posX, int posY, int action);

    int** grid;
    int sizeX;
    int sizeY;

    vector<Treasure> getTreasures();
    vector<Monster> getMonsters();

    bool isTreasure(int posX, int posY);
    bool isMonster(int posX, int posY);

    Treasure& getTreasure(int posX, int posY);
    //Monster getMonster(int posX, int posY);

    void deleteTreasure(int posX, int posY);

    GLuint createVboCube(Cube &cube);
    GLuint createVboSphere(Sphere &sphere);
    // void createVboObject(Object &object);

    void createVao(GLuint vbo);

    private:
    vector<Treasure> treasures;
    vector<Monster> monsters;


};

#endif
