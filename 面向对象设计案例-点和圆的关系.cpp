#include <iostream>

using namespace std;

//点类
class Point
{
public:
    void setX(int x)
    {
        m_X = x;
    }
    void setY(int y)
    {
        m_Y = y;
    }
    int getX()
    {
        return m_X;
    }
    int getY()
    {
        return m_Y;
    }

private:
    int m_X;
    int m_Y;
};

//圆类
class Circle
{
public:
    //设置半径
    void setR(int r)
    {
        m_R = r;
    }

    //获取半径
    int getR()
    {
        return m_R;
    }

    //设置圆心
    void setCenter(Point p)
    {
        m_Center = p;
    }

    //获取圆心
    Point getCenter()
    {
        return m_Center;
    }


    //利用成员函数判断点和圆的关系
private:
    int m_R;        //半径
    Point m_Center; //圆心
};

void isInCircle(Circle &c, Point &p)
{
    int distance = (c.getCenter().getX() - p.getX()) * (c.getCenter().getX() - p.getX()) + (c.getCenter().getY() - p.getY()) * (c.getCenter().getY() - p.getY());
    int rDistance = c.getR() * c.getR();

    if (distance == rDistance)
    {
        cout << "点在圆上" << endl;
    }
    else if (distance < rDistance)
    {
        cout << "点在圆内" << endl;
    }
    else
    {
        cout << "点在圆外" << endl;
    }
}

void test01()
{
    Point p1;
    p1.setX(10);
    p1.setY(11);

    Circle c1;
    Point center;
    center.setX(10);
    center.setY(0);
    c1.setCenter(center);
    c1.setR(10);

    //利用全局函数判断点和圆之间的关系
    isInCircle(c1, p1);
}

int main()
{
    test01();
    return 0;
}