#include <iostream>
#include <vector>

using namespace std;

template<typename T> 
class Matrix
{
public:
	Matrix()
	{
		this->size_col = 0;
		this->size_row = 0;
		this->mtx.clear();
		return;
	}

	Matrix(const T row, const T column)
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

	Matrix(T row, T column, T init)
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

	Matrix(const Matrix& m)
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

	Matrix& operator =(const Matrix& m)
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
		Matrix res(0,0,0);
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
		Matrix res;
		res = (*this);
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
	
	void insert_row(vector<T>& v, int position)
	{
		if (v.size() != this->size_col)
		{
			throw "Size row error!";
			return;
		}

		if (position < 1 || position > (mtx.size() + 1))
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
		mtx.insert(it + position - 1, vector<T>(size_col));
		
		++this->size_row;

		for (int i = 0; i < size_col; i++)
		{
			this->mtx[position-1][i] = v[i];
		}

		return;
	}

	void push_back_row(vector<T>& v)
	{
		if (v.size() != this->size_col)
		{
			throw "Size row error!";
			return;
		}

		mtx.push_back(vector<T>(size_col));

		++this->size_row;

		for (int i = 0; i < size_col; i++)
		{
			this->mtx[mtx.size() - 1][i] = v[i];
		}

		return;
	}

	void insert_col(vector<T>& v, int position)
	{
		if (v.size() != this->size_row)
		{
			throw "Size col error!";
			return;
		}

		if (position < 1 || position > (mtx[0].size() + 1))
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

	void push_back_col(vector<T>& v)
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

	void erase_row(int position)
	{
		if (position < 1 || position > (mtx.size() + 1))
		{
			throw "Agrument position incorrect!";
			return;
		}

		auto it = mtx.begin();
		mtx.erase(it + position - 1);

		--this->size_row;

		return;
	}
	
	void pop_back_row()
	{
		mtx.pop_back();

		--this->size_row;

		return;
	}

	void erase_col(int position)
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

	void pop_back_col()
	{
		for (int i = 0; i < size_row; i++)
		{
			mtx[i].pop_back();
		}

		--this->size_col;

		return;
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
			this->mtx[i].~vector();
		}
		mtx.clear();
		return;
	}

private:
	vector<vector<T>> mtx;
	T size_row;
	T size_col;
};