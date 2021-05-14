#include <iostream>

using namespace std;

//����
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

//Բ��
class Circle
{
public:
    //���ð뾶
    void setR(int r)
    {
        m_R = r;
    }

    //��ȡ�뾶
    int getR()
    {
        return m_R;
    }

    //����Բ��
    void setCenter(Point p)
    {
        m_Center = p;
    }

    //��ȡԲ��
    Point getCenter()
    {
        return m_Center;
    }


    //���ó�Ա�����жϵ��Բ�Ĺ�ϵ
private:
    int m_R;        //�뾶
    Point m_Center; //Բ��
};

void isInCircle(Circle &c, Point &p)
{
    int distance = (c.getCenter().getX() - p.getX()) * (c.getCenter().getX() - p.getX()) + (c.getCenter().getY() - p.getY()) * (c.getCenter().getY() - p.getY());
    int rDistance = c.getR() * c.getR();

    if (distance == rDistance)
    {
        cout << "����Բ��" << endl;
    }
    else if (distance < rDistance)
    {
        cout << "����Բ��" << endl;
    }
    else
    {
        cout << "����Բ��" << endl;
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

    //����ȫ�ֺ����жϵ��Բ֮��Ĺ�ϵ
    isInCircle(c1, p1);
}

int main()
{
    test01();
    return 0;
}