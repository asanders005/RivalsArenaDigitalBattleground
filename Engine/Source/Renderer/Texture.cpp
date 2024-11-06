#include "Texture.h"
#include "Renderer.h"
#include "Core/EAssert.h"
#include "Math/Vector2.h"
#include <SDL_image.h>
#include <iostream>

Texture::~Texture()
{
	if (m_texture) SDL_DestroyTexture(m_texture);
}

bool Texture::Create(std::string name, ...)
{
	va_list args;
	va_start(args, name);
	Renderer renderer = va_arg(args, Renderer);
	va_end(args);

    return Load(name, renderer);
}

bool Texture::Load(const std::string& filename, Renderer& renderer)
{
	// load image onto surface
	SDL_Surface* surface = IMG_Load(filename.c_str());
	if (!surface)
	{
		std::cerr << "Could not load image: " << filename << std::endl;
		return false;
	}

	// create texture from surface
	m_texture = SDL_CreateTextureFromSurface(renderer.m_renderer, surface);
	// once texture is created, can freee surface
	SDL_FreeSurface(surface);
	if (!m_texture)
	{
		std::cerr << "Could not create texture: " << filename << std::endl;
		return false;
	}

    return true;
}

Vector2 Texture::GetSize()
{
	ASSERT(m_texture);

	// query texture for size
	SDL_Point size;
	SDL_QueryTexture(m_texture, NULL, NULL, &size.x, &size.y);

	return { size.x, size.y };
}

