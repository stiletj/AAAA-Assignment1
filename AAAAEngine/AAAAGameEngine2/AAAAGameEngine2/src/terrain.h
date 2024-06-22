#pragma once

#define _USE_MATH_DEFINES

#include <fstream>
#include <string>
#include <iostream>
#include <memory>
#include <vector>
#include <cmath>

#include "GraphicsUtility.h"
#include "TextureManager.h"
#include "textureGenerator.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"
#include "Renderer.h"
#include "Shader.h"
#include "DataStructures.h"
#include "Material.h"
#include "MeshRenderer.h"
#include "LodManager.h"

/**
 * @class Terrain
 * @brief Represents a terrain object.
 */
class Terrain {
public:
	/**
	 * @brief Constructs a Terrain object with default scale values.
	 * @param scaleX The scale factor along the X-axis.
	 * @param scaleY The scale factor along the Y-axis.
	 * @param scaleZ The scale factor along the Z-axis.
	 */
	Terrain(float scaleX = 1.f, float scaleY = 1.f, float scaleZ = 1.f);

	/**
	 * @brief Constructs a Terrain object from a heightmap file.
	 * @param filename The filename of the heightmap file.
	 * @param size The size of the terrain.
	 * @param patchSize The size of a terrain patch.
	 * @param zfar The far clipping plane for LOD calculation.
	 */
	Terrain(std::string filename, int size, int patchSize, float zfar);

	/**
	 * @brief Default destructor for Terrain.
	 */
	~Terrain();

	/**
	 * @brief Loads a heightmap from a file.
	 * @param fileName The filename of the heightmap file.
	 * @param size The size of the terrain.
	 * @param patchSize The size of a terrain patch.
	 * @param zfar The far clipping plane for LOD calculation.
	 * @return True if the heightmap was loaded successfully, false otherwise.
	 */
	bool loadHeightMap(const std::string& fileName, const int size, int patchSize, float zfar);

	/**
	 * @brief Loads a texture for the terrain.
	 * @param fileName The filename of the texture file.
	 * @param ambient The ambient color of the material.
	 * @param diffuse The diffuse color of the material.
	 * @param specular The specular color of the material.
	 * @param specEx The specular exponent of the material.
	 */
	void loadTerrainTexture(const std::string& fileName, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float specEx);

	/**
	 * @brief Loads a detail map texture for the terrain.
	 * @param fileName The filename of the detail map texture file.
	 */
	void loadDetailMapTexture(const std::string& fileName);

	/**
	 * @brief Gets the height at a specific position on the terrain.
	 * @param xpos The x-coordinate position.
	 * @param zpos The z-coordinate position.
	 * @return The height at the specified position.
	 */
	float getHeight(int xpos, int zpos);

	/**
	 * @brief Gets the size of the terrain.
	 * @return The size of the terrain.
	 */
	const int getSize() const;

	/**
	 * @brief Renders the terrain.
	 * @param renderer The renderer used for rendering.
	 * @param shader The shader used for rendering.
	 * @param viewMatrix The view matrix.
	 * @param projectionMatrix The projection matrix.
	 * @param CameraPosition The position of the camera.
	 */
	void render(const Renderer& renderer, Shader& shader, const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix, glm::vec3 CameraPosition);

	/**
	 * @brief Creates a procedural texture for the terrain.
	 * @param ambient The ambient color of the material.
	 * @param diffuse The diffuse color of the material.
	 * @param specular The specular color of the material.
	 * @param specEx The specular exponent of the material.
	 * @return True if the procedural texture was created successfully, false otherwise.
	 */
	bool createProceduralTexture(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float specEx);

