
#include "exception.h"
#include <cstdio>

void Exception::msg(const char *msg)
{
	fprintf(stderr, "Error: %s\n", msg);
}

