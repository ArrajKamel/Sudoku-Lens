//
// Created by kamel arraj on 02.06.2025.
//

#ifndef PROJECT_V2_CELLSEXTRACTOR_H
#define PROJECT_V2_CELLSEXTRACTOR_H

#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;

Mat_<uchar> simpleLinesCorrection(const Mat_<uchar>& unclearSudokuGrid);
vector<Rect> extractCells(const Mat_<uchar>& correctedSudokuGrid);



#endif //PROJECT_V2_CELLSEXTRACTOR_H
