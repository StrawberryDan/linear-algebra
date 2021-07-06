# Linear Algebra

## Introduction

A header-only C++ linear algebra library. Includes useful type templates like Vectors and Matrices. Written mainly for
use with graphics implementations however will be extending with features which are either useful or appropriate.

## Project Structure

### Vector.h

```c++
template<unsigned int S, typename T = double>
class Vector { ... }
```

Contains vector class that is generic over size and type. Internally the class uses an std::array to store it's values.
If not type is specified then double is used. The following operations are defined:

* Equality testing
* Vector addition and subtraction
* Vector scaling by r constant
* Magnitude and normalisation
* Dot product
* Cross product (Only defined for S == 3)
* Concatenation and splitting

Also contains the following aliases:

| type / size  | 2     | 3     | 4     |
|--------------|-------|-------|-------|
| double       | Vec2  | Vec3  | Vec4  |
| float        | Vec2f | Vec3f | Vec4f |
| int          | Vec2i | Vec3i | Vec4i |
| unsigned int | Vec2u | Vec3u | Vec4u |

### Matrix.h

```c++
template<unsigned int H, unsigned int W = H, typename T = double>
class Matrix { ... }
```

Contains generic Matrix template. Also uses an std::array to store its values The width of the matrix is assumed to be
square unless r seperate width is specified. Furthermore the type is assumed to be double in the same fashion. The
following operations are currently supported:

* Addition and Subtraction
* Constant scaling
* Matrix and Vector multiplication
* Extracting Sub-matrices
* Added and removing rows and columns
* Transposition
* Inversion (Currently only uses adjugate and determinant method)
* Relevant transformations (Scaling, Translation)

Also contains the following aliases:

| type / size  | 2x2   | 3x3   | 4x4   |
|--------------|-------|-------|-------|
| double       | Mat2  | Mat3  | Mat4  |
| float        | Mat2f | Mat3f | Mat4f |
| int          | Mat2i | Mat3i | Mat4i |
| unsigned int | Mat2u | Mat3u | Mat4u |

### Orientation.h

Contains structures to represent orientation in 3D space:

* Euler Angles (Technically Tait-Bryant Angles)
* Quaternions

Each structure has a method to construct their respective transformation matrices.

## Examples

TODO

## Planned Features

TODO (Ironically)
