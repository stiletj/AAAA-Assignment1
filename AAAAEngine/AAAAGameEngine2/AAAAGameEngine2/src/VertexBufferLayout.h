#pragma once

#include "GraphicsUtility.h"
#include <vector>
#include <stdexcept>

/**
 * @struct VertexBufferElement
 *
 * @brief A structure representing an element of a vertex buffer layout.
 */
struct VertexBufferElement
{
	unsigned int type; /**< The data type of the element (e.g., GL_FLOAT). */
	unsigned int count; /**< The number of elements (e.g., 3 for a vector). */
	unsigned char normalized; /**< Whether the data should be normalized. */

	/**
	 * @brief Get the size of the data type in bytes.
	 *
	 * @param type The data type.
	 * @return The size of the data type in bytes.
	 */
	static unsigned int GetSizeOfType(unsigned int type)
	{
		switch (type)
		{
		case GraphicsEnum::FLOAT: return 4;
		case GraphicsEnum::UNSIGNED_INT: return 4;
		case GraphicsEnum::UNSIGNED_BYTE: return 1;
		case GraphicsEnum::DOUBLE: return 8;
		}
		return 0; // You can handle this error condition as needed
	}
};

/**
 * @class VertexBufferLayout
 *
 * @brief A class representing the layout of vertex data in a vertex buffer.
 */
class VertexBufferLayout {
private:
	std::vector<VertexBufferElement> m_Elements; /**< The elements in the layout. */
	unsigned int m_Stride; /**< The stride (size) of the layout. */

public:
	/**
	 * @brief Constructor for the VertexBufferLayout class.
	 */
	VertexBufferLayout() : m_Stride(0) {}

	/**
	 * @brief Push a new element into the layout.
	 *
	 * @tparam T The data type of the element.
	 * @param count The number of elements.
	 */
	template<typename T>
	void Push(unsigned int count)
	{
		// You can add error handling here if needed
	}

	/**
	 * @brief Push a float element into the layout.
	 *
	 * @param count The number of float elements.
	 */
	template<>
	void Push<float>(unsigned int count)
	{
		m_Elements.push_back({ GraphicsEnum::FLOAT, count, GraphicsEnum::FALSE });
		m_Stride += count * VertexBufferElement::GetSizeOfType(GraphicsEnum::FLOAT);
	}

	/**
	 * @brief Push a double element into the layout.
	 *
	 * @param count The number of double elements.
	 */
	template<>
	void Push<double>(unsigned int count)
	{
		m_Elements.push_back({ GraphicsEnum::DOUBLE, count, GraphicsEnum::FALSE });
		m_Stride += count * VertexBufferElement::GetSizeOfType(GraphicsEnum::DOUBLE);
	}

	/**
	 * @brief Push an unsigned int element into the layout.
	 *
	 * @param count The number of unsigned int elements.
	 */
	template<>
	void Push<unsigned int>(unsigned int count)
	{
		m_Elements.push_back({ GraphicsEnum::UNSIGNED_INT, count, GraphicsEnum::FALSE });
		m_Stride += count * VertexBufferElement::GetSizeOfType(GraphicsEnum::UNSIGNED_INT);
	}

	/**
	 * @brief Push an unsigned char element into the layout.
	 *
	 * @param count The number of unsigned char elements.
	 */
	template<>
	void Push<unsigned char>(unsigned int count)
	{
		m_Elements.push_back({ GraphicsEnum::UNSIGNED_BYTE, count, GraphicsEnum::TRUE });
		m_Stride += count * VertexBufferElement::GetSizeOfType(GraphicsEnum::UNSIGNED_BYTE);
	}

	/**
	 * @brief Get the elements in the layout.
	 *
	 * @return A vector of VertexBufferElement.
	 */
	inline const std::vector<VertexBufferElement> GetElements() const { return m_Elements; }

	/**
	 * @brief Get the stride (size) of the layout.
	 *
	 * @return The stride (size) of the layout.
	 */
	inline unsigned int GetStride() const { return m_Stride; }
};