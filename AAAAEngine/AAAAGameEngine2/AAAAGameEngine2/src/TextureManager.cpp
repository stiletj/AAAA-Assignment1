#include "TextureManager.h"

TextureManager::~TextureManager()
{
    DeleteAllTextures();
}

TextureManager& TextureManager::GetInstance()
{
    static TextureManager instance;
    return instance;
}

unsigned int TextureManager::updateTexture(const std::string& path)
{
    auto it = m_Textures.find(path);
    /*if (it != m_Textures.end()) {
        // Texture already loaded, return its ID
        return it->second;
    }*/

    Image image(path);

    GraphicsUtility::BindTexture(GraphicsEnum::TEXTURE_2D, m_Textures[path]);

    glTexSubImage2D(GraphicsEnum::TEXTURE_2D, 0, 0, 0, image.getWidth(), image.getHeight(), GL_RGB, GL_UNSIGNED_BYTE, image.getBuffer());

    return 0;
}

unsigned int TextureManager::LoadTexture(const std::string& path, TextureType type)
{
    // Check if the texture is already loaded
    auto it = m_Textures.find(path);
    if (it != m_Textures.end()) {
        // Texture already loaded, return its ID
        return it->second;
    }

    unsigned int textureID;
    GLenum textureTarget;

    if (type == TextureType::CUBEMAP) {
        // Handle loading of cube map
        std::cerr << "Cannot load a cube map from a single image path." << std::endl;
        return 0;
    }
    else {
        // Regular 2D texture
        textureTarget = GraphicsEnum::TEXTURE_2D;
        GraphicsUtility::GenTextures(1, &textureID);
        GraphicsUtility::BindTexture(textureTarget, textureID);

        // Set texture parameters
        GraphicsUtility::TexParameteri(GraphicsEnum::TEXTURE_2D, GraphicsEnum::TEXTURE_MIN_FILTER, GraphicsEnum::LINEAR);
        GraphicsUtility::TexParameteri(GraphicsEnum::TEXTURE_2D, GraphicsEnum::TEXTURE_MAG_FILTER, GraphicsEnum::LINEAR);
        GraphicsUtility::TexParameteri(GraphicsEnum::TEXTURE_2D, GraphicsEnum::TEXTURE_WRAP_S, GraphicsEnum::REPEAT);
        GraphicsUtility::TexParameteri(GraphicsEnum::TEXTURE_2D, GraphicsEnum::TEXTURE_WRAP_T, GraphicsEnum::REPEAT);

        Image image(path);
        GLenum format = (image.getBPP() == 4) ? GraphicsEnum::RGBA : GraphicsEnum::RGB;
        GraphicsUtility::TexImage2D(GraphicsEnum::TEXTURE_2D, 0, format, image.getHeight(), image.getWidth(), 0, format, GraphicsEnum::UNSIGNED_BYTE, image.getBuffer());
        GraphicsUtility::BindTexture(GraphicsEnum::TEXTURE_2D, 0);
    }

    // Store texture ID in the map
    m_Textures[path] = textureID;

    return textureID;
}

unsigned int TextureManager::LoadTexture(const std::vector<std::string>& paths, TextureType type)
{
    // Check if the texture is already loaded
    auto it = m_Textures.find(paths[0]);
    if (it != m_Textures.end()) {
        // Texture already loaded, return its ID
        return it->second;
    }

    if (type != TextureType::CUBEMAP) {
        std::cerr << "Invalid texture type for loading a cube map." << std::endl;
        return 0;
    }

    unsigned int textureID;
    GraphicsUtility::GenTextures(1, &textureID);
    GraphicsUtility::BindTexture(GraphicsEnum::TEXTURE_CUBE_MAP, textureID);

    GraphicsUtility::TexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    GraphicsUtility::TexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    GraphicsUtility::TexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    GraphicsUtility::TexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    GraphicsUtility::TexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    // Load and bind each face of the cubemap
    for (size_t i = 0; i < 6; ++i) {
        Image image(paths[i]);
        if (image.getWidth() == 0 || image.getHeight() == 0) {
            std::cerr << "Failed to load cubemap face: " << paths[i] << std::endl;
            continue; // Skip this face if loading fails
        }

        GLenum format = (image.getBPP() == 4) ? GL_RGBA : GL_RGB;
        GraphicsUtility::TexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, format, image.getWidth(), image.getHeight(), 0, format, GL_UNSIGNED_BYTE, image.getBuffer());
    }

    // Unbind texture
    glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

    // Store texture ID in the map
    m_Textures[paths[0]] = textureID;

    return textureID;
}


