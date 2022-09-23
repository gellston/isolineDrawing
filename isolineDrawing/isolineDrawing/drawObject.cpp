#include "drawObject.h"



hv::v1::drawObject::drawObject(std::string _name, std::string _type) : hv::v1::object(_name, _type), _color(new hv::v1::color("tmep", 0, 0, 0, 255)) {

	this->thickness = 1;

	this->_width = 1;
	this->_height = 1;
	this->_x = 0;
	this->_y = 0;

	this->_size = 5;
	this->_angle = 0;

}



std::string hv::v1::drawObject::to_string() {
	std::string temp = "";
	temp += this->type();
	temp += ":";
	temp += this->name();
	temp += ":[x:";
	temp += std::to_string(this->_x);
	temp += ",y:";
	temp += std::to_string(this->_y);
	temp += ",width:";
	temp += std::to_string(this->_width);
	temp += ",height:";
	temp += std::to_string(this->_height);
	temp += "]";

	return temp;
}

double hv::v1::drawObject::dimX() {
	return this->_x;
}
double hv::v1::drawObject::dimY() {
	return this->_y;
}
double hv::v1::drawObject::dimWidth() {
	return this->_width;
}
double hv::v1::drawObject::dimHeight() {
	return this->_height;
}



void hv::v1::drawObject::setDimX(double x) {
	this->_x = x;

}
void hv::v1::drawObject::setDimY(double y) {
	this->_y = y;
}
void hv::v1::drawObject::setDimWidth(double width) {
	if (width <= 0)
	{
		throw std::exception("Invalid parameter width");
	}
	this->_width = width;
}
void hv::v1::drawObject::setDimHeight(double height) {
	if (height <= 0)
	{
		throw std::exception("Invalid parameter height");
	}
	this->_height = height;
}
void hv::v1::drawObject::setDimSize(double size)
{
	if (size <= 0)
	{
		throw std::exception("Invalid paramter size");
	}
	this->_size = size;
}

double hv::v1::drawObject::dimSize() {
	return this->_size;
}


void hv::v1::drawObject::setColor(std::shared_ptr<hv::v1::color> _color) {
	this->_color = _color;

}
std::shared_ptr<hv::v1::color> hv::v1::drawObject::getColor() {
	return this->_color;
}


double hv::v1::drawObject::getThickness() {

	return this->thickness;
}
void hv::v1::drawObject::setThickness(double _thickness) {
	if (_thickness <= 0)
		_thickness = 1;

	this->thickness = _thickness;
}

void hv::v1::drawObject::setDimAngle(double angle) {
	this->_angle = angle;
}
double hv::v1::drawObject::getDimAngle() {
	return this->_angle;
}