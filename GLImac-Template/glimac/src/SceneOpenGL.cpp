#include "glimac/SceneOpenGL.hpp"


SceneOpenGL::SceneOpenGL() {
    heroHasWon = false;
    level = 1;
    startGame = true;
    gameOver = false;
    paused = true;
}

SceneOpenGL::~SceneOpenGL() {

}


int** SceneOpenGL::getGrid() const {
    return grid;
}

void SceneOpenGL::setGrid(int** &value) {
    grid = value;
}

bool SceneOpenGL::readLevel(const char * filepath) {
    ifstream file(filepath);  //Ouverture d'un fichier en lecture
    string line;

    unsigned int nbTreasures;
    unsigned int nbMonsters;

    if(file)
    {
        getline(file, line);
        // nom du donjon
        if(line[0] == '#') {
            cout << "Jeu " << line.erase(0,1) << endl;
        }

        // nom du fichier ppm
        getline(file, line);
        bool test = readDungeon(line.c_str());

        // nombre trésors
        getline(file, line);
        nbTreasures = atoi(line.c_str());

        for(unsigned int i = 0; i < nbTreasures; i++) {
            getline(file, line);

            // Get id
            int pos = line.find(':');
            string id_string = line.substr(0, pos);
            line = line.substr(pos+1);
            unsigned int id = atoi(id_string.c_str());

            // Pos X
            pos = line.find(':');
            string posX_string = line.substr(0, pos);
            line = line.substr(pos+1);
            unsigned int posX = atoi(posX_string.c_str());

            // Pos Y
            pos = line.find(':');
            string posY_string = line.substr(0, pos);
            line = line.substr(pos+1);
            unsigned int posY = atoi(posY_string.c_str());

            // Name
            pos = line.find(':');
            string name = line.substr(0, pos);
            line = line.substr(pos+1);

            // type
            pos = line.find(':');
            string type_string = line.substr(0, pos);
            line = line.substr(pos+1);
            int type = atoi(type_string.c_str());

            // Feature
            pos = line.find(':');
            string feature_string = line.substr(0, pos);
            line = line.substr(pos+1);
            int feature = atoi(feature_string.c_str());

            // 3D
            pos = line.find(':');
            string object = line.substr(0, pos);
            line = line.substr(pos+1);

            treasures.push_back(Treasure(id, posX, posY, name, type, feature, object));
        }

        // nombre trésors
        getline(file, line);
        nbMonsters = atoi(line.c_str());

        for(unsigned int i = 0; i < nbMonsters; i++) {
            getline(file, line);

            // Get id
            int pos = line.find(':');
            string id_string = line.substr(0, pos);
            line = line.substr(pos+1);
            unsigned int id = atoi(id_string.c_str());

            // Pos X
            pos = line.find(':');
            string posX_string = line.substr(0, pos);
            line = line.substr(pos+1);
            unsigned int posX = atoi(posX_string.c_str());

            // Pos Y
            pos = line.find(':');
            string posY_string = line.substr(0, pos);
            line = line.substr(pos+1);
            unsigned int posY = atoi(posY_string.c_str());

            // Name
            pos = line.find(':');
            string name = line.substr(0, pos);
            line = line.substr(pos+1);

            // type
            pos = line.find(':');
            string type_string = line.substr(0, pos);
            line = line.substr(pos+1);
            int type = atoi(type_string.c_str());

            // Attack
            pos = line.find(':');
            string attack_string = line.substr(0, pos);
            line = line.substr(pos+1);
            int attack = atoi(attack_string.c_str());

            // Defense
            pos = line.find(':');
            string defense_string = line.substr(0, pos);
            line = line.substr(pos+1);
            int defense = atoi(defense_string.c_str());

            // Life pts
            pos = line.find(':');
            string life_string = line.substr(0, pos);
            line = line.substr(pos+1);
            unsigned int life = atoi(life_string.c_str());

            // 3D
            pos = line.find(':');
            string object = line.substr(0, pos);
            line = line.substr(pos+1);

            monsters.push_back(new Monster(id, posX, posY, name, type, attack, defense, life, object));
            monsters[monsters.size() - 1]->setOrientation(0);
        }

        file.close();
        return true;
    }
    else
    {
        cout << "Impossible de trouver le fichier " << filepath << endl;
        return false;
    }

}

