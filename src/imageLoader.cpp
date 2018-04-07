#include <GL/glew.h>
#include <IL/il.h>
#include <IL/ilut.h>

#include <iostream>

ILuint ImageID;
ILenum Error;
ILuint width, height;
ILubyte *data;
GLuint textureID;

void imageLoader(const char* filename) {
	/*Image Loader with DevIL*/
	ilInit();
	ilutRenderer(ILUT_OPENGL);
	ilGenImages(1, &ImageID);
	ilBindImage(ImageID);
	ilLoadImage(filename);

	//Print Errors if Loading goes wrong
	do
	{
		Error = ilGetError();
		if (Error != IL_NO_ERROR) std::cout << Error << std::endl;
	} while (Error != IL_NO_ERROR);

	//Get basic data from image
	width = ilGetInteger(IL_IMAGE_WIDTH);
	height = ilGetInteger(IL_IMAGE_HEIGHT);
	data = ilGetData();

	// Create one OpenGL texture
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);

	// Give the image to OpenGL
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, data);

	// Nice trilinear filtering.
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glGenerateMipmap(GL_TEXTURE_2D);

	//textureID = ilutGLBindTexImage();
	ilDeleteImages(1, &ImageID);
}

