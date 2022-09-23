#include "image.h"


#include <stdexcept>
#include <execution>
#include <limits>
#include <valarray>

hv::v1::image::image(std::string name, unsigned int width, unsigned int height, unsigned int type, double resolution) : object(name, "image"),
_width(width),
_height(height),
_type((hv::v1::image_data_type)type),
_pixel_resolution(resolution) {



	int iwidth = (int)width;
	int iheight = (int)height;
	int itype = (int)type;


	if (iwidth <= 0 || iheight <= 0 || itype <= 0) {
		HVERROR(invalid_info, "Invalid image information");
	}

	unsigned int demension = width * height;

	switch (type) {
	case hv::v1::image_data_type::u8c1_image: {
		this->__data = std::make_shared<std::vector<unsigned char>>(std::vector<unsigned char>(demension));
		this->_stride = width * sizeof(unsigned char);
		this->_size = this->_stride * height;
		break;
	}
	case hv::v1::image_data_type::u16c1_image: {
		this->__data = std::make_shared<std::vector<unsigned short>>(std::vector<unsigned short>(demension));
		this->_stride = width * sizeof(unsigned short);
		this->_size = this->_stride * height;
		break;
	}
	case hv::v1::image_data_type::u32c1_image: {
		this->__data = std::make_shared<std::vector<unsigned long>>(std::vector<unsigned long>(demension));
		this->_stride = width * sizeof(unsigned long);
		this->_size = this->_stride * height;
		break;
	}
	case hv::v1::image_data_type::u64c1_image: {
		this->__data = std::make_shared<std::vector<unsigned  long long>>(std::vector<unsigned long long>(demension));
		this->_stride = width * sizeof(unsigned  long long);
		this->_size = this->_stride * height;
		break;
	}

											 // 3Channel
	case hv::v1::image_data_type::u8c3_image: {
		this->__data = std::make_shared<std::vector<unsigned char>>(std::vector<unsigned char>(demension * 3));
		this->_stride = width * sizeof(unsigned char) * 3;
		this->_size = this->_stride * height;
		break;
	}
	case hv::v1::image_data_type::u16c3_image: {
		this->__data = std::make_shared<std::vector<unsigned short>>(std::vector<unsigned short>(demension * 3));
		this->_stride = width * sizeof(unsigned short) * 3;
		this->_size = this->_stride * height;
		break;
	}
	case hv::v1::image_data_type::u32c3_image: {
		this->__data = std::make_shared<std::vector<unsigned long>>(std::vector<unsigned long>(demension * 3));
		this->_stride = width * sizeof(unsigned long) * 3;
		this->_size = this->_stride * height;
		break;
	}
	case hv::v1::image_data_type::u64c3_image: {
		this->__data = std::make_shared<std::vector<unsigned  long long>>(std::vector<unsigned long long>(demension * 3));
		this->_stride = width * sizeof(unsigned  long long) * 3;
		this->_size = this->_stride * height;
		break;
	}
	default:
		throw std::runtime_error("invaid type error");
		break;
	}


	this->_count = width * height;

}



hv::v1::image::image(image& instance) : object(instance.name(), "image"),
_width(instance._width),
_height(instance._height),
_type(instance._type),
__data(instance.__data),
_size(instance._size),
_stride(instance._stride),
_count(instance._count),
_pixel_resolution(instance._pixel_resolution) {

}


std::string hv::v1::image::to_string() {

	std::string temp = "";
	temp += this->type();
	temp += ":";
	temp += this->name();
	temp += ":[width:";
	temp += std::to_string(this->_width);
	temp += ",height:";
	temp += std::to_string(this->_height);
	temp += "]";

	return temp;
}

unsigned int hv::v1::image::width() {
	return this->_width;
}

unsigned int hv::v1::image::height() {
	return this->_height;
}

unsigned int hv::v1::image::size() {
	return this->_size;
}

