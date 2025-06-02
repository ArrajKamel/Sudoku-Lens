//
// Created by kamel arraj on 01.06.2025.
//

#include "include/preprocessing.h"

vector<double> generateGaussianKernel1D(int ksize, double sigma) {
    vector<double> kernel(ksize);
    int half = ksize / 2;
    double sum = 0.0;

    for (int i = 0; i < ksize; ++i) {
        int x = i - half;
        kernel[i] = exp(-(x * x) / (2 * sigma * sigma));
        sum += kernel[i];
    }

    // Normalize
    for (int i = 0; i < ksize; ++i)
        kernel[i] /= sum;

    return kernel;
}

Mat_<uchar> myGaussianBlur(const Mat_<uchar>& src, int ksize, double sigma) {
    Mat_<uchar> tmp(src.rows, src.cols);
    Mat_<uchar> dst(src.rows, src.cols);
    vector<double> kernel = generateGaussianKernel1D(ksize, sigma);
    int half = ksize / 2;

    // Horizontal pass
    for (int i = 0; i < src.rows; ++i) {
        for (int j = 0; j < src.cols; ++j) {
            double sum = 0.0;
            for (int k = -half; k <= half; ++k) {
                int jj = min(max(j + k, 0), src.cols - 1);
                sum += kernel[k + half] * src(i, jj);
            }
            tmp(i, j) = static_cast<uchar>(sum);
        }
    }

    // Vertical pass
    for (int i = 0; i < src.rows; ++i) {
        for (int j = 0; j < src.cols; ++j) {
            double sum = 0.0;
            for (int k = -half; k <= half; ++k) {
                int ii = min(max(i + k, 0), src.rows - 1);
                sum += kernel[k + half] * tmp(ii, j);
            }
            dst(i, j) = static_cast<uchar>(sum);
        }
    }

    return dst;
}


Mat_<uchar> myAdaptiveThreshold(const Mat_<uchar>& src, int blockSize, int C) {
    int half = blockSize / 2;
    Mat_<uchar> dst(src.rows, src.cols, uchar(0));

    for (int i = 0; i < src.rows; ++i) {
        for (int j = 0; j < src.cols; ++j) {
            int sum = 0;
            int count = 0;

            // Local window mean
            for (int m = -half; m <= half; ++m) {
                for (int n = -half; n <= half; ++n) {
                    int y = min(max(i + m, 0), src.rows - 1);
                    int x = min(max(j + n, 0), src.cols - 1);
                    sum += src(y, x);
                    ++count;
                }
            }

            int mean = sum / count;
            dst(i, j) = (src(i, j) < (mean - C)) ? 255 : 0;
        }
    }

    return dst;
}

