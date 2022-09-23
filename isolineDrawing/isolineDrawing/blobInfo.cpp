#include "blobInfo.h"



hv::v1::blobInfo::blobInfo(std::string name,
	int id,
	int rect_x,
	int rect_y,
	int rect_width,
	int rect_height,
	double centeroid_x,
	double centeroid_y,
	bool isBlack) : hv::v1::drawObject(name, "blobInfo") {

	if (id < 0 || rect_width <= 0 || rect_height <= 0) {
		throw std::runtime_error("Invalid blob info");
	}


	this->_id = id;
	this->_rect_x = rect_x;
	this->_rect_y = rect_y;
	this->_rect_width = rect_width;
	this->_rect_height = rect_height;

	this->_centeriod_x = centeroid_x;
	this->_centeriod_y = centeroid_y;

	this->_isBlack = isBlack;

	this->setDimX(this->_rect_x);
	this->setDimY(this->_rect_y);

	this->setDimWidth(this->_rect_width);
	this->setDimHeight(this->_rect_height);

	this->setThickness(1);

}

int hv::v1::blobInfo::id() {
	return this->_id;
}

int hv::v1::blobInfo::rectX() {
	return this->_rect_x;

}

int hv::v1::blobInfo::rectY() {
	return this->_rect_y;
}

int hv::v1::blobInfo::rectWidth() {
	return this->_rect_width;
}

int hv::v1::blobInfo::rectHeight() {
	return this->_rect_height;
}

double hv::v1::blobInfo::centeroidX() {
	return this->_centeriod_x;

}
double hv::v1::blobInfo::centeroidY() {
	return this->_centeriod_y;
}

bool hv::v1::blobInfo::isBlack() {
	return this->_isBlack;
}

void hv::v1::blobInfo::setBlobPoints(std::vector<std::shared_ptr<hv::v1::point>> points) {
	this->_blob_points = points;
}

std::vector<std::shared_ptr<hv::v1::point>> hv::v1::blobInfo::getBlobPoints() {
	return this->_blob_points;
}