void* hv::v1::image::ptr() {
	switch (this->_type) {
	case hv::v1::image_data_type::u8c1_image: {
		auto data = std::get<std::shared_ptr<std::vector<unsigned char>>>(this->__data);
		return data->data();
		break;
	}
	case hv::v1::image_data_type::u16c1_image: {
		auto data = std::get<std::shared_ptr<std::vector<unsigned short>>>(this->__data);
		return data->data();
		break;
	}
	case hv::v1::image_data_type::u32c1_image: {
		auto data = std::get<std::shared_ptr<std::vector<unsigned long>>>(this->__data);
		return data->data();
		break;
	}
	case hv::v1::image_data_type::u64c1_image: {
		auto data = std::get<std::shared_ptr<std::vector<unsigned long long>>>(this->__data);
		return data->data();
		break;
	}

											 // 3Channel
	case hv::v1::image_data_type::u8c3_image: {
		auto data = std::get<std::shared_ptr<std::vector<unsigned char>>>(this->__data);
		return data->data();
		break;
	}
	case hv::v1::image_data_type::u16c3_image: {
		auto data = std::get<std::shared_ptr<std::vector<unsigned short>>>(this->__data);
		return data->data();
		break;
	}
	case hv::v1::image_data_type::u32c3_image: {
		auto data = std::get<std::shared_ptr<std::vector<unsigned long>>>(this->__data);
		return data->data();
		break;
	}
	case hv::v1::image_data_type::u64c3_image: {
		auto data = std::get<std::shared_ptr<std::vector<unsigned long long>>>(this->__data);
		return data->data();
		break;
	}
	}

	return nullptr;
}


unsigned int hv::v1::image::stride() {
	return this->_stride;
}

unsigned int hv::v1::image::count() {
	return this->_count;
}

bool hv::v1::image::copy(hv::v1::image& data) {



	if (this->_width != data._width ||
		this->_height != data._height ||
		this->_count != data._count ||
		this->_type != data._type ||
		this->_size != data._size ||
		this->_stride != data._stride) return false;


	switch (this->_type) {
	case hv::v1::image_data_type::u8c1_image: {
		auto source = std::get<std::shared_ptr<std::vector<unsigned char>>>(this->__data);
		auto target = std::get<std::shared_ptr<std::vector<unsigned char>>>(data.__data);
		std::copy(std::execution::par_unseq, source->begin(), source->end(), target->begin());
		break;
	}
	case hv::v1::image_data_type::u16c1_image: {
		auto source = std::get<std::shared_ptr<std::vector<unsigned short>>>(this->__data);
		auto target = std::get<std::shared_ptr<std::vector<unsigned short>>>(data.__data);
		std::copy(std::execution::par_unseq, source->begin(), source->end(), target->begin());
		break;
	}
	case hv::v1::image_data_type::u32c1_image: {
		auto source = std::get<std::shared_ptr<std::vector<unsigned long>>>(this->__data);
		auto target = std::get<std::shared_ptr<std::vector<unsigned long>>>(data.__data);
		std::copy(std::execution::par_unseq, source->begin(), source->end(), target->begin());
		break;
	}
	case hv::v1::image_data_type::u64c1_image: {
		auto source = std::get<std::shared_ptr<std::vector<unsigned long long>>>(this->__data);
		auto target = std::get<std::shared_ptr<std::vector<unsigned long long>>>(data.__data);
		std::copy(std::execution::par_unseq, source->begin(), source->end(), target->begin());
		break;
	}

											 //3Channel
	case hv::v1::image_data_type::u8c3_image: {
		auto source = std::get<std::shared_ptr<std::vector<unsigned char>>>(this->__data);
		auto target = std::get<std::shared_ptr<std::vector<unsigned char>>>(data.__data);
		std::copy(std::execution::par_unseq, source->begin(), source->end(), target->begin());
		break;
	}
	case hv::v1::image_data_type::u16c3_image: {
		auto source = std::get<std::shared_ptr<std::vector<unsigned short>>>(this->__data);
		auto target = std::get<std::shared_ptr<std::vector<unsigned short>>>(data.__data);
		std::copy(std::execution::par_unseq, source->begin(), source->end(), target->begin());
		break;
	}
	case hv::v1::image_data_type::u32c3_image: {
		auto source = std::get<std::shared_ptr<std::vector<unsigned long>>>(this->__data);
		auto target = std::get<std::shared_ptr<std::vector<unsigned long>>>(data.__data);
		std::copy(std::execution::par_unseq, source->begin(), source->end(), target->begin());
		break;
	}
	case hv::v1::image_data_type::u64c3_image: {
		auto source = std::get<std::shared_ptr<std::vector<unsigned long long>>>(this->__data);
		auto target = std::get<std::shared_ptr<std::vector<unsigned long long>>>(data.__data);
		std::copy(std::execution::par_unseq, source->begin(), source->end(), target->begin());
		break;
	}
	default: return false; break;
	}



	return true;
}


