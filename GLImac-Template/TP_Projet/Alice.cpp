#include <glimac/SDLWindowManager.hpp>
#include <glimac/common.hpp>
#include <glimac/Object.hpp>
#include <glimac/Cube.hpp>
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

struct WallProgram {
    Program m_Program;


    GLint uMVPMatrix;
    GLint uMVMatrix;
    GLint uNormalMatrix;
    GLint uWallTexture;


    WallProgram(const FilePath& applicationPath):
        m_Program(loadProgram(applicationPath.dirPath() + "shaders/3D.vs.glsl",
                              applicationPath.dirPath() + "shaders/tex3D.fs.glsl")) {
        uMVPMatrix = glGetUniformLocation(m_Program.getGLId(), "uMVPMatrix");
        uMVMatrix = glGetUniformLocation(m_Program.getGLId(), "uMVMatrix");
        uNormalMatrix = glGetUniformLocation(m_Program.getGLId(), "uNormalMatrix");
        uWallTexture = glGetUniformLocation(m_Program.getGLId(), "uTexture");
    }
};

struct MapProgram {
    Program m_Program;


    GLint uModelMatrix;
    GLint uMapTexture;


    MapProgram(const FilePath& applicationPath):
        m_Program(loadProgram(applicationPath.dirPath() + "shaders/text2D.vs.glsl",
                              applicationPath.dirPath() + "shaders/text2D.fs.glsl")) {
        uModelMatrix = glGetUniformLocation(m_Program.getGLId(), "uModelMatrix");
        uMapTexture = glGetUniformLocation(m_Program.getGLId(), "uTexture");
    }
};

glm::mat3 translate(float x, float y) {
    return glm::mat3(glm::vec3(1, 0, 0), glm::vec3(0, 1, 0), glm::vec3(x, y, 1));
}

glm::mat3 scale(float a) {
    return glm::mat3(glm::vec3(a, 0, 0), glm::vec3(0, a, 0), glm::vec3(0, 0, a));
}

