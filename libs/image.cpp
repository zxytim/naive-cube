/*
 * $File: image.cpp
 * $Date: Wed Dec 01 10:56:29 2010 +0800
 * $Author: Zhou Xinyu <zxytim@gmail.com>
 */
/*
   This file is part of naive-cube

   Copyright (C) <2010>  Zhou Xinyu <zxytim@gmail.com>

   naive-cube is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   naive-cube is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with naive-cube.  If not, see <http://www.gnu.org/licenses/>.

*/
#include  "image.h"
#include <cstdio>
#include <cstdlib>

#define ul unsigned long

static unsigned int getint(FILE *fp)
{
	return getc(fp) + (getc(fp) << 8)
	   	+ (getc(fp) << 16) + (getc(fp) << 24);
}

static unsigned int getshort(FILE *fp)
{
	return getc(fp) + (getc(fp) << 8);
}

bool ImageLoad(const char *filename, Image *image)
{
	FILE *file;
	ul size, planes, bpp;

	if ((file = fopen(filename, "rb")) == NULL)
	{
		printf("Image file not found: %s\n", filename);
		return 0;
	}

	fseek(file, 18, SEEK_CUR);

	image->sizeX = getint(file);
	printf("Width of %s: %lu\n", filename, image->sizeX);

	image->sizeY = getint(file);
	printf("Height of %s: %lu\n", filename, image->sizeY);

	size = image->sizeX * image->sizeY * 3;

	planes = getshort(file);
	if (planes != 1)
	{
		printf("Planes from %s is not 1: %lu\n", filename, planes);
		return 0;
	}

	bpp = getshort(file);
	if (bpp != 24)
	{
		printf("Bpp from %s is not 24: %lu\n", filename, bpp);
		return 0;
	}

	fseek(file, 24, SEEK_CUR);

	image->data = (char *)malloc(size);
	if (image->data == NULL)
	{
		printf("Error allocating memory for color-corrected image data\n");
		return 0;
	}

	if (fread(image->data, size, 1, file) != 1)
	{
		printf("Error reading image data from %s.\n", filename);
		return 0;
	}

	for (ul i = 0; i < size; i += 3)
	{
		char t = image->data[i];
		image->data[i] = image->data[i + 2];
		image->data[i + 2] = t;
	}

	return true;
}

#undef ul
