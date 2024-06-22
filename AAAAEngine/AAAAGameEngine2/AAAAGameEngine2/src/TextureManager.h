#pragma once

#include <iostream>
#include <string>
#include <unordered_map>
#include "Image.h"
#include "GraphicsUtility.h"

/**
 * @enum TextureType
 * @brief Enumeration of texture types.
 */
enum class TextureType {
    DEFAULT, /**< Default texture type. */
    CUBEMAP /**< Cubemap texture type. */
};

/**
 * @class TextureManager
 * @brief A class for managing textures in OpenGL.
 */
class TextureManager {
private:
    std::unordered_map<std::string, unsigned int> m_Textures; /**< Map to store textures */

    /**
     * @brief Private constructor to enforce singleton pattern.
     */
    TextureManager() {}

public:
    TextureManager(const TextureManager&) = delete;
    TextureManager& operator=(const TextureManager&) = delete;

    /**
     * @brief Destructor to clean up resources.
     */
    ~TextureManager();

    /**
     * @brief Get the singleton instance of TextureManager.
     * @return Reference to the TextureManager instance.
     */
    static TextureManager& GetInstance();

    /**
     * @brief Updates an existing texture.
     * @param path The file path of the texture to update.
     * @return The ID of the updated texture.
     */
    unsigned int updateTexture(const std::string& path);

    /**
     * @brief Loads a texture from the specified file path.
     * @param path The file path of the texture.
     * @param type The type of the texture (default: TextureType::DEFAULT).
     * @return The ID of the loaded texture.
     */
    unsigned int LoadTexture(const std::string& path, TextureType type = TextureType::DEFAULT);

    /**
     * @brief Loads a cubemap texture from the specified file paths.
     * @param paths The file paths of the cubemap textures.
     * @param type The type of the texture (default: TextureType::CUBEMAP).
     * @return The ID of the loaded cubemap texture.
     */
    unsigned int LoadTexture(const std::vector<std::string>& paths, TextureType type = TextureType::CUBEMAP);

    //unsigned int LoadCubeMap(const std::string& path);

    /**
     * @brief Creates a new OpenGL texture from the provided image data.
     * @param name The name to associate with the created texture.
     * @param image The image data used to create the texture.
     * @return The ID of the created texture.
     */
    unsigned int CreateTexture(const std::string& name, Image& image);

    /**
     * @brief Get texture ID by its path.
     * @param path The path of the texture.
     * @return The ID of the texture, or 0 if not found.
     */
    unsigned int GetTexture(const std::string& path) const;

    /**
     * @brief Binds the texture correlating to id
     * @param id The id of the texture to bind.
     */
    void Bind(const unsigned int id, TextureType type = TextureType::DEFAULT, int slot = 0) const;

    void Unbind() const;

    /**
     * @brief Activate a texture for rendering.
     * This function binds and enables the specified texture.
     * @param path The path of the texture to activate.
     */
    void SetActiveTexture(const std::string& path, TextureType type = TextureType::DEFAULT, int slot = 0) const;

    /**
     * @brief Delete all textures managed by the TextureManager.
     */
    void DeleteAllTextures();
};