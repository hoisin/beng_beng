//--------------------------------------------------------------------------
//
//	24/03/2014
//
//	Holds the related VBOs to VAO.
//
//	Author: Matt © 2014
//
//--------------------------------------------------------------------------

#ifndef __CVERTEXDATA_H__
#define __CVERTEXDATA_H__

#include "GfxDefs.h"
#include "Errors.h"

class CVertexBuffer
{
public:
	CVertexBuffer();
	CVertexBuffer(const CVertexBuffer& other);
	~CVertexBuffer();

	ErrorId LoadData(void* pVertData, glm::uint32 vertexCount, EVertexType vertType);

	void UseBuffer();

	GLuint GetVertexArray() const;
	GLuint GetVertexCount() const;
	GLuint GetVertexBufferObjCount() const;
	EVertexType GetVertexType() const;
	bool IsLoadedData() const;

	void ShutDown();

private:
	GLuint m_vertCount;	// Number of vertices (assuming a vector 3)
	GLuint m_numVBOs;	// Number of vertex buffer objects
	GLuint m_VAO;		// Only one vertex array object per CVertexBuffer
	GLuint *m_pVBO;

	EVertexType m_vertType;	

	bool m_bLoadedData;
};

#endif