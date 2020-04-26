#pragma once
#ifndef VECTOR_H
#define VECTOR_H

class Vector
{
private:
    float* arr;
    int size;
public:
     Vector(int _size, float* _arr);
     float getElement(int index);
     int getSize();
};

#endif
