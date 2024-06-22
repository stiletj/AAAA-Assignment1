#include "Renderer.h"
#include <iostream>

void Renderer::Clear() const
{
	// Clear the screen
	GraphicsUtility::Clear(GraphicsEnum::COLOR_BUFFER_BIT | GraphicsEnum::DEPTH_BUFFER_BIT);
}

void Renderer::Render(const VertexArray& va, const IndexBuffer& ib, const Shader& shader, GLenum drawMode) const
{
	// Bind shader program
	shader.Bind();

	// Bind VAO and EBO
	va.Bind();
	ib.Bind();

	// Get the number of indices to draw from the IndexBuffer
	unsigned int count = ib.GetCount();

	// Draw using the specified draw mode
	GraphicsUtility::DrawElements(drawMode, count, GraphicsEnum::UNSIGNED_INT, nullptr); 
}

void Renderer::TerrainRender(const VertexArray& va, const IndexBuffer& ib, const Shader& shader, GLenum drawMode, GLsizei count, GLenum type, void *indices, GLint BaseVertex) const
{

	shader.Bind();

	va.Bind();
	ib.Bind();

	GraphicsUtility::DrawElementsBaseVertex(drawMode, count, type, indices, BaseVertex);

	
}
