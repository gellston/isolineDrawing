#pragma once
#pragma warning(disable : 4251)
#pragma warning(disable : 4275)
#pragma warning(disable : 4996)

#ifndef HV_MACRO
#define HV_MACRO


#include <stdexcept>



#if HVVAPI
#define HVAPI_EXPORT __declspec(dllexport)
//#define HVAPI_TEMPLATE_EXPORT
#else
#define HVAPI_EXPORT __declspec(dllimport)
//#define HVAPI_TEMPLATE_EXPORT extern
#endif


#define HVERROR(name, message) \
std::string name;name += "error:";name += __func__;name += ":";name += std::to_string(__LINE__);name += ":";name += message;throw std::runtime_error(name);\


#endif