//--------------------------------------------------------------------------
//
//	24/03/2014
//
//	Index Buffer
//
//	Author: Matt © 2014
//
//--------------------------------------------------------------------------

#ifndef __CINDEXBUFFER_H__
#define __CINDEXBUFFER_H__

#include "GfxDefs.h"
#include "Errors.h"

class CIndexBuffer
{
public:
	CIndexBuffer();
	CIndexBuffer(const CIndexBuffer& other);
	~CIndexBuffer();

	ErrorId LoadData(GLuint* pIndexData, GLuint indexCount);

	void UseBuffer();

	GLuint GetElementBuffer() const;
	GLuint GetIndexCount() const;
	bool IsLoadedData() const;
		
	void ShutDown();

private:
	GLuint m_idxCount;			// Number of index entries
	GLuint m_elementBuffer;
	bool m_bLoadedData;
};


#endif