bool hv::v1::image::fill(double value) {
	switch (this->_type) {
	case hv::v1::image_data_type::u8c1_image: {
		if (UCHAR_MAX < value || value < 0) return false;
		auto source = std::get<std::shared_ptr<std::vector<unsigned char>>>(this->__data);
		std::fill(std::execution::par_unseq, source->begin(), source->end(), static_cast<unsigned char>(value));
		break;
	}
	case hv::v1::image_data_type::u16c1_image: {
		if (USHRT_MAX < value || value < 0) return false;
		auto source = std::get<std::shared_ptr<std::vector<unsigned short>>>(this->__data);
		std::fill(std::execution::par_unseq, source->begin(), source->end(), static_cast<unsigned short>(value));
		break;
	}
	case hv::v1::image_data_type::u32c1_image: {
		if (ULONG_MAX < value || value < 0) return false;
		auto source = std::get<std::shared_ptr<std::vector<unsigned long>>>(this->__data);
		std::fill(std::execution::par_unseq, source->begin(), source->end(), static_cast<unsigned long>(value));
		break;
	}
	case hv::v1::image_data_type::u64c1_image: {
		if (ULLONG_MAX < value || value < 0) return false;
		auto source = std::get<std::shared_ptr<std::vector<unsigned long long>>>(this->__data);
		std::fill(std::execution::par_unseq, source->begin(), source->end(), static_cast<unsigned long long>(value));
		break;
	}

											 //3Channel
	case hv::v1::image_data_type::u8c3_image: {
		if (UCHAR_MAX < value || value < 0) return false;
		auto source = std::get<std::shared_ptr<std::vector<unsigned char>>>(this->__data);
		std::fill(std::execution::par_unseq, source->begin(), source->end(), static_cast<unsigned char>(value));
		break;
	}
	case hv::v1::image_data_type::u16c3_image: {
		if (USHRT_MAX < value || value < 0) return false;
		auto source = std::get<std::shared_ptr<std::vector<unsigned short>>>(this->__data);
		std::fill(std::execution::par_unseq, source->begin(), source->end(), static_cast<unsigned short>(value));
		break;
	}
	case hv::v1::image_data_type::u32c3_image: {
		if (ULONG_MAX < value || value < 0) return false;
		auto source = std::get<std::shared_ptr<std::vector<unsigned long>>>(this->__data);
		std::fill(std::execution::par_unseq, source->begin(), source->end(), static_cast<unsigned long>(value));
		break;
	}
	case hv::v1::image_data_type::u64c3_image: {
		if (ULLONG_MAX < value || value < 0) return false;
		auto source = std::get<std::shared_ptr<std::vector<unsigned long long>>>(this->__data);
		std::fill(std::execution::par_unseq, source->begin(), source->end(), static_cast<unsigned long long>(value));
		break;
	}
	default: return false; break;
	}

	return true;
}

