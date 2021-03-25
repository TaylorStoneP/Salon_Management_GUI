#ifndef MATRIX_REVISION_H
#define MATRIX_REVISION_H

#include <iostream>
#include <string>
#include <sstream>
#include "debuglogger.h"

//using mat2_int = Mat2<int>;
/*
using mat2_char		= Mat2<char>;
using mat2_short	= Mat2<short>;
using mat2_long		= Mat2<long>;
using mat2_float	= Mat2<float>;
using mat2_double	= Mat2<double>;
using mat2_u_char	= Mat2<unsigned char>;
using mat2_u_short	= Mat2<unsigned short>;
using mat2_u_int	= Mat2<unsigned int>;
using mat2_u_long	= Mat2<unsigned long>;
using mat2_string	= Mat2<std::string>;
*/

namespace Mat_2_Row_NS
{
	template<typename T>
	class Mat2Row
	{
		T* row;
		int cols;
	public:
		Mat2Row(T*& i_row, int n_cols) :row(i_row), cols(n_cols) { LOG_ALLOCATION("Mat2Row", this); }
		~Mat2Row() { row = nullptr;	LOG_DEALLOCATION("Mat2Row", this); }
		T& operator[](int index)
		{
			if (index >= 0 && index < cols) {
				return row[index];
			}
			LOG_WARN("\"Mat2\" column index out of bounds. index given was " + std::to_string(index) + " but bound is " + std::to_string(cols - 1));
			return row[0];
		}
	};
}

//2D Matrix Template Class.
//-Variety of functions not available for non-primitive types.
template<typename T>
//Matrix Template.
class Mat2
{
	T** mat;
	int m_rows;
	int m_cols;
public:
	const int& n_rows;	//Number of rows in matrix.
	const int& n_cols;	//Number of columns in matrix.

	//Main constructor.
	//Takes in a permanent number of rows, columns and an optional default allocated type.
	Mat2(int rows /*hello*/, int cols,T defaultType = T()):m_rows(rows),m_cols(cols), n_rows(m_rows), n_cols(m_cols) 
	{
		mat = new T*[n_rows];
		for (int i = 0; i < n_rows; i++)
		{
			mat[i] = new T[n_cols];
			for (int j = 0; j < n_cols; j++)
			{
				mat[i][j] = defaultType;
			}
		}
		LOG_ALLOCATION("Mat2", this);
	}
	//Copy constructor.
	Mat2(Mat2<T>& copy):m_rows(copy.n_rows),m_cols(copy.n_cols), n_rows(m_rows), n_cols(m_cols)
	{
		mat = new T * [n_rows];
		for (int i = 0; i < n_rows; i++)
		{
			mat[i] = new T[n_cols];
			for (int j = 0; j < n_cols; j++)
				mat[i][j] = copy[i][j];
		}
		LOG_ALLOCATION("Mat2-Copy", this);
	}
	//Copy constructor (r-value).
	Mat2(Mat2<T>&& copy) :m_rows(copy.n_rows), m_cols(copy.n_cols), n_rows(m_rows), n_cols(m_cols)
	{
		mat = new T * [n_rows];
		for (int i = 0; i < n_rows; i++)
		{
			mat[i] = new T[n_cols];
			for (int j = 0; j < n_cols; j++)
				mat[i][j] = copy[i][j];
		}
		LOG_ALLOCATION("Mat2-Copy", this);
	}
	//Takes in a string a converts it it a matrix. 
	//String must be in the form of:
	//"1 2 3\\n4 5 6\\n7 8 9"
	//Representing a 3x3:
	//1 2 3
	//4 5 6
	//7 8 9
	Mat2(std::string text):n_rows(m_rows), n_cols(m_cols)
	{
		std::stringstream matrix(text);
		std::stringstream line;
		std::string row;
		std::string temp;
		int rows = 0;
		int cols = 0;
		while (!matrix.eof())
		{
			std::getline(matrix, row);
			line = std::stringstream(row);
			if (rows == 0) {
				while (!line.eof())
				{
					std::getline(line, temp, ' ');
					cols++;
				}
			}
			rows++;
		}

		matrix = std::stringstream(text);
		mat = new T*[rows];
		for (int i = 0; i < rows; i++)
		{
			std::getline(matrix, row);
			line = std::stringstream(row);
			mat[i] = new T[cols];
			for (int j = 0; j < cols; j++)
			{
				std::getline(line, temp, ' ');
				mat[i][j] = std::stod(temp);
			}
		}
		m_rows = rows;
		m_cols = cols;
	}
	~Mat2()
	{
		for (int i = 0; i < n_rows; i++)
		{
			delete mat[i];
		}
		delete mat;
		LOG_DEALLOCATION("Mat2", this);
	}
	
