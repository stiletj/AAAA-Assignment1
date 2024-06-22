#pragma once

#include <string>

#include "DataStructures.h"

/**
 * @class LightSource
 * @brief Base class for a generic light source with color and intensity properties.
 */
class LightSource
{
public:
	/**
	 * @brief Default constructor for the LightSource class.
	 */
	LightSource();

	/**
	 * @brief Constructor for the LightSource class with color and intensity parameters.
	 *
	 * @param colour The color of the light.
	 * @param intensity The overall intensity of the light.
	 * @param dIntensity The diffuse intensity of the light.
	 */
	LightSource(glm::vec3 colour, float intensity, float dIntensity);

	/**
	 * @brief Destructor for the LightSource class.
	 */
	virtual ~LightSource();

	/**
	 * @brief Get the color of the light source.
	 *
	 * @return The color of the light source.
	 */
	glm::vec3 GetColour();

	/**
	 * @brief Set the color of the light source.
	 *
	 * @param colour The new color of the light source.
	 */
	void SetColour(glm::vec3 colour);

	/**
	 * @brief Get the overall intensity of the light source.
	 *
	 * @return The overall intensity of the light source.
	 */
	float GetIntensity();

	/**
	 * @brief Set the overall intensity of the light source.
	 *
	 * @param intensity The new overall intensity of the light source.
	 */
	void SetIntensity(float intensity);

	/**
	 * @brief Get the diffuse intensity of the light source.
	 *
	 * @return The diffuse intensity of the light source.
	 */
	const float GetDIntensity() const;

	/**
	 * @brief Set the diffuse intensity of the light source.
	 *
	 * @param intensity The new diffuse intensity of the light source.
	 */
	void SetDIntensity(float intensity);

private:
	glm::vec3 m_colour;
	float m_ambientIntensity;
	float m_diffuseIntensity;
};

/**
 * @class DirectionalLightSource
 * @brief A class representing a directional light source.
 */
class DirectionalLightSource : public LightSource
{
public:
	/**
	 * @brief Default constructor for the DirectionalLightSource class.
	 */
	DirectionalLightSource();

	/**
	 * @brief Constructor for the DirectionalLightSource class with color, ambient intensity, diffuse intensity, and direction parameters.
	 *
	 * @param colour The color of the light.
	 * @param aIntensity The ambient intensity of the light.
	 * @param dIntensity The diffuse intensity of the light.
	 * @param direction The direction of the light.
	 */
	DirectionalLightSource(glm::vec3 colour, float aIntensity, float dIntensity, glm::vec3 direction);

	/**
	 * @brief Get the world-space direction vector of the light.
	 *
	 * @return The world-space direction vector of the light.
	 */
	const glm::vec3 GetWDirection() const;

	/**
	 * @brief Set the direction of the light source and calculate its local direction.
	 *
	 * @param direction The new direction of the light source.
	 * @param World The world transformation matrix for the light.
	 */
	void SetDirection(glm::vec3 direction, glm::mat4& World);

	/**
	 * @brief Get the local-space direction vector of the light.
	 *
	 * @return The local-space direction vector of the light.
	 */
	const glm::vec3 GetLDirection() const;

private:
	glm::vec3 m_worldDirection;
	glm::vec3 m_localDirection;

	void CalcLocalDirection(glm::mat4& World);
};

/**
 * @class PointLightSource
 * @brief A class representing a point light source.
 */
class PointLightSource : public LightSource
{
public:
	/**
	 * @brief Default constructor for the PointLightSource class.
	 */
	PointLightSource();

	/**
	 * @brief Constructor for the PointLightSource class with color, ambient intensity, diffuse intensity, position, and attenuation parameters.
	 *
	 * @param colour The color of the light.
	 * @param aIntensity The ambient intensity of the light.
	 * @param dIntensity The diffuse intensity of the light.
	 * @param position The position of the light.
	 * @param atten The attenuation factors of the light.
	 */
	PointLightSource(glm::vec3 colour, float aIntensity, float dIntensity, glm::vec3 position, glm::vec3 atten);

	/**
	 * @brief Get the position of the light source.
	 *
	 * @return The position of the light source.
	 */
	glm::vec3 GetPosition();

	/**
	 * @brief Set the position of the light source.
	 *
	 * @param position The new position of the light source.
	 */
	void SetPosition(glm::vec3 position);

	/**
	 * @brief Get the local-space position of the light source based on the world matrix.
	 *
	 * @param worldMatrix The world transformation matrix for the light source.
	 * @return The local-space position of the light source.
	 */
	glm::vec3 GetLocalPosition(glm::mat4 worldMatrix);

	/**
	 * @brief Get the attenuation factors of the light source.
	 *
	 * @return The attenuation factors of the light source.
	 */
	glm::vec3 GetAttenuation();

	/**
	 * @brief Set the attenuation factors of the light source.
	 *
	 * @param atten The new attenuation factors of the light source.
	 */
	void SetAttenuation(glm::vec3 atten);

private:
	glm::vec3 m_position;
	float m_constant;
	float m_linear;
	float m_exp;
};

/**
 * @class SpotLightSource
 * @brief A class representing a spot light source.
 */
class SpotLightSource : public LightSource
{
public:
	/**
	 * @brief Default constructor for the SpotLightSource class.
	 */
	SpotLightSource();

	/**
	 * @brief Constructor for the SpotLightSource class with color, ambient intensity, diffuse intensity, position, angle, and range parameters.
	 *
	 * @param colour The color of the light.
	 * @param aIntensity The ambient intensity of the light.
	 * @param dIntensity The diffuse intensity of the light.
	 * @param position The position of the light.
	 * @param angle The angle of the light cone.
	 * @param range The range of the light.
	 */
	SpotLightSource(glm::vec3 colour, float aIntensity, float dIntensity, glm::vec3 position, float angle, float range);

	/**
	 * @brief Get the position of the light source.
	 *
	 * @return The position of the light source.
	 */
	glm::vec3 GetPosition();

	/**
	 * @brief Set the position of the light source.
	 *
	 * @param position The new position of the light source.
	 */
	void SetPosition(glm::vec3 position);

	/**
	 * @brief Get the angle of the light cone.
	 *
	 * @return The angle of the light cone.
	 */
	float GetAngle();

	/**
	 * @brief Set the angle of the light cone.
	 *
	 * @param angle The new angle of the light cone.
	 */
	void SetAngle(float angle);

	/**
	 * @brief Get the range of the light.
	 *
	 * @return The range of the light.
	 */
	float GetRange();

	/**
	 * @brief Set the range of the light.
	 *
	 * @param range The new range of the light.
	 */
	void SetRange(float range);

private:
	glm::vec3 m_position;
	float m_angle;
	float m_range;
};