double hv::v1::image::reduce() {
	switch (this->_type) {
	case hv::v1::image_data_type::u8c1_image: {
		auto source = std::get<std::shared_ptr<std::vector<unsigned char>>>(this->__data);
		double sum = std::reduce(std::execution::par, source->begin(), source->end(), (double)0);
		return sum;
		break;
	}
	case hv::v1::image_data_type::u16c1_image: {
		auto source = std::get<std::shared_ptr<std::vector<unsigned short>>>(this->__data);
		double sum = std::reduce(std::execution::par, source->begin(), source->end(), (double)0);
		return sum;
		break;
	}
	case hv::v1::image_data_type::u32c1_image: {
		auto source = std::get<std::shared_ptr<std::vector<unsigned long>>>(this->__data);
		double sum = std::reduce(std::execution::par, source->begin(), source->end(), (double)0);
		return sum;
		break;
	}
	case hv::v1::image_data_type::u64c1_image: {
		auto source = std::get<std::shared_ptr<std::vector<unsigned long long>>>(this->__data);
		double sum = std::reduce(std::execution::par, source->begin(), source->end(), (double)0);
		return sum;
		break;
	}
											 //3Channel

	case hv::v1::image_data_type::u8c3_image: {
		auto source = std::get<std::shared_ptr<std::vector<unsigned char>>>(this->__data);
		double sum = std::reduce(std::execution::par, source->begin(), source->end(), (double)0);
		return sum;
		break;
	}
	case hv::v1::image_data_type::u16c3_image: {
		auto source = std::get<std::shared_ptr<std::vector<unsigned short>>>(this->__data);
		double sum = std::reduce(std::execution::par, source->begin(), source->end(), (double)0);
		return sum;
		break;
	}
	case hv::v1::image_data_type::u32c3_image: {
		auto source = std::get<std::shared_ptr<std::vector<unsigned long>>>(this->__data);
		double sum = std::reduce(std::execution::par, source->begin(), source->end(), (double)0);
		return sum;
		break;
	}
	case hv::v1::image_data_type::u64c3_image: {
		auto source = std::get<std::shared_ptr<std::vector<unsigned long long>>>(this->__data);
		double sum = std::reduce(std::execution::par, source->begin(), source->end(), (double)0);
		return sum;
		break;
	}
	default: return 0; break;
	}

	return 0;
}