bool SceneOpenGL::readDungeon(const char * imagepath){
    char fileName[200];
    strcpy(fileName, "../GLImac-Template/assets/files/");
    strcat(fileName, imagepath);
    ifstream file (fileName);  //Ouverture d'un fichier en lecture
    string line;

    if(file)
    {
        // Format ppm
        getline(file, line);

        // Commentaire
        getline(file, line);

        // nb x et y
        getline(file, line);
        int pos = line.find(' ');
        string x_string = line.substr(0, pos);
        int x = atoi(x_string.c_str());
        line = line.substr(pos+1);
        string y_string = line.substr(0, pos);
        int y = atoi(y_string.c_str());

        sizeX = x;
        sizeY = y;

        grid = new int*[sizeY];
        for(int i = 0; i < sizeY; ++i) {
            grid[i] = new int[sizeX];
        }

        // 255
        getline(file, line);

        string r, g, b;
        int value;

        // map

        for(int i = 0; i < sizeY; ++i) {
            for(int j = 0; j < sizeX; ++j) {
            
                getline(file, r);
                getline(file, g);
                getline(file, b);
                if(r == "0" && g == "0" && b == "0") value = WALL;
                else if(r == "255" && g == "255" && b == "255") value = CORRIDOR;
                else if(r == "255" && g == "0" && b == "0") value = ENTER;
                else if(r == "0" && g == "255" && b == "0") value = EXIT;
                else value = CORRIDOR;
                grid[i][j] = value;
            }
        }
        return true;
    }
    else {
        cout << "Impossible de trouver le fichier " << fileName << endl;
        return false;
    }
    file.close();
}

vector<Treasure> SceneOpenGL::getTreasures(){
    return treasures;
}

vector<Monster*> SceneOpenGL::getMonsters(){
    return monsters;
}

bool SceneOpenGL::hasObstacle(int posX, int posY){
    for(unsigned int i = 0; i < monsters.size(); i++){
        if(monsters[i]->getPosX() == posX && monsters[i]->getPosY() == posY) return true;
    }
    return false;
}