/*
unsigned int TextureManager::LoadCubeMap(const std::string& path) {
    // Load the cubemap image
    Image cubemapImage(path);

    // Ensure the image is loaded successfully
    if (cubemapImage.getWidth() == 0 || cubemapImage.getHeight() == 0) {
        std::cerr << "Failed to load cubemap image: " << path << std::endl;
        return 0;
    }

    unsigned int textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

    // Set texture parameters
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    // Calculate face dimensions
    int faceWidth = cubemapImage.getWidth() / 4;
    int faceHeight = cubemapImage.getHeight() / 3;

    // Load each face of the cubemap
    for (int i = 0; i < 6; ++i) {
        int row = i / 4;
        int col = i % 4;
        int xOffset = col * faceWidth;
        int yOffset = row * faceHeight;

        GLenum format = (cubemapImage.getBPP() == 4) ? GL_RGBA : GL_RGB;
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, format, faceWidth, faceHeight, 0, format, GL_UNSIGNED_BYTE, cubemapImage.getBuffer() + (xOffset + yOffset * cubemapImage.getWidth()) * cubemapImage.getBPP());
    }

    // Unbind texture
    glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

    // Store texture ID in the map
    m_Textures[path] = textureID;

    return textureID;
}
*/

unsigned int TextureManager::CreateTexture(const std::string& name, Image& image)
{
    // Check if the texture is already loaded
    auto it = m_Textures.find(name);
    if (it != m_Textures.end()) {
        // Texture already loaded, return its ID
        return it->second;
    }

    unsigned int textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    // Set texture parameters
    GraphicsUtility::TexParameteri(GraphicsEnum::TEXTURE_2D, GraphicsEnum::TEXTURE_WRAP_T, GraphicsEnum::REPEAT);
    GraphicsUtility::TexParameteri(GraphicsEnum::TEXTURE_2D, GraphicsEnum::TEXTURE_WRAP_T, GraphicsEnum::CLAMP_TO_EDGE);
    GraphicsUtility::TexParameteri(GraphicsEnum::TEXTURE_2D, GraphicsEnum::TEXTURE_WRAP_S, GraphicsEnum::REPEAT);
    GraphicsUtility::TexParameteri(GraphicsEnum::TEXTURE_2D, GraphicsEnum::TEXTURE_WRAP_S, GraphicsEnum::CLAMP_TO_EDGE);

    GraphicsUtility::TexParameteri(GraphicsEnum::TEXTURE_2D, GraphicsEnum::TEXTURE_MAG_FILTER, GraphicsEnum::LINEAR);
    GraphicsUtility::TexParameteri(GraphicsEnum::TEXTURE_2D, GraphicsEnum::TEXTURE_MIN_FILTER, GraphicsEnum::LINEAR_MIPMAP_LINEAR);

    GLenum format = (image.getBPP() == 4) ? GraphicsEnum::RGBA : GraphicsEnum::RGB;

    GraphicsUtility::TexImage2D(GraphicsEnum::TEXTURE_2D, 0, format, image.getHeight(), image.getWidth(), 0, format, GraphicsEnum::UNSIGNED_BYTE, image.getBuffer());

    // Generate mipmaps
    GraphicsUtility::GenerateMipMap(GraphicsEnum::TEXTURE_2D);

    GraphicsUtility::BindTexture(GraphicsEnum::TEXTURE_2D, 0);

    // Store texture ID in the map
    m_Textures[name] = textureID;

    return textureID;
}

unsigned int TextureManager::GetTexture(const std::string& path) const
{
    auto it = m_Textures.find(path);
    if (it != m_Textures.end()) {
        return it->second;
    }
    return 0; // Texture not found
}

void TextureManager::Bind(const unsigned int id, TextureType type, int slot) const
{
    if (id != 0) {
        switch (type) {
        case TextureType::DEFAULT:
            glActiveTexture(GL_TEXTURE0 + slot); // Activate the texture slot
            GraphicsUtility::Enable(GraphicsEnum::TEXTURE_2D);
            GraphicsUtility::BindTexture(GraphicsEnum::TEXTURE_2D, id);
            break;
        case TextureType::CUBEMAP:
            glActiveTexture(GL_TEXTURE0 + slot); // Activate the texture slot
            GraphicsUtility::Enable(GraphicsEnum::TEXTURE_CUBE_MAP);
            GraphicsUtility::BindTexture(GraphicsEnum::TEXTURE_CUBE_MAP, id);
            break;
        }
    }
}

void TextureManager::Unbind() const
{
    glBindTexture(GL_TEXTURE_2D, 0);
}

void TextureManager::SetActiveTexture(const std::string& path, TextureType type, int slot) const
{
    unsigned int textureID = GetTexture(path);
    if (textureID != 0) {
        switch (type) {
        case TextureType::DEFAULT:
            glActiveTexture(GL_TEXTURE0 + slot);
            GraphicsUtility::Enable(GraphicsEnum::TEXTURE_2D);
            GraphicsUtility::BindTexture(GraphicsEnum::TEXTURE_2D, textureID);
            break;
        case TextureType::CUBEMAP:
            glActiveTexture(GL_TEXTURE0 + slot);
            GraphicsUtility::Enable(GraphicsEnum::TEXTURE_CUBE_MAP);
            GraphicsUtility::BindTexture(GraphicsEnum::TEXTURE_CUBE_MAP, textureID);
            break;
        }
    }
}

void TextureManager::DeleteAllTextures() {
    for (auto& pair : m_Textures) {
        GraphicsUtility::DeleteTextures(1, &pair.second);
    }
    m_Textures.clear();
}
