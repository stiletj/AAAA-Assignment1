#pragma once

#include "glm.hpp"
#include <vector>
#include <iostream>

/**
 * @class LodManager
 * @brief Class responsible for managing Level of Detail (LOD) for terrain patches.
 */
class LodManager
{
public:
    /**
     * @brief Destructor for LodManager.
     */
    ~LodManager();

    /**
     * @brief Initializes the LodManager.
     * @param patchSize Size of each terrain patch.
     * @param numPatchesX Number of patches along the X-axis.
     * @param numPatchesZ Number of patches along the Z-axis.
     * @param zfar Far clipping plane of the camera.
     * @return 0 on success, -1 on failure.
     */
    int initLodManager(int patchSize, int numPatchesX, int numPatchesZ, float zfar);

    /**
     * @brief Updates the LOD based on the camera position.
     * @param camPos Position of the camera.
     */
    void UpdateLOD(const glm::vec3& camPos);

    /**
     * @struct patchLod
     * @brief Structure representing the LOD information for a terrain patch.
     */
    struct patchLod
    {
        int Core = 0; /**< LOD level for the core region of the patch. */
        int Left = 0; /**< LOD level for the left region of the patch. */
        int Right = 0; /**< LOD level for the right region of the patch. */
        int Top = 0; /**< LOD level for the top region of the patch. */
        int Bottom = 0; /**< LOD level for the bottom region of the patch. */
    };

    /**
     * @brief Retrieves the LOD information for a terrain patch.
     * @param PatchX X-coordinate of the patch.
     * @param PatchZ Z-coordinate of the patch.
     * @return LOD information for the specified patch.
     */
    const patchLod& getPatchLod(int PatchX, int PatchZ);

private:
    /**
     * @brief Calculates the LOD regions based on the far clipping plane.
     * @param zfar Far clipping plane of the camera.
     */
    void CalcLODRegions(float zfar);

    /**
     * @brief Calculates the maximum LOD level.
     */
    void CalcMaxLOD();

    /**
     * @brief Determines the LOD level based on distance.
     * @param Distance Distance from the camera.
     * @return LOD level.
     */
    int DistanceToLOD(float Distance);

    /**
     * @brief Pass 1 of the LOD map generation.
     * @param camPos Position of the camera.
     */
    void LODMapPass1(const glm::vec3& camPos);

    /**
     * @brief Pass 2 of the LOD map generation.
     * @param camPos Position of the camera.
     */
    void LODMapPass2(const glm::vec3& camPos);

    int m_numPatchesZ = 0; /**< Number of patches along the Z-axis. */
    int m_numPatchesX = 0; /**< Number of patches along the X-axis. */
    int m_patchSize = 0; /**< Size of each terrain patch. */
    int m_maxLOD = 0; /**< Maximum LOD level. */

    patchLod** m_map; /**< 2D array representing the LOD map. */
    std::vector<int> m_regions; /**< List of LOD regions. */
};

