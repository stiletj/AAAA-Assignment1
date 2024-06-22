#pragma once

#include "DataStructures.h"
#include "VertexBuffer.h"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Material.h"

/**
 * @struct Vertex
 * @brief Structure representing a vertex in 3D space.
 */
struct Vertex
{
    glm::vec3 position; /**< Position of the vertex. */
    glm::vec3 normal; /**< Normal vector of the vertex. */
    glm::vec2 texCoords; /**< Texture coordinates of the vertex. */
};

/**
 * @struct Mesh
 * @brief Structure representing a mesh composed of vertices and indices.
 */
struct Mesh
{
    std::vector<Vertex> vertices; /**< Vector containing vertices of the mesh. */
    std::vector<unsigned int> indices; /**< Vector containing indices of the mesh. */
    std::shared_ptr<VertexBuffer> vb; /**< Shared pointer to the vertex buffer containing vertex data. */
    VertexBufferLayout layout; /**< Layout of the vertex buffer. */
    std::shared_ptr<VertexArray> va; /**< Shared pointer to the vertex array containing vertex attributes. */
    std::shared_ptr<IndexBuffer> ib; /**< Shared pointer to the index buffer containing index data. */
};

/**
 * @struct WholeMesh
 * @brief Structure representing a complete mesh with materials.
 */
struct WholeMesh
{
    std::vector<Material> materials; /**< Vector containing materials used in the mesh. */
    std::vector<Mesh> meshes; /**< Vector containing meshes composing the whole mesh. */

    /**
     * @brief Default constructor for WholeMesh.
     */
    WholeMesh();

    /**
     * @brief Copy constructor for WholeMesh.
     * @param mesh Another WholeMesh object to copy from.
     */
    WholeMesh(WholeMesh& mesh);

    /**
     * @brief Constructs a WholeMesh object with specified materials and meshes.
     * @param mats Vector of materials.
     * @param mesh Vector of meshes.
     */
    WholeMesh(std::vector<Material> mats, std::vector<Mesh> mesh);

    void Clear();
};
