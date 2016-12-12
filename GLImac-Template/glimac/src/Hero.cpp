#include "glimac/Hero.hpp"

unsigned int Hero::getPosX() const {
	return posX;
}

unsigned int Hero::getPosY() const {
	return posY;
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
}

Hero::~Hero(){}

void Hero::down() {
	camera.moveFront(-1);
}

void Hero::up() {
	camera.moveFront(1);
}

void Hero::left() {
	camera.rotateLeft(90);
}

void Hero::right() {
	camera.rotateLeft(-90);
}