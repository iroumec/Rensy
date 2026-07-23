module;

/*
    ============================================================================
    vec.h

    Fixed-size mathematical vector implementation.

    This header defines a generic vector type whose dimension is known at
    compile time. The vector dimension is encoded in the type itself through
    a class template, allowing the compiler to optimize memory layout and
    generated code while preventing accidental operations between vectors of
    different dimensions.

    A complete specialization for three-dimensional vectors is provided to
    expose the components as x, y and z, which is the conventional notation
    used in computer graphics and computational geometry.

    Characteristics
    ---------------
    - Fixed size determined at compile time.
    - No dynamic memory allocation.
    - Contiguous memory layout.
    - Bounds checking during debug builds through assertions.
    - Direct support for formatted output to C++ streams.

    Example
    -------
        vec<2> uv;
        vec<4> color;
        vec3 position;
    ============================================================================
*/

#include <cmath> // Standard mathematical library.
                 // Declares functions such as std::sqrt(), std::sin(),
                 // std::cos(), std::abs(), etc.

#include <cassert> // Declares the assert() macro.
                   //
                   // Assertions verify programmer assumptions during
                   // development. If an assertion fails in a Debug build,
                   // the program terminates immediately and reports the
                   // location of the failure.
                   //
                   // Assertions are automatically disabled when NDEBUG is
                   // defined (typically in Release builds).

#include <iostream> // Declares std::ostream and stream insertion operators.
                    //
                    // Required to implement operator<< so vectors can be
                    // written directly to output streams such as std::cout.

export module geometry;

/*
    Generic fixed-size vector.

    Template Parameters
    -------------------
    n
        Number of components stored in the vector.

    Every distinct value of 'n' produces a different type at compile time.

        vec<2>
        vec<3>
        vec<8>

    are unrelated types.

    Storage is embedded directly inside the object using a fixed-size array.
    Consequently, no heap allocation occurs and the size of the object is
    known entirely at compile time.
*/
export template <int n>
struct vec
{
    /*
        Storage for the vector components.

        All elements are value-initialized to zero.

        Memory layout:

            data[0]
            data[1]
            ...
            data[n - 1]
    */
    double data[n] = {0};

    /*
        Returns a mutable reference to the requested component.

        Parameters
        ----------
        i
            Zero-based component index.

        Returns
        -------
        A reference to the selected component.

        Notes
        -----
        An assertion verifies that the index belongs to the valid interval
        [0, n). Attempting to access an invalid index is considered a
        programming error.
    */
    double &operator[](const int i)
    {
        assert(i >= 0 && i < n);
        return data[i];
    }

    /*
        Returns a copy of the requested component.

        This overload is selected automatically when the vector is const,
        preventing modification of its contents.
    */
    double operator[](const int i) const
    {
        assert(i >= 0 && i < n);
        return data[i];
    }
};

/*
    Stream insertion operator.

    Writes every vector component to an output stream, separating consecutive
    values with a single space.

    Example
    -------
        vec<3> v;

        std::cout << v;

    Output

        0 0 0

    Returning the stream allows output operations to be chained.

        std::cout << a << b << c;
*/
export template <int n>
std::ostream &operator<<(std::ostream &out, const vec<n> &v)
{
    for (int i = 0; i < n; ++i)
        out << v[i] << ' ';

    return out;
}

/**
* Complete specialization for three-dimensional vectors.

    Three-dimensional vectors are extremely common in computer graphics.
    While the generic implementation stores its components inside an array,
    this specialization exposes them as x, y and z to improve readability.

    Both access methods remain valid:

        v.x
        v.y
        v.z

    and

        v[0]
        v[1]
        v[2]

    always refer to the same underlying values.
*/
export template <>
struct vec<3>
{
    /*
        Cartesian coordinates.

        Every component is initialized to zero.
    */
    double x = 0;
    double y = 0;
    double z = 0;

    /*
        Returns a mutable reference to the requested component.

        Index mapping

            0 -> x
            1 -> y
            2 -> z
    */
    double &operator[](const int i)
    {
        assert(i >= 0 && i < 3);
        return i ? (i == 1 ? y : z) : x;
    }

    /*
        Returns a copy of the requested component.

        This overload is selected automatically for const objects.
    */
    double operator[](const int i) const
    {
        assert(i >= 0 && i < 3);
        return i ? (i == 1 ? y : z) : x;
    }
};

/*
    Convenience alias for a three-dimensional vector.

    This declaration introduces no new type.

        vec3

    is exactly equivalent to

        vec<3>
*/
export using vec3 = vec<3>;