bool SceneOpenGL::canMove(int orientation, int posX, int posY, int action) {
    switch(orientation) {
        case 0:
            // S'il veut aller en avant
            if(action > 0) {
                if(posY-1 >= 0) {
                    if(grid[posY-1][posX] != WALL && !hasObstacle(posX, posY-1) && grid[posY-1][posX] != ENTER && grid[posY-1][posX] != EXIT) {
                        return true;
                    }
                    else return false;
                }
                else return false;
            }
            // S'il veut aller en arrière
            else if(action < 0) {
                if(posY+1 < sizeY) {
                    if(grid[posY+1][posX] != WALL && !hasObstacle(posX, posY+1) && grid[posY+1][posX] != ENTER && grid[posY+1][posX] != EXIT) {
                        return true;
                    }
                    else return false;
                }
                else return false;
            }
            else return false;
            break;
        case 90:
            // S'il veut aller en avant
            if(action > 0) {
                if(posX+1 < sizeX) {
                    if(grid[posY][posX+1] != WALL && !hasObstacle(posX+1, posY) && grid[posY][posX+1] != ENTER && grid[posY][posX+1] != EXIT) {
                        return true;
                    }
                    else return false;
                }
                else return false;
            }
            // S'il veut aller en arrière
            else if(action < 0) {
                if(posX-1 >= 0) {
                    if(grid[posY][posX-1] != WALL && !hasObstacle(posX-1, posY) && grid[posY][posX-1] != ENTER && grid[posY][posX-1] != EXIT) {
                        return true;
                    }
                    else return false;
                }
                else return false;
            }
            else return false;
            break;
        case 180:
            // S'il veut aller en avant
            if(action > 0) {
                if(posY+1 < sizeY) {
                    if(grid[posY+1][posX] != WALL && !hasObstacle(posX, posY+1) && grid[posY+1][posX] != ENTER && grid[posY+1][posX] != EXIT) {
                        return true;
                    }
                    else return false;
                }
                else return false;
            }
            // S'il veut aller en arrière
            else if(action < 0) {
                if(posY-1 >= 0) {
                    if(grid[posY-1][posX] != WALL && !hasObstacle(posX, posY-1) && grid[posY-1][posX] != ENTER && grid[posY-1][posX] != EXIT) {
                        return true;
                    }
                    else return false;
                }
                else return false;
            }
            else return false;
            break;
        case 270:
            // S'il veut aller en avant
            if(action > 0) {
                if(posX-1 >= 0) {
                    if(grid[posY][posX-1] != WALL && !hasObstacle(posX-1, posY) && grid[posY][posX-1] != ENTER && grid[posY][posX-1] != EXIT) {
                        return true;
                    }
                    else return false;
                }
                else return false;
            }
            // S'il veut aller en arrière
            else if(action < 0) {
                if(posX+1 < sizeX) {
                    if(grid[posY][posX+1] != WALL && !hasObstacle(posX+1, posY) && grid[posY][posX+1] != ENTER && grid[posY][posX+1] != EXIT) {
                        return true;
                    }
                    else return false;
                }
                else return false;
            }
            else return false;
            break;
        default:
            return false;
            break;
    }
    //return true;
}


void SceneOpenGL::choosePath(Monster &m){
    srand(time(NULL));
    int randomOrientation;
    int tmpOrientation = 0;

    randomOrientation = rand() % 2;
    // regarder d'abord si le mur de droite est libre
    if(randomOrientation == 1){
        tmpOrientation = m.getOrientation() + 90;
        if(tmpOrientation >= 360) tmpOrientation = 0;
        if(canMove(tmpOrientation, m.getPosX(), m.getPosY(), 1)){
            m.setOrientation(tmpOrientation);

        }else{
            tmpOrientation = m.getOrientation() - 90;
            if(tmpOrientation < 0) tmpOrientation = 270;
            
            if(canMove(tmpOrientation, m.getPosX(), m.getPosY(), 1)){
                m.setOrientation(tmpOrientation);
            // sinon demi tour
            }else{
                m.setOrientation(m.getOrientation() + 180);
                if(m.getOrientation() == 360) m.setOrientation(0);
                if(m.getOrientation() == 450) m.setOrientation(90);
            }
        }
    }
    // regarder d'abord si le mur de gauche est libre
    else{ 
        tmpOrientation = m.getOrientation() - 90;
        if(tmpOrientation < 0) tmpOrientation = 270;
        
        if(canMove(tmpOrientation, m.getPosX(), m.getPosY(), 1)){
            m.setOrientation(tmpOrientation);
        }
        // sinon regarder si le mur de droite est libre
        else{
            tmpOrientation = m.getOrientation() + 90;
            if(tmpOrientation >= 360) tmpOrientation = 0;

            if(canMove(tmpOrientation, m.getPosX(), m.getPosY(), 1)){
                m.setOrientation(tmpOrientation);
            }

            else{
                m.setOrientation(m.getOrientation() + 180);
                if(m.getOrientation() == 360) m.setOrientation(0);
                if(m.getOrientation() == 450) m.setOrientation(90);
            }
        }
    }
}

bool SceneOpenGL::isTreasure(int posX, int posY){
    bool exist = false;
    for(unsigned int i = 0; i < treasures.size(); i ++) {
        if(treasures[i].getPosX() == posX && treasures[i].getPosY() == posY) {
            exist = true;
        }
    }
    return exist; 
}

