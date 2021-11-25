#include <iostream>
#include <vector>

using namespace std;

template<typename T>
class Matrix
{
public:
	Matrix();
	Matrix(const int row, const int column);
	Matrix(int row, int column, T init);
	Matrix(const Matrix& m);

	Matrix& operator =(const Matrix& m);
	vector<T>& operator [](const int& row);

	bool operator ==(const Matrix& m) const;
	bool operator !=(const Matrix& m) const;
	
	Matrix& operator +=(const Matrix& m);
	Matrix operator +(const Matrix& m) const;

	Matrix& operator -=(const Matrix& m);
	Matrix operator -(const Matrix& m) const;

	Matrix operator *(const Matrix& m) const;

	friend ostream& operator<<<T>(ostream& out, Matrix& mtx);
	friend istream& operator>><T>(istream& in, Matrix& mtx);

	void clear();

	void insert_row(const vector<T>& v, int position);
	void push_back_row(const vector<T>& v);

	void insert_col(const vector<T>& v, int position);
	void push_back_col(const vector<T>& v);

	void erase_row(int position);
	void pop_back_row();

	void erase_col(int position);
	void pop_back_col();

	int determinator(/*size_row_this_matrix*/ int n) const;

	Matrix transponse();

	int alg_complement(const int row_pos, const int col_pos);

	Matrix<double> inverse();

	void resize(const int new_size_row, const int new_size_col);

	int get_size_row() const;
	int get_size_col() const;

	~Matrix();

private:
	vector<vector<T>> mtx;
	T size_row;
	T size_col;
};

template<typename T>
Matrix<T>::Matrix()
{
	this->size_col = 0;
	this->size_row = 0;
	this->mtx.clear();
	return;
}

template<typename T>
Matrix<T>::Matrix(const int row, const int column)
{
	this->size_row = row < 0 ? 3 : row;
	this->size_col = column < 0 ? 3 : column;
	this->mtx.clear();

	for (int i = 0; i < size_row; ++i)
	{
		mtx.push_back(vector<T>());
		for (int j = 0; j < size_col; ++j)
		{
			mtx[i].push_back(0);
		}
	}
	return;
}

template<typename T>
Matrix<T>::Matrix(int row, int column, T init)
{
	this->size_row = row < 0 ? 3 : row;
	this->size_col = column < 0 ? 3 : column;
	this->mtx.clear();

	for (int i = 0; i < size_row; ++i)
	{
		mtx.push_back(vector<T>());
		for (int j = 0; j < size_col; ++j)
		{
			mtx[i].push_back(init);
		}
	}
	return;
}

template<typename T>
Matrix<T>::Matrix(const Matrix& m)
{
	this->size_row = m.size_row;
	this->size_col = m.size_col;
	this->mtx.clear();

	for (int i = 0; i < size_row; ++i)
	{
		this->mtx.push_back(vector<T>(size_col));
		for (int j = 0; j < size_col; ++j)
		{
			this->mtx[i][j] = m.mtx[i][j];
		}
	}
	return;
}

template<typename T>
Matrix<T>& Matrix<T>::operator =(const Matrix<T>& m)
{
	if (m == *this)
		return *(this);

	for (int i = 0; i < this->mtx.size(); i++)
	{
		mtx[i].~vector();
	}
	mtx.clear();

	this->size_row = m.size_row;
	this->size_col = m.size_col;

	for (int i = 0; i < size_row; ++i)
	{
		this->mtx.push_back(vector<T>(size_col));
		for (int j = 0; j < size_col; ++j)
		{
			this->mtx[i][j] = m.mtx[i][j];
		}
	}

	return *this;
}

template<typename T>
vector<T>& Matrix<T>::operator [](const int& row)
{
	if (row < 0 || row >= this->size_row)
		throw "Error index!";

	return this->mtx[row];
}

template<typename T>
bool Matrix<T>::operator ==(const Matrix<T>& m) const
{
	if (this->size_row != m.size_row || this->size_col != m.size_col)
		return false;

	for (int i = 0; i < size_row; ++i)
	{
		for (int j = 0; j < size_col; ++j)
		{
			if (this->mtx[i][j] != m.mtx[i][j])
				return false;
		}
	}

	return true;
}

template<typename T>
bool Matrix<T>::operator !=(const Matrix<T>& m) const
{
	return !((*this) == m);
}

template<typename T>
Matrix<T>& Matrix<T>::operator +=(const Matrix<T>& m)
{
	if (this->size_row != m.size_row || this->size_col != m.size_col)
		throw "Error size matrix A and B";

	for (int i = 0; i < size_row; ++i)
	{
		for (int j = 0; j < size_col; ++j)
		{
			this->mtx[i][j] += m.mtx[i][j];
		}
	}
	return *this;
}

template<typename T>
Matrix<T> Matrix<T>::operator +(const Matrix<T>& m) const
{
	Matrix res(0, 0, 0);
	res = *this;
	res += m;
	return res;
}

