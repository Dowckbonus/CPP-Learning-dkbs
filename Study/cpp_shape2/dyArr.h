#ifndef DYARR_H_INCLUDED
#define DYARR_H_INCLUDED

#include <iostream>
#include <string>

using namespace std;

template <class T>
class dyArr
{
private:
    T *_pa = nullptr;
    int _len = 0;
    int _capacity = 0;

public:
    dyArr() {}
    //设置capacity
    dyArr(int capacity)
    {
        this->_capacity = capacity;
        this->_pa = new T[_capacity];
        this->_len = 0;
    }

    //初始化
    dyArr(int len, T value)
    {
        this->_len = len;
        this->_capacity = len * 2;
        this->_pa = new T[this->_capacity];
        for (int i = 0; i < len; i++)
        {
            _pa[i] = value;
        }
    }
    //用数组初始化
    dyArr(T *pa, int len)
    {
        this->_len = len;
        this->_capacity = len * 2;
        this->_pa = new T[this->_capacity];
        for (int i = 0; i < len; i++)
        {
            _pa[i] = pa[i];
        }
    }

    //拷贝构造
    dyArr(const dyArr &da)
    {
        this->_len = da.getLen();
        this->_capacity = da.getCap();
        this->_pa = new T[this->_capacity];
        for (int i = 0; i < da.getLen(); i++)
        {
            _pa[i] = da.getPa()[i];
        }
    }

    ~dyArr()
    {
        while (_pa != nullptr)
        {
            delete[] _pa;
            _pa = nullptr;
        }
    }

    //赋值运算符重载
    dyArr &operator=(const dyArr &obj)
    {
        if (this->_pa == obj._pa)
        {
            return *this;
        }
        if (this->_pa)
        {
            delete[] this->_pa;
            this->_pa = nullptr;
        }
        this->_len = obj.getLen();
        this->_capacity = obj.getCap();
        this->_pa = new T[this->_capacity];
        for (int i = 0; i < obj.getLen(); i++)
        {
            _pa[i] = obj.getPa()[i];
        }
        return *this;
    }

    T &operator[](int pos)
    {
        if (pos >= 0 && pos < this->_len)
        {
            return this->_pa[pos];
        }
        else
        {
            throw "错误：不可读取的位置";
        }
    }

    T *getPa() const
    {
        return this->_pa;
    }

    int getLen() const
    {
        return this->_len;
    }

    int getCap() const
    {
        return this->_capacity;
    }

    //改变capacity
    void reSize(int ncap)
    {
        T *pa = new T[ncap];
        for (int i = 0; i < this->_len; i++)
        {
            pa[i] = this->_pa[i];
        }
        while (this->_pa != nullptr)
        {
            delete[] this->_pa;
            this->_pa = nullptr;
        }
        this->_pa = pa;
        this->_capacity = ncap;
    }

    void allPrint()
    {
        for (int i = 0; i < this->_len; i++)
        {
            cout << _pa[i] << " ";
        }
        cout << endl;
    }

    //在指定位置前插入元素
    void insertArr(int pos, T &value)
    {
        this->_len += 1;
        if (this->_len >= this->_capacity)
        {
            reSize(this->_capacity * 2);
        }
        if (pos >= this->_len - 1)
        {
            this->_pa[this->_len] = value;
        }
        else
        {
            for (int i = this->_len - 2; i > pos - 1; i--)
            {
                this->_pa[i + 1] = this->_pa[i];
            }
            this->_pa[pos] = value;
        }
    }

    void pushback(T &value)
    {
        if (this->_capacity <= 10)
        {
            reSize(this->_capacity = 10);
        }
        this->_pa[this->_len] = value;
        this->_len += 1;
        if (this->_len >= this->_capacity)
        {
            reSize(this->_capacity * 2);
        }
    }

    //删除指定位置元素
    void delArr(int pos)
    {
        this->_len -= 1;
        for (int i = pos; i < this->_len + 1; i++)
        {
            _pa[i] = _pa[i + 1];
        }
    }
};

#endif