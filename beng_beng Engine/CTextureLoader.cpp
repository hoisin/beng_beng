//--------------------------------------------------------------------------
//
//	Class handling texture loading
//
//	Using FreeImage library for loading images
//
//--------------------------------------------------------------------------

#include "CTextureLoader.h"
#include "FreeImage.h"

CTextureLoader::CTextureLoader()
{
	FreeImage_Initialise();
}


CTextureLoader::~CTextureLoader()
{
	FreeImage_DeInitialise();
}

//------------------------------------------------------------------
//
//	CTextureLoader()
//
//	Params:
//	fileName		- directory to file
//	outWidth		- returns width of loaded texture
//	outHeight		- returns height of loaded texture
//	texFormat		- returns the textureFormat
//	bytesPerPixel	- returns the bytes per pixel of loaded texture
//	pOutData		- returns pointer to texture data
//
//	Loads texture into memory.
//  Supported types:
//	BMP
//	TARGA
//	PNG
//
//------------------------------------------------------------------
ErrorId CTextureLoader::LoadFile(const std::string &fileName, unsigned int &outWidth, unsigned int &outHeight,
	ETextureFormat &eTexFormat, unsigned int &bytesPerPixel, unsigned char** pOutData)
{
	FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;

	// Pointer to the image, once loaded
	FIBITMAP *dib(0);
	
	// pointer to the image data
	BYTE* bits(0);
	
	unsigned int width(0), height(0);

	fif = FreeImage_GetFileType(fileName.c_str(), 0);

	// Return the file format
	switch (fif)
	{
	case FIF_BMP:
		eTexFormat = eTextureFormatBMP;
		break;

	case FIF_TARGA:
		eTexFormat = eTextureFormatTGA;
		break;

	case FIF_PNG:
		eTexFormat = eTextureFormatPNG;
		break;

	default:
		eTexFormat = eTextureFormatNone;
		break;
	}

	// If still unknown, try to get the file format from the file extension
	if(fif == FIF_UNKNOWN)
		fif = FreeImage_GetFIFFromFilename(fileName.c_str());

	if(fif == FIF_UNKNOWN)
		return ERRORID_GFX_TEXTURE_LOAD_UNKNOWN_FORMAT;

	// check that the pluging has reading capabilities and load the file
	if (FreeImage_FIFSupportsReading(fif))
		dib = FreeImage_Load(fif, fileName.c_str());

	// If the image failed to load, return fail
	if(!dib) 
		return ERRORID_GFX_TEXTURE_LOAD_FAILED;

	// Retrieve the image data
	bits = FreeImage_GetBits(dib);

	// Get the image height and width
	width = FreeImage_GetWidth(dib);
	height = FreeImage_GetHeight(dib);

	// If somehow one of these fail, return fail
	if(bits == 0 || width == 0 || height == 0)
		return ERRORID_GFX_TEXTURE_LOAD_INVALID_WIDTH_HEIGHT_BITS;

	unsigned int bpp = FreeImage_GetBPP(dib) / 8;
	
	// Output bits per pixel
	bytesPerPixel = bpp;

	// Create copy of image data
	*pOutData = new unsigned char[bpp * width * height];
	outWidth = width;
	outHeight = height;

	memcpy(*pOutData, bits, bpp * width * height);

	FreeImage_Unload(dib);

	return ERRORID_NONE;
}