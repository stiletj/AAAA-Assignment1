#include "VertexArray.h"

VertexArray::VertexArray() : m_RenderedID(0)
{
	GraphicsUtility::GenerateVertexArrays(1, &m_RenderedID);
}

VertexArray::~VertexArray()
{
	GraphicsUtility::DeleteVertexArrays(1, &m_RenderedID); 
}

void VertexArray::AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout)
{
	Bind();
	vb.Bind();
	const auto& elements = layout.GetElements();
	unsigned int offset = 0;
	for (int i = 0; i < elements.size(); i++)
	{
		const auto& element = elements[i];
		// Define the vertex attribute pointer
		GraphicsUtility::EnableVertexAttribArray(i); 
		GraphicsUtility::VertexAttribPointer(i, element.count, element.type, element.normalized, layout.GetStride(), (const void*)offset);
		offset += element.count * VertexBufferElement::GetSizeOfType(element.type);
	}
}

void VertexArray::Bind() const
{
	GraphicsUtility::BindVertexArray(m_RenderedID);
}

void VertexArray::Unbind() const
{
	GraphicsUtility::BindVertexArray(0);
}