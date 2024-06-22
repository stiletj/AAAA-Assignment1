#include "VertexBuffer.h"

VertexBuffer::VertexBuffer(const void* data, unsigned int size)
	: m_RenderedID(0)
{
	GraphicsUtility::GenBuffers(1, &m_RenderedID); 
	GraphicsUtility::BindBuffer(GraphicsEnum::ARRAY_BUFFER, m_RenderedID);
	GraphicsUtility::BufferData(GraphicsEnum::ARRAY_BUFFER, size, data, GraphicsEnum::STATIC_DRAW); 
}

VertexBuffer::~VertexBuffer()
{
	GraphicsUtility::DeleteBuffers(1, &m_RenderedID); 
}

void VertexBuffer::Bind() const
{
	GraphicsUtility::BindBuffer(GraphicsEnum::ARRAY_BUFFER, m_RenderedID); 
}

void VertexBuffer::Unbind() const
{
	GraphicsUtility::BindBuffer(GraphicsEnum::ARRAY_BUFFER, 0);
}