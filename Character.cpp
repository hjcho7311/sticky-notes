//Character.cpp

#include "Character.h"
#include "Visitor.h"

Character::Character(Long width, Long height, bool highLight) {
	this->width = width;
	this->height = height;
	this->highLight = highLight;
}

Character::Character(const Character& source) {
	this->width = source.width;
	this->height = source.height;
	this->highLight = source.highLight;

}

Character::~Character() {

}

Character& Character::operator=(const Character& source) {
	this->width = source.width;
	this->height = source.height;
	this->highLight = source.highLight;

	return *this;
}

void Character::SetHighLight(bool highLight) {
	this->highLight = highLight;
}

void Character::Accept(Visitor *visitor) {
	visitor->Visit(this);
}
