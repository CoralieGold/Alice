#include <glimac/SDLWindowManager.hpp>
#include <glimac/common.hpp>
#include <glimac/Program.hpp>
#include <glimac/FilePath.hpp>
#include <glimac/Image.hpp>
#include <glimac/SceneOpenGL.hpp>
#include <glimac/Face.hpp>
#include <GL/glew.h>
#include <iostream>
#include <vector>

using namespace glimac;
using namespace std;


int main(int argc, char** argv) {
    // Initialize SDL and open a window
    SDLWindowManager windowManager(1080, 720, "Alice");

    // Initialize glew for OpenGL3+ support
    GLenum glewInitError = glewInit();
    if(GLEW_OK != glewInitError) {
        cerr << glewGetErrorString(glewInitError) << endl;
        return EXIT_FAILURE;
    }

    cout << "OpenGL Version : " << glGetString(GL_VERSION) << endl;
    cout << "GLEW Version : " << glewGetString(GLEW_VERSION) << endl;

    /*********************************
     * HERE SHOULD COME THE INITIALIZATION CODE
     *********************************/

    int timer = 0;

    // Initialisation de la scene opengl
    SceneOpenGL scene = SceneOpenGL();
    Hero alice = Hero();
    scene.levelInit(1, &alice);

    FilePath applicationPath(argv[0]);
    Program3D prog3D(applicationPath);
    Program2D prog2D(applicationPath);


    GLuint textureMurHaut = scene.createTexture("../GLImac-Template/assets/textures/texture_feuilles_haut.jpg");
    GLuint textureMurBas = scene.createTexture("../GLImac-Template/assets/textures/texture_feuilles_bas.jpg");
    GLuint texturePorteDepartHaut = scene.createTexture("../GLImac-Template/assets/textures/porte_depart_haut_02.jpg");
    GLuint texturePorteDepartBas = scene.createTexture("../GLImac-Template/assets/textures/porte_depart_bas_01.jpg");
    GLuint texturePorteArriveeHaut = scene.createTexture("../GLImac-Template/assets/textures/porte_arrivee_haut_04.jpg");
    GLuint texturePorteArriveeBas = scene.createTexture("../GLImac-Template/assets/textures/porte_arrivee_bas_03.jpg");

    /** MAP **/

    /** Texture mur -- MAP **/
    GLuint textureMurMap = scene.createTexture("../GLImac-Template/assets/textures/violet_fonce.jpg");
    GLuint texturePorteMap = scene.createTexture("../GLImac-Template/assets/textures/violet_clair.jpg");
    GLuint textureHeroMap = scene.createTexture("../GLImac-Template/assets/textures/bleu_clair.jpg");
    GLuint textureFondMap = scene.createTexture("../GLImac-Template/assets/textures/bleu_fonce.jpg");
    /** Texture sol **/
    GLuint textureSol = scene.createTexture("../GLImac-Template/assets/textures/Sol.png");
    /** Texture plafond **/
    GLuint texturePlafond = scene.createTexture("../GLImac-Template/assets/textures/texture_ciel2.png");
  
    /** Texture monstre soldat 5 **/
    GLuint textureMonster5 = scene.createTexture("../GLImac-Template/assets/textures/soldat_carte05_carre-04.jpg");
    /** Texture monstre soldat 7 **/
    GLuint textureMonster7 = scene.createTexture("../GLImac-Template/assets/textures/soldat_carte07_carre-05.jpg");
    /** Texture monstre soldat 10 **/
    GLuint textureMonster10 = scene.createTexture("../GLImac-Template/assets/textures/soldat_carte10_carre-06.jpg");
    /** Texture monstre soldat Queen **/
    GLuint textureMonsterQueen = scene.createTexture("../GLImac-Template/assets/textures/reine_carte.jpg");
    /** Texture monstre soldat Valet **/
    GLuint textureMonsterValet = scene.createTexture("../GLImac-Template/assets/textures/valet_carte.jpg");

    /** Texture monstre soldat 5 **/
    GLuint textureTreasureHat = scene.createTexture("../GLImac-Template/assets/textures/chapeau.jpg");
    GLuint textureTreasureDrinkMe = scene.createTexture("../GLImac-Template/assets/textures/drinkme.jpg");
    /** Texture monstre soldat Queen **/
    GLuint textureTreasureKey = scene.createTexture("../GLImac-Template/assets/textures/cle.jpg");
    /** Texture monstre soldat Valet **/
    GLuint textureTreasureClock = scene.createTexture("../GLImac-Template/assets/textures/clock.jpg");

    /** CHIFFRES **/
    GLuint textureNombreGlobale = scene.createTexture("../GLImac-Template/assets/textures/globale.jpg");
    GLuint textureNombre0 = scene.createTexture("../GLImac-Template/assets/textures/0.jpg");
    GLuint textureNombre5 = scene.createTexture("../GLImac-Template/assets/textures/05.jpg");
    GLuint textureNombre10 = scene.createTexture("../GLImac-Template/assets/textures/10.jpg");
    GLuint textureNombre15 = scene.createTexture("../GLImac-Template/assets/textures/15.jpg");
    GLuint textureNombre20 = scene.createTexture("../GLImac-Template/assets/textures/20.jpg");
    GLuint textureNombre25 = scene.createTexture("../GLImac-Template/assets/textures/25.jpg");
    GLuint textureNombre30 = scene.createTexture("../GLImac-Template/assets/textures/30.jpg");
    GLuint textureNombre35 = scene.createTexture("../GLImac-Template/assets/textures/35.jpg");
    GLuint textureNombre40 = scene.createTexture("../GLImac-Template/assets/textures/40.jpg");
    GLuint textureNombre45 = scene.createTexture("../GLImac-Template/assets/textures/45.jpg");
    GLuint textureNombre50 = scene.createTexture("../GLImac-Template/assets/textures/50.jpg");
    GLuint textureNombre55 = scene.createTexture("../GLImac-Template/assets/textures/55.jpg");
    GLuint textureNombre60 = scene.createTexture("../GLImac-Template/assets/textures/60.jpg");
    GLuint textureNombre65 = scene.createTexture("../GLImac-Template/assets/textures/65.jpg");
    GLuint textureNombre70 = scene.createTexture("../GLImac-Template/assets/textures/70.jpg");
    GLuint textureNombre75 = scene.createTexture("../GLImac-Template/assets/textures/75.jpg");
    GLuint textureNombre80 = scene.createTexture("../GLImac-Template/assets/textures/80.jpg");
    GLuint textureNombre85 = scene.createTexture("../GLImac-Template/assets/textures/85.jpg");
    GLuint textureNombre90 = scene.createTexture("../GLImac-Template/assets/textures/90.jpg");
    GLuint textureNombre95 = scene.createTexture("../GLImac-Template/assets/textures/95.jpg");
    GLuint textureNombre100 = scene.createTexture("../GLImac-Template/assets/textures/100.jpg");

    GLuint textureNombreGlobale_soldat = scene.createTexture("../GLImac-Template/assets/textures/soldat.jpg");
    GLuint textureNombreGlobale_valet = scene.createTexture("../GLImac-Template/assets/textures/valet.jpg");
    GLuint textureNombreGlobale_queen = scene.createTexture("../GLImac-Template/assets/textures/reine.jpg");
    GLuint textureNombre0m = scene.createTexture("../GLImac-Template/assets/textures/m0.jpg");
    GLuint textureNombre5m = scene.createTexture("../GLImac-Template/assets/textures/m05.jpg");
    GLuint textureNombre10m = scene.createTexture("../GLImac-Template/assets/textures/m10.jpg");
    GLuint textureNombre15m = scene.createTexture("../GLImac-Template/assets/textures/m15.jpg");
    GLuint textureNombre20m = scene.createTexture("../GLImac-Template/assets/textures/m20.jpg");
    GLuint textureNombre25m = scene.createTexture("../GLImac-Template/assets/textures/m25.jpg");
    GLuint textureNombre30m = scene.createTexture("../GLImac-Template/assets/textures/m30.jpg");
    GLuint textureNombre35m = scene.createTexture("../GLImac-Template/assets/textures/m35.jpg");
    GLuint textureNombre40m = scene.createTexture("../GLImac-Template/assets/textures/m40.jpg");
    GLuint textureNombre45m = scene.createTexture("../GLImac-Template/assets/textures/m45.jpg");
    GLuint textureNombre50m = scene.createTexture("../GLImac-Template/assets/textures/m50.jpg");
    GLuint textureNombre55m = scene.createTexture("../GLImac-Template/assets/textures/m55.jpg");
    GLuint textureNombre60m = scene.createTexture("../GLImac-Template/assets/textures/m60.jpg");
    GLuint textureNombre65m = scene.createTexture("../GLImac-Template/assets/textures/m65.jpg");
    GLuint textureNombre70m = scene.createTexture("../GLImac-Template/assets/textures/m70.jpg");
    GLuint textureNombre75m = scene.createTexture("../GLImac-Template/assets/textures/m75.jpg");
    GLuint textureNombre80m = scene.createTexture("../GLImac-Template/assets/textures/m80.jpg");
    GLuint textureNombre85m = scene.createTexture("../GLImac-Template/assets/textures/m85.jpg");
    GLuint textureNombre90m = scene.createTexture("../GLImac-Template/assets/textures/m90.jpg");
    GLuint textureNombre95m = scene.createTexture("../GLImac-Template/assets/textures/m95.jpg");
    GLuint textureNombre100m = scene.createTexture("../GLImac-Template/assets/textures/m100.jpg");

    GLuint texturePause = scene.createTexture("../GLImac-Template/assets/textures/pause.jpg");

    /*** INFOS ***/
    GLuint textureBegin = scene.createTexture("../GLImac-Template/assets/textures/intro.jpg");
    GLuint textureGameOver = scene.createTexture("../GLImac-Template/assets/textures/game-over.jpg");
    GLuint textureWon = scene.createTexture("../GLImac-Template/assets/textures/gagne.jpg");
    GLuint texturePaused = scene.createTexture("../GLImac-Template/assets/textures/play.jpg");

    Cube cube(1);
    Sphere sphere(0.25, 16, 32);

    GLuint vaoCube = scene.createVao3D(scene.createVboCube(cube));
    GLuint vaoSphere = scene.createVao3D(scene.createVboSphere(sphere));
    GLuint vaoMap = scene.createVao2D(scene.createVboFace());

    // activation test profondeur GPU
    glEnable(GL_DEPTH_TEST); 



    glm::mat4 ProjMatrix, MVMatrix, NormalMatrix;
    ProjMatrix = glm::perspective(glm::radians(70.f), 800.f/600.f, 0.1f, 100.f);
    MVMatrix = glm::translate(MVMatrix, glm::vec3(0.,0.,-5.0));
    NormalMatrix = glm::transpose(glm::inverse(MVMatrix));



    bool isHurt = false, lookUp = false, lookDown = false;


    // Application loop:
    bool done = false;
    while(!done) {
        // Event loop:
        SDL_Event e;
        while(windowManager.pollEvent(e)) {
            switch(e.type) {
                case SDL_QUIT:
                    done = true; // Leave the loop after this iteration
                break;
                case SDL_KEYDOWN : // touche clavier
                    switch(e.key.keysym.sym) {
                        case SDLK_DOWN :
                        case SDLK_s :
                            if(!scene.startGame && !scene.gameOver && !scene.paused && !scene.heroHasWon) {
                                if(scene.canMove(alice.getOrientation(), alice.getPosX(), alice.getPosY(), -1)) {
                                    alice.down();
                                }
                                if(scene.isTreasure(alice.getPosX(), alice.getPosY())) {
                                    alice.applyTreasure(scene.getTreasure(alice.getPosX(), alice.getPosY()));
                                    scene.deleteTreasure(alice.getPosX(), alice.getPosY());
                                }
                            }    
                            break;
                        case SDLK_UP :
                        case SDLK_z :
                            if(!scene.startGame && !scene.gameOver && !scene.paused && !scene.heroHasWon) {
                                if(scene.canMove(alice.getOrientation(), alice.getPosX(), alice.getPosY(), 1)) {
                                    alice.up();
                                } 
                                if(scene.isTreasure(alice.getPosX(), alice.getPosY())) {
                                    alice.applyTreasure(scene.getTreasure(alice.getPosX(), alice.getPosY()));
                                    scene.deleteTreasure(alice.getPosX(), alice.getPosY());
                                }
                            }
                            break;
                        case SDLK_LEFT :
                        case SDLK_q :
                            if(!scene.startGame && !scene.gameOver && !scene.paused && !scene.heroHasWon) {
                                alice.left();
                            }
                        break;
                        case SDLK_RIGHT:
                        case SDLK_d :
                            if(!scene.startGame && !scene.gameOver && !scene.paused && !scene.heroHasWon) {
                                alice.right();
                            }
                        break;
                    }
                break;
                case SDL_MOUSEBUTTONDOWN :
                    switch(e.button.button) {
                        case SDL_BUTTON_LEFT :
                            if(!scene.startGame && !scene.gameOver && !scene.paused && !scene.heroHasWon) {
                                if(scene.doorExitNextToHero(alice)) {
                                    if(alice.getHasKey()) {
                                        scene.heroHasWon = true;
                                    }
                                    else {
                                        cout << "You need to find the key..." << endl;
                                    }
                                }
                                else {
                                    // Attaque
                                    for(unsigned int i = 0; i < scene.getMonsters().size(); i ++) {
                                        if(scene.monsterNextToHero(*scene.getMonsters()[i], alice)) {
                                            scene.getMonsters()[i]->setLife(scene.attack(alice, *scene.getMonsters()[i]));
                                            if(scene.getMonsters()[i]->getLife() == 0) {
                                                scene.deleteMonster(i);
                                            }
                                        }
                                    }
                                }
                            }
                            break;
                    }
                    if(!scene.paused) {
                        if(e.button.x > 900 && e.button.x < 1080  && e.button.y > 600 && e.button.y < 720) {
                            scene.paused = true;
                        }
                    }

                    if(scene.startGame) {
                        if(e.button.x > 550 && e.button.x < 900  && e.button.y > 550 && e.button.y < 700) {
                            scene.startGame = false;
                            scene.paused = false;
                        }
                    }
                    if(scene.gameOver) {
                        if(e.button.x > 150 && e.button.x < 300  && e.button.y > 500 && e.button.y < 700) {
                            scene.paused = false;
                            done = true;
                        }
                    }
                    if(scene.heroHasWon) {
                        if(e.button.x > 700 && e.button.x < 1000  && e.button.y > 500 && e.button.y < 700) {
                            scene.paused = false;
                            done = true;
                        }
                    }
                    if(scene.paused) {
                        if(e.button.x > 500 && e.button.x < 700  && e.button.y > 400 && e.button.y < 700) {
                            scene.paused = false;
                        }
                    }
                break;
            }
        }

        /*********************************
         * HERE SHOULD COME THE RENDERING CODE
        *********************************/

        timer ++;
        if(timer%MONSTERS_SPEED == 0 && !scene.startGame && !scene.gameOver && !scene.paused) {
            for(unsigned int i = 0; i < scene.getMonsters().size(); i ++) {
                if(scene.getMonsters()[i]->getType() == MONSTER_QUEEN) scene.getMonsters()[i]->setOrientation(180);
                if(scene.monsterSeeHero(*scene.getMonsters()[i], alice)) {
                    if(scene.monsterNextToHero(*scene.getMonsters()[i], alice)) {
                        alice.setLife(scene.isAttacked(*scene.getMonsters()[i], alice));
                        if(alice.getLife() == 0) {
                            scene.gameOver = true;
                            scene.paused = true;
                        }
                        isHurt = true;
                    }
                    else if(scene.getMonsters()[i]->getType() != MONSTER_VALET && scene.getMonsters()[i]->getType() != MONSTER_QUEEN)  {
                        scene.getMonsters()[i]->move();
                    }
                    
                }
                else if(scene.getMonsters()[i]->getType() != MONSTER_VALET && scene.getMonsters()[i]->getType() != MONSTER_QUEEN) {
                    if(scene.canMove(scene.getMonsters()[i]->getOrientation(), scene.getMonsters()[i]->getPosX(), scene.getMonsters()[i]->getPosY(), 1)) {
                        // if(timer%(MONSTERS_SPEED*2) == 0){
                        //     scene.choosePath(* scene.getMonsters()[i]);
                        //     scene.getMonsters()[i]->move();
                        // }
                        scene.getMonsters()[i]->move();
                    }
                    else {
                        scene.choosePath(* scene.getMonsters()[i]);
                        scene.getMonsters()[i]->move();
                    }
                }

            }
        }

        if(timer%10 == 0 && isHurt == true){
            alice.rotateUp();
            lookUp = true;
        }else if(isHurt == true){
            alice.rotateDown();
            lookDown = true;
        }
        if(lookDown == true && lookUp == true){
            lookDown = false;
            lookUp = false;
            isHurt = false;
        }

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


        glm::mat4 viewMatrix = alice.getCamera().getViewMatrix();




        if(scene.startGame) {
            prog2D.m_Program.use();
            scene.drawStory(prog2D, vaoMap, textureBegin);
        }
        else if(scene.gameOver) {
            prog2D.m_Program.use();
            scene.drawStory(prog2D, vaoMap, textureGameOver);
        }
        else if(scene.heroHasWon) {
            prog2D.m_Program.use();
            scene.drawStory(prog2D, vaoMap, textureWon);
        }
        else if(scene.paused && !scene.startGame && !scene.gameOver && !scene.heroHasWon) {
            prog2D.m_Program.use();
            scene.drawStory(prog2D, vaoMap, texturePaused);
        }
        else {
            prog2D.m_Program.use();
            
            scene.drawInfo(prog2D, vaoMap, texturePause, 6.2, -6.2, 0.15);

            // Dessin vie Alice
            GLuint textLifeHero;
            switch(alice.getLife()) {
                case 0:
                    textLifeHero = textureNombre0;
                    break;
                case 5:
                    textLifeHero = textureNombre5;
                    break;
                case 10:
                    textLifeHero = textureNombre10;
                    break;
                case 15:
                    textLifeHero = textureNombre15;
                    break;
                case 20:
                    textLifeHero = textureNombre20;
                    break;
                case 25:
                    textLifeHero = textureNombre25;
                    break;
                case 30:
                    textLifeHero = textureNombre30;
                    break;
                case 35:
                    textLifeHero = textureNombre35;
                    break;
                case 40:
                    textLifeHero = textureNombre40;
                    break;
                case 45:
                    textLifeHero = textureNombre45;
                    break;
                case 50:
                    textLifeHero = textureNombre50;
                    break;
                case 55:
                    textLifeHero = textureNombre55;
                    break;
                case 60:
                    textLifeHero = textureNombre60;
                    break;
                case 65:
                    textLifeHero = textureNombre65;
                    break;
                case 70:
                    textLifeHero = textureNombre70;
                    break;
                case 75:    
                    textLifeHero = textureNombre75;
                    break;
                case 80:    
                    textLifeHero = textureNombre80;
                    break;
                case 85:    
                    textLifeHero = textureNombre85;
                    break;
                case 90:   
                    textLifeHero = textureNombre90;
                    break;
                case 95:    
                    textLifeHero = textureNombre95;
                    break;
                case 100:    
                    textLifeHero = textureNombre100;
                    break;
            }
            scene.drawInfo(prog2D, vaoMap, textLifeHero, -7.5, 10.2, 0.09);

            // Dessin defense Alice
            GLuint textAttackHero;
            switch(alice.getAttack()) {
                case 0:
                    textAttackHero = textureNombre0;
                    break;
                case 5:
                    textAttackHero = textureNombre5;
                    break;
                case 10:
                    textAttackHero = textureNombre10;
                    break;
                case 15:
                    textAttackHero = textureNombre15;
                    break;
                case 20:
                    textAttackHero = textureNombre20;
                    break;
                case 25:
                    textAttackHero = textureNombre25;
                    break;
                case 30:
                    textAttackHero = textureNombre30;
                    break;
                case 35:
                    textAttackHero = textureNombre35;
                    break;
                case 40:
                    textAttackHero = textureNombre40;
                    break;
                case 45:
                    textAttackHero = textureNombre45;
                    break;
                case 50:
                    textAttackHero = textureNombre50;
                    break;
                case 55:
                    textAttackHero = textureNombre55;
                    break;
                case 60:
                    textAttackHero = textureNombre60;
                    break;
                case 65:
                    textAttackHero = textureNombre65;
                    break;
                case 70:
                    textAttackHero = textureNombre70;
                    break;
                case 75:    
                    textAttackHero = textureNombre75;
                    break;
                case 80:    
                    textAttackHero = textureNombre80;
                    break;
                case 85:    
                    textAttackHero = textureNombre85;
                    break;
                case 90:   
                    textAttackHero = textureNombre90;
                    break;
                case 95:    
                    textAttackHero = textureNombre95;
                    break;
                case 100:    
                    textAttackHero = textureNombre100;
                    break;
            }
            scene.drawInfo(prog2D, vaoMap, textAttackHero, -7.5, 8.9, 0.09);


            // Dessin defense Alice
            GLuint textDefenseHero;
            switch(alice.getDefense()) {
                case 0:
                    textDefenseHero = textureNombre0;
                    break;
                case 5:
                    textDefenseHero = textureNombre5;
                    break;
                case 10:
                    textDefenseHero = textureNombre10;
                    break;
                case 15:
                    textDefenseHero = textureNombre15;
                    break;
                case 20:
                    textDefenseHero = textureNombre20;
                    break;
                case 25:
                    textDefenseHero = textureNombre25;
                    break;
                case 30:
                    textDefenseHero = textureNombre30;
                    break;
                case 35:
                    textDefenseHero = textureNombre35;
                    break;
                case 40:
                    textDefenseHero = textureNombre40;
                    break;
                case 45:
                    textDefenseHero = textureNombre45;
                    break;
                case 50:
                    textDefenseHero = textureNombre50;
                    break;
                case 55:
                    textDefenseHero = textureNombre55;
                    break;
                case 60:
                    textDefenseHero = textureNombre60;
                    break;
                case 65:
                    textDefenseHero = textureNombre65;
                    break;
                case 70:
                    textDefenseHero = textureNombre70;
                    break;
                case 75:    
                    textDefenseHero = textureNombre75;
                    break;
                case 80:    
                    textDefenseHero = textureNombre80;
                    break;
                case 85:    
                    textDefenseHero = textureNombre85;
                    break;
                case 90:   
                    textDefenseHero = textureNombre90;
                    break;
                case 95:    
                    textDefenseHero = textureNombre95;
                    break;
                case 100:    
                    textDefenseHero = textureNombre100;
                    break;
            }
            scene.drawInfo(prog2D, vaoMap, textDefenseHero, -7.5, 7.6, 0.09);
            
            // Dessin infos globales
            scene.drawInfo(prog2D, vaoMap, textureNombreGlobale, -2, 2, 0.4);


            // Affichage de cubes sur la carte
            for(int i = 0; i < scene.sizeY; ++i) {
                for(int j = 0; j < scene.sizeX; ++j) {


                    // TEST SOL ET CIEL -- MODIFIER TEXTURE
                    prog3D.m_Program.use();
                    scene.drawCube(prog3D, cube, viewMatrix, ProjMatrix, MVMatrix, NormalMatrix, vaoCube, textureSol, j, -1, i);

                    prog3D.m_Program.use();
                    scene.drawCube(prog3D, cube, viewMatrix, ProjMatrix, MVMatrix, NormalMatrix, vaoCube, texturePlafond, j, 2, i);

                    // Si on a un mur, afficher un cube sur la case
                    if(scene.grid[i][j] == WALL) {
                        prog3D.m_Program.use();

                        // MUR BAS
                        scene.drawCube(prog3D, cube, viewMatrix, ProjMatrix, MVMatrix, NormalMatrix, vaoCube, textureMurBas, j, 0, i);
                        // MUR HAUT -- MODIFIER TEXTURE
                        scene.drawCube(prog3D, cube, viewMatrix, ProjMatrix, MVMatrix, NormalMatrix, vaoCube, textureMurHaut, j, 1, i);


                        // MINI CARTE 
                        prog2D.m_Program.use();
                        scene.drawMap(prog2D, vaoMap, textureMurMap, j, i);
                    }
                    else if(j == alice.getPosX() && i == alice.getPosY()) {
                        prog2D.m_Program.use();
                        scene.drawMap(prog2D, vaoMap, textureHeroMap, j, i);
                    }
                    else if(scene.grid[i][j] == ENTER) {
                        // PORTES HAUT & BAS
                        prog3D.m_Program.use();
                        scene.drawCube(prog3D, cube, viewMatrix, ProjMatrix, MVMatrix, NormalMatrix, vaoCube, texturePorteDepartHaut, j, 1, i+1);
                        scene.drawCube(prog3D, cube, viewMatrix, ProjMatrix, MVMatrix, NormalMatrix, vaoCube, texturePorteDepartBas, j, 0, i+1);

                        // MINI CARTE 
                        prog2D.m_Program.use();
                        scene.drawMap(prog2D, vaoMap, texturePorteMap, j, i);

                    }
                    else if(scene.grid[i][j] == EXIT) {
                        // PORTES HAUT & BAS
                        prog3D.m_Program.use();
                        scene.drawCube(prog3D, cube, viewMatrix, ProjMatrix, MVMatrix, NormalMatrix, vaoCube, texturePorteArriveeHaut, j, 1, i-1);
                        scene.drawCube(prog3D, cube, viewMatrix, ProjMatrix, MVMatrix, NormalMatrix, vaoCube, texturePorteArriveeBas, j, 0, i-1);

                        // MINI CARTE 
                        prog2D.m_Program.use();
                        scene.drawMap(prog2D, vaoMap, texturePorteMap, j, i);
                    }
                    else if(scene.grid[i][j] == CORRIDOR) {
                        prog2D.m_Program.use();
                        scene.drawMap(prog2D, vaoMap, textureFondMap, j, i);
                    }

                    if(scene.isTreasure(j, i)) {
                        prog3D.m_Program.use();

                        GLuint textTreasure;
                        switch(scene.getTreasure(j, i).getType()) {
                            case TREASURE_LIFE:
                                textTreasure = textureTreasureDrinkMe;
                                break;
                            case TREASURE_DEFENSE:
                                textTreasure = textureTreasureHat;
                                break;
                            case TREASURE_ATTACK:
                                textTreasure = textureTreasureClock;
                                break;
                            case TREASURE_LEVEL:
                                textTreasure = textureTreasureKey;
                                break;
                            default:
                                break;
                        }
                        prog3D.m_Program.use();
                        scene.drawTreasure(prog3D, sphere, viewMatrix, ProjMatrix, MVMatrix, NormalMatrix, vaoSphere, textTreasure, j, 0, i, windowManager.getTime()+i);

                    }
                    if(scene.isMonster(j, i)) {
                        GLuint textMonster;
                        switch(scene.getMonster(j, i).getType()) {
                            case MONSTER_5:
                                textMonster = textureMonster5;
                                break;
                            case MONSTER_7:
                                textMonster = textureMonster7;
                                break;
                            case MONSTER_10:
                                textMonster = textureMonster10;
                                break;
                            case MONSTER_QUEEN:
                                textMonster = textureMonsterQueen;
                                break;
                            case MONSTER_VALET:
                                textMonster = textureMonsterValet;
                                break;
                            default:
                                break;
                        }
                        prog3D.m_Program.use();
                        scene.drawMonster(prog3D, cube, viewMatrix, ProjMatrix, MVMatrix, NormalMatrix, vaoCube, textMonster, j, 0, i);
                    

                        if(scene.monsterNextToHero(scene.getMonster(j, i), alice)) {
                            prog2D.m_Program.use();

                            // Dessin vie Monster
                            GLuint textLifeMonster;
                            switch(scene.getMonster(j, i).getLife()) {
                                case 0:
                                    textLifeMonster = textureNombre0m;
                                    break;
                                case 5:
                                    textLifeMonster = textureNombre5m;
                                    break;
                                case 10:
                                    textLifeMonster = textureNombre10m;
                                    break;
                                case 15:
                                    textLifeMonster = textureNombre15m;
                                    break;
                                case 20:
                                    textLifeMonster = textureNombre20m;
                                    break;
                                case 25:
                                    textLifeMonster = textureNombre25m;
                                    break;
                                case 30:
                                    textLifeMonster = textureNombre30m;
                                    break;
                                case 35:
                                    textLifeMonster = textureNombre35m;
                                    break;
                                case 40:
                                    textLifeMonster = textureNombre40m;
                                    break;
                                case 45:
                                    textLifeMonster = textureNombre45m;
                                    break;
                                case 50:
                                    textLifeMonster = textureNombre50m;
                                    break;
                                case 55:
                                    textLifeMonster = textureNombre55m;
                                    break;
                                case 60:
                                    textLifeMonster = textureNombre60m;
                                    break;
                                case 65:
                                    textLifeMonster = textureNombre65m;
                                    break;
                                case 70:
                                    textLifeMonster = textureNombre70m;
                                    break;
                                case 75:    
                                    textLifeMonster = textureNombre75m;
                                    break;
                                case 80:    
                                    textLifeMonster = textureNombre80m;
                                    break;
                                case 85:    
                                    textLifeMonster = textureNombre85m;
                                    break;
                                case 90:   
                                    textLifeMonster = textureNombre90m;
                                    break;
                                case 95:    
                                    textLifeMonster = textureNombre95m;
                                    break;
                                case 100:    
                                    textLifeMonster = textureNombre100m;
                                    break;
                            }
                            scene.drawInfo(prog2D, vaoMap, textLifeMonster, -7.5, 4.5, 0.09);

                            
                            // Dessin infos globales
                            GLuint textureNombreGlobaleMonstre;
                            switch (scene.getMonster(j, i).getType()) {
                                case MONSTER_5:
                                case MONSTER_7:
                                case MONSTER_10:
                                    textureNombreGlobaleMonstre = textureNombreGlobale_soldat;
                                    break;
                                case MONSTER_VALET:
                                    textureNombreGlobaleMonstre = textureNombreGlobale_valet;
                                    break;
                                case MONSTER_QUEEN:
                                    textureNombreGlobaleMonstre = textureNombreGlobale_queen;
                                    break;
                                default:
                                    break;
                            }
                            scene.drawInfo(prog2D, vaoMap, textureNombreGlobaleMonstre, -2, 1, 0.4);
                        }

                    }
                }
            } 
        }
      


        // Update the display
        windowManager.swapBuffers();
    }

    // Delete the text's VBO, the shader and the texture
    // cleanupText2D();

    return EXIT_SUCCESS;
}
