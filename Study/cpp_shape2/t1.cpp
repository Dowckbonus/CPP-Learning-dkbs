#include "shapeManage.h"
using namespace std;

int main()
{
    shapeManage objClient;
    int shapeNum;
    SHAPENAME shapeType = SHAPE_NULL;
    //
    cout << "请输入图形数目" << endl;
    cin >> shapeNum;
    for (int num = 0; num < shapeNum; num++)
    {
        cout << "请输入图形类型对应数字\n(1 - TRIANGLE, \n 2 - RECTANGLE, 3 - CIRCLE, \n 4 - ELLIPSE, 5 - POLYGON)" << endl;
        cin >> shapeType;
        switch (shapeType)
        {
        case SHAPE_TRIANGLE:
        {
            Shape *ptri = new Triangle;
            Point2d pt;
            dyArr<Point2d> pointArr(10);
            for (int i = 0; i < 3; i++)
            {
                int x, y;
                cout << "输入第" << i + 1 << "个点的坐标，空格隔开" << endl;
                cin >> x >> y;
                pt.setPos(x, y);
                pointArr.pushback(pt);
            }
            cout << "第" << num + 1 << "个图形输入完毕" << endl;
            ptri->setAllPt(pointArr);
            //
            objClient.addShape(ptri);
            break;
        }
        case SHAPE_RECTANGLE:
        {
            Shape *ptri = new Rectangle;
            Point2d pt;
            dyArr<Point2d> pointArr(10);

            int x, y;
            cout << "输入左下角点的坐标，空格隔开" << endl;
            cin >> x >> y;
            pt.setPos(x, y);
            pointArr.pushback(pt);
            cout << "输入长和宽，空格隔开" << endl;
            cin >> x >> y;
            ptri->setLS(x, y);

            cout << "第" << num + 1 << "个图形输入完毕" << endl;
            ptri->setAllPt(pointArr);
            //
            objClient.addShape(ptri);
            break;
        }
        case SHAPE_CIRCLE:
        {
            Shape *ptri = new Circle;
            Point2d pt;
            dyArr<Point2d> pointArr(10);

            int x, y;
            cout << "输入圆心的坐标，空格隔开" << endl;
            cin >> x >> y;
            pt.setPos(x, y);
            pointArr.pushback(pt);
            cout << "输入半径" << endl;
            cin >> x;
            ptri->setLS(x);

            cout << "第" << num + 1 << "个图形输入完毕" << endl;
            ptri->setAllPt(pointArr);
            //
            objClient.addShape(ptri);
            break;
        }
        case SHAPE_ELLIPSE:
        {
            Shape *ptri = new Ellipse;
            Point2d pt;
            dyArr<Point2d> pointArr(10);

            int x, y;
            cout << "输入圆心的坐标，空格隔开" << endl;
            cin >> x >> y;
            pt.setPos(x, y);
            pointArr.pushback(pt);
            cout << "输入短轴和长轴，空格隔开" << endl;
            cin >> x >> y;
            ptri->setLS(x, y);

            cout << "第" << num + 1 << "个图形输入完毕" << endl;
            ptri->setAllPt(pointArr);
            //
            objClient.addShape(ptri);
            break;
        }
        case SHAPE_POLYGON:
        {
            Shape *ptri = new Polygon;
            Point2d pt;
            int sides = 0;
            cout << "请输入多边形边数" << endl;
            cin >> sides;
            dyArr<Point2d> pointArr(10);
            for (int i = 0; i < sides; i++)
            {
                int x, y;
                cout << "输入第" << i + 1 << "个点的坐标，空格隔开" << endl;
                cin >> x >> y;
                pt.setPos(x, y);
                pointArr.pushback(pt);
            }
            cout << "第" << num + 1 << "个图形输入完毕" << endl;
            ptri->setAllPt(pointArr);
            //
            objClient.addShape(ptri);
            break;
        }
        default:
        {
            cout << "输入错误，请重试" << endl;
            break;
        }
        }
    }
    objClient.calAllShapeArea();
    objClient.calAllShapeGirth();
    Shape *ptemp = objClient.findShape(0);
    //ptemp->printData();
    cout << "第1个图形类型为：";
    SHAPENAME type = ptemp->getShapeName();
    switch (type)
    {
    case SHAPE_NULL:
    {
        cout << "无类型" << endl;
        break;
    }
    case SHAPE_TRIANGLE:
    {
        cout << "三角形" << endl;
        break;
    }
    case SHAPE_RECTANGLE:
    {
        cout << "矩形" << endl;
        break;
    }
    case SHAPE_CIRCLE:
    {
        cout << "圆形" << endl;
        break;
    }
    case SHAPE_ELLIPSE:
    {
        cout << "椭圆形" << endl;
        break;
    }
    case SHAPE_POLYGON:
    {
        cout << "多边形" << endl;
        break;
    }
    }
    return 0;
}