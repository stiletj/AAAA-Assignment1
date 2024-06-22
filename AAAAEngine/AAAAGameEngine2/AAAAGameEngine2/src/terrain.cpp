#include "Terrain.h"

Terrain::Terrain(float scaleX, float scaleY, float scaleZ) : scaleX(scaleX), scaleY(scaleY), scaleZ(scaleZ), m_Width(0), m_Length(0), m_Size(0) {}

Terrain::Terrain(std::string filename, int size, int patchSize, float zfar)
{
	loadHeightMap(filename, size, patchSize, zfar);
}

Terrain::~Terrain() {}

bool Terrain::loadHeightMap(const std::string& fileName, const int size, int patchSize, float zfar)
{
    std::ifstream file(fileName, std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "Failed to open heightmap file: " << fileName << std::endl;
        return false;
    }

    m_Size = size;
    m_Width = size;
    m_Length = size;
    m_Heights.resize(size * size);


    //file.read(reinterpret_cast<char*>(m_Heights.data()), size * size * sizeof(float));

    // Read heightmap data
    for (int i = 0; i < size * size; ++i) {
        unsigned char height;
        file.read(reinterpret_cast<char*>(&height), sizeof(unsigned char));
        m_Heights[i] = static_cast<float>(height);
    }

    file.close();

    CreateGeomipmapGrid(m_Width, m_Length, patchSize, zfar);

    return true;
}

void Terrain::loadTerrainTexture(const std::string& fileName, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float specEx)
{
	material.SetTextureFile(fileName);
    material.SetAmbient(ambient);
    material.SetDiffuse(diffuse);
    material.SetSpecular(specular);
    material.SetSpecularExponent(specEx);

	TextureManager::GetInstance().LoadTexture(fileName);
}

void Terrain::loadDetailMapTexture(const std::string& fileName)
{
	detailMapTextureFile = fileName;
	TextureManager::GetInstance().LoadTexture(fileName);
}

float Terrain::getHeight(int xpos, int zpos)
{
	if (inbounds(xpos, zpos)) {
		return ((float)(m_Heights[(zpos * m_Size) + xpos]));
	}
	return 0.0f;
}

const int Terrain::getSize() const
{
    return m_Size;
}

