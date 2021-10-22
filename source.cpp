#include <iostream>
#include "matrix.hpp"

using namespace std;

int main()
{
	Matrix<int> mtx(3, 3, 5);
	Matrix<int> mtxx(3, 3, 2);
	cout << mtx;
	cout << mtxx;
	mtxx = mtx * mtxx;
	cout << mtxx;
	return 0;
}