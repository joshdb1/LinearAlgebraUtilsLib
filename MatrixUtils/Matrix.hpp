#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <complex>
#include <vector>

template<typename T>
class Matrix
{
  public:
    Matrix()
    {

    }

    Matrix(size_t _rows, size_t _cols, T fillVal = 0)
    {
      m_vData.clear();
      m_vData.resize(_rows, std::vector<T>(_cols));
      m_rows = _rows;
      m_cols = _cols;
      for (size_t r = 0; r < _rows; ++r)
      {
        std::fill(m_Data.begin(), m_vData.end(), fillVal);
      }
    }

    Matrix(Matrix& rhs)
    {
      this->m_vData = rhs.m_vData;
    }

    void resize(const size_t _rows, const size_t _cols)
    {
      m_vData.resize(_rows, std::vector<T>(_cols));
      m_rows = _rows;
      m_cols = _cols;
    }

    T& operator()(const size_t row, const size_t col)
    {
      T val;
      try
      {
        if (row >= m_rows || col >= m_cols)
        {
          throw std::exception("ERROR [Matrix.hpp]: Row or column index out of bounds.");
        }

        val = m_vData[row][col];
      }
      catch(const std::exception& e)
      {
        std::cerr << e.what() << '\n';
      }
      
      return val;
    }
    
    Matrix operator+(const Matrix& rhs)
    {
      Matrix out;
      try
      {
        if (this->m_rows != rhs.m_rows || this->m_cols != rhs.m_cols)
        {
          throw std::exception("ERROR [Matrix.hpp]: Matrix sizes must be equal.");
        }

        out.resize(m_rows, m_cols);
        
        for (size_t r = 0; r < m_rows; ++r)
        {
          for (size_t c = 0; c < m_cols; ++r)
          {
            out.m_vData[r][c] = this->m_vData[r][c] + rhs.m_vData[r][c];
          }
        }
      }
      catch(const std::exception& e)
      {
        std::cerr << e.what() << '\n';
      }
      
      return out;
    }

    Matrix operator*(const Matrix& rhs)
    {
      try
      {
        if (this->m_cols != rhs.m_rows)
        {
          throw std::exception("ERROR [Matrix.hpp]: Incorrect dimensions for Matrix Multiplication")
        }

        Matrix<T> out(m_rows, rhs.m_cols, 0);

        for (size_t i = 0; i < m_rows; ++i)
        {
          for (size_t j = 0; j < rhs.m_cols; ++j)
          {
            for (size_t k = 0; k < m_cols; ++k)
            {
              out[i][j] += this->m_vData[i][k] * rhs.m_vData[k][j];
            }
          }
        }

        return out;
      }
      catch(const std::exception& e)
      {
        std::cerr << e.what() << '\n';
      }
    }

    std::vector<T> operator*(const std::vector<T>& rhs)
    {
      try
      {
        if (this->m_cols != rhs.m_rows)
        {
          throw std::exception("ERROR [Matrix.hpp]: Incorrect dimensions for Matrix Multiplication")
        }

        std::vector<T> out(m_rows, 1, 0);

        for (size_t i = 0; i < m_rows; ++i)
        {
          for (size_t k = 0; k < m_cols; ++k)
          {
            out[i] += this->m_vData[i][k] * rhs[k];
          }
        }

        return out;
      }
      catch(const std::exception& e)
      {
        std::cerr << e.what() << '\n';
      }
    }

    Matrix operator=(const Matrix& rhs)
    {
      m_vData = rhs.m_vData;
      m_rows = rhs.m_rows;
      m_cols = rhs.m_cols;
    }

  private:
    std::vector<std::vector<T>> m_vData;
    size_t m_rows = 0;
    size_t m_cols = 0;

};

#endif // MATRIX_HPP