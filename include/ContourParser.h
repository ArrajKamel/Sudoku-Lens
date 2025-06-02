//
// Created by kamel arraj on 01.06.2025.
//

#ifndef PROJECT_V2_CONTOURPARSER_H
#define PROJECT_V2_CONTOURPARSER_H

#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;


//double euclideanDist(const Point2f& a, const Point2f& b);
vector<Point2f> findCorners(const vector<Point>& contour);
vector<Point> findLargestContour(const Mat_<uchar>& img);

#endif //PROJECT_V2_CONTOURPARSER_H
