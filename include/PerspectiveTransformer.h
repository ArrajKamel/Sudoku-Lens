//
// Created by kamel arraj on 02.06.2025.
//

#ifndef PROJECT_V2_PERSPECTIVETRANSFORMER_H
#define PROJECT_V2_PERSPECTIVETRANSFORMER_H

#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

// Warps the original preprocessed image directly based on the largest contour found in it.
Mat_<uchar> warpSudokuFromImage(const Mat_<uchar>& binaryImage, vector<Point2f> corners);

#endif //PROJECT_V2_PERSPECTIVETRANSFORMER_H