bool SceneOpenGL::isMonster(int posX, int posY){
    bool exist = false;
    for(unsigned int i = 0; i < monsters.size(); i ++) {
        if(monsters[i]->getPosX() == posX && monsters[i]->getPosY() == posY) {
            exist = true;
        }
    }
    return exist; 
}

Treasure& SceneOpenGL::getTreasure(int posX, int posY) {
    for(unsigned int i = 0; i < treasures.size(); i ++) {
        if(treasures[i].getPosX() == posX && treasures[i].getPosY() == posY) {
            return treasures[i];
        }
    }
}

void SceneOpenGL::deleteTreasure(int posX, int posY) {
    for(unsigned int i = 0; i < treasures.size(); i ++) {
        if(treasures[i].getPosX() == posX && treasures[i].getPosY() == posY) {
            treasures.erase(treasures.begin() + i);
        }
    }
}

void SceneOpenGL::deleteMonster(unsigned int id) {
    for(unsigned int i = 0; i < monsters.size(); i ++) {
        if(i == id) {
            monsters.erase(monsters.begin() + i);
        }
    }
}


Monster& SceneOpenGL::getMonster(int posX, int posY) {
    for(unsigned int i = 0; i < monsters.size(); i ++) {
        if(monsters[i]->getPosX() == posX && monsters[i]->getPosY() == posY) {
            return *monsters[i];
        }
    }
}


bool SceneOpenGL::monsterSeeHero(Monster m, Hero a){
    unsigned int i, tmpInf = 0, tmpSup = 0;

    // meme case
    if(m.getPosX() == a.getPosX() && m.getPosY() == a.getPosY()) return true;
    // meme colonne
    if(m.getPosX() == a.getPosX()){
        if(m.getPosY() < a.getPosY() && m.getOrientation() == 180){
            tmpInf = m.getPosY();
            tmpSup = a.getPosY();
        }
        else if(m.getPosY() > a.getPosY() && m.getOrientation() == 0){
            tmpInf = a.getPosY();
            tmpSup = m.getPosY();
        }else{
            return false; // faire autre chose = meme case tous les deux
        }
        for(i = tmpInf; i < tmpSup; i++){
            if(grid[i][m.getPosX()] != CORRIDOR ) return false;
        }
        return true;       
    }
    // meme ligne
    if(m.getPosY() == a.getPosY()){
        if(m.getPosX() < a.getPosX() && m.getOrientation() == 90){
            tmpInf = m.getPosX();
            tmpSup = a.getPosX();
        }
        else if(m.getPosX() > a.getPosX() && m.getOrientation() == 270){
            tmpInf = a.getPosX();
            tmpSup = m.getPosX();
        }else{
            return false; // faire autre chose = meme case tous les deux
        }
        for(i = tmpInf; i < tmpSup; i++){
            if(grid[m.getPosY()][i] != CORRIDOR ) return false;
        }
        return true;       
    }

    return false;
}

bool SceneOpenGL::monsterNextToHero(Monster m, Hero a){
    if(((m.getPosX()+1 == a.getPosX()) && (m.getPosY() == a.getPosY())) 
        || (m.getPosX()-1 == a.getPosX()) && (m.getPosY() == a.getPosY())
        || (m.getPosY()+1 == a.getPosY()) && (m.getPosX() == a.getPosX())
        || (m.getPosY()-1 == a.getPosY()) && (m.getPosX() == a.getPosX())) {
        return true;
    }
    else {
        return false;
    }
}

bool SceneOpenGL::doorExitNextToHero(Hero a) {
    for(int i = 0; i < sizeY; ++i) {
        for(int j = 0; j < sizeX; ++j) {
            if(grid[i][j] == EXIT){
                if(a.getOrientation() == 0 && a.getPosX() == j && a.getPosY() == i+1){
                    return true;
                }
            }
        }
    }
    return false;

}

// Héro attaque le monstre
unsigned int SceneOpenGL::attack(Hero &h, Monster &m) {
    int life = m.getLife() - (h.getAttack() - m.getDefense());
    if(life > 0) return (unsigned int) life;
    else return 0;
}