void Terrain::render(const Renderer& renderer, Shader& shader, const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix, glm::vec3 CameraPosition)
{
    MeshRenderer rend;
    Transform trans(glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));

    rend.UpdateWorldMatrix(trans);

    glm::mat4 mvpMatrix = projectionMatrix * viewMatrix;
    glm::vec2 terrainSize = glm::vec2(m_Width, m_Length);

    m_LODManager.UpdateLOD(CameraPosition);

    shader.Bind();

    // Set uniform matrices
    shader.SetUniformMat4f("u_MVP", mvpMatrix);
    shader.SetUniform2f("terrainSize", terrainSize);

    // Set lighting uniforms
    LightingManager::SetLightingUniforms(shader, rend.GetWorldMatrix());
    shader.SetUniform1i("u_IsLight", LightingManager::GetIsDirLight());

    // Set camera pos uniform
    glm::vec3 cameraPosition = glm::vec3(glm::inverse(viewMatrix)[3]);
    glm::vec4 cameraPositionVec4 = { cameraPosition, 1.0f };
    glm::vec4 localCamPosVec4 = cameraPositionVec4 * glm::vec4(0, 0, 0, 0);
    glm::vec3 localCamPos = { localCamPosVec4.x, localCamPosVec4.y, localCamPosVec4.z };
    shader.SetUniform3f("u_LocalCamPos", localCamPos);

    // Set material properties
    //shader.SetUniform4f("u_AmbientColour", { material.GetAmbient(), 1.0f });
    shader.SetUniform4f("u_AmbientColour", glm::vec4(material.GetDiffuse(), 1));
    shader.SetUniform4f("u_DiffuseColour", glm::vec4(material.GetDiffuse(), 1));
    shader.SetUniform4f("u_SpecularColour", glm::vec4(material.GetSpecular(), 1));
    shader.SetUniform1f("u_SpecularExponent", material.GetSpecularExponent());


    if (!material.GetTexture().empty()) {
        TextureManager::GetInstance().SetActiveTexture(material.GetTexture(), TextureType::DEFAULT, 0);
        shader.SetUniform1i("u_Texture1", 0);
        shader.SetUniform1f("u_TextureSet", 1);
    }
    else
    {
        shader.SetUniform1f("u_TextureSet", 0);
    }

    if (!detailMapTextureFile.empty()) {
        TextureManager::GetInstance().SetActiveTexture(detailMapTextureFile, TextureType::DEFAULT, 1);
        shader.SetUniform1i("u_Texture2", 1);
    }

    float PatchSize = ((float)m_patchSize - 1.0f) * 1;
    float halfPatchSize = PatchSize / 2;

    std::vector<int> baseVertexGroup;
    std::vector<size_t> baseIndiceGroup;

    for (int PatchZ = 0; PatchZ < m_numPatchesZ; PatchZ++)
    {
        for (int PatchX = 0; PatchX < m_numPatchesX; PatchX++)
        {
            int z = PatchZ * (m_patchSize - 1);
            int x = PatchX * (m_patchSize - 1);

            const LodManager::patchLod& PLOD = m_LODManager.getPatchLod(PatchX, PatchZ);

            int C = PLOD.Core;
            int L = PLOD.Left;
            int R = PLOD.Right;
            int T = PLOD.Top;
            int B = PLOD.Bottom;

            size_t baseIndex = sizeof(unsigned int) * m_LODinfo[C].info[L][R][T][B].Start;

            int baseVertex = z * m_Width + x;

            baseIndiceGroup.push_back(baseIndex);

            renderer.TerrainRender(m_VAO, *m_IBO, shader, GraphicsEnum::TRIANGLES, m_LODinfo[C].info[L][R][T][B].Count, GraphicsEnum::UNSIGNED_INT, (void*)baseIndex, baseVertex);
        }
    }

    TextureManager::GetInstance().Unbind();
    shader.Unbind();

}

bool Terrain::createProceduralTexture(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float specEx)
{
    int size = m_Size - 1; 

    if (m_Heights.empty() || texGen.getNumTextures() == 0)
    {
        return false;
    }

    unsigned char curHeight; //current height in the heightmap
    float weight; //weight of influence of tex to height
    //setup room for the new texture
    texGen.setupNewTexture(size, size);
    ImgRGB<unsigned char> color;
    ImgRGB<unsigned char> totalColor;
    float range = texGen.getRange();
    //loop through each point in the heightmap
    // and get height value
        for (int z = 0; z < size; z++) {
            for (int x = 0; x < size; x++) {
                totalColor.reset();
                curHeight = getHeight(x, z);
                //calculate the contribution from for each texture
                for (int i = 0; i < texGen.getNumTextures(); i++) {
                    weight = (range - abs((float)curHeight - texGen.getTextureMax(i))) / range;
                    if (weight > 0.0) {
                        unsigned int texX = x;
                        unsigned int texZ = z;
                        getTexCoord(i, texX, texZ);
                        color = texGen.getColor(i, texX, texZ);
                        totalColor.r += color.r * weight;
                        totalColor.g += color.g * weight;
                        totalColor.b += color.b * weight;
                    } // end if
                } // end for i
                //add the combined color to the new texture.
                texGen.setColor(x, z, totalColor);
                ambient.x += totalColor.r;
                ambient.y += totalColor.g;
                ambient.z += totalColor.b;
            } // end for x
        } // end for z
        //load the new texture into memory ready for use

        ambient.x = ambient.x / (size * size);
        ambient.y = ambient.y / (size * size);
        ambient.z = ambient.z / (size * size);

        material.SetTextureFile("terrain");
        material.SetAmbient(ambient);
        material.SetDiffuse(diffuse);
        material.SetSpecular(specular);
        material.SetSpecularExponent(specEx);

    TextureManager::GetInstance().CreateTexture(material.GetTexture(), texGen.getTex());
    return true;
}

