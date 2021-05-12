#include <iostream>

using namespace std;

class Cube
{
public:
    //设置长
    void setL(int l)
    {
        m_L = l;
    }
    //获取长
    int getL() const//表示这个函数是不会改变类的成员变量
    {
        return m_L;
    }

    //设置高
    void setH(int h)
    {
        m_H = h;
    }
    //获取高
    int getH() const
    {
        return m_H;
    }

    //设置宽
    void setW(int w)
    {
        m_W = w;
    }
    //获取宽
    int getW() const
    {
        return m_W;
    }

    //求立方体的面积
    void getCubeS() const
    {
        cout << "立方体的面积：" << 2 * m_L * m_W + 2 * m_L * m_H + 2 * m_W * m_H << endl;
    }

    //求立方体的体积
    void getCubeV() const
    {
        cout << "立方体的体积：" << m_L * m_W * m_H << endl;
    }

    //通过成员函数判断立方体是否相等
    bool compareCubeByClass(Cube &cub){
        bool flag = (m_L == cub.getL() && m_H == cub.getH() && m_W == cub.getW());
        return flag;
    }

private:
    int m_L; //长
    int m_W; //宽
    int m_H; //高
};

//全局函数判断，两个立方体是否相等
bool compareCube(const Cube &cub1, const Cube &cub2){
    if (cub1.getL() == cub2.getL() && cub1.getH() == cub2.getH() && cub1.getW() == cub2.getW()){
        return true;
    }

    return false;
}

void test01()
{
    Cube c1;
    c1.setL(10);
    c1.setH(10);
    c1.setW(10);

    c1.getCubeV();//600
    c1.getCubeS();//1000

    //通过全局函数判断两个立方体是否相等
    Cube c2;
    c2.setL(10);
    c2.setH(10);
    c2.setW(10);

    if (compareCube(c1, c2)){
        cout << "通过全员函数：c1和c2是相等的!" << endl;
    }
    else {
        cout << "通过全员函数：c1和c2是不相等的!" << endl;
    }

    //通过成员函数判断两个立方体是否相等
    if (c1.compareCubeByClass(c2)){
        cout << "通过成员函数：c1和c2是相等的!" << endl;
    }
    else {
        cout << "通过成员函数：c1和c2是不相等的!" << endl;
    }

}

int main()
{
    test01();
    return 0;
}