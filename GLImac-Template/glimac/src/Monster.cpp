#include "glimac/Monster.hpp"

unsigned int Monster::getId() const {
	return id;
}

unsigned int Monster::getPosX() const {
	return posX;
}

unsigned int Monster::getPosY() const {
	return posY;
}

string Monster::getName() const {
	return name;
}

int Monster::getType() const {
	return type;
}

int Monster::getAttack() const {
    return attack;
}

int Monster::getDefense() const {
    return defense;
}

unsigned int Monster::getLife() const {
    return life;
}

string Monster::getObject() const {
	return object;
}

int Monster::getOrientation() const {
	return orientation;
}

void Monster::setId(const unsigned int &value) {
	id = value;
}

void Monster::setPosX(const unsigned int &value) {
	posX = value;
}

void Monster::setPosY(const unsigned int &value) {
	posY = value;
}

void Monster::setName(const string &value) {
	name = value;
}

void Monster::setType(const int &value) {
	type = value;
}

void Monster::setAttack(const int &value) {
    attack = value;
}

void Monster::setDefense(const int &value) {
    defense = value;
}

void Monster::setLife(const unsigned int &value) {
    life = value;
}

void Monster::setObject(const string &value) {
	object = value;
}

void Monster::setOrientation(const int &value) {
	orientation = value;
}

void Monster::setMonster(const  unsigned int &id, const  unsigned int &posX, const  unsigned int &posY, const  string &name, const  int &type, const int &attack, const int &defense, const unsigned int &life, const  string &object) {
	setId(id);
	setPosX(posX);
	setPosY(posY);
	setName(name);
	setType(type);
	setAttack(attack);
	setDefense(defense);
	setLife(life);
	setObject(object);
}

Monster::Monster(unsigned int &id, unsigned int &posX, unsigned int &posY, string &name, int &type, int &attack, int &defense, unsigned int &life, string &object) {
	setMonster(id, posX, posY, name, type, attack, defense, life, object);
}

Monster::~Monster(){}

void Monster::move() {
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
}
