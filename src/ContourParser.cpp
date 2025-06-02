//
// Created by kamel arraj on 01.06.2025.
//

#include "include/ContourParser.h"
#include <vector>
#include <algorithm>

using namespace cv;
using namespace std;

vector<Point2f> findCorners(const vector<Point>& contour) {
    Point2f tl, tr, br, bl;
    double minSum = 1e9, maxSum = -1e9;
    double minDiff = 1e9, maxDiff = -1e9;

    for (const Point& p : contour) {
        double sum = p.x + p.y;
        double diff = p.x - p.y;

        if (sum < minSum) { minSum = sum; tl = p; }
        if (sum > maxSum) { maxSum = sum; br = p; }
        if (diff < minDiff) { minDiff = diff; bl = p; }
        if (diff > maxDiff) { maxDiff = diff; tr = p; }
    }

    return { tl, tr, br, bl };
}

vector<Point> findMostLikelyGridComponent(const Mat_<uchar>& img) {
    int rows = img.rows, cols = img.cols;
    Mat_<bool> visited(rows, cols, false);

    const int dx[4] = {-1, 0, 1, 0};
    const int dy[4] = {0, -1, 0, 1};

    int maxSize = 0;
    vector<Point> bestComponent;

    for (int y = 0; y < rows; ++y) {
        for (int x = 0; x < cols; ++x) {
            if (!visited(y, x) && img(y, x) == 255) {
                queue<Point> q;
                vector<Point> component;
                q.push(Point(x, y));
                visited(y, x) = true;

                while (!q.empty()) {
                    Point p = q.front(); q.pop();
                    component.push_back(p);

                    for (int k = 0; k < 4; ++k) {
                        int nx = p.x + dx[k], ny = p.y + dy[k];
                        if (nx >= 0 && ny >= 0 && nx < cols && ny < rows &&
                            !visited(ny, nx) && img(ny, nx) == 255) {
                            visited(ny, nx) = true;
                            q.push(Point(nx, ny));
                        }
                    }
                }

                if ((int)component.size() > maxSize) {
                    maxSize = (int)component.size();
                    bestComponent = component;
                }
            }
        }
    }
    return bestComponent;
}


vector<Point> findLargestContour(const Mat_<uchar>& img) {
//    vector<vector<Point>> contours;
////    findContours(img.clone(), contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

    vector<Point> bestContour = findMostLikelyGridComponent(img);
    return bestContour;
//    int maxIdx = -1;
//    double maxArea = 0;
//    for (size_t i = 0; i < contours.size(); ++i) {
//        double area = contourArea(contours[i]);
//        if (area > maxArea) {
//            maxArea = area;
//            maxIdx = (int)i;
//        }
//    }
//
//    if (maxIdx == -1) return {};
//    return contours[maxIdx];
}