#ifndef SHAPECAL_H_INCLUDED
#define SHAPECAL_H_INCLUDED

#include "dyArr.h"
#include <cmath>
#define PI 3.1415926

using namespace std;

enum SHAPENAME
{
    SHAPE_NULL = 0,
    SHAPE_TRIANGLE,
    SHAPE_RECTANGLE,
    SHAPE_CIRCLE,
    SHAPE_ELLIPSE,
    SHAPE_POLYGON
};

istream &operator>>(istream &in, SHAPENAME &type)
{
    int n;
    in >> n;
    type = SHAPENAME(n);
    return in;
}

//
struct Point2d
{
    float _x = 0;
    float _y = 0;
    Point2d() : _x(0), _y(0) {}
    Point2d(float x, float y) : _x(x), _y(y) {}
    void setPos(float x, float y)
    {
        this->_x = x;
        this->_y = y;
    }
};

//基类
class Shape
{
protected:
    float _girth = 0;
    float _area = 0;

public:
    Shape() {}
    virtual ~Shape() {}
    virtual float calGirth() = 0;
    virtual float calArea() = 0;
    virtual SHAPENAME getShapeName() { return SHAPE_NULL; }
    virtual void printData()
    {
        cout << "Girth is " << _girth << "\nArea is " << _area << endl;
    }
    virtual void setAllPt(dyArr<Point2d> &pointArr) = 0;
    virtual void setLS(float height, float width = 0) = 0;
};

//多边形
class Polygon : public Shape
{
protected:
    dyArr<Point2d> _pointArr;
    int _N;

public:
    Polygon() {}
    //按坐标构造
    Polygon(dyArr<Point2d> &pointArr) : _pointArr(pointArr), _N(pointArr.getLen())
    {
    }

    //
    virtual float calGirth()
    {
        _girth = sqrt(pow(_pointArr[_N - 1]._x - _pointArr[0]._x, 2) + pow((_pointArr[_N - 1]._y - _pointArr[0]._y), 2));
        for (int i = 0; i < _N - 1; i++)
        {
            _girth += sqrt(pow((_pointArr[i]._x - _pointArr[i + 1]._x), 2) + pow((_pointArr[i]._y - _pointArr[i + 1]._y), 2));
        }
        return _girth;
    }

    virtual float calArea()
    {
        for (int i = 0; i < _N; i++)
        {
            int j = (i + 1) % _N;
            _area += _pointArr[i]._x * _pointArr[j]._y;
            _area -= _pointArr[i]._y * _pointArr[j]._x;
        }
        _area /= 2;
        return _area = (_area < 0 ? -_area : _area);
    }

    virtual SHAPENAME getShapeName() { return SHAPE_POLYGON; }

    virtual void setAllPt(dyArr<Point2d> &pointArr)
    {
        _pointArr = pointArr;
    }
    virtual void setLS(float height, float width = 0){}
};

//圆
class Circle : public Shape
{
protected:
    Point2d _center;
    float _r = 0;

public:
    Circle() {}
    Circle(float r) : _r(r) {}
    virtual float calGirth()
    {
        _girth = (PI * 2 * this->_r);
        return _girth;
    }
    virtual float calArea()
    {
        _area = (PI * this->_r * this->_r);
        return _area;
    }
    virtual void setAllPt(dyArr<Point2d> &pointArr)
    {
        _center = pointArr[0];
    }
    virtual void setLS(float height, float width = 0)
    {
        _r = height;
    }
};

//椭圆
class Ellipse : public Shape
{
protected:
    Point2d _center;
    float _sr = 0;
    float _lr = 0;

public:
    Ellipse() {}
    Ellipse(float sr, float lr) : _sr(sr), _lr(lr) {}
    virtual float calGirth()
    {
        _girth = PI * (1.5 * (_lr + _sr) - sqrt(_lr * _sr));
        return _girth;
    }
    virtual float calArea()
    {
        _area = (PI * this->_sr * this->_lr);
        return _area;
    }

    virtual SHAPENAME getShapeName() { return SHAPE_ELLIPSE; }
    virtual void setAllPt(dyArr<Point2d> &pointArr)
    {
        _center = pointArr[0];
    }
    virtual void setLS(float height, float width = 0)
    {
        _sr = height;
        _lr = width;
    }
};

//正三角形
class Triangle : public Shape
{
protected:
    Point2d _A;
    Point2d _B;
    Point2d _C;

public:
    Triangle() {}
    virtual float calGirth()
    {
        _girth += sqrt(pow((_A._x) - (_B._x), 2) + pow((_A._y) - (_B._y), 2));
        _girth += sqrt(pow((_A._x) - (_C._x), 2) + pow((_A._y) - (_C._y), 2));
        _girth += sqrt(pow((_B._x) - (_C._x), 2) + pow((_B._y) - (_C._y), 2));
        return _girth;
    }
    virtual float calArea()
    {
        _area = (((_A._x * _B._y) - (_B._x * _A._y)) + ((_B._x * _C._y) - (_C._x * _B._y)) + ((_C._x * _A._y) - (_A._x * _C._y))) * 0.5;
        return _area = (_area > 0 ? _area : -_area);
    }
    virtual SHAPENAME getShapeName() { return SHAPE_TRIANGLE; }
    virtual void setAllPt(dyArr<Point2d> &pointArr)
    {
        _A = pointArr[0];
        _B = pointArr[1];
        _C = pointArr[2];
    }
    virtual void setLS(float height, float width = 0){}
};

//矩形
class Rectangle : public Shape
{
protected:
    float _height = 0;
    float _width = 0;
    Point2d _LBpoint;

public:
    Rectangle() {}
    Rectangle(float height, float width) : _height(height), _width(width) {}
    virtual float calGirth()
    {
        _girth = (_width + _height) * 2;
        return _girth;
    }
    virtual float calArea()
    {
        _area = _width * _height;
        return _area;
    }
    virtual SHAPENAME getShapeName() { return SHAPE_RECTANGLE; }
    
    //设置左下角点
    virtual void setAllPt(dyArr<Point2d> &pointArr)
    {
        _LBpoint = pointArr[0];
    }
    void setLS(float height, float width = 0)
    {
        _height = height;
        _width = width;
    }
};

#endif