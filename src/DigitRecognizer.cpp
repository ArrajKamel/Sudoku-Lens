//
// Created by kamel arraj on 02.06.2025.
//

#include "include/DigitRecognizer.h"
#include <vector>

bool DigitRecognizer::loadModel(const std::string& modelPath) {
    knn = ml::KNearest::load(modelPath);
    return knn != nullptr;
}

int DigitRecognizer::recognize(const Mat& cellImage) {
    Mat processed = preprocessCell(cellImage);

    // Check if cell is empty
    double meanVal = mean(processed)[0];
    if (meanVal > 240) return -1; // likely empty

    // Resize to 20x20 for input
    Mat resized;
    resize(processed, resized, Size(20, 20));
    resized = resized.reshape(1, 1); // flatten
    resized.convertTo(resized, CV_32F);

    Mat result;
    knn->findNearest(resized, 3, result);
    return static_cast<int>(result.at<float>(0));
}

Mat DigitRecognizer::preprocessCell(const Mat& cell){
    Mat cleaned = cell.clone();

    // Assume cell is already binary with white digits on black background (or inverted)
    // Step 1: Remove small noise (white spots)
//    morphologyEx(cell, cleaned, MORPH_OPEN, Mat(), Point(-1, -1), 1);
//
//    // Step 2: Fill small gaps inside digits (optional)
//    morphologyEx(cleaned, cleaned, MORPH_CLOSE, Mat(), Point(-1, -1), 1);
//

    // Step 3: Find contours to isolate the largest blob (digit)
    vector<vector<Point>> contours;
    findContours(cleaned.clone(), contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
    cout << contours.size()<< endl ;
    imshow("test", cleaned);
    if (!contours.empty()) {
        // Find largest contour by area
        size_t maxIdx = 0;
        size_t secondMaxIdx = maxIdx;

        double maxArea = 0;
        for (size_t i = 0; i < contours.size(); ++i) {
            double area = contourArea(contours[i]);
            if (area > maxArea) {
                maxArea = area;
                secondMaxIdx = maxIdx;
                maxIdx = i;
            }
        }

        // Create blank image
        Mat digitOnly = Mat::zeros(cleaned.size(), cleaned.type());

        // Draw largest contour filled in white
//        drawContours(digitOnly, contours, (int)secondMaxIdx, Scalar(255), FILLED);
        for(auto p: contours.at(maxIdx))
            digitOnly.at<uchar>(p.y, p.x) = 255;

        imshow("only digit", digitOnly);
//        // Optional: Center the digit by cropping bounding rect and placing in center of 20x20
//        Rect bbox = boundingRect(contours[maxIdx]);
//        Mat digitCropped = digitOnly(bbox);
//
//        Mat centered = Mat::zeros(20, 20, cleaned.type());
//        int offsetX = (20 - bbox.width) / 2;
//        int offsetY = (20 - bbox.height) / 2;
//
//        digitCropped.copyTo(centered(Rect(offsetX, offsetY, bbox.width, bbox.height)));
//
//        imshow("cell", centered);
        return digitOnly;
    }

    // If no contours found, return cleaned image as is
    return cleaned;
}
