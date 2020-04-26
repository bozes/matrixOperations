#pragma once
#ifndef MATRIX_H
#define MATRIX_H
class Matrix
{
private:
     float**  arr;
     int rows;
     int cols;
public:
    Matrix(int rows, int cols, float** arr);
    float getElement(int row, int col);
    int getRows();
    float* getRow(int index);
    int getCols();
};

#endif