	Mat_2_Row_NS::Mat2Row<T> operator[](int index)
	{
		if (index >= 0 && index < n_rows)
		{
			return Mat_2_Row_NS::Mat2Row<T>(mat[index], n_cols);
		}
		LOG_WARN("\"Mat2\" row index out of bounds. index given was " + std::to_string(index) + " but bound is " + std::to_string(n_rows - 1));
		return Mat_2_Row_NS::Mat2Row<T>(mat[0], n_cols);
	}
	Mat2<T>& operator=(Mat2<T>& copy)
	{
		if (n_rows == copy.n_rows && n_cols == copy.n_cols)
		{
			for (int i = 0; i < n_rows; i++)
				for (int j = 0; j < n_cols; j++)
					mat[i][j] = copy[i][j];
		}
		else
		{
			LOG_WARN("cannot set Mat2 as Mat2 - incorrect shape. shape given was (" + std::to_string(copy.n_rows) + "," + std::to_string(copy.n_cols) + "). expected shape was (" + std::to_string(n_rows) + "," + std::to_string(n_cols) + ").");
		}
		return *this;
	}
	Mat2<T>& operator=(Mat2<T>&& copy)
	{
		if (n_rows == copy.n_rows && n_cols == copy.n_cols)
		{
			for (int i = 0; i < n_rows; i++)
				for (int j = 0; j < n_cols; j++)
					mat[i][j] = copy[i][j];
		}
		else
		{
			LOG_WARN("cannot set Mat2 as Mat2 - incorrect shape. shape given was (" + std::to_string(copy.n_rows) + "," + std::to_string(copy.n_cols) + "). expected shape was (" + std::to_string(n_rows) + "," + std::to_string(n_cols) + ").");
		}
		return *this;
	}

	//Returns a transposed matrix.
	Mat2<T> Transpose()
	{
		Mat2<T> transposed(n_cols, n_rows);
		for (int i = 0; i < n_cols; i++)
			for (int j = 0; j < n_rows; j++)
				transposed[i][j] = this->operator[](j).operator[](i);
		return transposed;
	}

	//Returns a string of the matrix in the form:
	//[[a b c]
	//[d e f]
	//[g h i]]
	//Only available for types with std::to_string() conversion.
	std::string To_String()
	{
		std::string out = "[";
		for (int i = 0; i < n_rows; i++)
		{
			out += "[";
			for (int j = 0; j < n_cols; j++)
			{
				out += std::to_string(this->operator[](i).operator[](j));
				if (j != n_cols - 1)
					out += "\t";
			}
			out += i==n_rows-1?"]]\n":"]\n";
		}
		return out;
	}