	/**
	 * @brief Generates a terrain using the fault formation algorithm.
	 * @param iterations The number of iterations for the algorithm.
	 * @param hSize The size of the terrain.
	 * @param minHeight The minimum height of the terrain.
	 * @param maxHeight The maximum height of the terrain.
	 * @param weight The weight parameter for the algorithm.
	 * @param random Flag indicating whether to use random values.
	 * @param patchSize The size of a terrain patch.
	 * @param zfar The far clipping plane for LOD calculation.
	 * @return True if the terrain was generated successfully, false otherwise.
	 */
	bool genFaultFormation(int iterations, int hSize, int minHeight, int maxHeight, float weight, bool random, int patchSize, float zfar);

	/**
	 * @brief Sets the height at a specific position on the terrain.
	 * @param height The height value to set.
	 * @param xpos The x-coordinate position.
	 * @param zpos The z-coordinate position.
	 */
	void setHeightAtPoint(float height, int xpos, int zpos);

	/**
	 * @brief Adds a procedural texture to the terrain.
	 * @param fileName The filename of the procedural texture file.
	 * @return True if the procedural texture was added successfully, false otherwise.
	 */
	bool addProceduralTexture(const std::string& fileName);

	int GetMaxHeight();

	int GetMinHeight();

	std::vector<float> GetVertices();

private:
    int m_Size; /**< The size of the terrain. */
    unsigned int m_Width; /**< The width of the terrain. */
    unsigned int m_Length; /**< The length of the terrain. */

    std::vector<float> m_Heights; /**< The heights of the terrain vertices. */
    std::vector<float> m_Vertices;
    float scaleX; /**< The scaling factor in the x-axis. */
    float scaleY; /**< The scaling factor in the y-axis. */
    float scaleZ; /**< The scaling factor in the z-axis. */

	int m_MaxHeight;
	int m_MinHeight;

    TextureGenerator texGen; /**< The texture generator used for procedural textures. */
    std::string terrainTextureFile; /**< The filename of the terrain texture. */
    std::string detailMapTextureFile; /**< The filename of the detail map texture. */

    VertexArray m_VAO; /**< The Vertex Array Object for rendering. */
    std::unique_ptr<VertexBuffer> m_VBO; /**< The Vertex Buffer Object for storing vertex data. */
    std::unique_ptr<IndexBuffer> m_IBO; /**< The Index Buffer Object for storing indices. */

    Material material; /**< The material used for rendering the terrain. */

    int m_patchSize; /**< The size of a terrain patch. */
    int m_maxLOD; /**< The maximum level of detail for the terrain. */

    struct SingleLODInfo
    {
        int Start = 0, Count = 0; /**< Start and count values for a single level of detail. */
    };

    #define LEFT 2 /**< Number of left LODs. */
    #define RIGHT 2 /**< Number of right LODs. */
    #define TOP 2 /**< Number of top LODs. */
    #define BOTTOM 2 /**< Number of bottom LODs. */

    struct LODInfo
    {
        SingleLODInfo info[LEFT][RIGHT][TOP][BOTTOM]; /**< Information about LODs. */
    };

    std::vector<LODInfo> m_LODinfo; /**< Vector storing information about LODs. */
    int m_numPatchesX = 0; /**< Number of patches in the x-direction. */
    int m_numPatchesZ = 0; /**< Number of patches in the z-direction. */

    LodManager m_LODManager; /**< The LOD manager for managing level of detail. */

    /**
     * @brief Adds a triangle to the index buffer.
     * @param Index The current index in the index buffer.
     * @param Indices The vector storing indices.
     * @param v1 The index of vertex 1.
     * @param v2 The index of vertex 2.
     * @param v3 The index of vertex 3.
     * @return The updated index.
     */
    unsigned int AddTriangle(unsigned int Index, std::vector<unsigned int>& Indices, unsigned int v1, unsigned int v2, unsigned int v3);

    /**
     * @brief Initializes the index buffer.
     * @param Indices The vector storing indices.
     * @return The number of indices.
     */
    int InitIndices(std::vector<unsigned int>& Indices);

