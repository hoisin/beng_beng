#include "Errors.h"

bool IsError(ErrorId error)
{
	if (error == ERRORID_NONE)
		return false;
	
	return true;
}

bool IsNoError(ErrorId error)
{
	if (error == ERRORID_NONE)
		return true;

	return false;
}