#include "CVertexBuffer.h"

CVertexBuffer::CVertexBuffer() : m_vertCount(0),
m_numVBOs(0), m_VAO(0), m_pVBO(nullptr), m_vertType(eVertexUnknown), m_bLoadedData(false)
{
}

CVertexBuffer::CVertexBuffer(const CVertexBuffer & other)
{
	m_vertCount = other.m_vertCount;
	m_numVBOs = other.m_numVBOs;
	m_VAO = other.m_VAO;
	m_pVBO = other.m_pVBO;
	m_vertType = other.m_vertType;
	m_bLoadedData = other.m_bLoadedData;
}


CVertexBuffer::~CVertexBuffer()
{
}


//----------------------------------------------------------------------------------------------------
//
//	LoadData(..)
//
//	Params:
//	pVertData		-	pointer to data
//	vertexCount		-	number of vertices
//	vertType		-	the vertex type
//
//	Description:
//	Loads mesh data in RAM to VRAM.
//
//----------------------------------------------------------------------------------------------------
ErrorId CVertexBuffer::LoadData(void* pVertData, glm::uint32 vertexCount, EVertexType vertType)
{
	if (pVertData == nullptr)
		return ERRORID_GFX_VERTEX_BUFFER_NULL_DATA;

	if (vertexCount == 0)
		return ERRORID_GFX_VERTEX_BUFFER_ZERO_VERTEX_COUNT;

	if (vertType == EVertexType::eVertexUnknown)
		return ERRORID_GFX_VERTEX_BUFFER_UNKNOWN_VERTEXTYPE;

	m_vertCount = vertexCount;
	m_vertType = vertType;

	// Generate & setup VAO
	glGenVertexArrays(1, &m_VAO);
	glBindVertexArray(m_VAO);
	
	// Generate buffers based on vertex type
	switch(m_vertType)
	{
	case eVertexPC:
		m_numVBOs = 2;
		m_pVBO = new GLuint[m_numVBOs];

		// Generate and setup VBOs
		glGenBuffers(m_numVBOs, m_pVBO);

		// Position buffer
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, m_pVBO[0]);
		glBufferData(GL_ARRAY_BUFFER, m_vertCount*sizeof(SVertexTypePC), pVertData, GL_STATIC_DRAW);
		glVertexAttribPointer((GLuint)0, 3, GL_FLOAT, GL_FALSE, sizeof(SVertexTypePC), 0);
		
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		// Colour buffer
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, m_pVBO[1]);
		glBufferData(GL_ARRAY_BUFFER, m_vertCount*sizeof(SVertexTypePC), pVertData, GL_STATIC_DRAW);
		glVertexAttribPointer((GLuint)1, 3, GL_FLOAT, GL_FALSE, sizeof(SVertexTypePC), (void*)sizeof(glm::vec3));
		
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		break;

	case eVertexPT:
		m_numVBOs = 2;
		m_pVBO = new GLuint[m_numVBOs];

		// Generate and setup VBOs
		glGenBuffers(m_numVBOs, m_pVBO);

		// Position buffer
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, m_pVBO[0]);
		glBufferData(GL_ARRAY_BUFFER, m_vertCount*sizeof(SVertexTypePT), pVertData, GL_STATIC_DRAW);
		glVertexAttribPointer((GLuint)0, 3, GL_FLOAT, GL_FALSE, sizeof(SVertexTypePT), 0);
		
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		// Texture buffer
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, m_pVBO[1]);
		glBufferData(GL_ARRAY_BUFFER, m_vertCount*sizeof(SVertexTypePT), pVertData, GL_STATIC_DRAW);
		glVertexAttribPointer((GLuint)1, 2, GL_FLOAT, GL_FALSE, sizeof(SVertexTypePT), (void*)sizeof(glm::vec3));
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		break;

	case eVertexPNC:
		m_numVBOs = 3;
		m_pVBO = new GLuint[m_numVBOs];

		// Generate and setup VBOs
		glGenBuffers(m_numVBOs, m_pVBO);

		// Position buffer
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, m_pVBO[0]);
		glBufferData(GL_ARRAY_BUFFER, m_vertCount*sizeof(SVertexTypePNC), pVertData, GL_STATIC_DRAW);
		glVertexAttribPointer((GLuint)0, 3, GL_FLOAT, GL_FALSE, sizeof(SVertexTypePNC), 0);
		
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		// Normal buffer
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, m_pVBO[1]);
		glBufferData(GL_ARRAY_BUFFER, m_vertCount*sizeof(SVertexTypePNC), pVertData, GL_STATIC_DRAW);
		glVertexAttribPointer((GLuint)1, 3, GL_FLOAT, GL_FALSE, sizeof(SVertexTypePNC), (void*)sizeof(glm::vec3));
		
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		// Colour buffer
		glEnableVertexAttribArray(2);
		glBindBuffer(GL_ARRAY_BUFFER, m_pVBO[2]);
		glBufferData(GL_ARRAY_BUFFER, m_vertCount*sizeof(SVertexTypePNC), pVertData, GL_STATIC_DRAW);
		glVertexAttribPointer((GLuint)2, 3, GL_FLOAT, GL_FALSE, sizeof(SVertexTypePNC), (void*)(sizeof(glm::vec3) * 2));

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		break;

	case eVertexPNT:
		m_numVBOs = 3;
		m_pVBO = new GLuint[m_numVBOs];

		// Generate and setup VBOs
		glGenBuffers(m_numVBOs, m_pVBO);

		// Position buffer
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, m_pVBO[0]);
		glBufferData(GL_ARRAY_BUFFER, m_vertCount*sizeof(SVertexTypePNT), pVertData, GL_STATIC_DRAW);
		glVertexAttribPointer((GLuint)0, 3, GL_FLOAT, GL_FALSE, sizeof(SVertexTypePNT), 0);
		
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		// Normal buffer
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, m_pVBO[1]);
		glBufferData(GL_ARRAY_BUFFER, m_vertCount*sizeof(SVertexTypePNT), pVertData, GL_STATIC_DRAW);
		glVertexAttribPointer((GLuint)1, 3, GL_FLOAT, GL_FALSE, sizeof(SVertexTypePNT), (void*)sizeof(glm::vec3));
		
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		// Texture buffer
		glEnableVertexAttribArray(2);
		glBindBuffer(GL_ARRAY_BUFFER, m_pVBO[2]);
		glBufferData(GL_ARRAY_BUFFER, m_vertCount*sizeof(SVertexTypePNT), pVertData, GL_STATIC_DRAW);
		glVertexAttribPointer((GLuint)2, 2, GL_FLOAT, GL_FALSE, sizeof(SVertexTypePNT), (void*)(sizeof(glm::vec3) * 2));
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		break;

	case eVertexPNTT:
		m_numVBOs = 4;
		m_pVBO = new GLuint[m_numVBOs];

		// Generate and setup VBOs
		glGenBuffers(m_numVBOs, m_pVBO);

		// Position buffer
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, m_pVBO[0]);
		glBufferData(GL_ARRAY_BUFFER, m_vertCount*sizeof(SVertexTypePNTT), pVertData, GL_STATIC_DRAW);
		glVertexAttribPointer((GLuint)0, 3, GL_FLOAT, GL_FALSE, sizeof(SVertexTypePNTT), 0);

		glBindBuffer(GL_ARRAY_BUFFER, 0);

		// Normal buffer
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, m_pVBO[1]);
		glBufferData(GL_ARRAY_BUFFER, m_vertCount*sizeof(SVertexTypePNTT), pVertData, GL_STATIC_DRAW);
		glVertexAttribPointer((GLuint)1, 3, GL_FLOAT, GL_FALSE, sizeof(SVertexTypePNTT), (void*)sizeof(glm::vec3));

		glBindBuffer(GL_ARRAY_BUFFER, 0);

		// Tangent buffer
		glEnableVertexAttribArray(2);
		glBindBuffer(GL_ARRAY_BUFFER, m_pVBO[2]);
		glBufferData(GL_ARRAY_BUFFER, m_vertCount*sizeof(SVertexTypePNTT), pVertData, GL_STATIC_DRAW);
		glVertexAttribPointer((GLuint)2, 3, GL_FLOAT, GL_FALSE, sizeof(SVertexTypePNTT), (void*)(sizeof(glm::vec3) * 2));

		glBindBuffer(GL_ARRAY_BUFFER, 0);

		// Texture buffer
		glEnableVertexAttribArray(3);
		glBindBuffer(GL_ARRAY_BUFFER, m_pVBO[3]);
		glBufferData(GL_ARRAY_BUFFER, m_vertCount*sizeof(SVertexTypePNTT), pVertData, GL_STATIC_DRAW);
		glVertexAttribPointer((GLuint)3, 2, GL_FLOAT, GL_FALSE, sizeof(SVertexTypePNTT), (void*)(sizeof(glm::vec3) * 3));
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		break;

	case eVertexPNBTT:
		m_numVBOs = 5;
		m_pVBO = new GLuint[m_numVBOs];

		// Generate and setup VBOs
		glGenBuffers(m_numVBOs, m_pVBO);

		// Position buffer
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, m_pVBO[0]);
		glBufferData(GL_ARRAY_BUFFER, m_vertCount*sizeof(SVertexTypePNTT), pVertData, GL_STATIC_DRAW);
		glVertexAttribPointer((GLuint)0, 3, GL_FLOAT, GL_FALSE, sizeof(SVertexTypePNTT), 0);

		glBindBuffer(GL_ARRAY_BUFFER, 0);

		// Normal buffer
		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, m_pVBO[1]);
		glBufferData(GL_ARRAY_BUFFER, m_vertCount*sizeof(SVertexTypePNTT), pVertData, GL_STATIC_DRAW);
		glVertexAttribPointer((GLuint)1, 3, GL_FLOAT, GL_FALSE, sizeof(SVertexTypePNTT), (void*)sizeof(glm::vec3));

		glBindBuffer(GL_ARRAY_BUFFER, 0);

		// Tangent buffer
		glEnableVertexAttribArray(2);
		glBindBuffer(GL_ARRAY_BUFFER, m_pVBO[2]);
		glBufferData(GL_ARRAY_BUFFER, m_vertCount*sizeof(SVertexTypePNTT), pVertData, GL_STATIC_DRAW);
		glVertexAttribPointer((GLuint)2, 3, GL_FLOAT, GL_FALSE, sizeof(SVertexTypePNTT), (void*)(sizeof(glm::vec3) * 2));

		glBindBuffer(GL_ARRAY_BUFFER, 0);

		// Bi-Tangent buffer
		glEnableVertexAttribArray(3);
		glBindBuffer(GL_ARRAY_BUFFER, m_pVBO[3]);
		glBufferData(GL_ARRAY_BUFFER, m_vertCount*sizeof(SVertexTypePNTT), pVertData, GL_STATIC_DRAW);
		glVertexAttribPointer((GLuint)3, 3, GL_FLOAT, GL_FALSE, sizeof(SVertexTypePNTT), (void*)(sizeof(glm::vec3) * 3));

		glBindBuffer(GL_ARRAY_BUFFER, 0);

		// Texture buffer
		glEnableVertexAttribArray(4);
		glBindBuffer(GL_ARRAY_BUFFER, m_pVBO[4]);
		glBufferData(GL_ARRAY_BUFFER, m_vertCount*sizeof(SVertexTypePNTT), pVertData, GL_STATIC_DRAW);
		glVertexAttribPointer((GLuint)4, 2, GL_FLOAT, GL_FALSE, sizeof(SVertexTypePNTT), (void*)(sizeof(glm::vec3) * 4));
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		break;

	default:
		break;
	}

	glBindVertexArray(0);

	m_bLoadedData = true;
	return ERRORID_NONE;
}


