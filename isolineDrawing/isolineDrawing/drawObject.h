#pragma once

#ifndef HV_DRAW_OBJECT
#define HV_DRAW_OBJECT

#include "object.h"
#include "color.h"
#include "data_type.h"

#include <string>
#include <variant>
#include <memory>
#include <vector>
#include <list>


#include <iostream>

namespace hv::v1 {

	class drawObject : public object {


	private:

		double thickness;

		double _x;
		double _y;
		double _width;
		double _height;
		double _angle;

		double _size;

		std::shared_ptr<hv::v1::color> _color;


	public:


		drawObject(std::string name, std::string type);
		~drawObject() override { }

		double dimX();
		double dimY();
		double dimWidth();
		double dimHeight();
		double dimSize();

		void setDimX(double x);
		void setDimY(double y);
		void setDimWidth(double width);
		void setDimHeight(double height);
		void setDimSize(double size);

		void setDimAngle(double angle);
		double getDimAngle();

		void setColor(std::shared_ptr<hv::v1::color> _color);
		std::shared_ptr<hv::v1::color> getColor();


		double getThickness();
		void setThickness(double thickness);

		virtual std::string to_string() override;

	};

	static std::shared_ptr<hv::v1::drawObject> to_drawObject(std::shared_ptr<hv::v1::object> _data) {
		if (_data == nullptr) {
			HVERROR(error, "Null pointer error");
		}
		return std::static_pointer_cast<hv::v1::drawObject>(_data);
	}
}

#endif // !HV_IMAGE