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

    int** grid;
    int sizeX;
    int sizeY;

    private:
    vector<Treasure> treasures;
    vector<Monster> monsters;


};

#endif
