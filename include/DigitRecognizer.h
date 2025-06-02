//
// Created by kamel arraj on 02.06.2025.
//

#ifndef PROJECT_V2_DIGITRECOGNIZER_H
#define PROJECT_V2_DIGITRECOGNIZER_H


#include <opencv2/opencv.hpp>
#include <opencv2/ml.hpp>

using namespace cv;
using namespace std;

class DigitRecognizer {
public:
    bool loadModel(const std::string& modelPath);
    int recognize(const Mat& cellImage); // Returns 0–9, or -1 if empty
    static Mat preprocessCell(const Mat& cell) ;
private:
    Ptr<ml::KNearest> knn;
};

#endif //PROJECT_V2_DIGITRECOGNIZER_H
