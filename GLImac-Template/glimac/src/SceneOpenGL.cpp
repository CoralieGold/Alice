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
            //cout << "position : " << posX << " , " << posY << endl;

            // Name
            pos = line.find(':');
            string name = line.substr(0, pos);
            line = line.substr(pos+1);
            //cout << "name : " << name << endl;

                    // type
                    pos = line.find(':');
                    string type = line.substr(0, pos);
                    line = line.substr(pos+1);
                    //cout << "type : " << type << endl;

                    // Feature
                    pos = line.find(':');
                    string feature = line.substr(0, pos);
                    line = line.substr(pos+1);
                    //cout << "feature : " << type << endl;

                    // 3D
                    pos = line.find(':');
                    string object = line.substr(0, pos);
                    line = line.substr(pos+1);
                    //cout << "object 3D : " << object << endl;

                    treasures.push_back(Treasure(id, posX, posY, name, type, feature, object));
                    grid[posX][posY] = 7;
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

                    monsters.push_back(Monster(id, posX, posY, name, type, attack, defense, life, object));
                    grid[posX][posY] = 8;
                }

                cout << "Carte chargee : " << endl;

                for(int i = 0; i < 10; i++) {
                    for(int j = 0; j < 10; j++) {
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

        grid = new int*[x];
        for(int i = 0; i < x; ++i) {
            grid[i] = new int[y];
        }

        sizeX = x;
        sizeY = y;

        // 255
        getline(file, line);

        string r, g, b;
        int value;

        // map
        for(int i = 0; i < x; ++i) {
            for(int j = 0; j < y; ++j) {
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

/*void Hero::rotateLevel() {
    int gridTmp[sizeX][sizeY];

    for (int i = 0; i < sizeX; ++i)
    {
        for (int j = 0; j < sizeY; ++j)
        {
            gridTmp[i][j] = grid[]
        }
    }
}*/
