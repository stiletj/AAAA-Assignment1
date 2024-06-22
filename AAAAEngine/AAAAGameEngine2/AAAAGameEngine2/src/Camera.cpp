#include "Camera.h"

//constructors and destructors

Camera::Camera()
{
	m_pitch = 0;
	m_yaw = 0;
	m_position = glm::vec3(0, 0, 0);
	m_upVector = glm::vec3(0, 1, 0);
	m_forwardVect = glm::vec3(0, 0, 0);
	glm::lookAt(m_position, m_position + m_forwardVect, m_upVector);
}

Camera::Camera(Camera& camera)
{
	m_position = camera.GetPosition();
	m_forwardVect = camera.GetForwardVector();
	m_upVector = camera.GetUpVector();
	m_pitch = camera.GetPitch();
	m_yaw = camera.GetYaw();
	glm::lookAt(m_position, m_position + m_forwardVect, m_upVector);
}

Camera::Camera(glm::vec3 position, glm::vec3 forwardVector, glm::vec3 upVector, double pitch, double yaw)
{
	m_position = position;
	m_forwardVect = forwardVector;
	m_upVector = upVector;
	m_pitch = pitch;
	m_yaw = yaw;
	glm::lookAt(m_position, m_position + m_forwardVect, m_upVector);
}

Camera::~Camera() {} //no clue

//getters

const glm::vec3 Camera::GetPosition() const
{
	return m_position;
}
const glm::vec3 Camera::GetForwardVector() const
{
	return m_forwardVect;
}
const glm::vec3 Camera::GetUpVector() const
{
	return m_upVector;
}
const double Camera::GetPitch() const
{
	return m_pitch;
}
const double Camera::GetYaw() const
{
	return m_yaw;
}

//setters

void Camera::SetPosition(glm::vec3 position)
{
	m_position = position;
	glm::lookAt(m_position, m_position + m_forwardVect, m_upVector);
}
void Camera::SetForwardVector(glm::vec3 forwardVector)
{
	m_forwardVect = forwardVector;
	glm::lookAt(m_position, m_position + m_forwardVect, m_upVector);
}
void Camera::SetPitch(double pitch)
{
	m_pitch = pitch;
	glm::lookAt(m_position, m_position + m_forwardVect, m_upVector);
}
void Camera::SetYaw(double yaw)
{
	m_yaw = yaw;
	glm::lookAt(m_position, m_position + m_forwardVect, m_upVector);
}
void Camera::SetAngles(double pitch, double yaw)
{
	m_pitch = pitch;
	glm::lookAt(m_position, m_position + m_forwardVect, m_upVector);
}
void Camera::SetUpVector(glm::vec3 UpVector)
{
	m_upVector = UpVector;
	glm::lookAt(m_position, m_position + m_forwardVect, m_upVector);
}
void Camera::Set(glm::vec3 position, glm::vec3 forwardVector, glm::vec3 upVector, double pitch, double yaw)
{
	m_position = position;
	m_forwardVect = forwardVector;
	m_upVector = upVector;
	m_pitch = pitch;
	m_yaw = yaw;
	glm::lookAt(m_position, m_position + m_forwardVect, m_upVector);
}

//extra funcs

const glm::mat4 Camera::getViewMatrix() const
{
	glm::vec3 m_placeholder = m_position + m_forwardVect;
	return glm::lookAt(m_position, m_placeholder, m_upVector);
}

const glm::mat4 Camera::getProjectionMatrix(float screenWidth, float screenHeight, bool isPerspective, float fov, float near, float far, float orthoSize) const
{
	if (isPerspective)
	{
		// Perspective Projection Matrix
		return glm::perspective(glm::radians(fov), screenWidth / screenHeight, near, far);
	}
	else
	{
		// Orthographic Projection Matrix
		return glm::ortho(-orthoSize, orthoSize, -orthoSize * (screenHeight / screenWidth), orthoSize * (screenHeight / screenWidth), near, far);
	}
}