	//Returns the result matrix of a matrix multiplication.
	//Only available for types with operator* overloaded function.
	Mat2<T> operator*(Mat2<T>& other)
	{
		if (n_cols == other.n_rows)
		{
			Mat2<T> out(n_rows, other.n_cols);
			for (int i = 0; i < out.n_rows; i++)
			{
				for (int j = 0; j < out.n_cols; j++)
				{
					for (int n = 0; n < n_cols; n++)
					{
						out[i][j] += this->operator[](i).operator[](n) * other[n][j];
					}
				}
			}
			return out;
		}
		else
			LOG_WARN("cannot multiply Mat2 - incorrect shape. shape given was (" + std::to_string(other.n_rows)+","+ std::to_string(other.n_cols)+"). expected shape was (" + std::to_string(n_cols) + ",~).");
		return Mat2<T>(1, 1);
	}
	//Returns the result matrix of a matrix multiplication.
	//Only available for types with operator* overloaded function.
	Mat2<T> operator*(T other)
	{
		Mat2<T> out(*this);
		for (int i = 0; i < out.n_rows; i++)
			for (int j = 0; j < out.n_cols; j++)
				out[i][j] *= other;
		return out;
	}
	//Returns the result matrix of a matrix multiplication.
	//Only available for types with operator+ overloaded function.
	Mat2<T> operator+(Mat2<T>& other)
	{
		if (n_rows == other.n_rows && n_cols == other.n_cols)
		{
			Mat2<T> out(*this);
			for (int i = 0; i < out.n_rows; i++)
				for (int j = 0; j < out.n_cols; j++)
					out[i][j] +=  other[i][j];
			return out;
		}
		else
			LOG_WARN("cannot add Mat2 - incorrect shape. shape given was (" + std::to_string(other.n_rows) + "," + std::to_string(other.n_cols) + "). expected shape was (" + std::to_string(n_rows) + ","+ std::to_string(n_cols) +").");
		return Mat2<T>(1, 1);
	}
	//Returns the result matrix of a matrix multiplication.
	//Only available for types with operator- overloaded function.
	Mat2<T> operator-(Mat2<T>& other)
	{
		if (n_rows == other.n_rows && n_cols == other.n_cols)
		{
			Mat2<T> out(*this);
			for (int i = 0; i < out.n_rows; i++)
				for (int j = 0; j < out.n_cols; j++)
					out[i][j] -= other[i][j];
			return out;
		}
		else
			LOG_WARN("cannot subtract Mat2 - incorrect shape. shape given was (" + std::to_string(other.n_rows) + "," + std::to_string(other.n_cols) + "). expected shape was (" + std::to_string(n_rows) + "," + std::to_string(n_cols) + ").");
		return Mat2<T>(1, 1);
	}
	//Returns the determinant of the matrix.
	//Only available for arithmetic and primitive types, i.e requires overloaded operator+ and operator* functions.
	double Determinant()
	{
		if (n_rows == n_cols)
		{
			double det = 0;
			Mat2<T> temp(n_rows-1,n_cols-1);
			int added = 0;
			if (n_rows == 1)
				det= this->operator[](0).operator[](0);
			else
				for (int i = 0; i < n_cols; i++)
				{
					for (int n = 1; n < n_cols; n++)
						for (int p = 0; p < n_cols; p++)
							if (p != i)
							{
								temp[added / temp.n_cols][added % temp.n_cols] = this->operator[](n).operator[](p);
								added++;
							}
					det += i % 2 == 0 ? this->operator[](0).operator[](i) * temp.Determinant() : this->operator[](0).operator[](i) * temp.Determinant()*-1;
					added = 0;
				}
			
			return det;
		}
		else
			LOG_WARN("cannot find determinant of Mat2 - incorrect shape. shape given was (" + std::to_string(n_rows) + "," + std::to_string(n_cols) + "). expected shape was sqaure, e.g.(3,3).");
		return T();
	}

	//Returns the echelon matrix from a matrix with a given exclusion row and column.
	Mat2<T> Echelon(int exclusion_row, int exclusion_column)
	{
		Mat2<T> temp(n_rows - 1, n_cols - 1);
		int added = 0;
		for (int n = 0; n < n_cols; n++)
			for (int p = 0; p < n_cols; p++)
				if (p != exclusion_column && n!=exclusion_row)
				{
					temp[added / temp.n_cols][added % temp.n_cols] = this->operator[](n).operator[](p);
					added++;
				}
		return temp;
	}

	//Returns the matrix of minors
	Mat2<T> Minors()
	{
		if (n_rows == n_cols)
		{
			Mat2<T> temp(n_rows, n_cols);
			for (int i = 0; i < n_rows; i++)
				for (int j = 0; j < n_cols; j++)
					temp[i][j] = Echelon(i, j).Determinant();
			return temp;
		}
		else
			LOG_WARN("cannot find matrix of minors of Mat2 - incorrect shape. shape given was (" + std::to_string(n_rows) + "," + std::to_string(n_cols) + "). expected shape was sqaure, e.g.(3,3).");
		return Mat2<T>(1, 1);
	}

	Mat2<T> Cofactors()
	{
		if (n_rows == n_cols)
		{
			Mat2<T> temp(Minors());
			for (int i = 0; i < n_rows; i++)
				for (int j = 0; j < n_cols; j++)
					temp[i][j] = (i * n_cols + j) % 2 == 0 ? temp[i][j] : temp[i][j] * -1;
			return temp;
		}
		else
			LOG_WARN("cannot find matrix of cofactors of Mat2 - incorrect shape. shape given was (" + std::to_string(n_rows) + "," + std::to_string(n_cols) + "). expected shape was sqaure, e.g.(3,3).");
		return Mat2<T>(1, 1);
	}

	Mat2<T> Adjugate()
	{
		if (n_rows == n_cols)
			return Cofactors().Transpose();
		else
			LOG_WARN("cannot find adjugate of Mat2 - incorrect shape. shape given was (" + std::to_string(n_rows) + "," + std::to_string(n_cols) + "). expected shape was sqaure, e.g.(3,3).");
		return Mat2<T>(1, 1);
	}

	Mat2<T> Inverse()
	{
		if (n_rows == n_cols)
			return Adjugate() * (1.0 / Determinant());
		else
			LOG_WARN("cannot find inverse matrix of Mat2 - incorrect shape. shape given was (" + std::to_string(n_rows) + "," + std::to_string(n_cols) + "). expected shape was sqaure, e.g.(3,3).");
		return Mat2<T>(1,1);
	}
};

#endif