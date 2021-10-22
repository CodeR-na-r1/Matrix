#include <iostream>
#include <vector>

using namespace std;

template<typename T> 
class Matrix
{
public:
	Matrix()
	{
		return;
	}
	Matrix(const T row, const T column)
	{
		this->size_row = row < 0 ? 3 : row;
		this->size_col = column < 0 ? 3 : column;

		for (int i = 0; i < size_row; ++i)
		{
			mtx.push_back(new int[size_col]);
			for (int j = 0; j < size_col; ++j)
			{
				mtx[i][j] = 0;
			}
		}
		return;
	}
	Matrix(int row, T column, T init)
	{
		this->size_row = row < 0 ? 3 : row;
		this->size_col = column < 0 ? 3 : column;

		for (int i = 0; i < size_row; ++i)
		{
			mtx.push_back(new int[size_col]);
			for (int j = 0; j < size_col; ++j)
			{
				mtx[i][j] = init;
			}
		}
		return;
	}
	Matrix(const Matrix& m)
	{
		this->size_row = m.size_row;
		this->size_col = m.size_col;

		for (int i = 0; i < size_row; ++i)
		{
			this->mtx.push_back(new int[size_col]);
			for (int j = 0; j < size_col; ++j)
			{
				this->mtx[i][j] = m.mtx[i][j];
			}
		}
		return;
	}

	Matrix& operator =(const Matrix& m)
	{
		if (m == *this)
			return *(this);

		this->size_row = m.size_row;
		this->size_col = m.size_col;

		this->mtx.clear();

		for (int i = 0; i < size_row; ++i)
		{
			this->mtx.push_back(new int[size_col]);
			for (int j = 0; j < size_col; ++j)
			{
				this->mtx[i][j] = m.mtx[i][j];
			}
		}

		return *this;
	}

	bool operator ==(const Matrix& m) const
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

	bool operator !=(const Matrix& m) const
	{
		return !((*this) == m);
	}
	
	Matrix& operator +=(const Matrix& m)
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

	Matrix operator +(const Matrix& m) const
	{
		Matrix res();
		res = *this;
		res += m;
		return res;
	}

	Matrix& operator -=(const Matrix& m)
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

	Matrix operator -(const Matrix& m) const
	{
		Matrix res();
		res = *this;
		res -= m;
		return res;
	}

	Matrix operator *(const Matrix& m) const
	{
		if (this->size_row != m.size_col)
			throw "Error matrix size";

		Matrix res(this->size_row, m.size_col);

		int count_index = 0;

		for (int i = 0; i < this->size_row; ++i)
		{
			for (int j = 0; j < this->size_col; ++j)
			{
				res.mtx[count_index / size_col][count_index % size_col] = this->mtx[i][j] * m.mtx[j][i];
				++count_index;
			}
		}

		return res;
	}
	
	friend ostream& operator<<(ostream& out, Matrix& mtx)
	{
		for (int i = 0; i < mtx.get_size_row(); i++)
		{
			for (int j = 0; j < mtx.get_size_col(); j++)
			{
				out << mtx.mtx[i][j] << " ";
			}
			out << endl;
		}
		return out;
	}
	
	int determinator() const
	{

	}

	Matrix transponse(const Matrix& mtx)
	{

	}

	Matrix inverse(const Matrix& mtx)
	{

	}

	int get_size_row() const
	{
		return this->size_row;
	}

	int get_size_col() const
	{
		return this->size_col;
	}

	~Matrix()
	{
		for (int i = 0; i < size_row; ++i)
		{
			delete[] mtx[i];
		}
		mtx.clear();
		return;
	}

private:
	vector<T*> mtx;
	T size_row;
	T size_col;
};