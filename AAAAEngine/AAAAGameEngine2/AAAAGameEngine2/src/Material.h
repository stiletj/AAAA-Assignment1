#pragma once

#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

#include "DataStructures.h"

/**
 * @class Material
 * @brief Class representing a material used for rendering.
 */
class Material
{
public:
    /**
     * @brief Default constructor for Material.
     */
    Material();

    /**
     * @brief Constructs a Material object from the specified input file.
     * @param inputFile Path to the input file.
     */
    Material(std::string inputFile);

    /**
     * @brief Destructor for Material.
     */
    ~Material();

    /**
     * @brief Retrieves the ambient color of the material.
     * @return The ambient color.
     */
    const glm::vec3 GetAmbient() const;

    /**
     * @brief Sets the ambient color of the material.
     * @param ambient The ambient color to set.
     */
    void SetAmbient(glm::vec3 ambient);

    /**
     * @brief Retrieves the specular color of the material.
     * @return The specular color.
     */
    const glm::vec3 GetSpecular() const;

    /**
     * @brief Sets the specular color of the material.
     * @param specular The specular color to set.
     */
    void SetSpecular(glm::vec3 specular);

    /**
     * @brief Retrieves the specular exponent of the material.
     * @return The specular exponent.
     */
    const float GetSpecularExponent() const;

    /**
     * @brief Sets the specular exponent of the material.
     * @param exp The specular exponent to set.
     */
    void SetSpecularExponent(float exp);

    /**
     * @brief Retrieves the diffuse color of the material.
     * @return The diffuse color.
     */
    const glm::vec3 GetDiffuse() const;

    /**
     * @brief Sets the diffuse color of the material.
     * @param diffuse The diffuse color to set.
     */
    void SetDiffuse(glm::vec3 diffuse);

    /**
     * @brief Retrieves the name of the material.
     * @return The name of the material.
     */
    const std::string GetName() const;

    /**
     * @brief Sets the name of the material.
     * @param name The name to set.
     */
    void SetName(std::string name);

    /**
     * @brief Retrieves the texture file used by the material.
     * @return The path to the texture file.
     */
    const std::string GetTexture() const;

    /**
     * @brief Sets the texture file used by the material.
     * @param filePath The path to the texture file.
     */
    void SetTextureFile(std::string filePath);

private:
    glm::vec3 m_ambientColour; /**< Ambient color of the material. */
    glm::vec3 m_diffuseColour; /**< Diffuse color of the material. */
    glm::vec3 m_specularColour; /**< Specular color of the material. */
    float m_specularExponent; /**< Specular exponent of the material. */
    std::string m_materialName; /**< Name of the material. */
    std::string m_textureFile; /**< Path to the texture file used by the material. */
};

/**
 * @brief Reads a Wavefront .mtl file and returns a vector of Material objects.
 * @param inputFile Path to the .mtl file.
 * @return Vector of Material objects read from the file.
 */
std::vector<Material> readMTLFile(std::string inputFile);
