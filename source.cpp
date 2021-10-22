#include <iostream>
#include "matrix.hpp"

using namespace std;

int main()
{
	Matrix<int> mtx(3, 3, 2);
	Matrix<int> mtxx(3, 3, 2);
	cout << mtx;
	cout << mtxx;
	bool f = mtx == mtxx;
	cout << f;
	return 0;
}