// Monstre attaque le héro
unsigned int SceneOpenGL::isAttacked(Monster &m, Hero &h) {
    int life = h.getLife() - (m.getAttack() - h.getDefense());
    if(life > 0) return (unsigned int) life;
    else return 0;
}

GLuint SceneOpenGL::createVboCube(Cube &cube) {
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

    return vbo;
}

GLuint SceneOpenGL::createVboSphere(Sphere &sphere) {
    // Creation d'un seul VBO
    GLuint vbo;
    glGenBuffers(1, &vbo);
    // A partir de ce point, la variable vbo contient l'identifiant d'une VBO

    /*** Binding du VBO ***/

    // Binding d'un VBO sur la cible GL_ARRAY_BUFFER
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    // On peut à présent modifier le VBO en passant par la cible GL_ARRAY_BUFFER

    /*** Remplir le VBO ***/
    glBufferData(GL_ARRAY_BUFFER, sphere.getVertexCount() * sizeof(ShapeVertex), sphere.getDataPointer(), GL_STATIC_DRAW);

    /*** Débinder le VBO ***/
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    return vbo;
}

GLuint SceneOpenGL::createVboFace() {
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
    return vbo;
}

GLuint SceneOpenGL::createVao2D(GLuint vbo) {
    /*** Création du VAO ***/
    GLuint vao;
    glGenVertexArrays(1, &vao);

    /*** Binding du vao ***/
    glBindVertexArray(vao);

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
    return vao;
}

GLuint SceneOpenGL::createVao3D(GLuint vbo) {
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

    return vao;
}

GLuint SceneOpenGL::createTexture(const char* imagePath) {
    std::unique_ptr<Image> image = loadImage(imagePath);
    if(image == NULL) std::cout << "La texture " << imagePath << " n'a pas pu etre chargee !" << std::endl;
    
    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image->getWidth(), image->getHeight(), 0, GL_RGBA, GL_FLOAT, image->getPixels());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);

    return texture;
}

void SceneOpenGL::drawCube(Program3D &prog, Cube &cube, glm::mat4 viewMatrix, glm::mat4 ProjMatrix, glm::mat4 MVMatrix, glm::mat4 NormalMatrix, GLuint vao, GLuint texture, float x, float y, float z) {
    glBindVertexArray(vao);

    glBindTexture(GL_TEXTURE_2D, texture);

    glUniform1i(prog.uWallTexture,0);

    MVMatrix = glm::translate(glm::mat4(1), glm::vec3(x, y, z));
    MVMatrix = viewMatrix * MVMatrix;
    glUniformMatrix4fv(prog.uMVMatrix, 1, GL_FALSE, glm::value_ptr(MVMatrix));
    glUniformMatrix4fv(prog.uNormalMatrix, 1, GL_FALSE, glm::value_ptr(NormalMatrix));
    glUniformMatrix4fv(prog.uMVPMatrix, 1, GL_FALSE, glm::value_ptr(ProjMatrix * MVMatrix));

    glDrawArrays(GL_TRIANGLES, 0, cube.getVertexCount());

    glBindTexture(GL_TEXTURE_2D, 0);

    glBindVertexArray(0);
}

void SceneOpenGL::drawTreasure(Program3D &prog, Sphere &sphere, glm::mat4 viewMatrix, glm::mat4 ProjMatrix, glm::mat4 MVMatrix, glm::mat4 NormalMatrix, GLuint vao, GLuint texture, float x, float y, float z, float r) {
    glBindVertexArray(vao);

    glBindTexture(GL_TEXTURE_2D, texture);

    glUniform1i(prog.uWallTexture,0);

    MVMatrix = glm::translate(glm::mat4(1), glm::vec3(x, y, z));
    MVMatrix = glm::scale(MVMatrix, glm::vec3(0.3, 0.3, 0.3));
    MVMatrix = glm::rotate(MVMatrix, r, glm::vec3(0, 1, 0));
    MVMatrix = viewMatrix * MVMatrix;
    glUniformMatrix4fv(prog.uMVMatrix, 1, GL_FALSE, glm::value_ptr(MVMatrix));
    glUniformMatrix4fv(prog.uNormalMatrix, 1, GL_FALSE, glm::value_ptr(NormalMatrix));
    glUniformMatrix4fv(prog.uMVPMatrix, 1, GL_FALSE, glm::value_ptr(ProjMatrix * MVMatrix));

    glDrawArrays(GL_TRIANGLES, 0, sphere.getVertexCount());

    glBindTexture(GL_TEXTURE_2D, 0);

    glBindVertexArray(0);
}

