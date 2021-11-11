#include <iostream>
#include "matrix.h"

using namespace std;

int main()
{
	Matrix<int> mtx;
	mtx.push_back_row(vector<int>{ 8,5,7 });
	mtx.push_back_row(vector<int>{ 5,2,4 });
	mtx.push_back_row(vector<int>{ 2,5,2 });
	Matrix<int> mtxx;
	mtxx.push_back_row(vector<int>{ 3, 3, 3 });
	mtxx.push_back_row(vector<int>{ 3, 3, 3 });
	mtxx.push_back_row(vector<int>{ 3, 1, 3 });
	cout << mtx << endl;
	cout << mtxx << endl;

	cout << "multiplication check" << endl;
	mtx = mtx*mtxx;
	cout << mtx << endl;

	cout << endl << "insert_row check";
	vector<int> vc{30,30,30};
	mtx.insert_row(vc, 1);
	cout << endl << mtx;

	cout << endl << "push_back_row check";
	mtx.push_back_row(vc);
	cout << endl<<mtx;

	cout << endl << "push_back_col check";
	vector<int> col{ 90,90,90,90,90};
	mtx.push_back_col(col);
	cout << endl << mtx;

	cout << endl << "insert_col check";
	mtx.insert_col(col, 1);
	cout << endl << mtx;

	cout << endl << "pop_back_row check";
	mtx.pop_back_row();
	cout << endl << mtx;

	cout << endl << "erase_row check";
	mtx.erase_row(1);
	cout << endl << mtx;

	cout << endl << "pop_back_col check";
	mtx.pop_back_col();
	cout << endl << mtx;

	cout << endl << "erase_col check";
	mtx.erase_col(1);
	cout << endl << mtx;

	cout << endl << "operator [] check";
	mtx[2][2] = 1;
	cout << endl << mtx;

	cout << endl << "determinator check" << endl;
	cout << mtx.determinator(mtx.get_size_row()) << endl;

	cout << endl << "resize check";
	mtx.resize(2,2);
	cout << endl << mtx;
	
	cout << endl << "transponse check";
	mtx = mtx.transponse();
	cout << endl << mtx;

	cout << endl << "inverse check";
	Matrix<double> reversed = mtx.inverse();
	cout << endl << reversed;

	cout << endl << "inverse check again";
	Matrix<int> mtx_3;
	mtx_3.push_back_row(vector<int>{ 2, 5, 7 });
	mtx_3.push_back_row(vector<int>{ 6, 3, 4 });
	mtx_3.push_back_row(vector<int>{ 5, -2, -3 });
	Matrix<double> reversed_1 = mtx_3.inverse();
	cout << endl << reversed_1;

	try
	{
		cout << "\nChecking the input:\n" << endl;
		Matrix<int> t;
		cin >> t;
		cout << "\n\nYou entered: " << endl;
		cout << t;
	}
	catch (const char* ex)
	{
		cout << ex << endl;
	}

	return 0;
}