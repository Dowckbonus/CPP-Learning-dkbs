#include <cstring>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#define FILENAME "stulist.dat"
#define FILENAME2 "stulist_b.dat"

using namespace std;

//学生类
class Student
{
private:
    int64_t _ID = 20191000000;
    char _name[64] = "";
    int _age = 0;
    double _GPA = 0;

public:
    Student() {}
    Student(int64_t id, string name, int age, double gpa) : _ID(id), _age(age), _GPA(gpa)
    {
        for (int i = 0; i < (int)name.size(); i++)
        {
            _name[i] = name[i];
        }
    }
    Student &operator=(const Student &stu)
    {
        _ID = stu._ID;
        _age = stu._age;
        _GPA = stu._GPA;
        strcpy(_name, "");
        for (int i = 0; i < (int)sizeof(stu._name); i++)
        {
            _name[i] = stu._name[i];
        }
        return *this;
    }

    int64_t getid()
    {
        return _ID;
    }
    char *getname()
    {
        return _name;
    }
    int getage()
    {
        return _age;
    }
    double getgpa()
    {
        return _GPA;
    }
};

//排序方式
using PFCMP = bool (*)(Student &, Student &);

bool cmpGPA(Student &obj1, Student &obj2)
{
    return (obj1.getgpa() > obj2.getgpa()) ? true : false;
}

bool cmpAge(Student &obj1, Student &obj2)
{
    return (obj1.getage() > obj2.getage()) ? true : false;
}

bool cmpID(Student &obj1, Student &obj2)
{
    return (obj1.getid() > obj2.getid()) ? true : false;
}

//保存文本文件
void saveTxt(vector<Student> &v)
{
    ofstream ofs(FILENAME, ios::out | ios::trunc);
    for (int i = 0; i < (int)v.size(); i++)
    {
        ofs << v[i].getid() << '#' << v[i].getname() << '#' << v[i].getage() << '#' << v[i].getgpa() << endl;
    }
    ofs.close();
}

//保存二进制文件
void saveBinary(vector<Student> &v)
{
    ofstream ofs(FILENAME2, ios::out | ios::binary | ios::trunc);
    for (int i = 0; i < (int)v.size(); i++)
    {
        ofs.write((const char *)&v[i], sizeof(v[i]));
    }
    ofs.close();
}

//读取文本文件
vector<Student> readTxt(vector<Student> &v)
{
    ifstream ifs(FILENAME, ios::in);
    if (!ifs.is_open())
    {
        cout << "文件打开失败" << endl;
        return v;
    }
    string buf, temp;
    char delim = '#';
    cout << "文本文件读取" << endl;
    while (getline(ifs, buf))
    {
        int64_t id;
        string name;
        int age;
        float gpa;
        //分割字符串
        istringstream iss(buf);
        vector<string> result;
        while ((getline(iss, temp, delim)))
        {
            result.emplace_back(move(temp));
        }
        {
            istringstream iss2(result[0]);
            iss2 >> id;
        }
        {
            istringstream iss2(result[1]);
            iss2 >> name;
        }
        {
            istringstream iss2(result[2]);
            iss2 >> age;
        }
        {
            istringstream iss2(result[3]);
            iss2 >> gpa;
        }
        cout << "学号：" << id << " 姓名：" << name << " 年龄：" << age << " 绩点：" << gpa << endl;
        Student stu(id, name, age, gpa);
        v.push_back(stu);
    }
    cout << "文本文件读取完毕" << endl;
    ifs.close();
    return v;
}

//读取二进制文件
vector<Student> readBinary(vector<Student> &v)
{
    Student stu;
    ifstream ifs(FILENAME2, ios::in | ios::binary);
    if (!ifs.is_open())
    {
        cout << "文件打开失败" << endl;
        return v;
    }
    cout << "二进制文件读取" << endl;
    while (ifs.read((char *)&stu, sizeof(stu)))
    {
        v.push_back(stu);
        cout << "学号：" << stu.getid() << " 姓名：" << stu.getname() << " 年龄：" << stu.getage() << " 绩点：" << stu.getgpa() << endl;
    }
    cout << "二进制文件读取完成" << endl;
    ifs.close();
    return v;
}

//排序
void sortStu(vector<Student> &v, PFCMP pf)
{
    for (int i = 0; i < (int)v.size() - 1; i++)
    {
        for (int j = 0; j < (int)v.size() - i - 1; j++)
        {
            if (pf(v[j], v[j + 1]))
            {
                Student temp = v[j];
                v[j] = v[j + 1];
                v[j + 1] = temp;
            }
        }
    }
}

//打印信息
void printAll(vector<Student> &v)
{
    for (vector<Student>::iterator it = v.begin(); it != v.end(); it++)
    {
        cout << "学号：" << it->getid() << " 姓名：" << it->getname() << " 年龄：" << it->getage() << " 绩点：" << it->getgpa() << endl;
    }
    cout << endl;
}

void test01(vector<Student> &vstu)
{
    int64_t id;
    string name;
    int age;
    float gpa;
    int num = 0;
    cout << "请输入学生个数" << endl;
    cin >> num;
    for (int i = 0; i < num; i++)
    {
        cout << "请输入第" << i + 1 << "个学生信息（ID NAME AGE GPA）" << endl;
        cin >> id >> name >> age >> gpa;
        Student stu(id, name, age, gpa);
        vstu.push_back(stu);
    }
    saveTxt(vstu);
    saveBinary(vstu);
}

int main()
{
    vector<Student> vstu;
    test01(vstu);
    vstu.clear();
    cout << endl;
    if (vstu.empty())
    {
        readTxt(vstu);
        vstu.clear();
        cout << endl;
        readBinary(vstu);
    }
    cout << "\n按绩点排序" << endl;
    sortStu(vstu, cmpGPA);
    printAll(vstu);
    cout << "\n按年龄排序" << endl;
    sortStu(vstu, cmpAge);
    printAll(vstu);
    cout << "\n按学号排序" << endl;
    sortStu(vstu, cmpID);
    printAll(vstu);
    //保存
    saveTxt(vstu);
    saveBinary(vstu);
    return 0;
}

/*示例输入
3
20191001111 aaa 12 3.9
20191003333 bbb 14 2.3
20191002222 ccc 13 3.4

*/