//
// Created by kamel arraj on 01.06.2025.
//

#ifndef PROJECT_V2_GRIDDETECTOR_H
#define PROJECT_V2_GRIDDETECTOR_H


#include <iostream>
#include <opencv2/opencv.hpp>
#include "algorithm"
#include "ContourParser.h"
#include "DigitRecognizer.h"
#include "PerspectiveTransformer.h"
#include "CellsExtractor.h"
#include "preprocessing.h"

using namespace cv;
using namespace std;

// Sudoku Grid Detector
namespace sgd {
    /**
     * @brief Applies preprocessing steps to the input image to prepare it for contour detection.
     *
     *  Steps include:
     * - Grayscale conversion
     * - Gaussian blurring
     * - Adaptive thresholding
     *
     * @param input The original BGR or grayscale input image.
     * @return A binarized image with enhanced grid features for contour detection.
     */
    Mat_<uchar> preprocessing(const Mat& input);

    /**
     * Extracts the four corner points of the largest external contour in a preprocessed binary image.
     *
     * @param preprocessedImg A binary image where the largest contour
     *                        corresponds to a rectangular region (the Sudoku grid).
     * @return A vector of 4 corner points (in float precision) representing the corners of the
     *         largest detected contour. If no contour is found, the function returns an empty vector.
     *
     * @note This function assumes that the input image is already preprocessed (e.g., thresholded)
     *       and contains a clear external contour of interest. Internally, it finds the largest contour
     *       and detects its corners using ::findLargestContour and ::findCorners helpers.
     */
    vector<Point2f> getContourCorners(const Mat_<uchar>& preprocessedImg);

    /**
     * @brief Applies a perspective transformation to warp the Sudoku grid to a top-down square view.
     *
     * Steps:
     * - Compute homography using `getPerspectiveTransform()`
     * - Apply warping with `warpPerspective()` to normalize the grid
     *
     * @param preprocessed, the preprocessed image
     * @param corners, the four corners of the grid
     * @return A square, top-down binary image of the Sudoku grid.
     */
    Mat_<uchar> perspectiveTransform(const Mat_<uchar>& preprocessed, vector<Point2f> corners) ;

    /**
     * @brief Extracts rectangular cell regions from a binary Sudoku grid image.
     *
     * This function first applies a basic line correction heuristic on the input image
     * to reinforce horizontal and vertical grid lines that might be faint or broken.
     * It then segments the corrected grid into 81 equally-sized rectangular regions,
     * corresponding to the 9x9 Sudoku cell layout.
     *
     *  @param unclearSudokuGrid A binary (black and white) image of the Sudoku grid,
     *                          potentially with imperfect or missing lines.
     * @return A vector of 81 cv::Rect objects, each representing the bounding box of a Sudoku cell.
     */
    vector<Rect> extractCellRectsFromGrid( Mat_<uchar>& unclearSudokuGrid);


    /**
     * @brief Detects and recognizes the digits in each cell of the Sudoku grid.
     *
     * Best practices:
     * - Extract each cell using the coordinates
     * - Preprocess each cell (thresholding, center alignment, resizing)
     * - Apply digit classification (template matching, CNN, or trained ML model)
     *
     * @param sudokuGrid The normalized grid image.
     * @param cellsCoordinates Vector of cell bounding box coordinates.
     * @return A 9x9 matrix where each element is the detected digit (0 if empty).
     */
    Mat_<int> detectNumbers(const Mat_<uchar>& sudokuGrid, const vector<Rect>& cellRects);
}


#endif //PROJECT_V2_GRIDDETECTOR_H

