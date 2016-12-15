#include "glimac/Hero.hpp"

unsigned int Hero::getPosX() const {
	return posX;
}

unsigned int Hero::getPosY() const {
	return posY;
}

int Hero::getOrientation() const {
	return orientation;
}

string Hero::getName() const {
	return name;
}

int Hero::getAttack() const {
    return attack;
}

int Hero::getDefense() const {
    return defense;
}

unsigned int Hero::getLife() const {
    return life;
}

FreeflyCamera Hero::getCamera() const {
	return camera;
}

bool Hero::getHasKey() const {
	return hasKey;
}

void Hero::setPosX(const unsigned int &value) {
	posX = value;
}

void Hero::setPosY(const unsigned int &value) {
	posY = value;
}

void Hero::setOrientation(const int &value) {
	orientation = value;
}

void Hero::setName(const string &value) {
	name = value;
}
void Hero::setAttack(const int &value) {
    attack = value;
}

void Hero::setDefense(const int &value) {
    defense = value;
}

void Hero::setLife(const unsigned int &value) {
    life = value;
}

void Hero::setCamera(const FreeflyCamera &value) {
	camera = value;
}

void Hero::setHasKey(const bool &value) {
	hasKey = value;
}

void Hero::setHero(unsigned int posX, unsigned int posY, string name, int attack, int defense, unsigned int &life, FreeflyCamera &camera, bool hasKey) {
	setPosX(posX);
	setPosY(posY);
	setName(name);
	setAttack(attack);
	setDefense(defense);
	setLife(life);
	setCamera(camera);
	setHasKey(hasKey);
}

Hero::Hero(unsigned int &posX, unsigned int &posY, string &name, int &attack, int &defense, unsigned int &life, FreeflyCamera camera, bool &hasKey) {
	setHero(posX, posY, name, attack, defense, life, camera, hasKey);
	orientation = 0;
}

Hero::~Hero(){}

void Hero::down() {
	camera.moveFront(-1);
	switch(orientation) {
		case 0:
			posY ++;
			break;
		case 90:
			posX --;
			break;
		case 180:
			posY --;
			break;
		case 270:
			posX ++;
			break;
		default:
			break;
	}
	//std::cout << "Position actuelle x:y : " << posX << " : " << posY << std::endl;
	//std::cout << "Orientation : " << orientation << std::endl;
}

void Hero::up() {
	camera.moveFront(1);
	switch(orientation) {
		case 0:
			posY --;
			break;
		case 90:
			posX ++;
			break;
		case 180:
			posY ++;
			break;
		case 270:
			posX --;
			break;
		default:
			break;
	}
	//std::cout << "Position actuelle x:y : " << posX << " : " << posY << std::endl;
	//std::cout << "Orientation : " << orientation << std::endl;
}

void Hero::left() {
	camera.rotateLeft(90);
	orientation -= 90;
	if(orientation < 0) orientation = 270;
	//std::cout << "Position actuelle x:y : " << posX << " : " << posY << std::endl;
	//std::cout << "Orientation : " << orientation << std::endl;
}

void Hero::right() {
	camera.rotateLeft(-90);
	orientation += 90;
	
	if(orientation >= 360) orientation = 0;
	//std::cout << "Position actuelle x:y : " << posX << " : " << posY << std::endl;
	//std::cout << "Orientation : " << orientation << std::endl;
}

void Hero::rotateUp() {
	camera.rotateUp(10);
}

void Hero::rotateDown() {
	camera.rotateUp(-10);
}


void Hero::applyTreasure(Treasure &treasure) {
    switch(treasure.getType()) {
    	case TREASURE_LIFE : // ajoute de la vie
    		if(life + treasure.getFeature() <= LIFE_MAX)
    			life += treasure.getFeature();
    		else life = LIFE_MAX;
    		break;

    	case TREASURE_ATTACK : // ajoute de l'attaque
    		attack += treasure.getFeature();
    		break;

    	case TREASURE_DEFENSE : // ajoute de la défense
    		defense += treasure.getFeature();
    		break;

    	case TREASURE_LEVEL : // utile pour le niveau
    		hasKey = true;
    		break;

    	default :
    		break;
    }
}

Hero::Hero() {

}