void Terrain::setHeightAtPoint(float height, int xpos, int zpos)
{
    if (inbounds(xpos, zpos))
    {
        m_Heights[zpos * m_Size + xpos] = height;
    }
}

bool Terrain::inbounds(int xpos, int zpos)
{
    return (xpos >= 0 && xpos < m_Size && zpos >= 0 && zpos < m_Size);
}

void Terrain::getTexCoord(int texNum, unsigned int& x, unsigned int& y)
{
    unsigned int height = texGen.getTexHeight(texNum);
    unsigned int width = texGen.getTexWidth(texNum);

    int repeatX = -1; // number of repeats in X direction
    int repeatY = -1; // number of repeats in Y direction
    int i = 0;

    // loop until we figure out how many times the tile
    // has repeated (on the X axis)
    while (repeatX == -1) {
        i++;
        //if x is less than the total width, found
        if (x < (width * i)) {
            repeatX = i - 1;
        }
    }

    // loop until we figure out how many times the tile
    // has repeated (on the Y axis)
    i = 0;
    while (repeatY == -1) {
        i++;
        //if y is less than the total height good
        if (y < (height * i)) {
            repeatY = i - 1;
        }
    }
    // update the given texture coordinates
    x = x - (width * repeatX);
    y = y - (height * repeatY);

}

unsigned int Terrain::AddTriangle(unsigned int Index, std::vector<unsigned int>& Indices, unsigned int v1, unsigned int v2, unsigned int v3)
{
    //std::cout << "Index: " << Index << " Size: " << Indices.size() << std::endl;
    assert(Index < Indices.size());
    Indices[Index++] = v1;
    assert(Index < Indices.size());
    Indices[Index++] = v2;
    assert(Index < Indices.size());
    Indices[Index++] = v3;

    return Index;
}

int Terrain::InitIndices(std::vector<unsigned int>& Indices)
{

    int Index = 0;

    for (int LOD = 0; LOD <= m_maxLOD; LOD++)
    {
        Index = InitIndicesLOD(Index, Indices, LOD);
    }

    return Index;
    
}

int Terrain::InitIndicesLOD(int Index, std::vector<unsigned int>& indices, int LOD)
{
    int TotalIndicesForLOD = 0;

    for (int l = 0; l < LEFT; l++)
    {
        for (int r = 0; r < RIGHT; r++)
        {
            for (int t = 0; t < TOP; t++)
            {
                for (int b = 0; b < BOTTOM; b++)
                {
                    m_LODinfo[LOD].info[l][r][t][b].Start = Index;
                    Index = InitIndicesLODSingle(Index, indices, LOD, LOD + l, LOD + r, LOD + t, LOD + b);

                    m_LODinfo[LOD].info[l][r][t][b].Count = Index - m_LODinfo[LOD].info[l][r][t][b].Start;
                    //TotalIndicesForLOD += m_LODinfo[LOD].info[l][r][t][b].Count;

                }
            }
        }
    }

    return Index;
}

int Terrain::InitIndicesLODSingle(int Index, std::vector<unsigned int>& indices, int LODCore, int LODLeft, int LODRight, int LODTop, int LODBottom)
{
    int fanStep = std::pow(2, LODCore + 1);

    int EndPos = m_patchSize - 1 - fanStep;

    for (int z = 0; z <= EndPos; z += fanStep)
    {
        for (int x = 0; x <= EndPos; x += fanStep)
        {
            int lLeft = x == 0 ? LODLeft : LODCore;
            int lRight = x == EndPos ? LODRight : LODCore;
            int lBottom = x == 0 ? LODBottom : LODCore;
            int lTop = x == EndPos ? LODTop : LODCore;
        
            Index = createTriangeFan(Index, indices, LODCore, lLeft, lRight, lTop, lBottom, x, z);
        }
    }

    return Index;

}

