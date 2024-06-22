#pragma once

#include "ECS.h"
#include "GraphicsUtility.h"
#include "DataStructures.h"
#include "Shader.h"
#include "Renderer.h"
#include "LightingManager.h"
#include "TextureManager.h"

/**
 * @class MeshRenderer
 * @brief Class responsible for rendering meshes using ECS and OpenGL.
 */
class MeshRenderer
{
private:
    glm::mat4 m_worldMatrix; /**< World transformation matrix. */

public:
    /**
     * @brief Default constructor for MeshRenderer.
     */
    MeshRenderer();

    /**
     * @brief Destructor for MeshRenderer.
     */
    ~MeshRenderer();

    /**
     * @brief Renders meshes using ECS and OpenGL.
     * @param registry The ECS registry containing mesh entities.
     * @param renderer The Renderer object for rendering.
     * @param shader The Shader object for rendering.
     * @param viewMatrix The view matrix for the camera.
     * @param projectionMatrix The projection matrix for the camera.
     */
    void Render(ECS& registry, const Renderer& renderer, Shader& shader, const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix);

    /**
     * @brief Updates the world transformation matrix.
     * @param trans The Transform component specifying the position, rotation, and scale of the mesh.
     */
    void UpdateWorldMatrix(Transform trans);

    /**
     * @brief Retrieves the world transformation matrix.
     * @return The world transformation matrix.
     */
    glm::mat4 GetWorldMatrix();
};

