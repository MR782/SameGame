#include "Object.h"

Object::Object()
{
	this->anime = std::make_unique<Animation>();
	this->hitBox = Rect{ 0,0,0,0 };
	this->position = Point(0, 0);
}

void Object::draw()
{
	this->anime->draw_anime(this->position);
}

Rect Object::get_hitBox()
{
	return this->hitBox;
}
