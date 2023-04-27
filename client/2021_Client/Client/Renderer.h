#pragma once
#include "Singleton.h"

class Renderer : public Singleton<Renderer>
{
	SDL_Renderer* m_renderer;
public:
	Renderer();
	virtual ~Renderer();

	SDL_Renderer*& GetRenderer();
};
