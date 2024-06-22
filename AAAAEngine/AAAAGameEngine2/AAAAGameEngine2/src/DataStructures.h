//glm
#pragma once
#include "glm.hpp"
#include "gtc/matrix_transform.hpp"

/********************************************************************/

/**
 * @class Vector2
 * @brief Class representing a 2D vector.
 */
class Vector2
{
private:
	glm::vec2 data; /**< Internal data storage for the vector. */

public:
	Vector2() : data(glm::vec2(0.0f)) {}
	Vector2(float x, float y) : data(glm::vec2(x, y)) {}

	float& x(); /**< Returns a reference to the x component of the vector. */
	float& y(); /**< Returns a reference to the y component of the vector. */

	int length(); /**< Calculates the length of the vector. */
	void normalise(); /**< Normalizes the vector. */

	operator glm::vec2() const; /**< Conversion operator to glm::vec2. */
	const Vector2& operator+ (const Vector2& otherMat) const; /**< Addition operator for vectors. */
};

/********************************************************************/

/**
 * @class Vector3
 * @brief Class representing a 3D vector.
 */
class Vector3
{
private:
	glm::vec3 data; /**< Internal data storage for the vector. */

public:
	Vector3() : data(glm::vec3(0.0f)) {}
	Vector3(float x, float y, float z) : data(glm::vec3(x, y, z)) {}

	float& x(); /**< Returns a reference to the x component of the vector. */
	float& y(); /**< Returns a reference to the y component of the vector. */
	float& z(); /**< Returns a reference to the z component of the vector. */
	 
	void SetX(float n) { data.x = n; } /**< Sets the value of the x component. */
	void SetY(float n) { data.y = n; } /**< Sets the value of the y component. */
	void SetZ(float n) { data.z = n; } /**< Sets the value of the z component. */

	int length();
	void normalise();

	void Set(float x, float y, float z);

	operator glm::vec3() const; /**< Conversion operator to glm::vec3. */
	const Vector3 operator+ (const Vector3& other) const; /**< Addition operator for vectors. */
};



/********************************************************************/

/**
 * @class Vector4
 * @brief Class representing a 4D vector.
 */
class Vector4
{
private:
	glm::vec4 data; /**< Internal data storage for the vector. */

public:
	Vector4() : data(glm::vec4(0.0f)) {}
	Vector4(float x, float y, float z, float w) : data(glm::vec4(x, y, z, w)) {}
	Vector4(Vector3 vec, float w) : data(glm::vec4(vec.x(), vec.y(), vec.z(), w)) {}
	Vector4(glm::vec4 vec) : data(vec.x, vec.y, vec.z, vec.w) {}

	float& x(); /**< Returns a reference to the x component of the vector. */
	float& y(); /**< Returns a reference to the y component of the vector. */
	float& z(); /**< Returns a reference to the z component of the vector. */
	float& w(); /**< Returns a reference to the w component of the vector. */

	int length(); /**< Calculates the length of the vector. */
	void normalise(); /**< Normalizes the vector. */

	operator glm::vec4() const; /**< Conversion operator to glm::vec4. */
	const Vector4& operator+ (const Vector4& otherMat) const; /**< Addition operator for vectors. */
};

/********************************************************************/

/**
 * @class Mat4x4
 * @brief Class representing a 4x4 matrix.
 */
class Mat4x4
{
private:
	glm::mat4 data; /**< Internal data storage for the matrix. */

public:
	Mat4x4() : data(glm::mat4(1.0f)) {}
	Mat4x4(const glm::mat4& mat) : data(mat) {}

	static Mat4x4 Identity(); /**< Returns an identity matrix. */

	Mat4x4 operator*(const Mat4x4& otherMat) const; /**< Multiplication operator for matrices. */
	Vector4& operator[](int row); /**< Accessor for matrix rows. */

	operator glm::mat4() const; /**< Conversion operator to glm::mat4. */
};

/********************************************************************/

/**
 * @class Mat3x3
 * @brief Class representing a 3x3 matrix.
 */
class Mat3x3
{
private:
	glm::mat3 data; /**< Internal data storage for the matrix. */

public:
	Mat3x3() : data(glm::mat3(1.0f)) {}
	Mat3x3(const glm::mat3& mat) : data(mat) {}
	Mat3x3(Mat4x4 mat);

	static Mat3x3 Identity(); /**< Returns an identity matrix. */

	Mat3x3 operator*(const Mat3x3& otherMat) const; /**< Multiplication operator for matrices. */
	glm::vec3 operator[](int row); /**< Accessor for matrix rows. */

	operator glm::mat3() const; /**< Conversion operator to glm::mat3. */
};

/********************************************************************/

Mat4x4 LookAt(Vector3 position, Vector3 target, Vector3 up); /**< Constructs a view matrix. */
Mat4x4 Perspective(float fov, float aspect, float near, float far); /**< Constructs a perspective projection matrix. */
Mat4x4 Ortho(float left, float right, float bottom, float top, float near, float far); /**< Constructs an orthographic projection matrix. */
Mat4x4 inverse(Mat4x4 mat); /**< Calculates the inverse of a matrix. */
Mat3x3 transpose(Mat3x3 mat); /**< Transposes a matrix. */
Vector3 normalize(Vector3 vec); /**< Normalizes a vector. */
Vector3 operator*(Vector3& vec, Mat3x3& mat); /**< Multiplies a vector by a matrix. */
Vector4 operator*(Vector4& vec, Mat4x4& mat); /**< Multiplies a vector by a matrix. */

Mat4x4 translate(Mat4x4 mat, Vector3 vec); /**< Constructs a translation matrix. */
Mat4x4 rotate(Mat4x4 mat, float angle, Vector3 axis); /**< Constructs a rotation matrix. */
Mat4x4 scale(Mat4x4 mat, Vector3 vec); /**< Constructs a scaling matrix. */

float radians(float degrees); /**< Converts degrees to radians. */
Vector3 vec4To3(Vector4 vec); /**< Converts a 4D vector to a 3D vector. */