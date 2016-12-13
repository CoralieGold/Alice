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

bool SceneOpenGL::readLevel() {
    ifstream file ("../GLImac-Template/assets/files/level.txt");  //Ouverture d'un fichier en lecture
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
        bool test = readDungeon(line);

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

bool SceneOpenGL::readDungeon(string image){
    ifstream file ("../GLImac-Template/assets/files/level.ppm");  //Ouverture d'un fichier en lecture
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
                if(r == "0" && g == "0" && b == "0") value = 1; // mur
                else if(r == "255" && g == "255" && b == "255") value = 2; // couloir
                else if(r == "255" && g == "0" && b == "0") value = 3; // entree
                else if(r == "0" && g == "255" && b == "0") value = 4; // sortie
                else if(r == "170" && g == "119" && b == "34") value = 5; // porte
                else if(r == "0" && g == "0" && b == "255") value = 6; // eau
                else value = 1;
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


bool SceneOpenGL::canMove(int orientation, int posX, int posY, int action) {
    switch(orientation) {
        case 0:
            // S'il veut aller en avant
            if(action > 0) {
                if(posY-1 >= 0) {
                    if(grid[posY-1][posX] != 1) {
                        return true;
                    }
                    else return false;
                }
                else return false;
            }
            // S'il veut aller en arrière
            else if(action < 0) {
                if(posY+1 < sizeY) {
                    if(grid[posY+1][posX] != 1) {
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
                    if(grid[posY][posX+1] != 1) {
                        return true;
                    }
                    else return false;
                }
                else return false;
            }
            // S'il veut aller en arrière
            else if(action < 0) {
                if(posX-1 >= 0) {
                    if(grid[posY][posX-1] != 1) {
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
                    if(grid[posY+1][posX] != 1) {
                        return true;
                    }
                    else return false;
                }
                else return false;
            }
            // S'il veut aller en arrière
            else if(action < 0) {
                if(posY-1 >= 0) {
                    if(grid[posY-1][posX] != 1) {
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
                    if(grid[posY][posX-1] != 1) {
                        return true;
                    }
                    else return false;
                }
                else return false;
            }
            // S'il veut aller en arrière
            else if(action < 0) {
                if(posX+1 < sizeX) {
                    if(grid[posY][posX+1] != 1) {
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

/*Monster SceneOpenGL::getMonster(int posX, int posY) {

}*/


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
            if(grid[i][m.getPosX()] != 2 ) return false;
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
            if(grid[m.getPosY()][i] != 2 ) return false;
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