//----------------------------------------------------------------------------------------------------
//
//	UseBuffer(..)
//
//	Description:
//	Set this buffer to be the current buffer in use
//
//----------------------------------------------------------------------------------------------------
void CVertexBuffer::UseBuffer()
{
	if (m_bLoadedData)
	{
		// Free previous used buffer
		glBindVertexArray(0);			// Probably don't need this
		glBindVertexArray(m_VAO);
	}
}

GLuint CVertexBuffer::GetVertexArray() const
{
	return m_VAO;
}

GLuint CVertexBuffer::GetVertexCount() const
{
	return m_vertCount;
}

GLuint CVertexBuffer::GetVertexBufferObjCount() const
{
	return m_numVBOs;
}

EVertexType CVertexBuffer::GetVertexType() const
{
	return m_vertType;
}

bool CVertexBuffer::IsLoadedData() const
{
	return m_bLoadedData;
}

//----------------------------------------------------------------------------------------------------
//
//	ShutDown(..)
//
//	Description:
//	Clean up
//
//----------------------------------------------------------------------------------------------------
void CVertexBuffer::ShutDown()
{
	if (m_bLoadedData)
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glDeleteBuffers(m_numVBOs, m_pVBO);
		glDeleteVertexArrays(1, &m_VAO);

		if (m_numVBOs > 0)
			delete[] m_pVBO;

		m_VAO = 0;
		m_pVBO = nullptr;
		m_numVBOs = 0;
		m_vertCount = 0;
		m_bLoadedData = false;
	}
}