#include <glimac/SDLWindowManager.hpp>
#include <glimac/common.hpp>
#include <glimac/Sphere.hpp>
#include <glimac/Cube.hpp>
#include <glimac/Program.hpp>
#include <glimac/FilePath.hpp>
#include <glimac/Image.hpp>
#include <glimac/SceneOpenGL.hpp>
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
    unsigned int ptsVie = 100;

    for(int i = 0; i < scene.sizeX; i++) {
        for(int j = 0; j < scene.sizeY; j++) {
            // Si on a l'entrée, on dit que c'est le départ pour la caméra et le perso
            if(scene.grid[i][j] == 3) {
                departY = i +1;
                departX = j - 1;
            }
        }
    }
    
    cout << departX << " : " << departY << endl;
    
    FreeflyCamera camera(glm::vec3(departX, 0, departY));
    Hero alice(departX, departY, nom, attaque, defense, ptsVie, camera);


    std::unique_ptr<Image> earthImage = loadImage("/home/6im2/mroche/Documents/SyntheseImage/GLImac-Template/assets/textures/EarthMap.jpg");
    if(earthImage != NULL) std::cout << "La texture est bien chargée !" << std::endl;

    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, earthImage->getWidth(), earthImage->getHeight(), 0, GL_RGBA, GL_FLOAT, earthImage->getPixels());

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glBindTexture(GL_TEXTURE_2D, 0);

    int uTexture;

    FilePath applicationPath(argv[0]);
    Program program = loadProgram(applicationPath.dirPath() + "shaders/" + argv[1],
        applicationPath.dirPath() + "shaders/" + argv[2]);
    program.use();

    Cube cube(1);
    
    // Creation d'un seul VBO
    GLuint vbo;
    glGenBuffers(1, &vbo);
    // A partir de ce point, la variable vbo contient l'identifiant d'une VBO

    /*** Binding du VBO ***/

    // Binding d'un VBO sur la cible GL_ARRAY_BUFFER
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    // On peut à présent modifier le VBO en passant par la cible GL_ARRAY_BUFFER

    /*** Remplir le VBO ***/
    glBufferData(GL_ARRAY_BUFFER, cube.getVertexCount() * sizeof(ShapeVertex), cube.getDataPointer(), GL_STATIC_DRAW);

    /*** Débinder le VBO ***/
    glBindBuffer(GL_ARRAY_BUFFER, 0);

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
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
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
                        case SDLK_DOWN:    
                            // Reculer
                            alice.down();
                            //cout << "Recule" << endl;
                        break;
                        case SDLK_UP :
                            // Avancer
                            alice.up();
                            //cout << "Avance" << endl;
                        break;
                        case SDLK_LEFT :
                            // Tourner à gauche de 90°
                            alice.left();
                            //cout << "Gauche" << endl;
                        break;
                        case SDLK_RIGHT:
                            // Tourner à droite de 90°
                            alice.right();
                            //cout << "Droite" << endl;
                        break;
                        case SDLK_s:    
                            // Reculer
                            alice.down();
                            //cout << "Recule" << endl;
                        break;
                        case SDLK_z :
                            // Avancer
                            alice.up();
                            //cout << "Avance" << endl;
                        break;
                        case SDLK_q :
                            // Tourner à gauche de 90°
                            alice.left();
                            //cout << "Gauche" << endl;
                        break;
                        case SDLK_f:
                            // Tourner à droite de 90°
                            alice.right();
                           // cout << "Droite" << endl;
                        break;
                        case SDLK_o:
                            // Defense
                            //cout << "Defense" << endl;
                        break;
                        case SDLK_i :
                            // Attaque
                            //cout << "Attaque" << endl;
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

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        /*** Binding du vao ***/
        glBindVertexArray(vao);

        glm::mat4 viewMatrix = alice.getCamera().getViewMatrix();
        //MVMatrix = MVMatrix * viewMatrix;

        glBindTexture(GL_TEXTURE_2D, texture);
        glUniform1i(glGetUniformLocation(program.getGLId(), "uTexture"), 0);

        // Affichage de cubes sur la carte
        for(int i = 0; i < scene.sizeX; i++) {
            for(int j = 0; j < scene.sizeY; j++) {
                // Si on a un mur, afficher un cube sur la case
                if(scene.grid[i][j] == 1) {
                    glm::mat4 MVMatrix = glm::translate(glm::mat4(1), glm::vec3(i, 0, j));
                    MVMatrix = MVMatrix * viewMatrix;
                    /*glUniformMatrix4fv(uMVPMatrix, 1, GL_FALSE, glm::value_ptr(ProjMatrix*MVMatrix*viewMatrix));
                    glUniformMatrix4fv(uMVMatrix, 1, GL_FALSE, glm::value_ptr(MVMatrix*viewMatrix));
                    glUniformMatrix4fv(uNormalMatrix, 1, GL_FALSE, glm::value_ptr(NormalMatrix));*/
                    glUniformMatrix4fv(uMVMatrix, 1, GL_FALSE, glm::value_ptr(MVMatrix));
                    glUniformMatrix4fv(uNormalMatrix, 1, GL_FALSE, glm::value_ptr(NormalMatrix));
                    glUniformMatrix4fv(uMVPMatrix, 1, GL_FALSE, glm::value_ptr(ProjMatrix * MVMatrix));

                    glDrawArrays(GL_TRIANGLES, 0, cube.getVertexCount());
                }
            }
        }

        glBindTexture(GL_TEXTURE_2D, 0);

        /*** Débinding du vao ***/
        glBindVertexArray(0);





        // Update the display
        windowManager.swapBuffers();
    }

    return EXIT_SUCCESS;
}
