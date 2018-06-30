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

class CTextureLoader
{
public:
	CTextureLoader();
	~CTextureLoader();

	bool LoadFile(const std::string &fileName, unsigned int &outWidth, unsigned int &outHeight, 
		ETextureFormat &eTexFormat, unsigned int &bytesPerPixel, unsigned char** pOutData);

	// Can probably remove this
	// Not used.
	bool LoadBMP(const std::string &fileName, unsigned int &outWidth, unsigned int &outHeight,
		unsigned char** pOutData);
};

#endif