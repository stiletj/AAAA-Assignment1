#include "MeshRenderer.h"


void MeshRenderer::UpdateWorldMatrix(Transform trans)
{
	m_worldMatrix = glm::mat4(1.0f);
	m_worldMatrix = translate(m_worldMatrix, trans.m_pos);
	m_worldMatrix = rotate(m_worldMatrix, radians(trans.m_rot.x), glm::vec3(1.0f, 0.0f, 0.0f));
	m_worldMatrix = rotate(m_worldMatrix, radians(trans.m_rot.y), glm::vec3(0.0f, 1.0f, 0.0f));
	m_worldMatrix = rotate(m_worldMatrix, radians(trans.m_rot.z), glm::vec3(0.0f, 0.0f, 1.0f));
	m_worldMatrix = scale(m_worldMatrix, trans.m_scale);
}

glm::mat4 MeshRenderer::GetWorldMatrix()
{
	return m_worldMatrix;
}

MeshRenderer::MeshRenderer()
{
	m_worldMatrix = glm::mat4(1.0f);
	m_worldMatrix = glm::translate(m_worldMatrix, glm::vec3(0, 0, 0));
	m_worldMatrix = glm::rotate(m_worldMatrix, 0.0f, glm::vec3(1.0f, 1.0f, 1.0f));
	m_worldMatrix = glm::scale(m_worldMatrix, glm::vec3(1, 1, 1));
}

MeshRenderer::~MeshRenderer()
{
}

void MeshRenderer::Render(ECS& registry, const Renderer& renderer, Shader& shader, const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix)
{
	ENTITY ent;

	for (entt::entity entity : registry.GetRenders())
	{
		ent.Set(entity);
		UpdateWorldMatrix(registry.GetComponent<Transform>(ent));

		shader.Bind();

		glm::mat4 mvpMatrix = projectionMatrix * viewMatrix * m_worldMatrix;

		// Set uniform matrices
		shader.SetUniformMat4f("u_MVP", mvpMatrix);

		// Set texture uniform
		shader.SetUniform1i("u_Texture", 0);

		// Set lighting uniforms
		LightingManager::SetLightingUniforms(shader, m_worldMatrix);
		shader.SetUniform1i("u_IsLight", LightingManager::GetIsDirLight());

		// Set camera position in local coordinates
		glm::vec3 cameraPosition = glm::vec3(glm::inverse(viewMatrix)[3]);
		glm::vec4 cameraPositionVec4 = { cameraPosition, 1.0f };
		glm::vec4 localCamPosVec4 = cameraPositionVec4 * inverse(m_worldMatrix);
		glm::vec3 localCamPos = { localCamPosVec4.x, localCamPosVec4.y, localCamPosVec4.z};
		shader.SetUniform3f("u_LocalCamPos", localCamPos);

		if (registry.HasComponent<WholeMesh>(ent))
		{
			WholeMesh entityMesh = registry.GetComponent<WholeMesh>(ent);

			// Iterate through materials
			for (int i = 0; i < entityMesh.meshes.size(); i++)
			{
				// Check if the material index is valid
				if (entityMesh.materials.size() > 0)
				{
					// Set material properties
					shader.SetUniform4f("u_AmbientColour", { entityMesh.materials[i].GetAmbient(), 1.0f});
					shader.SetUniform4f("u_AmbientColour", glm::vec4(entityMesh.materials[i].GetDiffuse(), 1));
					shader.SetUniform4f("u_DiffuseColour", glm::vec4(entityMesh.materials[i].GetDiffuse(), 1));
					shader.SetUniform4f("u_SpecularColour", glm::vec4(entityMesh.materials[i].GetSpecular(), 1));
					shader.SetUniform1f("u_SpecularExponent", entityMesh.materials[i].GetSpecularExponent());

					// Bind texture if available
					std::string texture = entityMesh.materials[i].GetTexture();
					if (texture != "NA" && !texture.empty()) {
						shader.SetUniform1i("u_HasTexture", 1);
						TextureManager::GetInstance().SetActiveTexture(texture);
					}

					renderer.Render(*entityMesh.meshes[i].va, *entityMesh.meshes[i].ib, shader, GL_TRIANGLES);
					TextureManager::GetInstance().Unbind();
					shader.SetUniform1i("u_HasTexture", 0);
				}
				else
				{
					// Render the object using the vertex and index data
					renderer.Render(*entityMesh.meshes[i].va, *entityMesh.meshes[i].ib, shader, GL_TRIANGLES);
				}
			}
			// Unbind the shader after rendering all materials
			shader.Unbind();
		}
	}

}
