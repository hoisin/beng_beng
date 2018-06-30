#include "CIndexBuffer.h"


CIndexBuffer::CIndexBuffer() : m_idxCount(0),
	m_elementBuffer(0), m_bLoadedData(false)
{
}

CIndexBuffer::CIndexBuffer(const CIndexBuffer & other)
{
	m_idxCount = other.m_idxCount;
	m_elementBuffer = other.m_elementBuffer;
	m_bLoadedData = other.m_bLoadedData;
}


CIndexBuffer::~CIndexBuffer()
{
}

//------------------------------------------------------------------
//
//	LoadData(..)
//
//	Params:
//	pIndexData		-	pointer to index array
//	indexCount		-	number of elements in index array
//
//	Loads index data into OpenGL element array buffer
//
//------------------------------------------------------------------
bool CIndexBuffer::LoadData(GLuint* pIndexData, GLuint indexCount)
{
	bool result = false;

	if (pIndexData != nullptr && indexCount != 0)
	{
		m_idxCount = indexCount;

		glGenBuffers(1, &m_elementBuffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_elementBuffer);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_idxCount * sizeof(glm::uint32), pIndexData, GL_STATIC_DRAW);

		if (glGetError() != GL_NO_ERROR)
		{
			glDeleteBuffers(1, &m_elementBuffer);
			m_idxCount = 0;
			m_elementBuffer = 0;
			result = false;
		}
		else
		{
			result = true;
			m_bLoadedData = true;
		}

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	return result;
}


GLuint CIndexBuffer::GetElementBuffer() const
{
	return m_elementBuffer;
}


GLuint CIndexBuffer::GetIndexCount() const
{
	return m_idxCount;
}

//------------------------------------------------------------------
//
//	UseBuffer(..)
//
//	Binds this element buffer to use if it has loaded data
//
//------------------------------------------------------------------
void CIndexBuffer::UseBuffer()
{
	if (m_bLoadedData)
	{
		// Free previous used index buffer
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);	// Probably don't need this
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_elementBuffer);
	}
}

//------------------------------------------------------------------
//
//	IsLoadedData(..)
//
//	Returns true if index buffer has loaded data onto GPU
//
//------------------------------------------------------------------
bool CIndexBuffer::IsLoadedData() const
{
	return m_bLoadedData;
}

//------------------------------------------------------------------
//
//	ShutDown(..)
//
//	Free OpenGL element buffer if loaded
//
//------------------------------------------------------------------
void CIndexBuffer::ShutDown()
{
	if (m_bLoadedData)
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glDeleteBuffers(1, &m_elementBuffer);
		m_elementBuffer = 0;
		m_idxCount = 0;
		m_bLoadedData = false;
	}
}