bool hv::v1::image::multiply(double value) {
	switch (this->_type) {
	case hv::v1::image_data_type::u8c1_image: {
		auto source = std::get<std::shared_ptr<std::vector<unsigned char>>>(this->__data);
		unsigned char* pointer = source->data();
		std::for_each(std::execution::par_unseq, source->begin(), source->end(), [&](unsigned char& element) {
			element = static_cast<unsigned char>(((double)element * value));
			});
		break;
	}
	case hv::v1::image_data_type::u16c1_image: {
		auto source = std::get<std::shared_ptr<std::vector<unsigned short>>>(this->__data);
		std::for_each(std::execution::par_unseq, source->begin(), source->end(), [&](unsigned short& element) {
			element = static_cast<unsigned short>(((double)element * value));
			});
		break;
	}
	case hv::v1::image_data_type::u32c1_image: {
		auto source = std::get<std::shared_ptr<std::vector<unsigned long>>>(this->__data);
		std::for_each(std::execution::par_unseq, source->begin(), source->end(), [&](unsigned long& element) {
			element = static_cast<unsigned long>(((double)element * value));
			});
		break;
	}
	case hv::v1::image_data_type::u64c1_image: {
		auto source = std::get<std::shared_ptr<std::vector<unsigned long long>>>(this->__data);
		std::for_each(std::execution::par_unseq, source->begin(), source->end(), [&](unsigned long long& element) {
			element = static_cast<unsigned long long>(((double)element * value));
			});
		break;
	}
											 // 3Channel
	case hv::v1::image_data_type::u8c3_image: {
		auto source = std::get<std::shared_ptr<std::vector<unsigned char>>>(this->__data);
		unsigned char* pointer = source->data();
		std::for_each(std::execution::par_unseq, source->begin(), source->end(), [&](unsigned char& element) {
			element = static_cast<unsigned char>(((double)element * value));
			});
		break;
	}
	case hv::v1::image_data_type::u16c3_image: {
		auto source = std::get<std::shared_ptr<std::vector<unsigned short>>>(this->__data);
		std::for_each(std::execution::par_unseq, source->begin(), source->end(), [&](unsigned short& element) {
			element = static_cast<unsigned short>(((double)element * value));
			});
		break;
	}
	case hv::v1::image_data_type::u32c3_image: {
		auto source = std::get<std::shared_ptr<std::vector<unsigned long>>>(this->__data);
		std::for_each(std::execution::par_unseq, source->begin(), source->end(), [&](unsigned long& element) {
			element = static_cast<unsigned long>(((double)element * value));
			});
		break;
	}
	case hv::v1::image_data_type::u64c3_image: {
		auto source = std::get<std::shared_ptr<std::vector<unsigned long long>>>(this->__data);
		std::for_each(std::execution::par_unseq, source->begin(), source->end(), [&](unsigned long long& element) {
			element = static_cast<unsigned long long>(((double)element * value));
			});
		break;
	}
	default: return false; break;
	}

	return true;
}
bool hv::v1::image::divide(double value) {
	switch (this->_type) {
	case hv::v1::image_data_type::u8c1_image: {
		auto source = std::get<std::shared_ptr<std::vector<unsigned char>>>(this->__data);
		std::for_each(std::execution::par_unseq, source->begin(), source->end(), [&](unsigned char& element) {
			if (element == 0 || value == 0) return;
			element = static_cast<unsigned char>(((double)element / value));
			});
		break;
	}
	case hv::v1::image_data_type::u16c1_image: {
		auto source = std::get<std::shared_ptr<std::vector<unsigned short>>>(this->__data);
		std::for_each(std::execution::par_unseq, source->begin(), source->end(), [&](unsigned short& element) {
			if (element == 0 || value == 0) return;
			element = static_cast<unsigned short>(((double)element / value));
			});
		break;
	}
	case hv::v1::image_data_type::u32c1_image: {
		auto source = std::get<std::shared_ptr<std::vector<unsigned long>>>(this->__data);
		std::for_each(std::execution::par_unseq, source->begin(), source->end(), [&](unsigned long& element) {
			if (element == 0 || value == 0) return;
			element = static_cast<unsigned long>(((double)element / value));
			});
		break;
	}
	case hv::v1::image_data_type::u64c1_image: {
		auto source = std::get<std::shared_ptr<std::vector<unsigned long long>>>(this->__data);
		std::for_each(std::execution::par_unseq, source->begin(), source->end(), [&](unsigned long long& element) {
			if (element == 0 || value == 0) return;
			element = static_cast<unsigned long long>(((double)element / value));
			});
		break;
	}

											 //3Channel
	case hv::v1::image_data_type::u8c3_image: {
		auto source = std::get<std::shared_ptr<std::vector<unsigned char>>>(this->__data);
		std::for_each(std::execution::par_unseq, source->begin(), source->end(), [&](unsigned char& element) {
			if (element == 0 || value == 0) return;
			element = static_cast<unsigned char>(((double)element / value));
			});
		break;
	}
	case hv::v1::image_data_type::u16c3_image: {
		auto source = std::get<std::shared_ptr<std::vector<unsigned short>>>(this->__data);
		std::for_each(std::execution::par_unseq, source->begin(), source->end(), [&](unsigned short& element) {
			if (element == 0 || value == 0) return;
			element = static_cast<unsigned short>(((double)element / value));
			});
		break;
	}
	case hv::v1::image_data_type::u32c3_image: {
		auto source = std::get<std::shared_ptr<std::vector<unsigned long>>>(this->__data);
		std::for_each(std::execution::par_unseq, source->begin(), source->end(), [&](unsigned long& element) {
			if (element == 0 || value == 0) return;
			element = static_cast<unsigned long>(((double)element / value));
			});
		break;
	}
	case hv::v1::image_data_type::u64c3_image: {
		auto source = std::get<std::shared_ptr<std::vector<unsigned long long>>>(this->__data);
		std::for_each(std::execution::par_unseq, source->begin(), source->end(), [&](unsigned long long& element) {
			if (element == 0 || value == 0) return;
			element = static_cast<unsigned long long>(((double)element / value));
			});
		break;
	}

	default: return false; break;
	}

	return true;
}


