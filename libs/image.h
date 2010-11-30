
#ifndef __LIBS_CUBE_IMAGE__
#define __LIBS_CUBE_IMAGE__

#define ul unsigned long

class Image
{
	public:
		ul sizeX;
		ul sizeY;
		char *data;
};

bool ImageLoad(const char *filename, Image *image);

#undef ul
#endif // __LIBS_CUBE_IMAGE__
