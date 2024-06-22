#pragma once

#include "GraphicsUtility.h"

/**
 * @class IndexBuffer
 * @brief A class for managing OpenGL index buffers.
 *
 * The IndexBuffer class provides methods for creating, binding, and unbinding
 * OpenGL index buffers used for indexed rendering of vertex data.
 */

class IndexBuffer
{
private:
    unsigned int m_RenderedID; /**< The OpenGL ID of the index buffer. */
    unsigned int m_Count; /**< The number of indices in the index buffer. */

public:
    /**
     * @brief Constructor for IndexBuffer.
     *
     * Creates an OpenGL index buffer and initializes it with the provided data.
     *
     * @param data A pointer to the index data.
     * @param count The number of indices in the buffer.
     */
    IndexBuffer(const unsigned int* data, unsigned int count);

    /**
     * @brief Destructor for IndexBuffer.
     *
     * Cleans up and deallocates the OpenGL index buffer.
     */
    ~IndexBuffer();

    //IndexBuffer(const IndexBuffer& cpy);

    /**
     * @brief Bind the index buffer for rendering.
     *
     * Binds the index buffer for use in rendering operations.
     */
    void Bind() const;

    /**
     * @brief Unbind the currently bound index buffer.
     *
     * Unbinds the currently bound index buffer, releasing it from rendering operations.
     */
    void Unbind() const;

    /**
     * @brief Get the number of indices in the index buffer.
     *
     * @return The number of indices in the index buffer.
     */
    inline unsigned int GetCount() const { return m_Count; }


};