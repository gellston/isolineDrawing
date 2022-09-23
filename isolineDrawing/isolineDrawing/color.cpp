#include "color.h"



hv::v1::color::color(std::string _name, double red, double green, double blue, double alpha) : hv::v1::object(_name, "color") {

	if (red < 0 || green < 0 || blue < 0 || alpha < 0)
	{
		throw std::exception("Invalid Parameter");
	}

	if (red > 255 || green > 255 || blue > 255 || alpha > 255)
	{
		throw std::exception("Invalid Parameter");
	}

	this->_red = red;
	this->_green = green;
	this->_blue = blue;
	this->_alpha = alpha;
}


double hv::v1::color::getRed() {


	return this->_red;
}


double hv::v1::color::getGreen() {


	return this->_green;
}



double hv::v1::color::getBlue() {


	return this->_blue;
}

double hv::v1::color::getAlpha() {


	return this->_alpha;
}


void hv::v1::color::setRed(double value)
{

	if (value < 0)
	{
		this->_red = 0;
	}
	else if (value > 255)
	{
		this->_red = 255;
	}
	else
	{
		this->_red = value;
	}
}
void hv::v1::color::setGreen(double value)
{
	if (value < 0)
	{
		this->_green = 0;
	}
	else if (value > 255)
	{
		this->_green = 255;
	}
	else
	{
		this->_green = value;
	}
}

void hv::v1::color::setBlue(double value)
{
	if (value < 0)
	{
		this->_blue = 0;
	}
	else if (value > 255)
	{
		this->_blue = 255;
	}
	else
	{
		this->_blue = value;
	}
}

void hv::v1::color::setAlpha(double value)
{
	if (value < 0)
	{
		this->_alpha = 0;
	}
	else if (value > 255)
	{
		this->_alpha = 255;
	}
	else
	{
		this->_alpha = value;
	}
}



std::string hv::v1::color::to_string() {
	std::string temp = "";
	temp += this->type();
	temp += ":";
	temp += this->name();
	temp += ":[red:";
	temp += std::to_string(this->_red);
	temp += ",green:";
	temp += std::to_string(this->_green);
	temp += ",blue:";
	temp += std::to_string(this->_blue);
	temp += ",alpha:";
	temp += std::to_string(this->_alpha);
	temp += "]";

	return temp;
}