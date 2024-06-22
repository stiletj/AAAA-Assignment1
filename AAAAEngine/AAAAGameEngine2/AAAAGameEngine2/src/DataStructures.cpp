#include "DataStructures.h"
#include <stdexcept>
/********************************************************************/
//Vector2
float& Vector2::x()
{
	return data.x;
}

float& Vector2::y()
{
	return data.y;
}

int Vector2::length()
{
	return data.length();
}

void Vector2::normalise()
{
	data = glm::normalize(data);
}

Vector2::operator glm::vec2() const
{
	return data;
}

const Vector2& Vector2::operator+ (const Vector2& other) const {
	return Vector2(this->data.x + other.data.x, this->data.y + other.data.y);
}
/********************************************************************/


/********************************************************************/
//Vector 3
float& Vector3::x()
{
	return data.x;
}

float& Vector3::y()
{
	return data.y;
}

float& Vector3::z()
{
	return data.z;
}

int Vector3::length()
{
	return data.length();
}

void Vector3::normalise()
{
	data = glm::normalize(data);
}

void Vector3::Set(float x, float y, float z)
{
	data.x = x;
	data.y = y;
	data.z = z;
}

Vector3::operator glm::vec3() const
{
	return data;
}

const Vector3 Vector3::operator+ (const Vector3& other) const {
	return Vector3(this->data.x + other.data.x, this->data.y + other.data.y, this->data.z + other.data.z);
}

/********************************************************************/

/********************************************************************/
//Vector4

float& Vector4::x()
{
	return data.x;
}

float& Vector4::y()
{
	return data.y;
}

float& Vector4::z()
{
	return data.z;
}

float& Vector4::w()
{
	return data.w;
}

int Vector4::length()
{
	return data.length();
}

void Vector4::normalise()
{
	data = glm::normalize(data);
}

Vector4::operator glm::vec4() const
{
	return data;
}

const Vector4& Vector4::operator+ (const Vector4& other) const {
	return Vector4(this->data.x + other.data.x, this->data.y + other.data.y, this->data.z + other.data.z, this->data.w + other.data.w);
}
/********************************************************************/

/********************************************************************/
//Matrix 3x3
Mat3x3 Mat3x3::Identity()
{
	return Mat3x3(glm::mat3(1.0f));
}

Mat3x3 Mat3x3::operator*(const Mat3x3& otherMat) const
{
	return Mat3x3(data * otherMat.data);
}

glm::vec3 Mat3x3::operator[](int row)
{
	if (row < 0 || row >= 3)
	{
		throw std::out_of_range("Matrix3 Out of Range!");
	}
	return data[row];
}

Mat3x3::operator glm::mat3() const
{
	return data;
}

Mat3x3::Mat3x3(Mat4x4 mat)
{
	this->data = glm::mat3(mat);
}

/********************************************************************/
//Matrix 4x4

Mat4x4 Mat4x4::Identity()
{
	return Mat4x4(glm::mat4(1.0f));
}

Mat4x4 Mat4x4::operator*(const Mat4x4& otherMat) const
{
	return Mat4x4(data * otherMat.data);
}

Vector4& Mat4x4::operator[](int row)
{
	if (row < 0 || row >= 4)
	{
		throw std::out_of_range("Matrix4 Out of Range!");
	}

	Vector4 vec(data[row]);

	return vec;
}

Mat4x4::operator glm::mat4() const
{
	return data;
}


/********************************************************************/
//EXTRA FUNCTIONS

Mat4x4 LookAt(Vector3 position, Vector3 target, Vector3 up) {
	return glm::lookAt(glm::vec3(position.x(), position.y(), position.z()),
		glm::vec3(target.x(), target.y(), target.z()),
		glm::vec3(up.x(), up.y(), up.z()));
}


Mat4x4 Perspective(float fov, float aspect, float near, float far) {
	return glm::perspective(fov, aspect, near, far);
}

Mat4x4 Ortho(float left, float right, float bottom, float top, float near, float far) {
	return glm::ortho(left, right, bottom, top, near, far);
}

Mat3x3 transpose(Mat3x3 mat) {
	return glm::transpose(static_cast<glm::mat3>(mat));
}


Mat4x4 inverse(Mat4x4 mat) {
	return glm::inverse(static_cast<glm::mat4>(mat));
}

Vector3 normalize(Vector3 vec)
{
	glm::vec3 normVec = glm::normalize(glm::vec3(vec.x(), vec.y(), vec.z()));
	return Vector3(normVec.x, normVec.y, normVec.z);
}

Vector3 operator*(Vector3& vec, Mat3x3& mat)
{
	float x = vec.x() * mat[0].x + vec.y() * mat[1].x + vec.z() * mat[2].x;
	float y = vec.x() * mat[0].y + vec.y() * mat[1].y + vec.z() * mat[2].y;
	float z = vec.x() * mat[0].z + vec.y() * mat[1].z + vec.z() * mat[2].z;
	return Vector3(x, y, z);
}

Vector4 operator*(Vector4& vec, Mat4x4& mat)
{
	float x = vec.x() * mat[0].x() + vec.y() * mat[1].x() + vec.z() * mat[2].x() + vec.w() * mat[3].x();
	float y = vec.x() * mat[0].y() + vec.y() * mat[1].y() + vec.z() * mat[2].y() + vec.w() * mat[3].y();
	float z = vec.x() * mat[0].z() + vec.y() * mat[1].z() + vec.z() * mat[2].z() + vec.w() * mat[3].z();
	float w = vec.x() * mat[0].w() + vec.y() * mat[1].w() + vec.z() * mat[2].w() + vec.w() * mat[3].w();
	return Vector4(x, y, z, w);
}


//translate
Mat4x4 translate(Mat4x4 mat, Vector3 vec) {
	return glm::translate(static_cast<glm::mat4>(mat), glm::vec3(vec.x(), vec.y(), vec.z()));
}

//rotate
Mat4x4 rotate(Mat4x4 mat, float angle, Vector3 axis) {
		return glm::rotate(static_cast<glm::mat4>(mat), angle, glm::vec3(axis.x(), axis.y(), axis.z()));
}

//scale
Mat4x4 scale(Mat4x4 mat, Vector3 vec) {
		return glm::scale(static_cast<glm::mat4>(mat), glm::vec3(vec.x(), vec.y(), vec.z()));
}

//radians
float radians(float degrees) {
		return glm::radians(degrees);
}

Vector3 vec4To3(Vector4 vec)
{
	glm::vec4 newVec4(vec.x(), vec.y(), vec.z(), vec.w());
	glm::vec3 newVec3(newVec4);
	Vector3 result(newVec3.x, newVec3.y, newVec3.z);
	return result;
}