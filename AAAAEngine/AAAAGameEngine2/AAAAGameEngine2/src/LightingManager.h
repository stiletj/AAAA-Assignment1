/**
 * @file LightingManager.h
 *
 * @brief Header file for the LightingManager class.
 */

#pragma once

#include <vector>
#include <iostream>

#include "Lighting.h"
#include "Shader.h"

#include "DataStructures.h"

 /**
  * @class LightingManager
  *
  * @brief A class responsible for managing various types of lights in a 3D scene.
  */
class LightingManager
{
public:
	/**
	 * @brief Default constructor for LightingManager.
	 */
	LightingManager();

	/**
	 * @brief Destructor for LightingManager.
	 */
	~LightingManager();

	/**
	 * @brief Create a directional light.
	 *
	 * @param colour The light color.
	 * @param aIntensity The ambient intensity of the light.
	 * @param dIntensity The diffuse intensity of the light.
	 * @param direction The direction of the light.
	 *
	 * @return An ID for the created light.
	 */
	unsigned int CreateLight(glm::vec3 colour, float aIntensity, float dIntensity, glm::vec3 direction);

	/**
	 * @brief Create a point light.
	 *
	 * @param colour The light color.
	 * @param aIntensity The ambient intensity of the light.
	 * @param dIntensity The diffuse intensity of the light.
	 * @param position The position of the light.
	 * @param atten The attenuation parameters.
	 *
	 * @return An ID for the created light.
	 */
	unsigned int CreateLight(glm::vec3 colour, float aIntensity, float dIntensity, glm::vec3 position, glm::vec3 atten);

	/**
	 * @brief Create a spot light.
	 *
	 * @param colour The light color.
	 * @param aIntensity The ambient intensity of the light.
	 * @param dIntensity The diffuse intensity of the light.
	 * @param position The position of the light.
	 * @param angle The light angle.
	 * @param range The light range.
	 *
	 * @return An ID for the created light.
	 */
	unsigned int CreateLight(glm::vec3 colour, float aIntensity, float dIntensity, glm::vec3 position, float angle, float range);

	/**
	 * @brief Activate a directional light with the given ID.
	 *
	 * @param currLight The ID of the directional light to activate.
	 */
	void ActivateDirLight(unsigned int currLight);

	/**
	 * @brief Activate a point light with the given ID.
	 *
	 * @param currLight The ID of the point light to activate.
	 */
	void ActivatePointLight(unsigned int currLight);

	/**
	 * @brief Deactivate the directional light.
	 */
	void DeactivateDirLight();

	/**
	 * @brief Deactivate a point light with the given ID.
	 *
	 * @param delLight The ID of the point light to deactivate.
	 */
	void DeactivatePointLight(unsigned int delLight);

	/**
	 * @brief Get the ID of the active directional light.
	 *
	 * @return The ID of the active directional light.
	 */
	int GetActiveDirLight();

	/**
	 * @brief Get a list of active point lights.
	 *
	 * @return A vector of IDs of active point lights.
	 */
	std::vector<unsigned int> GetActivePointLights();

	/**
	 * @brief Get the status of directional light.
	 *
	 * @return 1 if a directional light is active, 0 otherwise.
	 */
	static int GetIsDirLight();

	/**
	 * @brief Set lighting uniforms in a shader program.
	 *
	 * @param shader The shader program to set the lighting uniforms in.
	 * @param modelmatrix The model matrix for the object being rendered.
	 */
	static void SetLightingUniforms(Shader& shader, glm::mat4 modelmatrix);

private:
	static std::vector<DirectionalLightSource> m_dirLights;
	static std::vector<PointLightSource> m_pointLights;
	static std::vector<SpotLightSource> m_spotLights;
	static const unsigned int m_maxLights;
	static int m_activeDirLight;
	static std::vector<unsigned int> m_activePointLights;
	static std::vector<glm::vec4> m_pointLightColours;
	static std::vector<float> m_ambientIntensies;
	static std::vector<float> m_diffuseIntensies;
	static std::vector<float> m_constants;
	static std::vector<float> m_linears;
	static std::vector<float> m_exps;
	static int m_isDirLight;

	/**
	 * @brief Set directional light uniforms in a shader program.
	 *
	 * @param shader The shader program to set the directional light uniforms in.
	 */
	static void SetDirectionalUniforms(Shader& shader);

	/**
	 * @brief Set point light uniforms in a shader program.
	 *
	 * @param shader The shader program to set the point light uniforms in.
	 * @param worldMatrix The world matrix of the object being rendered.
	 */
	static void SetPointUniforms(Shader& shader, glm::mat4 worldMatrix);

	/**
	 * @brief Set point light uniforms in a shader program.
	 *
	 * @param shader The shader program to set the point light uniforms in.
	 * @param worldMatrix The world matrix of the object being rendered.
	 */
	void UpdateActivePoints();
};