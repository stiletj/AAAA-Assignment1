#pragma once

#include "GraphicsUtility.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

/**
 * @class VertexArray
 *
 * @brief A class representing a Vertex Array Object (VAO) in OpenGL.
 */
class VertexArray {
private:
	unsigned int m_RenderedID; /**< The OpenGL identifier for the Vertex Array Object (VAO). */

public:
	/**
	 * @brief Constructor for the VertexArray class.
	 */
	VertexArray();

	/**
	 * @brief Destructor for the VertexArray class.
	 */
	~VertexArray();

	/**
	 * @brief Add a vertex buffer and layout to the Vertex Array Object (VAO).
	 *
	 * @param vb The VertexBuffer to add.
	 * @param layout The VertexBufferLayout to specify the layout of the data in the VertexBuffer.
	 */
	void AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);

	/**
	 * @brief Bind the Vertex Array Object (VAO) for rendering.
	 */
	void Bind() const;

	/**
	 * @brief Unbind the currently bound Vertex Array Object (VAO).
	 */
	void Unbind() const;
};