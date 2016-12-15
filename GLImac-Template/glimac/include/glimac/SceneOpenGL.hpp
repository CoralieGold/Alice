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

#include "Program.hpp"
#include "Treasure.hpp"
#include "Monster.hpp"
#include "Hero.hpp"
#include "Cube.hpp"
#include "Sphere.hpp"
#include "Card.hpp"
#include "Image.hpp"
#include "Vertex2DUV.hpp"
#include "Functions2D.hpp"

#define MONSTERS_SPEED 50

#define WALL 1
#define CORRIDOR 2
#define ENTER 3
#define EXIT 4
#define DOOR 5

using namespace std;
using namespace glimac;

struct Program3D {
    Program m_Program;


    GLint uMVPMatrix;
    GLint uMVMatrix;
    GLint uNormalMatrix;
    GLint uWallTexture;


    Program3D(const FilePath& applicationPath):
        m_Program(loadProgram(applicationPath.dirPath() + "shaders/3D.vs.glsl",
                              applicationPath.dirPath() + "shaders/tex3D.fs.glsl")) {
        uMVPMatrix = glGetUniformLocation(m_Program.getGLId(), "uMVPMatrix");
        uMVMatrix = glGetUniformLocation(m_Program.getGLId(), "uMVMatrix");
        uNormalMatrix = glGetUniformLocation(m_Program.getGLId(), "uNormalMatrix");
        uWallTexture = glGetUniformLocation(m_Program.getGLId(), "uTexture");
    }
};

struct Program2D {
    Program m_Program;


    GLint uModelMatrix;
    GLint uMapTexture;


    Program2D(const FilePath& applicationPath):
        m_Program(loadProgram(applicationPath.dirPath() + "shaders/text2D.vs.glsl",
                              applicationPath.dirPath() + "shaders/text2D.fs.glsl")) {
        uModelMatrix = glGetUniformLocation(m_Program.getGLId(), "uModelMatrix");
        uMapTexture = glGetUniformLocation(m_Program.getGLId(), "uTexture");
    }
};

// Classe

class SceneOpenGL
{
    public:

    SceneOpenGL();
    ~SceneOpenGL();

    int** getGrid() const;
    void setGrid(int** &value);

    void clearMonsters();
    void clearTreasures();

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
    Monster& getMonster(int posX, int posY);

    void deleteTreasure(int posX, int posY);
    void deleteMonster(unsigned int id);

    GLuint createVboCube(Cube &cube);
    GLuint createVboSphere(Sphere &sphere);
    GLuint createVboFace();

    GLuint createVao3D(GLuint vbo);
    GLuint createVao2D(GLuint vbo);

    void drawCube(Program3D &prog, Cube &cube, glm::mat4 viewMatrix, glm::mat4 ProjMatrix, glm::mat4 MVMatrix, glm::mat4 NormalMatrix, GLuint vao, GLuint texture, float x, float y, float z);
    void drawTreasure(Program3D &prog, Sphere &sphere, glm::mat4 viewMatrix, glm::mat4 ProjMatrix, glm::mat4 MVMatrix, glm::mat4 NormalMatrix, GLuint vao, GLuint texture, float x, float y, float z, float r);
    void drawMonster(Program3D &prog, Cube &cube, glm::mat4 viewMatrix, glm::mat4 ProjMatrix, glm::mat4 MVMatrix, glm::mat4 NormalMatrix, GLuint vao, GLuint texture, float x, float y, float z);
    void drawMap(Program2D &prog, GLuint vao, GLuint texture, float x, float y);
    void drawInfo(Program2D &prog, GLuint vao, GLuint texture, float x, float y, float s);
    void drawStory(Program2D &prog, GLuint vao, GLuint texture);

    GLuint createTexture(const char* imagePath);

    bool monsterSeeHero(Monster m, Hero a);
    bool monsterNextToHero(Monster m, Hero a);

    bool doorExitNextToHero(Hero a);

    void choosePath(Monster &m);

    // Héro attaque le monstre
    unsigned int attack(Hero &h, Monster &m);

    // Monstre attaque le héro
    unsigned int isAttacked(Monster &m, Hero &h);

    void levelInit(int newLevel, Hero *a);
    unsigned int findEnterX();
    unsigned int findEnterY();
    void findOrientationHero(Hero *a, unsigned int departX, unsigned int departY);

    int** grid;
    int sizeX;
    int sizeY;
    bool heroHasWon;
    int level;
    bool startGame;
    bool gameOver;
    bool paused;

    private:
    vector<Treasure> treasures;
    vector<Monster*> monsters;


};

#endif
