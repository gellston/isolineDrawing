#include "point.h"



hv::v1::point::point(std::string _name, double _x, double _y) : hv::v1::drawObject(_name, "point") {
	this->_x = _x;
	this->_y = _y;


	this->setDimX(this->_x - this->dimSize() / 2);
	this->setDimWidth(this->dimSize());

	this->setDimY(this->_y - this->dimSize() / 2);
	this->setDimHeight(this->dimSize());
}


double hv::v1::point::x() {


	return this->_x;
}

double hv::v1::point::y() {
	return this->_y;
}

void hv::v1::point::setX(double x) {
	this->_x = x;

	this->setDimX(x - this->dimSize() / 2);
	this->setDimWidth(this->dimSize());


}
void hv::v1::point::setY(double y) {
	this->_y = y;

	this->setDimY(y - this->dimSize() / 2);
	this->setDimWidth(this->dimSize());

}




std::string hv::v1::point::to_string() {
	std::string temp = "";
	temp += this->type();
	temp += ":";
	temp += this->name();
	temp += ":[x:";
	temp += std::to_string(this->_x);
	temp += ",y:";
	temp += std::to_string(this->_y);
	temp += "]";

	return temp;
}