void SceneOpenGL::drawInfo(Program2D &prog, GLuint vao, GLuint texture, float x, float y, float s) {
    glBindVertexArray(vao);

    glBindTexture(GL_TEXTURE_2D, texture);

    glUniform1i(prog.uMapTexture, 0);

    glm::mat3 uModelMatrix = scale(s)*translate(x,y);
    glUniformMatrix3fv(prog.uModelMatrix, 1, GL_FALSE, glm::value_ptr(uModelMatrix));
    glDrawArrays(GL_TRIANGLES, 0, 6);

    glBindTexture(GL_TEXTURE_2D, 0);

    glBindVertexArray(0);
}

void SceneOpenGL::drawMonster(Program3D &prog, Cube &cube, glm::mat4 viewMatrix, glm::mat4 ProjMatrix, glm::mat4 MVMatrix, glm::mat4 NormalMatrix, GLuint vao, GLuint texture, float x, float y, float z) {
    glBindVertexArray(vao);

    glBindTexture(GL_TEXTURE_2D, texture);

    glUniform1i(prog.uWallTexture,0);

    MVMatrix = glm::translate(glm::mat4(1), glm::vec3(x, y, z));
    MVMatrix = glm::scale(MVMatrix, glm::vec3(0.5, 0.5, 0.5));
    MVMatrix = viewMatrix * MVMatrix;
    glUniformMatrix4fv(prog.uMVMatrix, 1, GL_FALSE, glm::value_ptr(MVMatrix));
    glUniformMatrix4fv(prog.uNormalMatrix, 1, GL_FALSE, glm::value_ptr(NormalMatrix));
    glUniformMatrix4fv(prog.uMVPMatrix, 1, GL_FALSE, glm::value_ptr(ProjMatrix * MVMatrix));

    glDrawArrays(GL_TRIANGLES, 0, cube.getVertexCount());

    glBindTexture(GL_TEXTURE_2D, 0);

    glBindVertexArray(0);
}

void SceneOpenGL::drawMap(Program2D &prog, GLuint vao, GLuint texture, float x, float y) {
    glBindVertexArray(vao);

    glBindTexture(GL_TEXTURE_2D, texture);

    glUniform1i(prog.uMapTexture, 0);

    glm::mat3 uModelMatrix = scale(0.02)*translate(x+20,y+30);
    glUniformMatrix3fv(prog.uModelMatrix, 1, GL_FALSE, glm::value_ptr(uModelMatrix));
    glDrawArrays(GL_TRIANGLES, 0, 6);

    glBindTexture(GL_TEXTURE_2D, 0);

    glBindVertexArray(0);

}

void SceneOpenGL::drawStory(Program2D &prog, GLuint vao, GLuint texture) {
    glBindVertexArray(vao);

    glBindTexture(GL_TEXTURE_2D, texture);

    glUniform1i(prog.uMapTexture, 0);

    glm::mat3 uModelMatrix = scale(2)*translate(0, 0);
    glUniformMatrix3fv(prog.uModelMatrix, 1, GL_FALSE, glm::value_ptr(uModelMatrix));
    glDrawArrays(GL_TRIANGLES, 0, 6);

    glBindTexture(GL_TEXTURE_2D, 0);

    glBindVertexArray(0);
}

