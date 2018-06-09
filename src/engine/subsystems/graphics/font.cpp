#include "engine/subsystems/graphics/font.h"

#include <cassert>
#include <algorithm>

Font::Font(const std::string & filename)
{
	auto error = FT_Init_FreeType(&library);
	assert(error == 0);
	error = FT_New_Face(library, filename.c_str(), 0, &face);
	assert(error == 0);
}

Font::~Font()
{
	FT_Done_Face(face);
	FT_Done_FreeType(library);
}

void Font::setSize(unsigned int size)
{
	FT_Set_Pixel_Sizes(face, 0, size);
}

void Font::renderText(const std::shared_ptr<Texture>& texture, const std::wstring& text)
{
	unsigned int maxWidth = 0;
	unsigned int currentWidth = 0;
	unsigned int height = 0;
	unsigned int lineCount = 1;
	int topLine = 0;
	int bottomLine = 0;
	for (const auto& c : text)
	{
		FT_Load_Char(face, c, FT_LOAD_DEFAULT);
		currentWidth += face->glyph->advance.x;
		topLine = std::max(face->glyph->bitmap_top, topLine);
		bottomLine = std::max(static_cast<int>(face->glyph->bitmap.rows) - face->glyph->bitmap_top, bottomLine);

		if (c == '\n')
		{
			maxWidth = std::max(currentWidth, maxWidth);
			currentWidth = 0;
			lineCount++;
		}
	}
	unsigned int width = std::max(currentWidth, maxWidth) >> 6;
	height = topLine + bottomLine;

	texture->init(width, height * lineCount);
	std::vector<uint8_t> data(width * height * lineCount * 4, 0);
	texture->setData(0, 0, width, height * lineCount, Texture::DataFormat::RGBA, &data[0]);

	unsigned int x = 0;
	unsigned int y = 0;

	for (const auto& c : text)
	{
		auto error = FT_Load_Char(face, c, FT_LOAD_RENDER);
		if (!error)
		{
			unsigned int w = face->glyph->bitmap.width;
			unsigned int h = face->glyph->bitmap.rows;
			unsigned int l = x + face->glyph->bitmap_left;
			unsigned int t = y + topLine - face->glyph->bitmap_top;

			std::vector<uint8_t> data(w * h * 4, 255);
			for (size_t i = 0; i < w * h; i++)
				data[3 + i * 4] = face->glyph->bitmap.buffer[i];

			if (w && h)
				texture->setData(l, t, w, h, Texture::DataFormat::RGBA, &data[0]);
		}
		x += face->glyph->advance.x >> 6;

		if (c == '\n')
		{
			x = 0;
			y += height;
		}
	}
}
