#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "MeshComponent.h"
#include "TextureManager.h"

/**
 * @class MeshLoader
 * @brief Class responsible for loading mesh data from file using the Assimp library.
 */
class MeshLoader
{
public:
    /**
     * @brief Default constructor for MeshLoader.
     */
    MeshLoader() = default;

    /**
     * @brief Destructor for MeshLoader.
     */
    ~MeshLoader() = default;

    /**
     * @brief Loads a mesh from the specified file.
     * @param filePath The path to the mesh file.
     * @return True if the mesh is successfully loaded, false otherwise.
     */
    bool LoadMesh(const std::string& filePath);

    /**
     * @brief Retrieves the loaded mesh.
     * @return Reference to the loaded mesh.
     */
    WholeMesh& GetMesh();

private:
    WholeMesh m_wholeMesh; /**< Loaded mesh data. */

    /**
     * @brief Processes a node in the Assimp scene hierarchy.
     * @param node The node to process.
     * @param scene The Assimp scene containing the node.
     */
    void ProcessNode(aiNode* node, const aiScene* scene);

    /**
     * @brief Processes a mesh in the Assimp scene.
     * @param mesh The mesh to process.
     * @param scene The Assimp scene containing the mesh.
     */
    void ProcessMesh(aiMesh* mesh, const aiScene* scene);
};

