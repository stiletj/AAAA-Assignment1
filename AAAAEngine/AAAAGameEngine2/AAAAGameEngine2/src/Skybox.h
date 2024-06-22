#pragma once

#include <string>
#include <memory>

#include "TextureManager.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "Renderer.h"

/**
 * @class Skybox
 * @brief Class representing a skybox.
 */
class Skybox {
private:
    std::vector<std::string>& paths; /**< Vector containing paths to skybox textures. */
    unsigned int textureID; /**< ID of the skybox texture. */

    std::shared_ptr<VertexArray> m_VAO; /**< Vertex Array Object (VAO) to store the skybox vertices. */
    std::shared_ptr<VertexBuffer> m_VBO; /**< Vertex Buffer Object (VBO) to store the skybox vertices. */
    std::shared_ptr<IndexBuffer> m_IBO; /**< Index Buffer Object (IBO) to store the skybox indices. */

public:
    /**
     * @brief Constructs a Skybox object with the given paths to skybox textures.
     * @param paths Vector containing paths to skybox textures.
     */
    Skybox(std::vector<std::string>& paths);

    /**
     * @brief Default destructor for Skybox.
     */
    ~Skybox() = default;

    /**
     * @brief Renders the skybox.
     * @param renderer Reference to the renderer.
     * @param shader Reference to the shader.
     * @param viewMatrix The view matrix.
     * @param projectionMatrix The projection matrix.
     */
    void Render(const Renderer& renderer, Shader& shader, const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix);
};

