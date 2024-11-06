#pragma once
#include "Resources/Resource.h"
#include <string>

class Font;
class Renderer;
struct Color;
class Texture;

class Text
{
public:
	Text() = default;
	Text(res_t<Font> font, bool centered = false) : m_font{ font }, m_centered{ centered } {}
	~Text() = default;

	void SetFont(res_t<Font> font) { m_font = font; }

	bool Create(Renderer& renderer, const std::string& text, const Color& color);
	void Draw(Renderer& renderer, float x, float y, float angle = 0.0f);

	res_t<Texture> GetTexture() { return m_texture; }

private:
	res_t<Font> m_font{ nullptr };
	res_t<Texture> m_texture{ nullptr };
	bool m_centered = false;
};