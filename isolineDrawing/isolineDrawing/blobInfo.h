#pragma once

#ifndef HV_BLOB_INFO
#define HV_BLOB_INFO

#include <vector>
#include <string> 
#include <memory>

#include "point.h"
#include "drawObject.h"

namespace hv::v1 {
    class blobInfo : public  hv::v1::drawObject {
    private:

        int _id;
        int _rect_x;
        int _rect_y;
        int _rect_width;
        int _rect_height;

        double _centeriod_x;
        double _centeriod_y;


        bool _isBlack;

        std::vector<std::shared_ptr<hv::v1::point>> _blob_points;

    public:

        blobInfo(std::string namne, int id, int rect_x, int rect_y, int rect_width, int rect_height, double centeroid_x, double centeroid_y, bool isBlack);

        int id();
        int rectX();
        int rectY();
        int rectWidth();
        int rectHeight();
        double centeroidX();
        double centeroidY();
        bool isBlack();


        void setBlobPoints(std::vector<std::shared_ptr<hv::v1::point>> points);
        std::vector<std::shared_ptr<hv::v1::point>> getBlobPoints();

    };

    static std::shared_ptr<hv::v1::blobInfo> to_blobInfo(std::shared_ptr<hv::v1::object> _data) {
        if (_data == nullptr) {
            HVERROR(error, "Null pointer error");
        }
        return std::static_pointer_cast<hv::v1::blobInfo>(_data);
    }
}



#endif