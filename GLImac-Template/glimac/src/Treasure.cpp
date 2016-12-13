#include "glimac/Treasure.hpp"

unsigned int Treasure::getId() const {
	return id;
}

unsigned int Treasure::getPosX() const {
	return posX;
}

unsigned int Treasure::getPosY() const {
	return posY;
}

string Treasure::getName() const {
	return name;
}

int Treasure::getType() const {
	return type;
}

int Treasure::getFeature() const {
	return feature;
}

string Treasure::getObject() const {
	return object;
}

void Treasure::setId(const unsigned int &value) {
	id = value;
}

void Treasure::setPosX(const unsigned int &value) {
	posX = value;
}

void Treasure::setPosY(const unsigned int &value) {
	posY = value;
}

void Treasure::setName(const string &value) {
	name = value;
}

void Treasure::setType(const int &value) {
	type = value;
}

void Treasure::setFeature(const int &value) {
	feature = value;
}

void Treasure::setObject(const string &value) {
	object = value;
}

void Treasure::setTreasure(const  unsigned int &id, const  unsigned int &posX, const  unsigned int &posY, const  string &name, const  int &type, const  int &feature, const  string &object) {
	setId(id);
	setPosX(posX);
	setPosY(posY);
	setName(name);
	setType(type);
	setFeature(feature);
	setObject(object);
}

Treasure::Treasure(unsigned int &id, unsigned int &posX, unsigned int &posY, string &name, int &type, int &feature, string &object) {
	setTreasure(id, posX, posY, name, type, feature, object);
}

Treasure::~Treasure(){}
