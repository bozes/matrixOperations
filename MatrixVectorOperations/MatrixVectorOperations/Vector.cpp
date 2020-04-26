#include "Vector.h"
#include <array>

#define EXTERN_OPERATIONS extern "C" __declspec(dllexport)

Vector::Vector(int _size, float* _arr)
{
    size = _size ;
    arr = _arr ;
}

float Vector::getElement(int index)
{
    if (index < size) {
        return arr[index];
    }
}

int Vector::getSize()
{
    return size;
}




EXTERN_OPERATIONS float* AddFloatVector( Vector* a,  Vector* b, float* c) {
    for (int i{ 0 }; i < a->getSize(); ++i) {
        c[i] = a->getElement(i) + b->getElement(i);
    }
    return 0;
}

EXTERN_OPERATIONS float* SubFloatVector( Vector* a,  Vector* b, float* c) {
    for (int i{ 0 }; i < a->getSize(); ++i) {
        c[i] = a->getElement(i) - b->getElement(i);
    }
    return 0;
}

EXTERN_OPERATIONS float* MultiplyVectorWithScalar( Vector* a, float scalar, float* c) {
    for (int i{ 0 }; i < a->getSize(); ++i) {
        c[i] = a->getElement(i) * scalar;
    }
    return 0;
}

EXTERN_OPERATIONS float* DivideVectorWithScalar( Vector* a, float scalar, float* c) {
    for (int i{ 0 }; i < a->getSize(); ++i) {
        c[i] = a->getElement(i) / scalar;
    }
    return 0;
}


extern "C"
{
    __declspec(dllexport) Vector* VectorNew( int size,  float*  arr) { return new Vector(size, arr); }
    __declspec(dllexport)  float  VectorGetElement(Vector* vec, int index) { return vec->getElement(index); }
    __declspec(dllexport)  int  VectorGetSize(Vector* vec) { return vec->getSize(); }

}