bool hv::v1::image::minus(double value) {
	switch (this->_type) {
	case hv::v1::image_data_type::u8c1_image: {
		auto source = std::get<std::shared_ptr<std::vector<unsigned char>>>(this->__data);
		unsigned char* pointer = source->data();
		std::for_each(std::execution::par_unseq, source->begin(), source->end(), [&](unsigned char& element) {
			element = static_cast<unsigned char>(((double)element - value));
			});
		break;
	}
	case hv::v1::image_data_type::u16c1_image: {
		auto source = std::get<std::shared_ptr<std::vector<unsigned short>>>(this->__data);
		std::for_each(std::execution::par_unseq, source->begin(), source->end(), [&](unsigned short& element) {
			element = static_cast<unsigned short>(((double)element - value));
			});
		break;
	}
	case hv::v1::image_data_type::u32c1_image: {
		auto source = std::get<std::shared_ptr<std::vector<unsigned long>>>(this->__data);
		std::for_each(std::execution::par_unseq, source->begin(), source->end(), [&](unsigned long& element) {
			element = static_cast<unsigned long>(((double)element - value));
			});
		break;
	}
	case hv::v1::image_data_type::u64c1_image: {
		auto source = std::get<std::shared_ptr<std::vector<unsigned long long>>>(this->__data);
		std::for_each(std::execution::par_unseq, source->begin(), source->end(), [&](unsigned long long& element) {
			element = static_cast<unsigned long long>(((double)element - value));
			});
		break;
	}

											 //3 channel
	case hv::v1::image_data_type::u8c3_image: {
		auto source = std::get<std::shared_ptr<std::vector<unsigned char>>>(this->__data);
		unsigned char* pointer = source->data();
		std::for_each(std::execution::par_unseq, source->begin(), source->end(), [&](unsigned char& element) {
			element = static_cast<unsigned char>(((double)element - value));
			});
		break;
	}
	case hv::v1::image_data_type::u16c3_image: {
		auto source = std::get<std::shared_ptr<std::vector<unsigned short>>>(this->__data);
		std::for_each(std::execution::par_unseq, source->begin(), source->end(), [&](unsigned short& element) {
			element = static_cast<unsigned short>(((double)element - value));
			});
		break;
	}
	case hv::v1::image_data_type::u32c3_image: {
		auto source = std::get<std::shared_ptr<std::vector<unsigned long>>>(this->__data);
		std::for_each(std::execution::par_unseq, source->begin(), source->end(), [&](unsigned long& element) {
			element = static_cast<unsigned long>(((double)element - value));
			});
		break;
	}
	case hv::v1::image_data_type::u64c3_image: {
		auto source = std::get<std::shared_ptr<std::vector<unsigned long long>>>(this->__data);
		std::for_each(std::execution::par_unseq, source->begin(), source->end(), [&](unsigned long long& element) {
			element = static_cast<unsigned long long>(((double)element - value));
			});
		break;
	}
	default: return false; break;
	}

	return true;
}

