#include "Lighting.h"

//Parent Class
LightSource::LightSource()
{
	m_colour = { 1.f, 1.f, 1.f };
	m_ambientIntensity = 1.f;
	m_diffuseIntensity = 0.1f;
}

LightSource::LightSource(glm::vec3 colour, float intensity, float dIntensity)
{
	m_colour = colour;
	m_ambientIntensity = intensity;
	m_diffuseIntensity = dIntensity;
}

LightSource::~LightSource()
{

}

glm::vec3 LightSource::GetColour()
{
	return m_colour;
}

void LightSource::SetColour(glm::vec3 colour)
{
	m_colour = colour;
}

float LightSource::GetIntensity()
{
	return m_ambientIntensity;
}

void LightSource::SetIntensity(float intensity)
{
	m_ambientIntensity = intensity;
}

const float LightSource::GetDIntensity() const
{
	return m_diffuseIntensity;
}

void LightSource::SetDIntensity(float intensity)
{
	m_diffuseIntensity = intensity;
}

//Child Class (Directional)
DirectionalLightSource::DirectionalLightSource() : LightSource()
{
	m_worldDirection = { 0.f, 0.f, 0.f };
	m_localDirection = { 0.f, 0.f, 0.f };
}

DirectionalLightSource::DirectionalLightSource(glm::vec3 colour, float aIntensity, float dIntensity, glm::vec3 direction) : LightSource(colour, aIntensity, dIntensity)
{
	m_worldDirection = direction;
	m_localDirection = direction;
}

const glm::vec3 DirectionalLightSource::GetWDirection() const
{
	return m_worldDirection;
}

void DirectionalLightSource::SetDirection(glm::vec3 direction, glm::mat4& World)
{
	m_worldDirection = direction;

	CalcLocalDirection(World);
}

const glm::vec3 DirectionalLightSource::GetLDirection() const
{
	return m_localDirection;
}

void DirectionalLightSource::CalcLocalDirection(glm::mat4& World)
{
	glm::mat3 World3f(World);							//initialize using top left corner
	//THIS IS ERROR
	glm::mat3 WorldToLocal(transpose(World3f));		//inverse local-to-world transformation using transpose (assuming uniform scaling)

	m_localDirection = m_worldDirection * WorldToLocal;		//transformation from world space to local space
	
	//THIS IS ERROR
	m_localDirection = normalize(m_localDirection);	//normalize localDirection so that when dot product with normal vector will provide cos(theta) which will give an angle for light to bounce off and gives light value.

}

//Child Class (Point)
PointLightSource::PointLightSource() : LightSource()
{
	m_position = { 0.f, 5.f, 0.f };
	m_constant = 1.f;
	m_linear = 0.2f;
	m_exp = 0.f;
}

PointLightSource::PointLightSource(glm::vec3 colour, float aIntensity, float dIntensity, glm::vec3 position, glm::vec3 atten) : LightSource(colour, aIntensity, dIntensity)
{
	m_position = position;
	m_constant = atten.x;
	m_linear = atten.y;
	m_exp = atten.z;
}

glm::vec3 PointLightSource::GetPosition()
{
	return m_position;
}

void PointLightSource::SetPosition(glm::vec3 position)
{
	m_position = position;
}

glm::vec3 PointLightSource::GetLocalPosition(glm::mat4 worldMatrix)
{
	//THIS IS ERROR
	glm::mat4 invertedWorldMatrix = inverse(worldMatrix);
	glm::vec4 placeHolder = glm::vec4(m_position, 1.0f) * invertedWorldMatrix;
	glm::vec3 localPos(placeHolder.x, placeHolder.y, placeHolder.z);

	return localPos;
}

glm::vec3 PointLightSource::GetAttenuation()
{
	return { m_constant, m_linear, m_exp };
}

void PointLightSource::SetAttenuation(glm::vec3 atten)
{
	m_constant = atten.x;
	m_linear = atten.y;
	m_exp = atten.z;
}

//Child Class (Spot)
SpotLightSource::SpotLightSource() : LightSource()
{
	m_position = { 0.f, 10.f, 0.f };
	m_angle = 45;
	m_range = 10.f;
}

SpotLightSource::SpotLightSource(glm::vec3 colour, float aIntensity, float dIntensity, glm::vec3 position, float angle, float range) : LightSource(colour, aIntensity, dIntensity)
{
	m_position = position;
	m_angle = angle;
	m_range = range;
}

glm::vec3 SpotLightSource::GetPosition()
{
	return m_position;
}

void SpotLightSource::SetPosition(glm::vec3 position)
{
	m_position = position;
}

float SpotLightSource::GetAngle()
{
	return m_angle;
}

void SpotLightSource::SetAngle(float angle)
{
	m_angle = angle;
}

float SpotLightSource::GetRange()
{
	return m_range;
}

void SpotLightSource::SetRange(float range)
{
	m_range = range;
}