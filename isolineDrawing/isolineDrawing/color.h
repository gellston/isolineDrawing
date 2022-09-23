#pragma once

#ifndef HV_COLOR
#define HV_COLOR

#include "object.h"
#include "data_type.h"

#include <string>
#include <variant>
#include <memory>
#include <vector>
#include <list>


#include <iostream>

namespace hv::v1 {

	class color : public hv::v1::object {


	private:

		double _red;
		double _green;
		double _blue;
		double _alpha;


	public:


		color(std::string name, double red, double green, double blue, double alpha);
		~color() override { }


		double getRed();
		double getGreen();
		double getBlue();
		double getAlpha();

		void setRed(double value);
		void setGreen(double value);

		void setBlue(double value);

		void setAlpha(double value);

		std::string to_string() override;

	};

	static std::shared_ptr<hv::v1::color> to_color(std::shared_ptr<hv::v1::object> _data) {
		if (_data == nullptr) {
			HVERROR(error, "Null pointer error");
		}
		return std::static_pointer_cast<hv::v1::color>(_data);
	}
}

#endif // !HV_IMAGE