glm::mat3 rotate(float a) {
    return glm::mat3(glm::vec3(cos(glm::radians(a)), sin(glm::radians(a)), 0), glm::vec3(-sin(glm::radians(a)), cos(glm::radians(a)), 0), glm::vec3(0, 0, 1));
}


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
    if(!scene.readLevel("../GLImac-Template/assets/files/level2.txt")) {
        cout << "Impossible de lancer le niveau !" << endl;
    }

    // A REVOIR
    unsigned int departX;
    unsigned int departY;
    string nom = "Alice";
    int defense = 5;
    int attaque = 10;
    unsigned int ptsVie = 90;

    //cout << "Taille carte x:y " << scene.sizeX << " : " << scene.sizeY << endl;

    for(int i = 0; i < scene.sizeY; i++) {
        for(int j = 0; j < scene.sizeX; j++) {
            // Si on a l'entrée, on dit que c'est le départ pour la caméra et le perso
            if(scene.grid[i][j] == ENTER) {
                departX = j;
                departY = i;
                //cout << "J'ai trouvé l'entrée en " << departX << " : " << departY << endl;
            }
        }
    }

    FreeflyCamera camera(glm::vec3(departX, 0, departY));
    Hero alice(departX, departY, nom, attaque, defense, ptsVie, camera);


    for(int i = 0; i < scene.sizeY; i++) {
        for(int j = 0; j < scene.sizeX; j++) {
            if(j == departX && i == departY) {
                if(i-1 >= 0) {
                    if(scene.getGrid()[i-1][j] != WALL) {
                        alice.setOrientation(0);
                    }  
                }
                else if(i+1 < scene.sizeY) {
                    if(scene.getGrid()[i+1][j] != WALL) {
                        alice.setOrientation(180);
                    }
                }
                else if(j+1 < scene.sizeX) {
                    if(scene.getGrid()[i][j+1] != WALL) {
                        alice.setOrientation(90);
                    }
                }
                else if(j-1 >= 0) {
                    if(scene.getGrid()[i][j-1] != WALL) {
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


    FilePath applicationPath(argv[0]);
    WallProgram wallProgram(applicationPath);
    MapProgram mapProgram(applicationPath);



    /** Texture mur **/
    GLuint textureMur = scene.createTexture("/home/6im2/mroche/Documents/Projet_Synthese_Image/GLImac-Template/assets/textures/Feuilles.png");

    /** Texture porte haut **/
    GLuint texturePorteHaut = scene.createTexture("/home/6im2/mroche/Documents/Projet_Synthese_Image/GLImac-Template/assets/textures/Sol.png");

    /** Texture porte bas **/
    GLuint texturePorteBas = scene.createTexture("/home/6im2/mroche/Documents/Projet_Synthese_Image/GLImac-Template/assets/textures/Sol.png");


    /** Texture mur -- MAP **/
    GLuint textureMurMap = scene.createTexture("/home/6im2/mroche/Documents/Projet_Synthese_Image/GLImac-Template/assets/textures/violet_fonce.jpg");
    /** Texture porte haut -- MAP**/
    GLuint texturePorteMap = scene.createTexture("/home/6im2/mroche/Documents/Projet_Synthese_Image/GLImac-Template/assets/textures/violet_clair.jpg");
    /** Texture perso -- MAP**/
    GLuint textureHeroMap = scene.createTexture("/home/6im2/mroche/Documents/Projet_Synthese_Image/GLImac-Template/assets/textures/bleu_clair.jpg");
    /** Texture fond -- MAP**/
    GLuint textureFondMap = scene.createTexture("/home/6im2/mroche/Documents/Projet_Synthese_Image/GLImac-Template/assets/textures/bleu_fonce.jpg");



    /** Texture sol **/
    GLuint textureSol = scene.createTexture("/home/6im2/mroche/Documents/Projet_Synthese_Image/GLImac-Template/assets/textures/Sol.png");

    /** Texture plafond **/
    GLuint texturePlafond = scene.createTexture("/home/6im2/mroche/Documents/Projet_Synthese_Image/GLImac-Template/assets/textures/Sol.png");

    /** Texture Objet mange moi **/
    GLuint textureTresorMangeMoi = scene.createTexture("/home/6im2/mroche/Documents/Projet_Synthese_Image/GLImac-Template/assets/textures/MangeMoi.jpg");

    /** Texture autre (test) **/
    GLuint textureTest = scene.createTexture("/home/6im2/mroche/Documents/Projet_Synthese_Image/GLImac-Template/assets/textures/MoonMap.jpg");

    /** Texture chiffre **/
    GLuint textureNombre5 = scene.createTexture("/home/6im2/mroche/Documents/Projet_Synthese_Image/GLImac-Template/assets/textures/5.jpg");

    /** Texture chiffre **/
    GLuint textureNombre10 = scene.createTexture("/home/6im2/mroche/Documents/Projet_Synthese_Image/GLImac-Template/assets/textures/10.jpg");


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



    // MAP

    Vertex2DUV map[] = { 
        Vertex2DUV(glm::vec2(-0.5, -0.5), glm::vec2(0, 1)),
        Vertex2DUV(glm::vec2(0.5, -0.5), glm::vec2(1, 1)),
        Vertex2DUV(glm::vec2(0.5, 0.5), glm::vec2(1, 0)),
        Vertex2DUV(glm::vec2(-0.5, -0.5), glm::vec2(0, 1)),
        Vertex2DUV(glm::vec2(0.5, 0.5), glm::vec2(1, 0)),
        Vertex2DUV(glm::vec2(-0.5, 0.5), glm::vec2(0, 0))
        
    };


    // Creation d'un seul VBO
     GLuint vbo;
     glGenBuffers(1, &vbo);
    // A partir de ce point, la variable vbo contient l'identifiant d'une VBO

    /*** Binding du VBO ***/

    // Binding d'un VBO sur la cible GL_ARRAY_BUFFER
     glBindBuffer(GL_ARRAY_BUFFER, vbo);
    // On peut à présent modifier le VBO en passant par la cible GL_ARRAY_BUFFER
    /*** Remplir le VBO ***/

    glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(Vertex2DUV), map, GL_STATIC_DRAW);

    /*** Débinder le VBO ***/
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    /*** Création du VAO ***/
    GLuint vaoMap;
    glGenVertexArrays(1, &vaoMap);

    /*** Binding du vao ***/
    glBindVertexArray(vaoMap);

    /*** Activation des attributs de vertex ***/
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);


    /** Rebindage **/
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex2DUV), (const GLvoid*) offsetof(Vertex2DUV, positionXY));
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex2DUV), (const GLvoid*) offsetof(Vertex2DUV, coordTextUV));
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    /*** Débinding du vao ***/
    glBindVertexArray(0);






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
                            for(unsigned int i = 0; i < scene.getMonsters().size(); i ++) {
                                if(scene.monsterNextToHero(*scene.getMonsters()[i], alice)) {
                                    scene.getMonsters()[i]->setLife(scene.attack(alice, *scene.getMonsters()[i]));
                                    cout << "Après attaque : " << scene.getMonsters()[i]->getLife() << endl;
                                    if(scene.getMonsters()[i]->getLife() == 0) {
                                        cout << "Monstre mort :D " << endl;
                                        scene.deleteMonster(i);
                                    }
                                }
                            }
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
                        alice.setLife(scene.isAttacked(*scene.getMonsters()[i], alice));
                        if(alice.getLife() == 0) cout << "Tu es morte :( " << endl;
                        isHurt = true;
                        cout << "Après attaque du monstre : " << alice.getLife() << endl;
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
                        scene.choosePath(* scene.getMonsters()[i]);
                        cout << "Orientation monstre " << scene.getMonsters()[i]->getOrientation() << endl;
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


        // AFFICHAGE CHIFFRES

        glBindVertexArray(vaoMap);

        mapProgram.m_Program.use();

        if(alice.getLife() > 5) glBindTexture(GL_TEXTURE_2D, textureNombre10);
        else glBindTexture(GL_TEXTURE_2D, textureNombre5);

        glUniform1i(mapProgram.uMapTexture, 0);
        

        glm::mat3 uModelMatrix = scale(0.1)*translate(-8,8);
        glUniformMatrix3fv(mapProgram.uModelMatrix, 1, GL_FALSE, glm::value_ptr(uModelMatrix));
        glDrawArrays(GL_TRIANGLES, 0, 6);

        glBindTexture(GL_TEXTURE_2D, 0);

        glBindVertexArray(0);


        // Affichage de cubes sur la carte
        for(int i = 0; i < scene.sizeY; i++) {
            for(int j = 0; j < scene.sizeX; j++) {


                // TEST SOL ET CIEL -- MODIFIER TEXTURE

                glBindVertexArray(vao);

                wallProgram.m_Program.use();

                glBindTexture(GL_TEXTURE_2D, textureSol);

                glUniform1i(wallProgram.uWallTexture,0);

                MVMatrix = glm::translate(glm::mat4(1), glm::vec3(j, -1, i));
                MVMatrix = viewMatrix * MVMatrix;
                glUniformMatrix4fv(wallProgram.uMVMatrix, 1, GL_FALSE, glm::value_ptr(MVMatrix));
                glUniformMatrix4fv(wallProgram.uNormalMatrix, 1, GL_FALSE, glm::value_ptr(NormalMatrix));
                glUniformMatrix4fv(wallProgram.uMVPMatrix, 1, GL_FALSE, glm::value_ptr(ProjMatrix * MVMatrix));

                glDrawArrays(GL_TRIANGLES, 0, cube.getVertexCount());

                glBindTexture(GL_TEXTURE_2D, 0);

                glBindVertexArray(0);



                glBindVertexArray(vao);

                wallProgram.m_Program.use();

                glBindTexture(GL_TEXTURE_2D, texturePlafond);

                glUniform1i(wallProgram.uWallTexture,0);

                MVMatrix = glm::translate(glm::mat4(1), glm::vec3(j, 2, i));
                MVMatrix = viewMatrix * MVMatrix;
                glUniformMatrix4fv(wallProgram.uMVMatrix, 1, GL_FALSE, glm::value_ptr(MVMatrix));
                glUniformMatrix4fv(wallProgram.uNormalMatrix, 1, GL_FALSE, glm::value_ptr(NormalMatrix));
                glUniformMatrix4fv(wallProgram.uMVPMatrix, 1, GL_FALSE, glm::value_ptr(ProjMatrix * MVMatrix));

                glDrawArrays(GL_TRIANGLES, 0, cube.getVertexCount());

                glBindTexture(GL_TEXTURE_2D, 0);

                glBindVertexArray(0);


                // Si on a un mur, afficher un cube sur la case
                if(scene.grid[i][j] == WALL) {
                    glBindVertexArray(vao);

                    wallProgram.m_Program.use();
                    
                    glBindTexture(GL_TEXTURE_2D, textureMur);

                    glUniform1i(wallProgram.uWallTexture,0);
                    
                    //glUniform1i(glGetUniformLocation(program.getGLId(), "uTexture"), 0);

                    
                    
                    glm::mat4 MVMatrix = glm::translate(glm::mat4(1), glm::vec3(j, 0, i));
                    MVMatrix = viewMatrix * MVMatrix;
                    glUniformMatrix4fv(wallProgram.uMVMatrix, 1, GL_FALSE, glm::value_ptr(MVMatrix));
                    glUniformMatrix4fv(wallProgram.uNormalMatrix, 1, GL_FALSE, glm::value_ptr(NormalMatrix));
                    glUniformMatrix4fv(wallProgram.uMVPMatrix, 1, GL_FALSE, glm::value_ptr(ProjMatrix * MVMatrix));

                    glDrawArrays(GL_TRIANGLES, 0, cube.getVertexCount());


                    // TEST CUBES DESSUS -- MODIFIER TEXTURE

                    MVMatrix = glm::translate(glm::mat4(1), glm::vec3(j, 1, i));
                    MVMatrix = viewMatrix * MVMatrix;
                    glUniformMatrix4fv(wallProgram.uMVMatrix, 1, GL_FALSE, glm::value_ptr(MVMatrix));
                    glUniformMatrix4fv(wallProgram.uNormalMatrix, 1, GL_FALSE, glm::value_ptr(NormalMatrix));
                    glUniformMatrix4fv(wallProgram.uMVPMatrix, 1, GL_FALSE, glm::value_ptr(ProjMatrix * MVMatrix));

                    glDrawArrays(GL_TRIANGLES, 0, cube.getVertexCount());



                    glBindTexture(GL_TEXTURE_2D, 0);

                    glBindVertexArray(0);


                    // MINI CARTE 
                    
                    glBindVertexArray(vaoMap);

                    mapProgram.m_Program.use();

                    glBindTexture(GL_TEXTURE_2D, textureMurMap);

                    glUniform1i(mapProgram.uMapTexture, 0);
                    

                    glm::mat3 uModelMatrix = scale(0.02)*translate(j+20,i+30);
                    glUniformMatrix3fv(mapProgram.uModelMatrix, 1, GL_FALSE, glm::value_ptr(uModelMatrix));
                    glDrawArrays(GL_TRIANGLES, 0, 6);

                    glBindTexture(GL_TEXTURE_2D, 0);

                    glBindVertexArray(0);

                    
                }
                else if(j == alice.getPosX() && i == alice.getPosY()) {
                    glBindVertexArray(vaoMap);
                 
                    mapProgram.m_Program.use();

                    glBindTexture(GL_TEXTURE_2D, textureHeroMap);

                    glUniform1i(mapProgram.uMapTexture, 0);
                    

                    glm::mat3 uModelMatrix = scale(0.02)*translate(j+20,i+30);
                    glUniformMatrix3fv(mapProgram.uModelMatrix, 1, GL_FALSE, glm::value_ptr(uModelMatrix));
                    glDrawArrays(GL_TRIANGLES, 0, 6);

                    glBindTexture(GL_TEXTURE_2D, 0);


                    glBindVertexArray(0);
                }
                else if(scene.grid[i][j] == ENTER || scene.grid[i][j] == EXIT) {

                    // PORTE HAUT

                    glBindVertexArray(vao);

                    wallProgram.m_Program.use();

                    glBindTexture(GL_TEXTURE_2D, texturePorteHaut);

                    glUniform1i(wallProgram.uWallTexture,0);

                    MVMatrix = glm::translate(glm::mat4(1), glm::vec3(j+1, 1, i));
                    MVMatrix = viewMatrix * MVMatrix;
                    glUniformMatrix4fv(wallProgram.uMVMatrix, 1, GL_FALSE, glm::value_ptr(MVMatrix));
                    glUniformMatrix4fv(wallProgram.uNormalMatrix, 1, GL_FALSE, glm::value_ptr(NormalMatrix));
                    glUniformMatrix4fv(wallProgram.uMVPMatrix, 1, GL_FALSE, glm::value_ptr(ProjMatrix * MVMatrix));

                    glDrawArrays(GL_TRIANGLES, 0, cube.getVertexCount());

                    glBindTexture(GL_TEXTURE_2D, 0);

                    glBindVertexArray(0);


                    // PORTE BAS

                    glBindVertexArray(vao);

                    wallProgram.m_Program.use();

                    glBindTexture(GL_TEXTURE_2D, texturePorteBas);

                    glUniform1i(wallProgram.uWallTexture,0);

                    MVMatrix = glm::translate(glm::mat4(1), glm::vec3(j+1, 0, i));
                    MVMatrix = viewMatrix * MVMatrix;
                    glUniformMatrix4fv(wallProgram.uMVMatrix, 1, GL_FALSE, glm::value_ptr(MVMatrix));
                    glUniformMatrix4fv(wallProgram.uNormalMatrix, 1, GL_FALSE, glm::value_ptr(NormalMatrix));
                    glUniformMatrix4fv(wallProgram.uMVPMatrix, 1, GL_FALSE, glm::value_ptr(ProjMatrix * MVMatrix));

                    glDrawArrays(GL_TRIANGLES, 0, cube.getVertexCount());

                    glBindTexture(GL_TEXTURE_2D, 0);

                    glBindVertexArray(0);



                    // MINI CARTE 
                    
                    glBindVertexArray(vaoMap);

                    mapProgram.m_Program.use();

                    glBindTexture(GL_TEXTURE_2D, texturePorteMap);

                    glUniform1i(mapProgram.uMapTexture, 0);
                    

                    glm::mat3 uModelMatrix = scale(0.02)*translate(j+20,i+30);
                    glUniformMatrix3fv(mapProgram.uModelMatrix, 1, GL_FALSE, glm::value_ptr(uModelMatrix));
                    glDrawArrays(GL_TRIANGLES, 0, 6);

                    glBindTexture(GL_TEXTURE_2D, 0);

                    glBindVertexArray(0);

                }
                else if(scene.grid[i][j] == CORRIDOR) {
                    glBindVertexArray(vaoMap);

                    mapProgram.m_Program.use();

                    glBindTexture(GL_TEXTURE_2D, textureFondMap);

                    glUniform1i(mapProgram.uMapTexture, 0);
                    

                    glm::mat3 uModelMatrix = scale(0.02)*translate(j+20,i+30);
                    glUniformMatrix3fv(mapProgram.uModelMatrix, 1, GL_FALSE, glm::value_ptr(uModelMatrix));
                    glDrawArrays(GL_TRIANGLES, 0, 6);

                    glBindTexture(GL_TEXTURE_2D, 0);

                    glBindVertexArray(0);

                }

                if(scene.isTreasure(j, i)) {
                    wallProgram.m_Program.use();
                    glBindTexture(GL_TEXTURE_2D, textureTresorMangeMoi);
                    glBindVertexArray(vao);

                    
                    //MVMatrix = glm::rotate(MVMatrix, 180.f, glm::vec3(1, 0, 0));
                    MVMatrix = glm::translate(glm::mat4(1), glm::vec3(j, 0, i));
                    MVMatrix = glm::scale(MVMatrix, glm::vec3(0.3, 0.3, 0.3));
                    MVMatrix = viewMatrix * MVMatrix;
                    glUniformMatrix4fv(wallProgram.uMVMatrix, 1, GL_FALSE, glm::value_ptr(MVMatrix));
                    glUniformMatrix4fv(wallProgram.uNormalMatrix, 1, GL_FALSE, glm::value_ptr(NormalMatrix));
                    glUniformMatrix4fv(wallProgram.uMVPMatrix, 1, GL_FALSE, glm::value_ptr(ProjMatrix * MVMatrix));
                    glDrawArrays(GL_TRIANGLES, 0, cube.getVertexCount());

                    glBindVertexArray(0);

                    glBindTexture(GL_TEXTURE_2D, 0);
                }
                if(scene.isMonster(j, i)) {
                    wallProgram.m_Program.use();
                    glBindTexture(GL_TEXTURE_2D, textureTest);
                    glUniform1i(wallProgram.uWallTexture,0);

                    glBindVertexArray(vao2);

                    MVMatrix = glm::translate(glm::mat4(1), glm::vec3(j, 0, i));
                    MVMatrix = viewMatrix * MVMatrix;
                    glUniformMatrix4fv(wallProgram.uMVMatrix, 1, GL_FALSE, glm::value_ptr(MVMatrix));
                    glUniformMatrix4fv(wallProgram.uNormalMatrix, 1, GL_FALSE, glm::value_ptr(NormalMatrix));
                    glUniformMatrix4fv(wallProgram.uMVPMatrix, 1, GL_FALSE, glm::value_ptr(ProjMatrix * MVMatrix));
                    glDrawArrays(GL_TRIANGLES, 0, sphere.getVertexCount());

                    glBindVertexArray(0);

                    glBindTexture(GL_TEXTURE_2D, 0);
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
