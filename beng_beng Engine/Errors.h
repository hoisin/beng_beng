//--------------------------------------------------------------------------
//
//	Error codes
//
//	20/10/2018
//
//--------------------------------------------------------------------------
#pragma once

enum ErrorId
{
	ERRORID_NONE = 0,

	// App errors
	ERRORID_APP_INIT_INVALID_WINDOW_WIDTH_HEIGHT,
	ERRORID_APP_INIT_FAILED,
	ERRORID_APP_INIT_MULTIPLE_INSTANCES_DETECTED,
	ERRORID_APP_INIT_REGISTER_APP_FAILED,
	ERRORID_APP_INIT_CREATE_WINDOW_FAILED,

	// Derived app errors
	ERRORID_APP_RENDERER_INIT_FAILED,
	ERRORID_APP_SCENEMGR_INIT_FAILED,
	ERRORID_APP_ASSETMGR_INIT_FAILED,

	// Graphics errors
	ERRORID_GFX_INIT_GLEW_FAILED,
	ERRORID_GFX_GLEW_CREATECONTEXT_PIXELFORMAT_ERROR,
	ERRORID_GFX_REGISTEROPENGLCLASS_FAILED,
	ERRORID_GFX_CREATE_WINDOW_FAILED,
	ERRORID_GFX_INVALID_PIXEL_FORMAT,
	ERRORID_GFX_SET_PIXEL_FORMAT_FAILED,
	ERRORID_GFX_MAKECURRENT_HDC_FAILED,

	ERRORID_GFX_INIT_OPENGL_FAILED,
	ERRORID_GFX_INIT_INVALID_NULL_HWND,
	ERRORID_GFX_INIT_INVALID_WINDOW_WIDTH_HEIGHT,

	ERRORID_GFX_NULL_HWND,
	ERRORID_GFX_RENDERER_INIT_FAILED,

	ERRORID_GFX_TEXTURE_LOAD_UNKNOWN_FORMAT,
	ERRORID_GFX_TEXTURE_LOAD_FAILED,
	ERRORID_GFX_TEXTURE_LOAD_INVALID_WIDTH_HEIGHT_BITS,

	ERRORID_TOTAL
};

// Helper functions
bool IsError(ErrorId error);