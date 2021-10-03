#include<iostream>
#include<cstring>

using namespace std;

int a[100] ,b[100] ,c[100];

int compare(int a[],int b[])
{
    if(a[0] > b[0]) return 1;
    if(a[0] < b[0]) return -1;
    for (int i = a[0]; i > 0; i -- )
    {
        if(a[i] > b[i]) return 1;
        if(a[i] < b[i]) return -1;
    }
    
    return 0;
}

void subduction(int a[],int b[])
{
    int flag = compare(a,b);
    if (flag == 0)
    {
        a[0] = 0;
        return;
    }
    if (flag)
    {
        for (int i = 1; i <= a[0]; i ++ )
        {
            if (a[i] < b[i])
            {
                a[i + 1] --;
                a[i] += 10;
            }
            a[i] -= b[i];
        }
        while(a[0] > 0 && a[a[0]] == 0) a[0] --;
    }
}

int main()
{
    char str1[100], str2[100];
    int temp[100];
    
    memset(a, 0, sizeof(a));
    memset(b, 0, sizeof(b));
    memset(c, 0, sizeof(c));
    memset(temp,0,sizeof(temp));
    
	cin >> str1 >> str2;
	
    a[0] = strlen(str1);
    b[0] = strlen(str2);
    c[0] = a[0] - b[0] + 1;
    
    for (int i = 1; i <= a[0]; i ++ ) a[i] = str1[a[0] - i] - '0';
    for (int i = 1; i <= b[0]; i ++ ) b[i] = str2[b[0] - i] - '0';
    
    for (int i = c[0]; i > 0; i -- )
    {
        for (int j = 1; j <= b[0]; j ++ ) temp[j + i - 1] = b[j];
        temp[0] = b[0] + i - 1;
        while(compare(a, temp) >= 0)
        {
            c[i] ++;
            subduction(a, temp);
        }
    }

    while(c[0] > 0 && c[c[0]] == 0) c[0] --;
    cout << "商为：";
    if(!c[0]) cout << 0 << endl;
    else
    {
        for (int i = c[0]; i > 0; i -- ) cout << c[i];
        cout << endl;
    }

    cout << "余数为：";
    if(!a[0]) cout << 0 << endl;
    else
    {
        for (int i = a[0]; i > 0; i -- ) cout << a[i];
    }

    return 0;
}