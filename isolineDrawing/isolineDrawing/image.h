#pragma once

#ifndef HV_IMAGE
#define HV_IMAGE

#include "object.h"
#include "drawObject.h"
#include "data_type.h"

#include <string>
#include <variant>
#include <memory>
#include <vector>
#include <list>

namespace hv::v1 {

	class image : public object {
		using image_type = std::variant<std::shared_ptr<std::vector<unsigned char>>,
			std::shared_ptr<std::vector<unsigned long>>,
			std::shared_ptr<std::vector<unsigned short>>,
			std::shared_ptr<std::vector<unsigned long long>>>;

	private:

		unsigned int _width;
		unsigned int _height;
		unsigned int _size;
		unsigned int _count;
		unsigned int _stride;
		double _pixel_resolution;

		image_type __data;

		image_data_type _type;


		std::vector<std::shared_ptr<hv::v1::drawObject>> _draw_objects;

	public:


		image(std::string _name, unsigned int _width, unsigned int _height, unsigned int _type, double _resolution = 1);
		explicit image(image& copy);
		~image() override { this->_draw_objects.clear(); }

		void register_draw_object(std::shared_ptr<hv::v1::drawObject> _object);
		std::vector<std::shared_ptr<hv::v1::drawObject>> drarw_objects();


		std::string to_string() override;
		unsigned int width();
		unsigned int height();
		unsigned int size();
		unsigned int stride();
		unsigned int count();
		void* ptr();
		bool copy(image& _data);
		std::shared_ptr<hv::v1::image> clone();
		bool fill(double _value);
		double reduce();
		bool multiply(double _value);
		bool divide(double _value);
		bool add(double _value);
		bool minus(double _value);
		double resolution();
		image_data_type pixel_type();

	};

	static std::shared_ptr<hv::v1::image> to_image(std::shared_ptr<hv::v1::object> _data) {
		if (_data == nullptr) {
			HVERROR(error, "Null pointer error");
		}
		return std::static_pointer_cast<hv::v1::image>(_data);
	}

}

#endif // !HV_IMAGE