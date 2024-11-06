#pragma once
#include "Resources/Resource.h"
#include <string>

struct _TTF_Font;

class Font : public Resource
{
public:
	Font() = default;
	~Font();

	bool Create(std::string name, ...) override;

	friend class Text;

private:
	_TTF_Font* m_ttfFont{ nullptr };

	bool Load(const std::string& name, int fontSize);
};