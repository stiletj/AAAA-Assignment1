#pragma once

#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "GraphicsUtility.h"

/**
 * @class Renderer
 *
 * @brief A class responsible for rendering operations using OpenGL.
 */
class Renderer {
public:
    
	/**
	 * @brief Clear the screen with the current clear color.
	 */
	void Clear() const;

	/**
	 * @brief Draw the specified Entity using the provided shader
	 *
	 * @param va Vertex Array
	 * @param ib Index Buffer
	 * @param shader The Shader program to use for rendering.
	 * @param drawMode The mode of drawing
	 */
	void Render(const VertexArray& va, const IndexBuffer& ib, const Shader& shader, GLenum drawMode) const;

	/**
	 * @brief Draw the specified terrain (CLOD style) using the provided shader 
	 *
	 * @param va Vertex Array
	 * @param ib Index Buffer
	 * @param shader The Shader program to use for rendering.
	 * @param drawMode The mode of drawing
	 * @param patchSize the size of the LOD patches
	 * @param length the length of the heightmap
	 * @param width of the heightmap
	 */
	void TerrainRender(const VertexArray& va, const IndexBuffer& ib, const Shader& shader, GLenum drawMode, GLsizei count, GLenum type, void* indices, GLint BaseVertex) const;
};