#include "IndexBuffer.h"


// Constructor for IndexBuffer
IndexBuffer::IndexBuffer(const unsigned int* data, unsigned int count) : m_RenderedID(0), m_Count(count)
{
    GraphicsUtility::GenBuffers(1, &m_RenderedID);
    GraphicsUtility::BindBuffer(GraphicsEnum::ELEMENT_ARRAY_BUFFER, m_RenderedID); 
    GraphicsUtility::BufferData(GraphicsEnum::ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GraphicsEnum::STATIC_DRAW);
}

// Destructor for IndexBuffer
IndexBuffer::~IndexBuffer()
{
    // Delete the OpenGL index buffer
    GraphicsUtility::DeleteBuffers(1, &m_RenderedID); 
}


// Bind the index buffer for rendering
void IndexBuffer::Bind() const
{
    GraphicsUtility::BindBuffer(GraphicsEnum::ELEMENT_ARRAY_BUFFER, m_RenderedID);
}

// Unbind the currently bound index buffer
void IndexBuffer::Unbind() const
{
    GraphicsUtility::BindBuffer(GraphicsEnum::ELEMENT_ARRAY_BUFFER, 0); 
}

