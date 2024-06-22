#include "MeshLoader.h"

bool MeshLoader::LoadMesh(const std::string& filePath)
{
    m_wholeMesh.Clear();

    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(filePath, aiProcess_Triangulate |
        aiProcess_JoinIdenticalVertices |
        aiProcess_SortByPType |
        aiProcess_GenSmoothNormals |
        aiProcess_FlipUVs);

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        std::cerr << "Error loading mesh: " << importer.GetErrorString() << std::endl;
        return false;
    }

    ProcessNode(scene->mRootNode, scene);

    return true;
}

WholeMesh& MeshLoader::GetMesh()
{
    return m_wholeMesh;
}

void MeshLoader::ProcessNode(aiNode* node, const aiScene* scene) {
    // Process all the node's meshes (if any)
    for (unsigned int i = 0; i < node->mNumMeshes; i++) {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        ProcessMesh(mesh, scene);
    }

    // Recursively process each of the node's children
    for (unsigned int i = 0; i < node->mNumChildren; i++) {
        ProcessNode(node->mChildren[i], scene);
    }
}

void MeshLoader::ProcessMesh(aiMesh* mesh, const aiScene* scene)
{
    for (unsigned int m = 0; m < scene->mNumMaterials; m++) {
        Material mat;
        aiMaterial* material = scene->mMaterials[m];
        aiString materialName;
        material->Get(AI_MATKEY_NAME, materialName);
        //std::cout << "Material name: " << materialName.C_Str() << std::endl;
        std::string name = std::string(materialName.C_Str());
        if (name.compare("DefaultMaterial") == 0) {
            std::cout << "mats detected" << std::endl;
            continue;
        }
        Mesh singleMesh;
        singleMesh.layout.Push<float>(3); // Positions (3 floats)
        singleMesh.layout.Push<float>(3); // Normals (3 floats)
        singleMesh.layout.Push<float>(2); // Texture coordinates (2 floats)

        // Assume Material class has the following functions:
        // setDiffuse(float r, float g, float b)
        // setSpecular(float r, float g, float b)
        // setAmbient(float r, float g, float b)
        // setShininess(float shininess)
        // You may need to adjust these based on your Material class implementation.

        aiColor3D color;
        if (material->Get(AI_MATKEY_COLOR_DIFFUSE, color) == AI_SUCCESS) {
            mat.SetDiffuse(glm::vec3(color.r, color.g, color.b));
        }

        aiColor3D specularColor;
        if (material->Get(AI_MATKEY_COLOR_SPECULAR, specularColor) == AI_SUCCESS) {
            mat.SetSpecular(glm::vec3(specularColor.r, specularColor.g, specularColor.b));
        }

        aiColor3D ambientColor;
        if (material->Get(AI_MATKEY_COLOR_AMBIENT, ambientColor) == AI_SUCCESS) {
            mat.SetAmbient(glm::vec3(ambientColor.r, ambientColor.g, ambientColor.b));
        }

        aiString texturePath;
        if (material->GetTexture(aiTextureType_DIFFUSE, 0, &texturePath) == AI_SUCCESS) {
            std::string textureFilePath = "resources/textures/" + std::string(texturePath.C_Str());
            std::cout << textureFilePath << std::endl;
            mat.SetTextureFile(textureFilePath);
            TextureManager::GetInstance().LoadTexture(textureFilePath);
        }

        float shininess;
        if (material->Get(AI_MATKEY_SHININESS, shininess) == AI_SUCCESS) {
            mat.SetSpecularExponent(shininess);
        }

        for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
            aiFace face = mesh->mFaces[i];
            if (mesh->mMaterialIndex == m) {
                for (unsigned int j = 0; j < face.mNumIndices; j++) {
                    unsigned int vertexIndex = face.mIndices[j];

                    Vertex vertex;
                    if (mesh->HasPositions()) {
                        aiVector3D pos = mesh->mVertices[vertexIndex];
                        vertex.position = glm::vec3(pos.x, pos.y, pos.z);
                    }
                    if (mesh->HasNormals()) {
                        aiVector3D normal = mesh->mNormals[vertexIndex];
                        vertex.normal = glm::vec3(normal.x, normal.y, normal.z);
                    }
                    if (mesh->HasTextureCoords(0)) {
                        aiVector3D texCoord = mesh->mTextureCoords[0][vertexIndex];
                        vertex.texCoords = glm::vec2(texCoord.x, texCoord.y);
                    }

                    singleMesh.vertices.push_back(vertex);
                    singleMesh.indices.push_back(singleMesh.vertices.size() - 1);
                }
            }
        }

        if (singleMesh.vertices.size() > 0)
        {
            singleMesh.va = std::make_shared<VertexArray>();
            singleMesh.vb = std::make_shared<VertexBuffer>(singleMesh.vertices.data(), singleMesh.vertices.size() * sizeof(Vertex));
            singleMesh.va->AddBuffer(*singleMesh.vb, singleMesh.layout);
            singleMesh.ib = std::make_shared<IndexBuffer>(singleMesh.indices.data(), singleMesh.indices.size());
            m_wholeMesh.meshes.push_back(singleMesh);
            m_wholeMesh.materials.push_back(mat);
        }
    }
}