#include <iostream>
#include "matrix.h"

using namespace std;

int main()
{
	Matrix<int> mtx(3, 3, 5);
	Matrix<int> mtxx(3, 3, 2);
	cout << mtx;
	cout << mtxx;
	mtx = mtx*mtxx;
	cout << mtx;
	vector<int> vc{30,30,30};
	mtx.insert_row(vc, 1);
	cout << endl << mtx;

	mtx.push_back_row(vc);
	cout << endl<<mtx;

	vector<int> col{ 90,90,90,90,90};
	mtx.push_back_col(col);
	cout << endl << mtx;

	mtx.insert_col(col, 1);
	cout << endl << mtx;

	mtx.pop_back_row();
	cout << endl << mtx;

	mtx.erase_row(1);
	cout << endl << mtx;

	mtx.pop_back_col();
	cout << endl << mtx;

	mtx.erase_col(1);
	cout << endl << mtx;

	return 0;
}