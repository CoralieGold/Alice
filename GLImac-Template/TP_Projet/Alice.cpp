#include <glimac/SDLWindowManager.hpp>
#include <glimac/common.hpp>
#include <glimac/Object.hpp>
#include <glimac/Cube.hpp>
#include <glimac/Program.hpp>
#include <glimac/FilePath.hpp>
#include <glimac/Image.hpp>
#include <glimac/SceneOpenGL.hpp>
#include <GL/glew.h>
#include <iostream>
#include <vector>

#include <stdlib.h>
#include <time.h>

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
    if(!scene.readLevel()) {
        cout << "Impossible de lancer le niveau !" << endl;
    }

    // A REVOIR
    unsigned int departX;
    unsigned int departY;
    string nom = "Alice";
    int defense = 100;
    int attaque = 100;
    unsigned int ptsVie = 90;

    cout << "Taille carte x:y " << scene.sizeX << " : " << scene.sizeY << endl;

    for(int i = 0; i < scene.sizeY; i++) {
        for(int j = 0; j < scene.sizeX; j++) {
            // Si on a l'entrée, on dit que c'est le départ pour la caméra et le perso
            if(scene.grid[i][j] == 3) {
                departX = j;
                departY = i;
                cout << "J'ai trouvé l'entrée en " << departX << " : " << departY << endl;
            }
        }
    }

    FreeflyCamera camera(glm::vec3(departX, 0, departY));
    Hero alice(departX, departY, nom, attaque, defense, ptsVie, camera);


    for(int i = 0; i < scene.sizeY; i++) {
        for(int j = 0; j < scene.sizeX; j++) {
            if(j == departX && i == departY) {
                if(i-1 >= 0) {
                    if(scene.getGrid()[i-1][j] != 1) {
                        alice.setOrientation(0);
                    }  
                }
                else if(i+1 < scene.sizeY) {
                    if(scene.getGrid()[i+1][j] != 1) {
                        alice.setOrientation(180);
                    }
                }
                else if(j+1 < scene.sizeX) {
                    if(scene.getGrid()[i][j+1] != 1) {
                        alice.setOrientation(90);
                    }
                }
                else if(j-1 >= 0) {
                    if(scene.getGrid()[i][j-1] != 1) {
                        alice.setOrientation(270);
                    }
                }
                else {
                    cout << "Le personnage est coincé !" << endl;
                }
            }
        }
    }

    //cout << "Orientation du personnage : " << alice.getOrientation() << endl;
    alice.getCamera().rotateLeft(alice.getOrientation());
   // cout << "Alice caméra : " << alice.getCamera().getViewMatrix().x << endl;

    /** Texture mur **/
    std::unique_ptr<Image> murImage = loadImage("/home/6im2/mroche/Documents/Projet_Synthese_Image/GLImac-Template/assets/textures/Feuilles.jpg");
    if(murImage != NULL) std::cout << "La texture des murs est bien chargée !" << std::endl;
    GLuint textureMur;
    glGenTextures(1, &textureMur);
    glBindTexture(GL_TEXTURE_2D, textureMur);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, murImage->getWidth(), murImage->getHeight(), 0, GL_RGBA, GL_FLOAT, murImage->getPixels());

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glBindTexture(GL_TEXTURE_2D, 0);

    /** Texture autre (test) **/
    std::unique_ptr<Image> testImage = loadImage("/home/6im2/mroche/Documents/Projet_Synthese_Image/GLImac-Template/assets/textures/MoonMap.jpg");
    if(testImage != NULL) std::cout << "La texture de test est bien chargée !" << std::endl;
    
    GLuint textureTest;
    glGenTextures(1, &textureTest);
    glBindTexture(GL_TEXTURE_2D, textureTest);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, testImage->getWidth(), testImage->getHeight(), 0, GL_RGBA, GL_FLOAT, testImage->getPixels());

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glBindTexture(GL_TEXTURE_2D, 0);





    int uTexture;



    FilePath applicationPath(argv[0]);
    Program program = loadProgram(applicationPath.dirPath() + "shaders/" + argv[1],
        applicationPath.dirPath() + "shaders/" + argv[2]);
    program.use();



    Cube cube(1);
    
    /*** Création du VAO ***/
    GLuint vao;
    glGenVertexArrays(1, &vao);
    /*** Binding du vao ***/
    glBindVertexArray(vao);
    /*** Activation des attributs de vertex ***/
    const GLuint VERTEX_ATTR_POSITION = 0;
    const GLuint VERTEX_ATTR_NORMAL = 1;
    const GLuint VERTEX_ATTR_TEXT_COORD = 2;
    glEnableVertexAttribArray(VERTEX_ATTR_POSITION);
    glEnableVertexAttribArray(VERTEX_ATTR_NORMAL);
    glEnableVertexAttribArray(VERTEX_ATTR_TEXT_COORD);
    /** Rebindage **/
    glBindBuffer(GL_ARRAY_BUFFER, scene.createVboCube(cube));
    glVertexAttribPointer(VERTEX_ATTR_POSITION, 3, GL_FLOAT, GL_FALSE, sizeof(ShapeVertex), (const GLvoid*) 0);
    glVertexAttribPointer(VERTEX_ATTR_NORMAL, 3, GL_FLOAT, GL_FALSE, sizeof(ShapeVertex), (const GLvoid*) offsetof(ShapeVertex, normal));
    glVertexAttribPointer(VERTEX_ATTR_TEXT_COORD, 2, GL_FLOAT, GL_FALSE, sizeof(ShapeVertex), (const GLvoid*) offsetof(ShapeVertex, texCoords));
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    /*** Débinding du vao ***/
    glBindVertexArray(0);




    Sphere sphere(0.25, 16, 32);

    /*** Création du VAO ***/
    GLuint vao2;
    glGenVertexArrays(1, &vao2);
    /*** Binding du vao ***/
    glBindVertexArray(vao2);
    /*** Activation des attributs de vertex ***/
    glEnableVertexAttribArray(VERTEX_ATTR_POSITION);
    glEnableVertexAttribArray(VERTEX_ATTR_NORMAL);
    glEnableVertexAttribArray(VERTEX_ATTR_TEXT_COORD);
    /** Rebindage **/
    glBindBuffer(GL_ARRAY_BUFFER, scene.createVboSphere(sphere));
    glVertexAttribPointer(VERTEX_ATTR_POSITION, 3, GL_FLOAT, GL_FALSE, sizeof(ShapeVertex), (const GLvoid*) 0);
    glVertexAttribPointer(VERTEX_ATTR_NORMAL, 3, GL_FLOAT, GL_FALSE, sizeof(ShapeVertex), (const GLvoid*) offsetof(ShapeVertex, normal));
    glVertexAttribPointer(VERTEX_ATTR_TEXT_COORD, 2, GL_FLOAT, GL_FALSE, sizeof(ShapeVertex), (const GLvoid*) offsetof(ShapeVertex, texCoords));
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    /*** Débinding du vao ***/
    glBindVertexArray(0);




    // Read our .obj file
    Object cone("/home/6im2/mroche/Documents/Projet_Synthese_Image/GLImac-Template/assets/models/coneText.obj");
    cone.loadObject();


    /*** Création du VAO ***/
    GLuint vaoCone;
    glGenVertexArrays(1, &vaoCone);
    /*** Binding du vao ***/
    glBindVertexArray(vaoCone);
    /*** Activation des attributs de vertex ***/
    glEnableVertexAttribArray(VERTEX_ATTR_POSITION);
    glEnableVertexAttribArray(VERTEX_ATTR_NORMAL);
    glEnableVertexAttribArray(VERTEX_ATTR_TEXT_COORD);
    /** Rebindage **/
    glBindBuffer(GL_ARRAY_BUFFER, scene.createVboObject(cone));
    glVertexAttribPointer(VERTEX_ATTR_POSITION, 3, GL_FLOAT, GL_FALSE, sizeof(ShapeVertex), (const GLvoid*) 0);
    glVertexAttribPointer(VERTEX_ATTR_NORMAL, 3, GL_FLOAT, GL_FALSE, sizeof(ShapeVertex), (const GLvoid*) offsetof(ShapeVertex, normal));
    glVertexAttribPointer(VERTEX_ATTR_TEXT_COORD, 2, GL_FLOAT, GL_FALSE, sizeof(ShapeVertex), (const GLvoid*) offsetof(ShapeVertex, texCoords));
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    /*** Débinding du vao ***/
    glBindVertexArray(0);




    // activation test profondeur GPU
    glEnable(GL_DEPTH_TEST); 
    GLint uMVPMatrix = glGetUniformLocation(program.getGLId(), "uMVPMatrix");
    GLint uMVMatrix = glGetUniformLocation(program.getGLId(), "uMVMatrix");
    GLint uNormalMatrix = glGetUniformLocation(program.getGLId(), "uNormalMatrix");



    glm::mat4 ProjMatrix, MVMatrix, NormalMatrix;
    ProjMatrix = glm::perspective(glm::radians(70.f), 800.f/600.f, 0.1f, 100.f);
    MVMatrix = glm::translate(MVMatrix, glm::vec3(0.,0.,-5.0));
    NormalMatrix = glm::transpose(glm::inverse(MVMatrix));

    srand(time(NULL));

    int randomOrientation;


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
                            // Reculer
                            if(scene.canMove(alice.getOrientation(), alice.getPosX(), alice.getPosY(), -1)) {
                                alice.down();
                            }
                            if(scene.isTreasure(alice.getPosX(), alice.getPosY())) {
                                alice.applyTreasure(scene.getTreasure(alice.getPosX(), alice.getPosY()));
                                scene.deleteTreasure(alice.getPosX(), alice.getPosY());
                                cout << "Tresor applique !" << endl;
                            }
                            // prendre en compte si trésor ET monstre sur la meme case
                            // if(scene.isMonster(alice.getPosX(), alice.getPosY())) {
                            //     cout << "Il y a un monstre !" << endl;
                            // }
                        break;
                        case SDLK_UP :
                        case SDLK_z :
                            // Avancer
                            if(scene.canMove(alice.getOrientation(), alice.getPosX(), alice.getPosY(), 1)) {
                                alice.up();
                            } 
                            if(scene.isTreasure(alice.getPosX(), alice.getPosY())) {
                                alice.applyTreasure(scene.getTreasure(alice.getPosX(), alice.getPosY()));
                                scene.deleteTreasure(alice.getPosX(), alice.getPosY());
                                cout << "Tresor applique !" << endl;
                            }
                            // prendre en compte si trésor ET monstre sur la meme case
                            // if(scene.isMonster(alice.getPosX(), alice.getPosY())) {
                            //     cout << "Il y a un monstre !" << endl;
                            // }
                        break;
                        case SDLK_LEFT :
                        case SDLK_q :
                            // Tourner à gauche de 90°
                            alice.left();
                            //cout << "Gauche" << endl;
                        break;
                        case SDLK_RIGHT:
                        case SDLK_d :
                            // Tourner à droite de 90°
                            alice.right();
                            //cout << "Droite" << endl;
                        break;
                        case SDLK_o:
                            // Defense
                            cout << "Defense" << endl;
                        break;
                        case SDLK_i :
                            // Attaque
                            cout << "Attaque" << endl;
                        break;
                    }
                break;
                case SDL_MOUSEBUTTONDOWN :
                    switch(e.button.button) {
                        case SDL_BUTTON_RIGHT:
                            // Defense
                            cout << "Defense" << endl;
                        break;
                        case SDL_BUTTON_LEFT :
                            // Attaque
                            cout << "Attaque" << endl;
                        break;
                    }
                break;
            }
        }

        /*********************************
         * HERE SHOULD COME THE RENDERING CODE
         *********************************/
        timer ++;
        if(timer%MONSTERS_SPEED == 0) {
            for(unsigned int i = 0; i < scene.getMonsters().size(); i ++) {
                if(scene.monsterSeeHero(*scene.getMonsters()[i], alice)) {
                    if(scene.monsterNextToHero(*scene.getMonsters()[i], alice)) {
                        cout << "A l'attaque !" << endl;
                    }
                    else {
                        scene.getMonsters()[i]->move();
                        cout << "Je me rapproche !" << endl; 
                    }
                    
                }
                else {
                    if(scene.canMove(scene.getMonsters()[i]->getOrientation(), scene.getMonsters()[i]->getPosX(), scene.getMonsters()[i]->getPosY(), 1)) {
                        scene.getMonsters()[i]->move();
                    }
                    else {
                        // regarder si un mur est libre (droite ou gauche selon aléatoire)
                        randomOrientation = rand() % 2;
                        if(randomOrientation == 1){
                            scene.getMonsters()[i]->setOrientation(scene.getMonsters()[i]->getOrientation() + 90);
                            if(scene.getMonsters()[i]->getOrientation() >= 360) scene.getMonsters()[i]->setOrientation(0);
                        }else{
                            scene.getMonsters()[i]->setOrientation(scene.getMonsters()[i]->getOrientation() - 90);
                            if(scene.getMonsters()[i]->getOrientation() < 0) scene.getMonsters()[i]->setOrientation(270);
                        }
                        
                    }
                }

            }
        }

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


        glm::mat4 viewMatrix = alice.getCamera().getViewMatrix();
        //MVMatrix = MVMatrix * viewMatrix;

        // Affichage de cubes sur la carte
        for(int i = 0; i < scene.sizeY; i++) {
            for(int j = 0; j < scene.sizeX; j++) {
                // Si on a un mur, afficher un cube sur la case
                if(scene.grid[i][j] == 1) {
                    glBindTexture(GL_TEXTURE_2D, textureMur);
                    glUniform1i(glGetUniformLocation(program.getGLId(), "uTexture"), 0);

                    glBindVertexArray(vao);
                    
                    glm::mat4 MVMatrix = glm::translate(glm::mat4(1), glm::vec3(j, 0, i));
                    MVMatrix = viewMatrix * MVMatrix;
                    glUniformMatrix4fv(uMVMatrix, 1, GL_FALSE, glm::value_ptr(MVMatrix));
                    glUniformMatrix4fv(uNormalMatrix, 1, GL_FALSE, glm::value_ptr(NormalMatrix));
                    glUniformMatrix4fv(uMVPMatrix, 1, GL_FALSE, glm::value_ptr(ProjMatrix * MVMatrix));

                    glDrawArrays(GL_TRIANGLES, 0, cube.getVertexCount());


                    // TEST CUBES DESSUS -- MODIFIER TEXTURE

                    MVMatrix = glm::translate(glm::mat4(1), glm::vec3(j, 1, i));
                    MVMatrix = viewMatrix * MVMatrix;
                    glUniformMatrix4fv(uMVMatrix, 1, GL_FALSE, glm::value_ptr(MVMatrix));
                    glUniformMatrix4fv(uNormalMatrix, 1, GL_FALSE, glm::value_ptr(NormalMatrix));
                    glUniformMatrix4fv(uMVPMatrix, 1, GL_FALSE, glm::value_ptr(ProjMatrix * MVMatrix));

                    glDrawArrays(GL_TRIANGLES, 0, cube.getVertexCount());


                    // TEST SOL ET CIEL -- MODIFIER TEXTURE

                    /*MVMatrix = glm::translate(glm::mat4(1), glm::vec3(i, 1, j));
                    MVMatrix = glm::scale(MVMatrix, glm::vec3(30, 30, 30));
                    MVMatrix = viewMatrix * MVMatrix;
                    glUniformMatrix4fv(uMVMatrix, 1, GL_FALSE, glm::value_ptr(MVMatrix));
                    glUniformMatrix4fv(uNormalMatrix, 1, GL_FALSE, glm::value_ptr(NormalMatrix));
                    glUniformMatrix4fv(uMVPMatrix, 1, GL_FALSE, glm::value_ptr(ProjMatrix * MVMatrix));

                    glDrawArrays(GL_TRIANGLES, 0, cube.getVertexCount());*/
                    glBindVertexArray(0);

                    glBindTexture(GL_TEXTURE_2D, 0);
                }
                else if(scene.isTreasure(j, i)) {
                    glBindTexture(GL_TEXTURE_2D, textureTest);
                    glBindVertexArray(vaoCone);

                    MVMatrix = glm::translate(glm::mat4(1), glm::vec3(j, 0, i));
                    MVMatrix = glm::scale(MVMatrix, glm::vec3(0.1, 0.1, 0.1));
                    MVMatrix = viewMatrix * MVMatrix;
                    glUniformMatrix4fv(uMVMatrix, 1, GL_FALSE, glm::value_ptr(MVMatrix));
                    glUniformMatrix4fv(uNormalMatrix, 1, GL_FALSE, glm::value_ptr(NormalMatrix));
                    glUniformMatrix4fv(uMVPMatrix, 1, GL_FALSE, glm::value_ptr(ProjMatrix * MVMatrix));
                    glDrawArrays(GL_TRIANGLES, 0, cone.vertex.size());

                    glBindVertexArray(0);

                    glBindTexture(GL_TEXTURE_2D, 0);
                }
                else if(scene.isMonster(j, i)) {
                    glBindTexture(GL_TEXTURE_2D, textureTest);
                    glUniform1i(glGetUniformLocation(program.getGLId(), "uTexture"), 0);

                    glBindVertexArray(vao2);

                    MVMatrix = glm::translate(glm::mat4(1), glm::vec3(j, 0, i));
                    MVMatrix = viewMatrix * MVMatrix;
                    glUniformMatrix4fv(uMVMatrix, 1, GL_FALSE, glm::value_ptr(MVMatrix));
                    glUniformMatrix4fv(uNormalMatrix, 1, GL_FALSE, glm::value_ptr(NormalMatrix));
                    glUniformMatrix4fv(uMVPMatrix, 1, GL_FALSE, glm::value_ptr(ProjMatrix * MVMatrix));
                    glDrawArrays(GL_TRIANGLES, 0, sphere.getVertexCount());

                    glBindVertexArray(0);

                    glBindTexture(GL_TEXTURE_2D, 0);
                }
            }
        }


        // Update the display
        windowManager.swapBuffers();
    }

    return EXIT_SUCCESS;
}
