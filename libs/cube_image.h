#define ul unsigned long

class Image
{
	public:
		ul sizeX;
		ul sizeY;
		char *data;
};

int ImageLoad(const char *filename, Image *image);

#undef ul