unsigned int Terrain::createTriangeFan(int Index, std::vector<unsigned int>& indices, int LODCore, int LODLeft, int LODRight, int LODTop, int LODBottom, int x, int z)
{

    int StepLeft = std::pow(2, LODLeft);
    int StepRight = std::pow(2, LODRight);
    int StepTop = std::pow(2, LODTop);
    int StepBottom = std::pow(2, LODBottom);
    int StepCenter = std::pow(2, LODCore);

    unsigned int IndexCenter = (z + StepCenter) * m_Width + x + StepCenter;

    unsigned int IndexTemp1 = z * m_Width + x;
    unsigned int IndexTemp2 = (z + StepLeft) * m_Width + x;

    Index = AddTriangle(Index, indices, IndexCenter, IndexTemp1, IndexTemp2);

    if (LODLeft == LODCore) {
        IndexTemp1 = IndexTemp2;
        IndexTemp2 += StepLeft * m_Width;

        Index = AddTriangle(Index, indices, IndexCenter, IndexTemp1, IndexTemp2);
    }

    IndexTemp1 = IndexTemp2;
    IndexTemp2 += StepTop;

    Index = AddTriangle(Index, indices, IndexCenter, IndexTemp1, IndexTemp2);

    if (LODTop == LODCore) {
        IndexTemp1 = IndexTemp2;
        IndexTemp2 += StepTop;

        Index = AddTriangle(Index, indices, IndexCenter, IndexTemp1, IndexTemp2);
    }

    IndexTemp1 = IndexTemp2;
    IndexTemp2 -= StepRight * m_Width;

    Index = AddTriangle(Index, indices, IndexCenter, IndexTemp1, IndexTemp2);

    if (LODRight == LODCore) {
        IndexTemp1 = IndexTemp2;
        IndexTemp2 -= StepRight * m_Width;

        Index = AddTriangle(Index, indices, IndexCenter, IndexTemp1, IndexTemp2);
    }

    IndexTemp1 = IndexTemp2;
    IndexTemp2 -= StepBottom;

    Index = AddTriangle(Index, indices, IndexCenter, IndexTemp1, IndexTemp2);

    if (LODBottom == LODCore) {
        IndexTemp1 = IndexTemp2;
        IndexTemp2 -= StepBottom;

        Index = AddTriangle(Index, indices, IndexCenter, IndexTemp1, IndexTemp2);
    }

    return Index;

}

int Terrain::calcNumIndices()
{
    int NumQUADS = (m_patchSize - 1) * (m_patchSize - 1);
    int numIndices = 0;
    int MaxPermsPerLevel = 16;
    const int IndicesPerQUAD = 6;

    for (int LOD = 0; LOD <= m_maxLOD; LOD++)
    {
        numIndices += NumQUADS * IndicesPerQUAD * MaxPermsPerLevel;
        NumQUADS /= 4;

    }

    return numIndices;
}