template<typename T>
Matrix<T>& Matrix<T>::operator -=(const Matrix<T>& m)
{
	if (this->size_row != m.size_row || this->size_col != m.size_col)
		throw "Error size matrix A and B";

	for (int i = 0; i < size_row; ++i)
	{
		for (int j = 0; j < size_col; ++j)
		{
			this->mtx[i][j] -= m.mtx[i][j];
		}
	}
	return *this;
}

template<typename T>
Matrix<T> Matrix<T>::operator -(const Matrix<T>& m) const
{
	Matrix res;
	res = (*this);
	res -= m;
	return res;
}

template<typename T>
Matrix<T> Matrix<T>::operator *(const Matrix<T>& m) const
{
	if (this->size_row != m.size_col)
		throw "Error matrix size";

	Matrix res(this->size_row, m.size_col);

	int count_index = 0;

	while (count_index < (res.size_row * res.size_col))
	{
		for (int i = 0; i < this->size_row; ++i)
		{
			res.mtx[count_index / size_col][count_index % size_col] += this->mtx[count_index / size_col][i] * m.mtx[i][count_index % size_col];
		}
		++count_index;
	}

	return res;
}

template<typename T>
ostream& operator<<(ostream& out, Matrix<T>& mtx)
{
	for (int i = 0; i < mtx.get_size_row(); i++)
	{
		for (int j = 0; j < mtx.get_size_col(); j++)
		{
			out << mtx[i][j] << " ";
		}
		out << endl;
	}
	return out;
}

template<typename T>
istream& operator>>(istream& in, Matrix<T>& mtx)
{
	cout << "enter the number of rows: " << endl;
enter_row_size:
	cin >> mtx.size_row;
	if (cin.fail() || mtx.size_row < 1)
	{
		cin.clear();
		cin.ignore(999, '\n');
		cout << "Error input! Try again: " << endl;
		goto enter_row_size;
	}

	T temp;
	for (int i = 0; i < mtx.size_row; i++)
	{
		mtx.mtx.push_back(vector<T>{});
		cout << "Enter row " << i + 1 << "	(elements separated by a space)" << endl;
		cin >> temp;
		mtx[i].push_back(temp);
		while (char(cin.peek()) == ' ')
		{
			cin >> temp;
			mtx[i].push_back(temp);
		}
	}

	mtx.size_col = mtx[0].size();
	for (int i = 1; i < mtx.mtx.size(); i++)
	{
		if (mtx.size_col != mtx[i].size())
			throw "The row sizes are different!";
	}

	return in;
}

template<typename T>
void Matrix<T>::clear()
{
	for (int i = 0; i < this->mtx.size(); i++)
	{
		this->mtx[i].~vector();
	}
	mtx.~vector();

	return;
}

template<typename T>
void Matrix<T>::insert_row(const vector<T>& v, int position)
{
	if (this->size_col && v.size() != this->size_col)
	{
		throw "Size row error!";
		return;
	}

	if (position < 1 || position >(mtx.size() + 1))
	{
		throw "Agrument position incorrect!";
		return;
	}

	if (position == mtx.size() + 1)
	{
		push_back_row(v);
		return;
	}

	auto it = mtx.begin();
	mtx.insert(it + position - 1, vector<T>(v.size()));

	++this->size_row;

	for (int i = 0; i < v.size(); i++)
	{
		this->mtx[position - 1][i] = v[i];
	}

	return;
}

template<typename T>
void Matrix<T>::push_back_row(const vector<T>& v)
{
	if (this->size_col && v.size() != this->size_col)
	{
		throw "Size row error!";
		return;
	}

	mtx.push_back(vector<T>(v.size()));

	this->size_col = v.size();	//�������������� �� ������ ����, ��� ��� ������ ������ ������� �� ��������� (�� ���� ������ ������� ��� ����)

	++this->size_row;

	for (int i = 0; i < v.size(); i++)
	{
		this->mtx[mtx.size() - 1][i] = v[i];
	}

	return;
}

template<typename T>
void Matrix<T>::insert_col(const vector<T>& v, int position)
{
	if (v.size() != this->size_row)
	{
		throw "Size col error!";
		return;
	}

	if (position < 1 || position >(mtx[0].size() + 1))
	{
		throw "Agrument position incorrect!";
		return;
	}

	if (position == mtx[0].size() + 1)
	{
		push_back_col(v);
		return;
	}

	for (int i = 0; i < size_row; i++)
	{
		auto it = mtx[i].begin();
		mtx[i].insert(it + position - 1, v[i]);
	}

	++this->size_col;

	return;
}

template<typename T>
void Matrix<T>::push_back_col(const vector<T>& v)
{
	if (v.size() != this->size_row)
	{
		throw "Size col error!";
		return;
	}

	for (int i = 0; i < size_row; i++)
	{
		mtx[i].push_back(v[i]);
	}

	++this->size_col;

	return;
}