    /**
     * @brief Initializes the index buffer for a given level of detail.
     * @param Index The current index in the index buffer.
     * @param indices The vector storing indices.
     * @param LOD The level of detail.
     * @return The number of indices.
     */
    int InitIndicesLOD(int Index, std::vector<unsigned int>& indices, int LOD);

    /**
     * @brief Initializes the index buffer for a given level of detail (single patch).
     * @param Index The current index in the index buffer.
     * @param indices The vector storing indices.
     * @param LODCore The level of detail for the core patch.
     * @param LODLeft The level of detail for the left patch.
     * @param LODRight The level of detail for the right patch.
     * @param LODTop The level of detail for the top patch.
     * @param LODBottom The level of detail for the bottom patch.
     * @return The number of indices.
     */
    int InitIndicesLODSingle(int Index, std::vector<unsigned int>& indices, int LODCore, int LODLeft, int LODRight, int LODTop, int LODBottom);

    /**
     * @brief Creates a triangle fan for a given patch.
     * @param Index The current index in the index buffer.
     * @param indices The vector storing indices.
     * @param LODCore The level of detail for the core patch.
     * @param LODLeft The level of detail for the left patch.
     * @param LODRight The level of detail for the right patch.
     * @param LODTop The level of detail for the top patch.
     * @param LODBottom The level of detail for the bottom patch.
     * @param x The x-coordinate of the patch.
     * @param z The z-coordinate of the patch.
     * @return The number of indices.
     */
    unsigned int createTriangeFan(int Index, std::vector<unsigned int>& indices, int LODCore, int LODLeft, int LODRight, int LODTop, int LODBottom, int x, int z);

    /**
     * @brief Calculates the number of indices.
     * @return The number of indices.
     */
    int calcNumIndices();

    /**
     * @brief Generates the vertex and index buffers for the terrain.
     */
    void generateTerrainBuffers();

    /**
     * @brief Calculates normals for the terrain based on vertices and indices.
     * @param Vertices The vector storing vertex positions.
     * @param Indices The vector storing indices.
     */
    void CalcLODNormals(std::vector<float>& Vertices, std::vector<unsigned int>& Indices);

    /**
     * @brief Creates a geomipmap grid for the terrain.
     * @param width The width of the terrain.
     * @param depth The depth of the terrain.
     * @param patchSize The size of a terrain patch.
     * @param zfar The far clipping plane for LOD calculation.
     */
    void CreateGeomipmapGrid(int width, int depth, int patchSize, float zfar);

    /**
     * @brief Applies a filter pass to the terrain data.
     * @param startP Pointer to the start of the terrain data.
     * @param increment The increment for the filter pass.
     * @param weight The weight of the filter pass.
     */
    void filterPass(float* startP, int increment, float weight);

    /**
     * @brief Adds a filter to the terrain data.
     * @param terrainData The vector storing terrain data.
     * @param weight The weight of the filter.
     */
    void addFilter(std::vector<float>& terrainData, float weight);

    /**
     * @brief Normalizes the terrain data.
     * @param terrainData The vector storing terrain data.
     */
    void normaliseTerrain(std::vector<float>& terrainData);

    /**
     * @brief Calculates the normal at a specific position on the terrain.
     * @param x The x-coordinate position.
     * @param z The z-coordinate position.
     * @return The normal vector.
     */
    glm::vec3 CalcNormal(int x, int z);

    /**
     * @brief Checks if a position is within the bounds of the terrain.
     * @param xpos The x-coordinate position.
     * @param zpos The z-coordinate position.
     * @return True if the position is within bounds, false otherwise.
     */
    bool inbounds(int xpos, int zpos);

    /**
     * @brief Calculates the texture coordinates for a given texture number.
     * @param texNum The texture number.
     * @param x The x-coordinate of the texture coordinate.
     * @param y The y-coordinate of the texture coordinate.
     */
    void getTexCoord(int texNum, unsigned int& x, unsigned int& y);

};
