#pragma once

#ifndef FAST_BLOB
#define FAST_BLOB

#include <vector>
#include <memory>
#include "blobInfo.h"
#include "image.h"

#include "macro.h"



namespace hv::v1 {

	class impl_fastBlob;

	class blobDetector {

	private:
		std::shared_ptr<impl_fastBlob> impl;

	public:

		blobDetector();
		~blobDetector();

		void compute(std::shared_ptr<hv::v1::image> image);
		std::vector<std::shared_ptr<hv::v1::blobInfo>> blobInfo();


		static std::vector<std::shared_ptr<hv::v1::blobInfo>> rectFilter(std::vector<std::shared_ptr<hv::v1::blobInfo>> blobInfo, int minWidth, int maxWidth, int minHeight, int maxHeight);
		static void blobFill(std::shared_ptr<hv::v1::image> image, unsigned char pixel, std::shared_ptr<hv::v1::blobInfo> info);
		static void blobFillAll(std::shared_ptr<hv::v1::image> image, unsigned char pixel, std::vector<std::shared_ptr<hv::v1::blobInfo>> infos);
	};
}




#endif