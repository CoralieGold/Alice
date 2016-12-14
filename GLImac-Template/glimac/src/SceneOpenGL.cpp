    #include "glimac/SceneOpenGL.hpp"


SceneOpenGL::SceneOpenGL() {

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
        //cout << nbTreasures << endl;

        for(unsigned int i = 0; i < nbTreasures; i++) {
            getline(file, line);

            // Get id
            int pos = line.find(':');
            string id_string = line.substr(0, pos);
            line = line.substr(pos+1);
            unsigned int id = atoi(id_string.c_str());
            //cout << "id : " << id << endl;

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
            //cout << "position tresor : " << posX << " , " << posY << endl;

            // Name
            pos = line.find(':');
            string name = line.substr(0, pos);
            line = line.substr(pos+1);
            //cout << "name : " << name << endl;

                    // type
                    pos = line.find(':');
                    string type_string = line.substr(0, pos);
                    line = line.substr(pos+1);
                    int type = atoi(type_string.c_str());
                    //cout << "type : " << type << endl;

                    // Feature
                    pos = line.find(':');
                    string feature_string = line.substr(0, pos);
                    line = line.substr(pos+1);
                    int feature = atoi(feature_string.c_str());
                    //cout << "feature : " << type << endl;

                    // 3D
                    pos = line.find(':');
                    string object = line.substr(0, pos);
                    line = line.substr(pos+1);
                    //cout << "object 3D : " << object << endl;

                    treasures.push_back(Treasure(id, posX, posY, name, type, feature, object));
                    //grid[posY][posX] = 8;
                    //cout << treasures[0].getId() << " pos : " << treasures[0].getPosX() << " " << treasures[0].getPosY() << endl; 
                }

                // nombre trésors
                getline(file, line);
                nbMonsters = atoi(line.c_str());
                //cout << nbMonsters << endl;

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
                    string type = line.substr(0, pos);
                    line = line.substr(pos+1);

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
                    //grid[posY][posX] = 7;
                }

                cout << "Carte chargee : " << endl;

                for(int i = 0; i < sizeY; i++) {
                    for(int j = 0; j < sizeX; j++) {
                        cout << grid[i][j];
                    }
                    cout << "" << endl;
                }

                file.close();
                return true;
            }
            else
            {
                cout << "Impossible de trouver le fichier level.txt" << endl;
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

        grid = new int*[sizeX];
        for(int i = 0; i < sizeX; ++i) {
            grid[i] = new int[sizeY];
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
                //cout << r << " " << g << " " << b << endl;
                if(r == "0" && g == "0" && b == "0") value = WALL; // mur
                else if(r == "255" && g == "255" && b == "255") value = CORRIDOR; // couloir
                else if(r == "255" && g == "0" && b == "0") value = ENTER; // entree
                else if(r == "0" && g == "255" && b == "0") value = EXIT; // sortie
                else if(r == "170" && g == "119" && b == "34") value = DOOR; // porte
                else value = WALL;
                //cout << value << endl;
                grid[i][j] = value;
            }
        }

        //rotateLevel();

        return true;
    }
    else {
        cout << "Impossible de trouver le fichier level.ppm" << endl;
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
        //std::cout << treasures[i].getPosX() << ":" << treasures[i].getPosY() << std::endl;
        if(treasures[i].getPosX() == posX && treasures[i].getPosY() == posY) {
            exist = true;
            //std::cout << treasures[i].getPosX() << ": ok " << treasures[i].getPosY() << std::endl;
        }
    }
    return exist; 
}

bool SceneOpenGL::isMonster(int posX, int posY){
    bool exist = false;
    for(unsigned int i = 0; i < monsters.size(); i ++) {
        //std::cout << treasures[i].getPosX() << ":" << treasures[i].getPosY() << std::endl;
        if(monsters[i]->getPosX() == posX && monsters[i]->getPosY() == posY) {
            exist = true;
            //std::cout << treasures[i].getPosX() << ": ok " << treasures[i].getPosY() << std::endl;
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


/*Monster SceneOpenGL::getMonster(int posX, int posY) {

}*/


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
    if(m.getPosX()+1 == a.getPosX() || m.getPosX()-1 == a.getPosX() || m.getPosY()+1 == a.getPosY() || m.getPosY()-1 == a.getPosY()) {
        return true;
    }
    else {
        return false;
    }
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

GLuint SceneOpenGL::createVboObject(Object &object) {
    // Creation d'un seul VBO
    GLuint vbo;
    glGenBuffers(1, &vbo);
    // A partir de ce point, la variable vbo contient l'identifiant d'une VBO

    /*** Binding du VBO ***/

    // Binding d'un VBO sur la cible GL_ARRAY_BUFFER
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    // On peut à présent modifier le VBO en passant par la cible GL_ARRAY_BUFFER

    /*** Remplir le VBO ***/
    // for(unsigned int i = 0; i < object.vertex.size(); i ++) {
    //     cout << object.vertex[i].position.x << " " << object.vertex[i].position.y << " " 
    //          << object.vertex[i].position.z << endl;
    // }
    glBufferData(GL_ARRAY_BUFFER, object.vertex.size() * sizeof(ShapeVertex), &object.vertex[0], GL_STATIC_DRAW);

    /*** Débinder le VBO ***/
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    return vbo;
}

void SceneOpenGL::createVao(GLuint vbo) {
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
}

GLuint SceneOpenGL::createTexture(const char* imagePath) {
    std::unique_ptr<Image> image = loadImage(imagePath);
    if(image != NULL) std::cout << "La texture des murs est bien chargée !" << std::endl;
    
    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image->getWidth(), image->getHeight(), 0, GL_RGBA, GL_FLOAT, image->getPixels());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);

    return texture;
}