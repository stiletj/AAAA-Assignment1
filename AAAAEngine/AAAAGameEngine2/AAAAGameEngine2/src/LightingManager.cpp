#include "LightingManager.h"

std::vector<DirectionalLightSource> LightingManager::m_dirLights;
std::vector<PointLightSource> LightingManager::m_pointLights;
std::vector<SpotLightSource> LightingManager::m_spotLights;

const unsigned int LightingManager::m_maxLights = 1;

int LightingManager::m_activeDirLight;
std::vector<unsigned int> LightingManager::m_activePointLights;

std::vector<glm::vec4> LightingManager::m_pointLightColours;
std::vector<float> LightingManager::m_ambientIntensies;
std::vector<float> LightingManager::m_diffuseIntensies;
std::vector<float> LightingManager::m_constants;
std::vector<float> LightingManager::m_linears;
std::vector<float> LightingManager::m_exps;

int LightingManager::m_isDirLight;

LightingManager::LightingManager()
{
	m_ambientIntensies = std::vector<float>();
	m_diffuseIntensies = std::vector<float>();
	m_constants = std::vector<float>();
	m_linears = std::vector<float>();
	m_exps = std::vector<float>();
}

LightingManager::~LightingManager()
{
}

//directional lights
unsigned int LightingManager::CreateLight(glm::vec3 colour, float aIntensity, float dIntensity, glm::vec3 direction)
{
	DirectionalLightSource newLight(colour, aIntensity, dIntensity, direction);
	m_ambientIntensies.push_back(aIntensity);
	m_diffuseIntensies.push_back(dIntensity);
	m_constants.push_back(0.f);
	m_linears.push_back(0.f);
	m_exps.push_back(0.f);

	m_dirLights.push_back(newLight);

	return m_dirLights.size() - 1;
}

//point lights
unsigned int LightingManager::CreateLight(glm::vec3 colour, float aIntensity, float dIntensity, glm::vec3 position, glm::vec3 atten)
{
	PointLightSource newLight(colour, aIntensity, dIntensity, position, atten);
	m_ambientIntensies.push_back(aIntensity);
	m_diffuseIntensies.push_back(dIntensity);
	m_constants.push_back(atten.x);
	m_linears.push_back(atten.y);
	m_exps.push_back(atten.z);
	m_pointLights.push_back(newLight);

	return m_pointLights.size() - 1;
}

//spot lights
unsigned int LightingManager::CreateLight(glm::vec3 colour, float aIntensity, float dIntensity, glm::vec3 position, float angle, float range)
{
	SpotLightSource newLight(colour, aIntensity, dIntensity, position, angle, range);
	m_ambientIntensies.push_back(aIntensity);
	m_diffuseIntensies.push_back(dIntensity);
	m_spotLights.push_back(newLight);
	m_constants.push_back(0.f);
	m_linears.push_back(0.f);
	m_exps.push_back(0.f);

	return m_spotLights.size() - 1;
}

void LightingManager::ActivateDirLight(unsigned int currLight)
{
	m_activeDirLight = currLight;

	UpdateActivePoints();

	if (m_isDirLight == 0)
	{
		m_isDirLight = 1;

		//std::cout << "Activate: " << m_isDirLight << std::endl;
	}
}

void LightingManager::ActivatePointLight(unsigned int currLight)
{
	m_activePointLights.push_back(currLight);

	UpdateActivePoints();
}

void LightingManager::DeactivateDirLight()
{
	m_activeDirLight = -1;

	if (m_isDirLight == 1)
	{
		m_isDirLight = 0;

		//std::cout << "Deactivate: " << m_isDirLight << std::endl;
	}
}

void LightingManager::DeactivatePointLight(unsigned int delLight)
{
	m_activePointLights.erase(std::remove(m_activePointLights.begin(), m_activePointLights.end(), delLight), m_activePointLights.end());

	UpdateActivePoints();
}

int LightingManager::GetIsDirLight()
{
	return m_isDirLight;
}

void LightingManager::SetLightingUniforms(Shader& shader, glm::mat4 modelMatrix)
{
	SetDirectionalUniforms(shader);

	SetPointUniforms(shader, modelMatrix);
}

void LightingManager::SetDirectionalUniforms(Shader& shader)
{
	unsigned int active;

	if (m_activeDirLight == -1)
	{
		active = 0;
	}
	else
	{
		active = m_activeDirLight;
	}

	//Ambient Lighting
	shader.SetUniform1f("u_AmbientIntensity", m_dirLights[active].GetIntensity());
	shader.SetUniform4f("u_LightColour", glm::vec4(m_dirLights[active].GetColour(), 1.0f ));

	//Diffuse Lighting
	glm::vec3 LDirection = m_dirLights[active].GetLDirection();
	shader.SetUniform3f("u_Direction", LDirection);
	shader.SetUniform1f("u_DiffuseIntensity", m_dirLights[active].GetDIntensity());
}

void LightingManager::SetPointUniforms(Shader& shader, glm::mat4 worldMatrix)
{
	m_pointLightColours.clear();
	std::vector<glm::vec3> positions;
	for (int i = 0; i < m_maxLights; i++)
	{
		if (i < m_activePointLights.size())
		{
			positions.push_back(m_pointLights[i].GetLocalPosition(worldMatrix));

			m_pointLightColours.push_back({ m_pointLights[m_activePointLights[i]].GetColour(), 1.0f });
		}
	}

	shader.SetUniform3fv("u_PointPositions", m_maxLights, positions);
	shader.SetUniform4fv("u_PointColours", m_maxLights, m_pointLightColours);
	shader.SetUniform1fv("u_PointAmbientIntensities", m_maxLights, m_ambientIntensies.data());
	shader.SetUniform1fv("u_PointDiffuseIntensities", m_maxLights, m_diffuseIntensies.data());
	shader.SetUniform1fv("u_PointConstants", m_maxLights, m_constants.data());
	shader.SetUniform1fv("u_PointLinears", m_maxLights, m_linears.data());
	shader.SetUniform1fv("u_PointExps", m_maxLights, m_exps.data());
	shader.SetUniform1i("u_NumOfPoints", m_activePointLights.size());
}

int LightingManager::GetActiveDirLight()
{
	if (m_isDirLight == 1)
	{
		return m_activeDirLight;
	}
	else
	{
		return -1;
	}
}

std::vector<unsigned int> LightingManager::GetActivePointLights()
{
	return m_activePointLights;
}

void LightingManager::UpdateActivePoints()
{
	for (int i = 0; i < m_maxLights; i++)
	{
		m_constants[i] = 0.f;
		m_linears[i] = 0.f;
		m_exps[i] = 0.f;

		m_ambientIntensies[i] = 0.f;
		m_diffuseIntensies[i] = 0.f;
	}

	for (int i = 0; i < m_maxLights; i++)
	{
		//std::cout << m_activePointLights.size() << std::endl;

		if (i < m_activePointLights.size())
		{
			glm::vec3 atten = m_pointLights[m_activePointLights[i]].GetAttenuation();

			m_constants[i] = atten.x;
			m_linears[i] = atten.y;
			m_exps[i] = atten.z;

			m_ambientIntensies[i] = m_pointLights[m_activePointLights[i]].GetIntensity();
			m_diffuseIntensies[i] = m_pointLights[m_activePointLights[i]].GetDIntensity();

			//std::cout << "\nconst: " << m_constants[i] << "\nlin: " << m_linears[i] << "\nexp: " << m_exps[i] << "\namb: " <<
				//m_ambientIntensies[i] << "\ndiff: " << m_diffuseIntensies[i] << std::endl;
		}
	}
}