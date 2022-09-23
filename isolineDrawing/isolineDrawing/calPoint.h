#pragma once

#ifndef HV_CAL_POINT
#define HV_CAL_POINT

#include <type_traits>

#pragma pack(push, 1)

namespace hv::v1 {
    struct calPoint {
        double x;
        double y;
    };


}

static_assert(std::is_standard_layout_v<hv::v1::calPoint>);
#pragma pack(pop) 


#endif