#include "Skybox.h"

Skybox::Skybox(std::vector<std::string>& paths): paths(paths) 
{
    textureID = TextureManager::GetInstance().LoadTexture(paths, TextureType::CUBEMAP);

    // Define the vertices for the skybox (a cube)
    float skyboxVertices[] = {
        //   Coordinates
        -1.0f, -1.0f,  1.0f,//        7--------6
         1.0f, -1.0f,  1.0f,//       /|       /|
         1.0f, -1.0f, -1.0f,//      4--------5 |
        -1.0f, -1.0f, -1.0f,//      | |      | |
        -1.0f,  1.0f,  1.0f,//      | 3------|-2
         1.0f,  1.0f,  1.0f,//      |/       |/
         1.0f,  1.0f, -1.0f,//      0--------1
        -1.0f,  1.0f, -1.0f
    };

    unsigned int skyboxIndices[] =
    {
        // Right
        1, 2, 6,
        6, 5, 1,
        // Left
        0, 4, 7,
        7, 3, 0,
        // Top
        4, 5, 6,
        6, 7, 4,
        // Bottom
        0, 3, 2,
        2, 1, 0,
        // Back
        0, 1, 5,
        5, 4, 0,
        // Front
        3, 7, 6,
        6, 2, 3
    };

    // Bind and fill the VBO with the skybox vertices
    m_VBO = std::make_shared<VertexBuffer>(skyboxVertices, sizeof(skyboxVertices));

    // Setup vertex layout
    VertexBufferLayout layout;
    layout.Push<float>(3); // positions

    // Add vertex layout to VAO
    m_VAO = std::make_shared<VertexArray>();
    m_VAO->AddBuffer(*m_VBO, layout);

    // Bind and fill the IBO with the skybox indices
    m_IBO = std::make_shared<IndexBuffer>(skyboxIndices, sizeof(skyboxIndices) / sizeof(skyboxIndices[0]));
}

void Skybox::Render(const Renderer& renderer, Shader& shader, const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix)
{
    glDepthFunc(GL_LEQUAL);

    // Bind the skybox texture
    TextureManager::GetInstance().Bind(textureID, TextureType::CUBEMAP);

    shader.Bind();

    glm::mat4 view = glm::mat4(glm::mat3(viewMatrix));
    glm::mat4 projection = projectionMatrix;
    shader.SetUniformMat4f("view", view);
    shader.SetUniformMat4f("projection", projection);

    renderer.Render(*m_VAO, *m_IBO, shader, GraphicsEnum::TRIANGLES);

    TextureManager::GetInstance().Unbind();

    glDepthFunc(GL_LESS);
}