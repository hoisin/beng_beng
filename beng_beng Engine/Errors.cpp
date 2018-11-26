#include "Errors.h"

bool IsError(ErrorId error)
{
	if (error == ERRORID_NONE)
		return false;
	else
		return true;
}