template<typename T>
void Matrix<T>::erase_row(int position)
{
	if (position < 1 || position >(mtx.size() + 1))
	{
		throw "Agrument position incorrect!";
		return;
	}

	auto it = mtx.begin();
	mtx.erase(it + position - 1);

	--this->size_row;

	return;
}

template<typename T>
void Matrix<T>::pop_back_row()
{
	mtx.pop_back();

	--this->size_row;

	return;
}

template<typename T>
void Matrix<T>::erase_col(int position)
{
	if (position < 1 || position >(mtx[0].size() + 1))
	{
		throw "Agrument position incorrect!";
		return;
	}

	for (int i = 0; i < size_row; i++)
	{
		auto it = mtx[i].begin();
		mtx[i].erase(it + position - 1);
	}

	--this->size_col;

	return;
}

template<typename T>
void Matrix<T>::pop_back_col()
{
	for (int i = 0; i < size_row; i++)
	{
		mtx[i].pop_back();
	}

	--this->size_col;

	return;
}

//Argument is size_row
template<typename T>
int Matrix<T>::determinator(/*size_row_this_matrix*/ int n) const
{
	if (this->size_col != this->size_row)
		throw " Error size matrix!";
	if (n == 1)
		return this->mtx[0][0];

	int det = 0;
	Matrix submatrix(this->size_row, this->size_row, 0);

	if (n == 2)
		return ((this->mtx[0][0] * this->mtx[1][1]) - (this->mtx[1][0] * this->mtx[0][1]));
	else {
		for (int x = 0; x < n; x++) {
			int subi = 0;
			for (int i = 1; i < n; i++) {
				int subj = 0;
				for (int j = 0; j < n; j++) {
					if (j == x)
						continue;
					submatrix[subi][subj] = this->mtx[i][j];
					subj++;
				}
				subi++;
			}
			det = det + (pow(-1, x) * this->mtx[0][x] * submatrix.determinator(n - 1));
		}
	}
	return det;
}

template<typename T>
Matrix<T> Matrix<T>::transponse()
{
	Matrix res(this->size_col, this->size_row, 0);

	for (int i = 0; i < this->size_row; i++)
	{
		for (int j = 0; j < this->size_col; j++)
		{
			res[j][i] = this->mtx[i][j];
		}
	}

	return res;
}

template<typename T>
int Matrix<T>::alg_complement(const int row_pos, const int col_pos)
{
	Matrix temp(*this);

	temp.erase_row(row_pos + 1);
	temp.erase_col(col_pos + 1);

	return pow(-1, row_pos + col_pos + 2) * temp.determinator(temp.size_row);
}

template<typename T>
Matrix<double> Matrix<T>::inverse()
{
	int determ = this->determinator(this->size_row);

	if (determ == 0)
		return Matrix<double>(0, 0, 0.0);

	Matrix transponse_matrix_A = this->transponse();

	Matrix united_matrix(transponse_matrix_A.size_row, transponse_matrix_A.size_col, 0);

	for (int i = 0; i < united_matrix.size_row; i++)
	{
		for (int j = 0; j < united_matrix.size_col; j++)
		{
			united_matrix[i][j] = transponse_matrix_A.alg_complement(i, j);
		}
	}

	Matrix<double> inverse_matrix(united_matrix.size_row, united_matrix.size_col, double(1 / this->determinator(this->size_row)));
	for (int i = 0; i < inverse_matrix.get_size_row(); i++)
	{
		for (int j = 0; j < inverse_matrix.get_size_col(); j++)
		{
			inverse_matrix[i][j] = (double)united_matrix[i][j];
			inverse_matrix[i][j] /= double(determ);	//��������, ��� ��� ��������� � int ��� �� ����� (���������� �� � �����)
		}
	}

	return inverse_matrix;
}

template<typename T>
void Matrix<T>::resize(const int new_size_row, const int new_size_col)
{
	if (new_size_row < 0 || new_size_col < 0)
		throw "Arguments error!";

	if (new_size_row < this->size_row)
	{
		while (this->size_row > new_size_row)
		{
			this->pop_back_row();
		}
	}
	if (new_size_row > this->size_row)
	{
		while (this->size_row < new_size_row)
		{
			this->push_back_row(vector<T>(this->size_col));
		}
	}

	if (new_size_col < this->size_col)
	{
		while (this->size_col > new_size_col)
		{
			this->pop_back_col();
		}
	}
	if (new_size_col > this->size_col)
	{
		while (this->size_col < new_size_col)
		{
			this->push_back_col(vector<T>(this->size_row));
		}
	}

	return;
}

template<typename T>
int Matrix<T>::get_size_row() const
{
	return this->size_row;
}

template<typename T>
int Matrix<T>::get_size_col() const
{
	return this->size_col;
}

template<typename T>
Matrix<T>::~Matrix()
{
	for (int i = 0; i < size_row; ++i)
	{
		this->mtx[i].~vector();
	}
	mtx.clear();
	return;
}