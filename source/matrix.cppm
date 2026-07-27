module;

#include <cmath>
#include <array>
#include <ostream>
#include <algorithm>
#include <stdexcept>
#include <initializer_list>

export module matrix;

// The dimensions must be always known in compilation.
export template <typename T, std::size_t Rows, std::size_t Columns>
class Matrix
{
    std::array<T, Rows * Columns> data{};

public:
    static constexpr Matrix getIdentity()
    {
        static_assert(Rows == Columns,
                      "Identity matrix requires a square matrix.");

        Matrix identity{};

        for (std::size_t i = 0; i < Rows; ++i)
            identity[i, i] = T{1};

        return identity;
    }

    // Contructor passing a list.
    constexpr Matrix() {}

    // Contructor passing a list.
    constexpr Matrix(std::initializer_list<T> values)
    {
        if (values.size() != Rows * Columns)
            throw std::invalid_argument("Incorrect number of elements");

        std::copy(values.begin(), values.end(), data.begin());
    }

    // Contructor passing a list of lists.
    constexpr Matrix(std::initializer_list<std::initializer_list<T>> rows)
    {
        std::size_t index = 0;

        for (const auto &row : rows)
        {
            if (row.size() != Columns)
                throw std::invalid_argument("Incorrect number of columns");

            for (const auto &value : row)
                data[index++] = value;
        }

        if (rows.size() != Rows)
            throw std::invalid_argument("Incorrect number of rows");
    }

    constexpr T &operator[](std::size_t row, std::size_t column) { return data[row * Columns + column]; }
    constexpr const T &operator[](std::size_t row, std::size_t column) const { return data[row * Columns + column]; }

    constexpr Matrix operator+(const Matrix &rightMatrix) const
    {
        Matrix result{};

        for (std::size_t i = 0; i < Rows * Columns; ++i)
            result.data[i] = this->data[i] + rightMatrix.data[i];

        return result;
    }

    constexpr Matrix operator-(const Matrix &rightMatrix) const
    {
        Matrix result{};

        for (std::size_t i = 0; i < Rows * Columns; ++i)
            result.data[i] = this->data[i] - rightMatrix.data[i];

        return result;
    }

    template <std::size_t OtherColumns>
    constexpr Matrix<T, Rows, OtherColumns>
    operator*(const Matrix<T, Columns, OtherColumns> &rightMatrix) const
    {
        Matrix<T, Rows, OtherColumns> result{};

        for (std::size_t i = 0; i < Rows; ++i)
            for (std::size_t j = 0; j < OtherColumns; ++j)
                for (std::size_t k = 0; k < Columns; ++k)
                    result[i, j] += (*this)[i, k] * rightMatrix[k, j];

        return result;
    }

    constexpr Matrix<T, Columns, Rows> transpose() const
    {
        Matrix<T, Columns, Rows> result{};

        for (std::size_t i = 0; i < Rows; ++i)
            for (std::size_t j = 0; j < Columns; ++j)
                result[j, i] = (*this)[i, j];

        return result;
    }

    constexpr Matrix inverse() const
        requires(Rows == Columns && std::floating_point<T>)
    {
        Matrix left = *this;
        Matrix right{};

        // Identity.
        for (std::size_t i = 0; i < Rows; ++i)
            right[i, i] = T{1};

        for (std::size_t k = 0; k < Rows; ++k)
        {
            // Search for the best pivot.
            std::size_t pivot = k;

            for (std::size_t i = k + 1; i < Rows; ++i)
            {
                if (std::abs(left[i, k]) > std::abs(left[pivot, k]))
                    pivot = i;
            }

            if (left[pivot, k] == T{})
                throw std::runtime_error("Matrix is singular.");

            // Rows are swapped.
            if (pivot != k)
            {
                for (std::size_t j = 0; j < Rows; ++j)
                {
                    std::swap(left[k, j], left[pivot, j]);
                    std::swap(right[k, j], right[pivot, j]);
                }
            }

            // The pivot row is normalized.
            T divisor = left[k, k];

            for (std::size_t j = 0; j < Rows; ++j)
            {
                left[k, j] /= divisor;
                right[k, j] /= divisor;
            }

            // The column is removed in the rest of the rows.
            for (std::size_t i = 0; i < Rows; ++i)
            {
                if (i == k)
                    continue;

                T factor = left[i, k];

                for (std::size_t j = 0; j < Rows; ++j)
                {
                    left[i, j] -= factor * left[k, j];
                    right[i, j] -= factor * right[k, j];
                }
            }
        }

        return right;
    }
};

export template <typename T, std::size_t Rows, std::size_t Columns>
std::ostream &operator<<(
    std::ostream &os,
    const Matrix<T, Rows, Columns> &matrix)
{
    for (std::size_t i = 0; i < Rows; ++i)
    {
        os << "[ ";

        for (std::size_t j = 0; j < Columns; ++j)
        {
            os << matrix[i, j];

            if (j + 1 < Columns)
                os << " | ";
        }

        os << " ]";

        if (i + 1 < Rows)
            os << '\n';
    }

    return os;
}