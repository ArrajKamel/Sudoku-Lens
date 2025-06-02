//
// Created by kamel arraj on 02.06.2025.
//

#include "include/CellsExtractor.h"

Mat_<uchar> simpleLinesCorrection(const Mat_<uchar>& unclearSudokuGrid){
    Mat_<uchar> correctedSudokuGrid = unclearSudokuGrid.clone();
    for(int i =0 ; i < unclearSudokuGrid.rows; i++) {
        int whiteCounter = 0;
        for (int j = 0; j < unclearSudokuGrid.cols; j++) {
            if (unclearSudokuGrid(i, j) == 255)
                whiteCounter++;
        }
        if (whiteCounter > unclearSudokuGrid.cols / 5) {
            for (int j = 0; j < unclearSudokuGrid.cols; j++) {
                correctedSudokuGrid(i, j) = 255;
            }
        }
    }


    for(int j =0 ; j < unclearSudokuGrid.cols; j++) {
        int whiteCounter = 0;
        for (int i = 0; i < unclearSudokuGrid.rows; i++) {
            if (unclearSudokuGrid(i, j) == 255)
                whiteCounter++;
        }
        if (whiteCounter > unclearSudokuGrid.rows / 3) {
            for (int i = 0; i < unclearSudokuGrid.rows; i++) {
                correctedSudokuGrid(i, j) = 255;
            }
        }
    }



    return correctedSudokuGrid;

}

vector<Rect> extractCells(const Mat_<uchar>& correctedSudokuGrid){
    vector<Rect> cellRects;
    int cellSizeX = correctedSudokuGrid.cols / 9;
    int cellSizeY = correctedSudokuGrid.rows / 9;

    for (int row = 0; row < 9; ++row) {
        for (int col = 0; col < 9; ++col) {
            int x = col * cellSizeX;
            int y = row * cellSizeY;
            cellRects.emplace_back(x, y, cellSizeX, cellSizeY);
        }
    }


    return cellRects;
}
