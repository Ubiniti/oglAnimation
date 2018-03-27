#include <iostream>
#include <glad/glad.h>
#include <stb_image.h>
#include "Texture.h"
#include "OpenGL.h"

bool Texture::operator==(const Texture & tex)
{
	return _path == tex._path;
}

Texture::Texture() :
	_id(0),
	_width(0),
	_height(0),
	_channels(0)
{
}

Texture::Texture(std::string path, bool generateMipmap, bool flip)
{
	stbi_set_flip_vertically_on_load(flip);
	unsigned char* data = stbi_load(path.c_str(), &_width, &_height, &_channels, 0);
	if (!data)
	{
		std::cout << "[STBI Error] Failed to load texture from " << path << std::endl;
	}
	else
	{
		_path = path;
		GLenum format;
		if (_channels == 1)
			format = GL_RED;
		else if (_channels == 3)
			format = GL_RGB;
		else if (_channels == 4)
			format = GL_RGBA;

		GlCall(glGenTextures(1, &_id));
		GlCall(glBindTexture(GL_TEXTURE_2D, _id));

		GlCall(glTexImage2D(GL_TEXTURE_2D, 0, format, _width, _height, 0, format, GL_UNSIGNED_BYTE, data));

		GlCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
		GlCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);)
		GlCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
		GlCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
		if (generateMipmap)
		{
			GlCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR));
			GlCall(glGenerateMipmap(GL_TEXTURE_2D));
		}
	}
	//std::cout << path << std::endl;
	stbi_image_free(data);
}

void Texture::unload()
{
	GlCall(glDeleteTextures(1, &_id));
}

void Texture::use() const
{
	GlCall(glActiveTexture(GL_TEXTURE0));
	GlCall(glBindTexture(GL_TEXTURE_2D, _id));
}

void Texture::use(int slot)
{
	GlCall(glActiveTexture(GL_TEXTURE0 + slot));
	GlCall(glBindTexture(GL_TEXTURE_2D, _id));
}
