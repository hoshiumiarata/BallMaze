#pragma once

#include <memory>
#include <string>

#include "texture.h"

#include <ft2build.h>
#include FT_FREETYPE_H

class Font
{
public:
	Font(const std::string& filename);
	~Font();

	void setSize(unsigned int size);
	void renderText(const std::shared_ptr<Texture>& texture, const std::wstring& text);
private:
	FT_Library library;
	FT_Face face;
};