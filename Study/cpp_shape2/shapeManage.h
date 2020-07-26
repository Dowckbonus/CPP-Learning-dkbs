#ifndef SHAPEMANAGE_H_INCLUDED
#define SHAPEMANAGE_H_INCLUDED

#include "shapeCal.h"

class shapeManage
{
private:
    dyArr<Shape *> _ShapeArray;
    float _girthSum = 0;
    float _areaSum = 0;

public:
    shapeManage() {}
    ~shapeManage()
    {
        for (int i = 0; i < _ShapeArray.getLen(); i++)
        {   
            if(_ShapeArray[i] != nullptr){
                delete _ShapeArray[i];
                _ShapeArray[i] = nullptr;
            }
        }
    }
    float calAllShapeGirth()
    {
        for (int i = 0; i < _ShapeArray.getLen(); i++)
        {
            _girthSum += _ShapeArray[i]->calGirth();
        }
        return _girthSum;
    }

    float calAllShapeArea()
    {
        for (int i = 0; i < _ShapeArray.getLen(); i++)
        {
            _areaSum += _ShapeArray[i]->calArea();
        }
        return _areaSum;
    }

    void addShape(Shape *shape)
    {
        _ShapeArray.pushback(shape);
    }
    Shape *findShape(int n)
    {
        return _ShapeArray[n];
    }
};

#endif