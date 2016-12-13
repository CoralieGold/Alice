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

// get inventory

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

// get inventory

void Hero::setHero(const  unsigned int &posX, const  unsigned int &posY, const  string &name, const int &attack, const int &defense, const unsigned int &life, const  FreeflyCamera &camera) {
	setPosX(posX);
	setPosY(posY);
	setName(name);
	setAttack(attack);
	setDefense(defense);
	setLife(life);
	setCamera(camera);
}

Hero::Hero(unsigned int &posX, unsigned int &posY, string &name, int &attack, int &defense, unsigned int &life, FreeflyCamera camera) {
	setHero(posX, posY, name, attack, defense, life, camera);
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
	std::cout << "Position actuelle x:y : " << posX << " : " << posY << std::endl;
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
	std::cout << "Position actuelle x:y : " << posX << " : " << posY << std::endl;
	//std::cout << "Orientation : " << orientation << std::endl;
}

void Hero::left() {
	camera.rotateLeft(90);
	orientation -= 90;
	if(orientation < 0) orientation = 270;
	std::cout << "Position actuelle x:y : " << posX << " : " << posY << std::endl;
	//std::cout << "Orientation : " << orientation << std::endl;
}

void Hero::right() {
	camera.rotateLeft(-90);
	orientation += 90;
	
	if(orientation >= 360) orientation = 0;
	std::cout << "Position actuelle x:y : " << posX << " : " << posY << std::endl;
	//std::cout << "Orientation : " << orientation << std::endl;
}

void Hero::applyTreasure(Treasure &treasure) {
    switch(treasure.getType()) {
    	case 1 : // ajoute de la vie
    		if(life + treasure.getFeature() <= LIFE_MAX)
    			life += treasure.getFeature();
    		else life = LIFE_MAX;
    		break;

    	case 2 : // ajoute de l'attaque
    		attack += treasure.getFeature();
    		break;

    	case 3 : // ajoute de la défense
    		defense += treasure.getFeature();
    		break;

    	case 4 : // utile pour le niveau
    		break;

    	default :
    		break;
    }
}