void Terrain::CalcLODNormals(std::vector<float>& Vertices, std::vector<unsigned int>& Indices)
{
    unsigned int Index = 0;

    int vertSize = 3;
    int texSize = 2;
    int normSize = 3;
    
    for (int z = 0; z < m_Length - 1; z += (m_patchSize - 1))
    {
        for (int x = 0; x < m_Width - 1; x += (m_patchSize - 1))
        {
            int baseVertex = z * m_Width + x;
            int numIndices = m_LODinfo[0].info[0][0][0][0].Count;;

            for (int i = 0; i < numIndices; i += 3)
            {
                unsigned int Index0 = baseVertex + Indices[i];
                unsigned int Index1 = baseVertex + Indices[i + 1];
                unsigned int Index2 = baseVertex + Indices[i + 2];


                glm::vec3 vec1 = glm::vec3(Vertices[(Index1 * 8)], Vertices[(Index1 * 8) + 1], Vertices[(Index1 * 8) + 2]) - glm::vec3(Vertices[(Index0 * 8)], Vertices[(Index0 * 8) + 1], Vertices[(Index0 * 8) + 2]);
                glm::vec3 vec2 = glm::vec3(Vertices[(Index2 * 8)], Vertices[(Index2 * 8) + 1], Vertices[(Index2 * 8) + 2]) - glm::vec3(Vertices[(Index0 * 8)], Vertices[(Index0 * 8) + 1], Vertices[(Index0 * 8) + 2]);
            
                glm::vec3 Normal = glm::cross(vec1, vec2);

                Normal = glm::normalize(Normal);

                Vertices[(Index0 * 8) + vertSize + texSize] += Normal.x;
                Vertices[(Index0 * 8) + vertSize + texSize + 1] += Normal.y;
                Vertices[(Index0 * 8) + vertSize + texSize + 2] += Normal.z;

                Vertices[(Index1 * 8) + vertSize + texSize] += Normal.x;
                Vertices[(Index1 * 8) + vertSize + texSize + 1] += Normal.y;
                Vertices[(Index1 * 8) + vertSize + texSize + 2] += Normal.z;

                Vertices[(Index2 * 8) + vertSize + texSize] += Normal.x;
                Vertices[(Index2 * 8) + vertSize + texSize + 1] += Normal.y;
                Vertices[(Index2 * 8) + vertSize + texSize + 2] += Normal.z;
            }
        }
    }

    for (int i = 0; i < Vertices.size() / 8; i ++)
    {
        glm::vec3 normal = glm::normalize(glm::vec3(Vertices[(i * 8) + vertSize + texSize], Vertices[(i * 8) + vertSize + texSize + 1], Vertices[(i * 8) + vertSize + texSize + 2]));

        Vertices[(i * 8) + vertSize + texSize] = normal.x;
        Vertices[(i * 8) + vertSize + texSize + 1] = normal.y;
        Vertices[(i * 8) + vertSize + texSize + 2] = normal.z;
        //std::cout << Vertices[(i * 8) + vertSize + texSize] << " " << Vertices[(i * 8) + vertSize + texSize + 1] << " " << Vertices[(i * 8) + vertSize + texSize + 2] << std::endl;
    }
}

void Terrain::CreateGeomipmapGrid(int width, int depth, int patchSize, float zfar)
{
    if ((width - 1) % (patchSize - 1) != 0) {
        int RecommendedWidth = ((width - 1 + patchSize - 1) / (patchSize - 1)) * (patchSize - 1) + 1;
        printf("Width minus 1 (%d) must be divisible by PatchSize minus 1 (%d)\n", width, patchSize);
        printf("Try using Width = %d\n", RecommendedWidth);
        exit(0);
    }

    if ((depth - 1) % (patchSize - 1) != 0) {
        int RecommendedDepth = ((depth - 1 + patchSize - 1) / (patchSize - 1)) * (patchSize - 1) + 1;
        printf("Depth minus 1 (%d) must be divisible by PatchSize minus 1 (%d)\n", depth, patchSize);
        printf("Try using Width = %d\n", RecommendedDepth);
        exit(0);
    }

    if (patchSize < 3) {
        printf("The minimum patch size is 3 (%d)\n", patchSize);
        exit(0);
    }

    if (patchSize % 2 == 0) {
        printf("Patch size must be an odd number (%d)\n", patchSize);
        exit(0);
    }

    m_Width = width;
    m_Length = depth;
    m_patchSize = patchSize;

    m_numPatchesX = (width - 1) / (patchSize - 1);
    m_numPatchesZ = (depth - 1) / (patchSize - 1);

    m_maxLOD = m_LODManager.initLodManager(patchSize, m_numPatchesX, m_numPatchesZ, zfar);

    m_LODinfo.resize(m_maxLOD + 1);

    generateTerrainBuffers();

}

void Terrain::filterPass(float* startP, int increment, float weight)
{
	float yprev = *startP;
	int j = increment;
	float k = weight;

	for (int i = 1; i < m_Size; i++) {
		*(startP + j) = k * yprev + (1 - k) * (*(startP + j));
		yprev = *(startP + j);
		j += increment;
	}
}