bool hv::v1::image::add(double value) {
	switch (this->_type) {
	case hv::v1::image_data_type::u8c1_image: {
		auto source = std::get<std::shared_ptr<std::vector<unsigned char>>>(this->__data);
		unsigned char* pointer = source->data();
		std::for_each(std::execution::par_unseq, source->begin(), source->end(), [&](unsigned char& element) {
			element = static_cast<unsigned char>(((double)element + value));
			});
		break;
	}
	case hv::v1::image_data_type::u16c1_image: {
		auto source = std::get<std::shared_ptr<std::vector<unsigned short>>>(this->__data);
		std::for_each(std::execution::par_unseq, source->begin(), source->end(), [&](unsigned short& element) {
			element = static_cast<unsigned short>(((double)element + value));
			});
		break;
	}
	case hv::v1::image_data_type::u32c1_image: {
		auto source = std::get<std::shared_ptr<std::vector<unsigned long>>>(this->__data);
		std::for_each(std::execution::par_unseq, source->begin(), source->end(), [&](unsigned long& element) {
			element = static_cast<unsigned long>(((double)element + value));
			});
		break;
	}
	case hv::v1::image_data_type::u64c1_image: {
		auto source = std::get<std::shared_ptr<std::vector<unsigned long long>>>(this->__data);
		std::for_each(std::execution::par_unseq, source->begin(), source->end(), [&](unsigned long long& element) {
			element = static_cast<unsigned long long>(((double)element + value));
			});
		break;
	}

											 //3 Channel
	case hv::v1::image_data_type::u8c3_image: {
		auto source = std::get<std::shared_ptr<std::vector<unsigned char>>>(this->__data);
		unsigned char* pointer = source->data();
		std::for_each(std::execution::par_unseq, source->begin(), source->end(), [&](unsigned char& element) {
			element = static_cast<unsigned char>(((double)element + value));
			});
		break;
	}
	case hv::v1::image_data_type::u16c3_image: {
		auto source = std::get<std::shared_ptr<std::vector<unsigned short>>>(this->__data);
		std::for_each(std::execution::par_unseq, source->begin(), source->end(), [&](unsigned short& element) {
			element = static_cast<unsigned short>(((double)element + value));
			});
		break;
	}
	case hv::v1::image_data_type::u32c3_image: {
		auto source = std::get<std::shared_ptr<std::vector<unsigned long>>>(this->__data);
		std::for_each(std::execution::par_unseq, source->begin(), source->end(), [&](unsigned long& element) {
			element = static_cast<unsigned long>(((double)element + value));
			});
		break;
	}
	case hv::v1::image_data_type::u64c3_image: {
		auto source = std::get<std::shared_ptr<std::vector<unsigned long long>>>(this->__data);
		std::for_each(std::execution::par_unseq, source->begin(), source->end(), [&](unsigned long long& element) {
			element = static_cast<unsigned long long>(((double)element + value));
			});
		break;
	}
	default: return false; break;
	}

	return true;
}


double hv::v1::image::resolution() {

	return this->_pixel_resolution;
}

void hv::v1::image::register_draw_object(std::shared_ptr<hv::v1::drawObject> _object) {
	this->_draw_objects.push_back(_object);
}

std::vector<std::shared_ptr<hv::v1::drawObject>> hv::v1::image::drarw_objects() {
	return this->_draw_objects;
}

hv::v1::image_data_type hv::v1::image::pixel_type() {

	return this->_type;
}


std::shared_ptr<hv::v1::image> hv::v1::image::clone() {
	std::shared_ptr<hv::v1::image> clone_image(new hv::v1::image(this->name(), this->width(), this->height(), this->pixel_type(), this->resolution()));
	std::memcpy(clone_image->ptr(), this->ptr(), this->size());

	for (auto& draw_object : this->_draw_objects)
		clone_image->register_draw_object(draw_object);

	return clone_image;
}