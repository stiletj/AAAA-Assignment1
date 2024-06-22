#pragma once

#include "GraphicsUtility.h"

/**
 * @class VertexBuffer
 *
 * @brief A class representing a Vertex Buffer in OpenGL.
 */
class VertexBuffer
{
private:
	unsigned int m_RenderedID; /**< The OpenGL identifier for the Vertex Buffer. */

public:
	
	/**
	 * @brief Constructor for the VertexBuffer class.
	 *
	 * @param data Pointer to the vertex data.
	 * @param size Size of the vertex data.
	 */
	VertexBuffer(const void* data, unsigned int size);

	/**
	 * @brief Destructor for the VertexBuffer class.
	 */
	~VertexBuffer();

	/**
	 * @brief Bind the Vertex Buffer for rendering.
	 */
	void Bind() const;

	/**
	 * @brief Unbind the currently bound Vertex Buffer.
	 */
	void Unbind() const;
};