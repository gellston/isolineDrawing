// isolineDrawing.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <opencv2/opencv.hpp>


#include "image.h"
#include "blobDetector.h"

int main()
{
    

    
    cv::Mat original = cv::imread("C://Users//gellston//Desktop//KakaoTalk_20220920_230436887.png", cv::IMREAD_GRAYSCALE);
    cv::Mat resultImage;


    cv::cvtColor(original, resultImage, cv::COLOR_GRAY2BGR);


    double step = 10;
    double maxValue = 255;
    double unit_step = 255 / step;


    hv::v1::blobDetector detector;
    for (int index = 0; index < step; index++) {


        int offset = -1;
        if (index + 1 == step)
            offset = 0;


        cv::Mat threshold;
        cv::threshold(original, threshold, index * unit_step, (index + 1) * unit_step + offset, cv::THRESH_BINARY);




        //cv threshold image to hv image

        std::shared_ptr<hv::v1::image> hvImage(new hv::v1::image("", (unsigned int)threshold.cols, (unsigned int)threshold.rows, hv::v1::image_data_type::u8c1_image, 1));
        std::memcpy(hvImage->ptr(), threshold.data, hvImage->size());

        detector.compute(hvImage);

        //Isolines!!!!!!!!!!!!
        auto blobs = detector.blobInfo();
       

        for (auto blob : blobs) {
            auto contourPoints = blob->getBlobPoints();
            for (auto point : contourPoints) {
                cv::circle(resultImage, cv::Point(point->x(), point->y()),1, cv::Scalar((index + 1) * unit_step + offset, 0, 0));
            }
        }




    }


    cv::namedWindow("original", cv::WINDOW_FREERATIO);
    cv::namedWindow("resultImage", cv::WINDOW_FREERATIO);

    cv::imshow("original", original);
    cv::imshow("resultImage", resultImage);
    cv::waitKey();

}

