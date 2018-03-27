#pragma once

#include <string>

/*	Contains basic information about texture and id refrence
	to it in video memory. Many refrences to the same id may exist
	so texture isn't deleted after object destruction, it has to be
	done manually.
*/
class Texture
{
	unsigned int _id = 0;
protected:
	std::string _path;
	int _width;
	int _height;
	int _channels; // e.g. rgb has 3 color channels
public:
	bool operator==(const Texture &tex);
	Texture();
	Texture(std::string path, bool generateMipmap = false, bool flip = false);
	bool Blank() const { return _id == 0; }
	// Unloads texture from video memory
	void unload();
	// Binds texture in slot 0
	void use() const;
	// Binds texture in specified slot
	void use(int slot);
	int getWidth() { return _width; }
	int getHeight() { return _height; }
	const char* getPath() { return _path.c_str(); }
};