void Terrain::addFilter(std::vector<float>& terrainData, float weight)
{
	// Erode left to right, starting from the beginning of each row
	for (int i = 0; i < m_Size; i++) {
		filterPass(&terrainData[m_Size * i], 1, weight);
	}

	// Erode right to left, starting from the end of each row
	for (int i = 0; i < m_Size; i++) {
		filterPass(&terrainData[m_Size * i + m_Size - 1], -1, weight);
	}

	// Erode top to bottom, starting from the beginning of each column
	for (int i = 0; i < m_Size; i++) {
		filterPass(&terrainData[i], m_Size, weight);
	}

	// Erode bottom to top, starting from the end of each column
	for (int i = 0; i < m_Size; i++) {
		filterPass(&terrainData[m_Size * (m_Size - 1) + i], -m_Size, weight);
	}
}

void Terrain::normaliseTerrain(std::vector<float>& terrainData)
{
	float fMin = terrainData[0];
	float fMax = terrainData[0];
	float fHeight;

	// Find the min and max values of the height terrainData
	for (int i = 1; i < m_Size * m_Size; i++) {
		if (terrainData[i] > fMax) {
			fMax = terrainData[i];
		}
		else if (terrainData[i] < fMin) {
			fMin = terrainData[i];
		}
	}

	// Find the range of the altitude
	if (fMax <= fMin) {
		return;
	}

	fHeight = fMax - fMin;

	// Scale the values to a range of 0-255
	for (int i = 0; i < m_Size * m_Size; i++) {
		terrainData[i] = ((terrainData[i] - fMin) / fHeight) * 255.0f;
	}
}

bool Terrain::genFaultFormation(int iterations, int hSize, int minHeight, int maxHeight, float weight, bool random, int patchSize, float zfar)
{
    int x1, x2, z1, z2;
    std::vector<float> data;
    int displacement;

    if (hSize <= 0) {
        return false;
    }

    if (random)
    {
        srand(static_cast<unsigned int>(time(NULL)));
    }

    m_Size = hSize;
    data.resize(m_Size * m_Size, 0);
    m_Heights.resize(m_Size * m_Size);

    // Generate heightfield
    for (int j = 0; j < iterations; j++) {
        // Calculate the displacement value for the current iteration
        displacement = maxHeight - ((maxHeight - minHeight) * j) / iterations;

        // Pick the first random point P1(x1, z1) from the height map
        x1 = (rand() % m_Size);
        z1 = (rand() % m_Size);

        // Pick up the second random point P2(x2, z2) and make sure it is different from the first point
        do {
            x2 = (rand() % m_Size);
            z2 = (rand() % m_Size);
        } while (x2 == x1 && z2 == z1);

        // For each point P(x, z) in the field, calculate the new height values
        for (int z = 0; z < m_Size; z++) {
            for (int x = 0; x < m_Size; x++) {
                // Determine which side of the line P1P2 the point P lies in
                if (((x - x1) * (z2 - z1) - (x2 - x1) * (z - z1)) > 0) {
                    data[(z * m_Size) + x] += static_cast<float>(displacement);
                }
            }
        }
        addFilter(data, weight);
    }

    // Normalise the heightfield
    normaliseTerrain(data);

    // Copy the float heightfield to terrainData (in unsigned char)
    for (int z = 0; z < m_Size; z++) {
        for (int x = 0; x < m_Size; x++) {
            setHeightAtPoint(data[(z * m_Size) + x], x, z);
        }
    }

    m_Heights = data;

    CreateGeomipmapGrid(m_Size, m_Size, patchSize, zfar);

    return true;
}


bool Terrain::addProceduralTexture(const std::string& fileName)
{
	return texGen.addTexture(fileName);
}

int Terrain::GetMaxHeight()
{
    return m_MaxHeight;
}

int Terrain::GetMinHeight()
{
    return m_MinHeight;
}

std::vector<float> Terrain::GetVertices()
{
    //return m_Vertices;
    return m_Heights;
}

