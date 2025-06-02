//
// Created by kamel arraj on 01.06.2025.
//

#ifndef PROJECT_V2_PREPROCESSING_H
#define PROJECT_V2_PREPROCESSING_H

#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;


Mat_<uchar> myGaussianBlur(const Mat_<uchar>& src, int ksize = 5, double sigma = 1.0);
Mat_<uchar> myAdaptiveThreshold(const Mat_<uchar>& src, int blockSize = 11, int C = 2);


#endif //PROJECT_V2_PREPROCESSING_H
