#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

//c = A * b, A > 0, b > 0
vector<int> mul(vector<int> &A, int b)
{
	vector<int> C;
	
	for (size_t i = 0, t = 0; i < A.size() || t; i ++ )
	{
		if (i < A.size()) t += A[i] * b;
		C.push_back(t % 10);
		t /= 10;
	}
	
	return C;
}

int main()
{
	string a;
	int b;
	
	cin >> a >> b;
	
	vector<int> A;
	for (int i = a.size() - 1; i >= 0; i -- ) A.push_back(a[i] - '0');
	
	auto C = mul(A, b);
	
	for (int i = C.size() - 1; i >= 0; i -- ) printf("%d", C[i]);
	
	return 0;
}