void Terrain::generateTerrainBuffers()
{
    float texCoordScaleX = 1.0f / (m_Width - 1);
    float texCoordScaleZ = 1.0f / (m_Length - 1);

    float xNorm = 0.0f;
    float yNorm = 1.0f;
    float zNorm = 0.0f;

    float min = m_Heights[0];
    float max = m_Heights[0];

    // Generate terrain vertices and texture coordinates
    std::vector<float> vertices;

    for (int z = 0; z < m_Size; ++z)
    {
        for (int x = 0; x < m_Size; ++x)
        {
            float xPos = static_cast<float>(x);
            float zPos = static_cast<float>(z);
            float yPos = m_Heights[z * m_Size + x];

            // Vertex positions
            vertices.push_back(xPos * scaleX);
            vertices.push_back(yPos * scaleY);
            vertices.push_back(zPos * scaleZ);

            // Texture coordinates (mapping the entire terrain's extent)
            //float texCoordX = static_cast<float>(x) / static_cast<float>(m_Size - 1);
            //float texCoordY = static_cast<float>(z) / static_cast<float>(m_Size - 1);

            float texCoordX = xPos * texCoordScaleX;
            float texCoordY = zPos * texCoordScaleZ;

            texCoordX *= m_Width;  
            texCoordY *= m_Length;

            vertices.push_back(texCoordX);
            vertices.push_back(texCoordY);

            glm::vec3 normal = CalcNormal(x, z);

            vertices.push_back(normal.x);
            vertices.push_back(normal.y);
            vertices.push_back(normal.z);

            float current = m_Heights[(z * m_Width) + x];
        }
    }

    for (int i = 0; i < m_Size; i++)
    {
        for (int j = 0; j < m_Size; j++)
        {
            if (j == 0 && i == 0) {
                m_MinHeight = getHeight(i, j);
                m_MaxHeight = getHeight(i, j);
            }
            if (getHeight(i, j) < m_MinHeight)
            {
                m_MinHeight = getHeight(i, j);
            }
            if (getHeight(i, j) > m_MaxHeight)
            {
                m_MaxHeight = getHeight(i, j);
            }
            //m_Vertices.push_back(getHeight(i, j));
        }
    }

    // Generate terrain indices
    std::vector<unsigned int> indices;

    //int numQuads = (m_patchSize - 1) * (m_patchSize - 1);
    //indices.resize(numQuads * 6);

    int NumIndices = calcNumIndices();
    indices.resize(NumIndices);

    InitIndices(indices);

    std::cout << m_Vertices.size() << std::endl;

    // Setup vertex array
    VertexBufferLayout layout;
    layout.Push<float>(3); // Vertex positions
    layout.Push<float>(2); // Texture coordinates
    layout.Push<float>(3); // Normals

    CalcLODNormals(vertices, indices);

    // Create and bind index buffer
    m_IBO = std::make_unique<IndexBuffer>(indices.data(), indices.size());

    // Create and bind vertex buffer
    m_VBO = std::make_unique<VertexBuffer>(vertices.data(), vertices.size() * sizeof(float));

    m_VAO.AddBuffer(*m_VBO, layout);
}

glm::vec3 Terrain::CalcNormal(int x, int z)
{
	float left;
	float right;
	float up;
	float down;

	if (x > 0)
	{
		left = m_Heights[(z * m_Width) + (x - 1)];
	}
	else
	{
		left = m_Heights[(z * m_Width) + x];
	}
	if (x < (m_Width - 1))
	{
		right = m_Heights[(z * m_Width) + (x + 1)];
	}
	else
	{
		right = m_Heights[(z * m_Width) + x];
	}
	if (z > 0)
	{
		up = m_Heights[((z - 1) * m_Width) + x];
	}
	else
	{
		up = m_Heights[(z * m_Width) + x];
	}
	if (z < (m_Length - 1))
	{
		down = m_Heights[((z + 1) * m_Width) + x];
	}
	else
	{
		down = m_Heights[(z * m_Width) + x];
	}

	glm::vec3 normal;
	normal.x = right - left;
	normal.y = 2.f;
	normal.z = down - up;
	glm::normalize(normal);

	return normal;
}

