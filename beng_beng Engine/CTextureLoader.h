//--------------------------------------------------------------------------
//
//	Class handling texture loading
//
//	Using FreeImage library for loading images
//
//--------------------------------------------------------------------------

#ifndef __CTEXTURELOADER_H__
#define __CTEXTURELOADER_H__

#include <string>
#include "GfxDefs.h"

#include "Errors.h"

class CTextureLoader
{
public:
	CTextureLoader();
	~CTextureLoader();

	ErrorId LoadFile(const std::string &fileName, unsigned int &outWidth, unsigned int &outHeight, 
		ETextureFormat &eTexFormat, unsigned int &bytesPerPixel, unsigned char** pOutData);
};

#endif