#include "Matrix.h"
#include "Vector.h"

#define EXTERN_OPERATIONS extern "C" __declspec(dllexport)


Matrix::Matrix( int _rows,  int _cols,   float**   _arr) 
{
    rows = _rows;
    cols = _cols;
    arr = _arr;
};

float Matrix::getElement(int row, int col) 
{
    if (row < rows && col < cols) {
        return arr[row][col];
    }
}

int Matrix::getRows() 
{
    return rows;
}

float* Matrix::getRow(int index)
{
    return arr[index];
}

int Matrix::getCols() 
{
    return cols;
}

EXTERN_OPERATIONS float** AddFloatMatrix( Matrix* matA, Matrix* matB, float** c) {
    for (int i{ 0 }; i < matA->getRows(); ++i) {
        for (int j{ 0 }; j < matA->getCols(); ++j) {
            c[i][j] = matA->getElement(i, j) + matB->getElement(i, j);
        }
    }
    return c;
}

EXTERN_OPERATIONS float** SubFloatMatrix( Matrix* a,  Matrix* b, float** c) {
    for (int i{ 0 }; i < a->getRows(); ++i) {
        for (int j{ 0 }; j < a->getCols(); ++j) {
            c[i][j] = a->getElement(i, j) - b->getElement(i, j);
        }
    }
    return c;
}

EXTERN_OPERATIONS float** MultiplyMatrixWithScalar( Matrix* matA, float scalar, float** c) {
    for (int i{ 0 }; i < matA->getRows(); ++i) {
        for (int j{ 0 }; j < matA->getCols(); ++j) {
            c[i][j] = matA->getElement(i, j) * scalar;
        }
    }
    return c;
}

EXTERN_OPERATIONS float** DivideMatrixWithScalar( Matrix* matA, float scalar, float** c) {
    for (int i{ 0 }; i < matA->getRows(); ++i) {
        for (int j{ 0 }; j < matA->getCols(); ++j) {
            c[i][j] = matA->getElement(i, j) / scalar;
        }
    }
    return c;
}


EXTERN_OPERATIONS float* MultiplyMatrixVector( Matrix* mat,  Vector* vec, float* c) {
    if (mat->getCols() != vec->getSize()) {
        throw "Not matching size";
    }
    for (int i{ 0 }; i < mat->getRows(); ++i) {
        float vecElement = vec->getElement(i);
        float sum = 0;
        for (int j{ 0 }; j < mat->getCols(); ++j) {
            sum += mat->getElement(i, j) * vecElement;
        }
        c[i] = sum;
    }
    return c;
}

float sum(const float* a, const float* b, int len) {
    float element = 0;
    for (int i{ 0 }; i < len; ++i) {
        element += a[i] * b[i];
    }
    return element;
}

EXTERN_OPERATIONS float** MultiplyMatrixMatrix( Matrix* matA,  Matrix* matB, float** c) {
    if (matA->getRows() != matB->getCols() || matA->getCols() != matB->getRows()) {
        throw "Not matching size";
    }
    int len = matA->getRows();
    for (int i{ 0 }; i < matA->getRows(); ++i) { 
        const float* oneRowA = matA->getRow(i);
        for (int j{ 0 }; j < matB->getCols(); ++j) {           
            const float* oneColB = matB->getRow(j);
            c[i][j] = sum(oneRowA, oneColB, len);
        }
    }
    return c;
}

extern "C"
{
    __declspec(dllexport) Matrix* MatrixNew( int rows,  int cols,  float** const arr) { return new Matrix(rows, cols, arr); }
    __declspec(dllexport)  float  MatrixGetElement(Matrix* mat, int row, int col) { return mat->getElement(row, col); }
    __declspec(dllexport)  int  MatrixGetRows(Matrix* mat) { return mat->getRows(); }
    __declspec(dllexport)  float* MatrixGetRow(Matrix* mat, int index) { return mat->getRow(index); }
    __declspec(dllexport)  int  MatrixGetCols(Matrix* mat) { return mat->getCols(); }
}



