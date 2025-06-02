//
// Created by kamel arraj on 01.06.2025.
//

#include "include/PerspectiveTransformer.h"

using namespace cv;
using namespace std;

//namespace {
//    double euclideanDist(const Point2f& a, const Point2f& b) {
//        return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
//    }
//
//    vector<Point2f> findCorners(const vector<Point>& contour) {
//        Point2f tl, tr, br, bl;
//        double minSum = 1e9, maxSum = -1e9;
//        double minDiff = 1e9, maxDiff = -1e9;
//
//        for (const Point& p : contour) {
//            double sum = p.x + p.y;
//            double diff = p.x - p.y;
//
//            if (sum < minSum) { minSum = sum; tl = p; }
//            if (sum > maxSum) { maxSum = sum; br = p; }
//            if (diff < minDiff) { minDiff = diff; bl = p; }
//            if (diff > maxDiff) { maxDiff = diff; tr = p; }
//        }
//
//        return { tl, tr, br, bl };
//    }
//
//    vector<Point> findLargestContour(const Mat_<uchar>& img) {
//        vector<vector<Point>> contours;
//        findContours(img.clone(), contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
//
//        int maxIdx = -1;
//        double maxArea = 0;
//        for (size_t i = 0; i < contours.size(); ++i) {
//            double area = contourArea(contours[i]);
//            if (area > maxArea) {
//                maxArea = area;
//                maxIdx = (int)i;
//            }
//        }
//
//        if (maxIdx == -1) return {};
//        return contours[maxIdx];
//    }
//}

double euclideanDist(const Point2f& a, const Point2f& b) {
    return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}

Mat_<uchar> warpSudokuFromImage(const Mat_<uchar>& binaryImage, vector<Point2f> corners) {
//    vector<Point> largestContour = findLargestContour(binaryImage);
//    if (largestContour.empty()) return binaryImage;
//
//    vector<Point2f> corners = findCorners(largestContour);

    double widthA = euclideanDist(corners[2], corners[3]);
    double widthB = euclideanDist(corners[1], corners[0]);
    double maxWidth = max(widthA, widthB);

    double heightA = euclideanDist(corners[0], corners[3]);
    double heightB = euclideanDist(corners[1], corners[2]);
    double maxHeight = max(heightA, heightB);

    vector<Point2f> dstCorners = {
            Point2f(0, 0),
            Point2f(maxWidth - 1, 0),
            Point2f(maxWidth - 1, maxHeight - 1),
            Point2f(0, maxHeight - 1)
    };

    Mat transform = getPerspectiveTransform(corners, dstCorners);
    Mat_<uchar> warped;
    warpPerspective(binaryImage, warped, transform, Size((int)maxWidth, (int)maxHeight));

    return warped;
}