void SceneOpenGL::levelInit(int newLevel, Hero *a) {
    //monsters.clear();
    clearMonsters();
    //treasures.clear();
    clearTreasures();
    sizeX = 0;
    sizeY = 0;
    grid = NULL;

    int defense;
    int attaque;
    unsigned int ptsVie;
    unsigned int departX = 0;
    unsigned int departY = 0;
    string nom;
    FreeflyCamera camera;

    switch(newLevel) {
        case 1:
            if(!readLevel("../GLImac-Template/assets/files/level.txt")) {
                cout << "Impossible de lancer le niveau !" << endl;
            }
            nom = "Alice";
            defense = 20;
            attaque = 20;
            ptsVie = 100;

            departX = findEnterX();
            departY = findEnterY();

            camera = FreeflyCamera(glm::vec3(departX, 0, departY));
            a->setHero(departX, departY, nom, attaque, defense, ptsVie, camera, false);
            findOrientationHero(a, departX, departY);
            a->getCamera().rotateLeft(a->getOrientation());

            break;

        /*case 2:
            if(!readLevel("../GLImac-Template/assets/files/level2.txt")) {
                cout << "Impossible de lancer le niveau !" << endl;
            }
            cout << "J'ai lu le level 2 !" << endl;
            departX = findEnterX();
            departY = findEnterY();
            ptsVie = 100;

            camera = FreeflyCamera(glm::vec3(departX, 0, departY));

            a->setHero(departX, departY, a->getName(), a->getAttack(), a->getDefense(), ptsVie, camera, false);
            findOrientationHero(a, departX, departY);
            a->getCamera().rotateLeft(a->getOrientation());

            cout << "J'ai modifié les infos d'Alice !" << endl;

            break;

        case 3:
            if(!readLevel("../GLImac-Template/assets/files/level3.txt")) {
                cout << "Impossible de lancer le niveau !" << endl;
            }
            departX = findEnterX();
            departY = findEnterY();
            ptsVie = 100;

            camera = FreeflyCamera(glm::vec3(departX, 0, departY));

            a->setHero(departX, departY, a->getName(), a->getAttack(), a->getDefense(), ptsVie, camera, false);
            findOrientationHero(a, departX, departY);
            a->getCamera().rotateLeft(a->getOrientation());
            break;*/

        default:
            break;
    }
}

unsigned int SceneOpenGL::findEnterX() {
    int enter = 0;
    for(int i = 0; i < sizeY; i++) {
        for(int j = 0; j < sizeX; j++) {
            if(grid[i][j] == ENTER) {
                enter = j;
            }
        }
    }
    return enter;
}

unsigned int SceneOpenGL::findEnterY() {
    int enter = 0;
    for(int i = 0; i < sizeY; i++) {
        for(int j = 0; j < sizeX; j++) {
            if(grid[i][j] == ENTER) {
                enter = i;
            }
        }
    }
    return enter;
}

void SceneOpenGL::findOrientationHero(Hero *a, unsigned int departX, unsigned int departY) {
    for(int i = 0; i < sizeY; i++) {
        for(int j = 0; j < sizeX; j++) {
            if(j == departX && i == departY) {
                if(i-1 >= 0) {
                    if(getGrid()[i-1][j] != WALL) {
                        a->setOrientation(0);
                    }  
                }
                else if(i+1 < sizeY) {
                    if(getGrid()[i+1][j] != WALL) {
                        a->setOrientation(180);
                    }
                }
                else if(j+1 < sizeX) {
                    if(getGrid()[i][j+1] != WALL) {
                        a->setOrientation(90);
                    }
                }
                else if(j-1 >= 0) {
                    if(getGrid()[i][j-1] != WALL) {
                        a->setOrientation(270);
                    }
                }
            }
        }
    }
}

void SceneOpenGL::clearMonsters() {
    for (int i = 0; i < monsters.size(); i++) {
        monsters.erase(monsters.begin());

    }
}

void SceneOpenGL::clearTreasures() {
    for (int i = 0; i < treasures.size(); i++) {
        treasures.erase(treasures.begin());

    }
}