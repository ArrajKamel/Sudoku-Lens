#include <iostream>
#include "./include/gridDetector.h"

int main() {
    DigitRecognizer recognizer;
//    Mat img = imread("./assets/double_sudoku.jpg", IMREAD_COLOR);
//    Mat img = imread("./assets/hard_sudoku.png", IMREAD_COLOR);
//    Mat img = imread("./assets/canny_sudoku.png", IMREAD_COLOR);
    Mat img = imread("./assets/simple_sudoku.jpg", IMREAD_COLOR);
//    Mat img = imread("./assets/sudoku1.jpg", IMREAD_COLOR);
    Mat_<uchar> test1 = sgd::preprocessing(img);
    vector<Point2f> corners = sgd::getContourCorners(test1);
    Mat_<uchar> test2 = sgd::perspectiveTransform(test1, corners);
    imshow("B&W Grid", test2);
//    cout << "number of columns per cell: " <<  test2.cols/9 << endl << "number of rows per cell: " << test2.rows/9 << endl;
    vector<Rect> test3 = sgd::extractCellRectsFromGrid(test2);
    Mat cell = test2(test3.at(22));
//    cv::Mat resized;
//    cv::resize(cell, resized, cv::Size(20, 20));
//    resized = resized.reshape(1, 1);          // Flatten to 1D
//    resized.convertTo(resized, CV_32F);       // Convert to float

//    Mat_<uchar> test2 = sgd::parseBigContour(test);
//    Mat_<uchar> test3 = sgd::perspectiveTransform(test2, test);
    imshow("preprocessing", test1);
    imshow("B&W Grid2", test2);
    imshow("cell 23", cell);
//    Mat newCell = DigitRecognizer::preprocessCell(cell);
//    imshow("cell 23 after processing", newCell);
//
//    imshow("resized 0", resized);

//    imshow("projection", test3);

//
    waitKey(0);
}
