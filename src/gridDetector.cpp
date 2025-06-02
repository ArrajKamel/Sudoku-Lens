//
// Created by kamel arraj on 01.06.2025.
//

#include "../include/gridDetector.h"

namespace sgd {
    Mat_<uchar> preprocessing(const Mat &input) {
        Mat_<uchar> gray;
        cvtColor(input, gray, COLOR_BGR2GRAY);
        Mat_<uchar> blurred = myGaussianBlur(gray, 5, 1.0);
        Mat_<uchar> thresholded = myAdaptiveThreshold(blurred, 11, 2);

        return thresholded;
    }

    vector<Point2f> getContourCorners(const Mat_<uchar>& preprocessedImg){
        vector<Point> largestContour = ::findLargestContour(preprocessedImg);
        if (largestContour.empty()) return preprocessedImg;
        vector<Point2f> corners = ::findCorners(largestContour);

        return corners;
    }

    Mat_<uchar> perspectiveTransform(const Mat_<uchar>& preprocessed, vector<Point2f> corners) {
        return ::warpSudokuFromImage(preprocessed, corners);
    }

    vector<Rect> extractCellRectsFromGrid( Mat_<uchar>& unclearSudokuGrid){
        unclearSudokuGrid= ::simpleLinesCorrection(unclearSudokuGrid);
        return ::extractCells(unclearSudokuGrid);
    }

    Mat_<int> detectNumbers(const Mat_<uchar>& sudokuGrid, const vector<Rect>& cellRects){
        DigitRecognizer recognizer;
        if (!recognizer.loadModel("model/knn_digits.yml")) {
            cerr << "Failed to load digit recognition model." << endl;
            return Mat_<int>::zeros(9, 9);
        }

        Mat_<int> result(9, 9);
        for (int i = 0; i < 81; ++i) {
            Rect rect = cellRects[i];
            Mat cell = sudokuGrid(rect);
            int digit = recognizer.recognize(cell);
            result(i / 9, i % 9) = digit == -1 ? 0 : digit;
        }
        return result;
    }


}