#pragma once
#include "Singletone.h"

class Renderer : public Singletone<Renderer>
{
	SDL_Renderer* m_renderer;
public:
	Renderer();
	virtual ~Renderer();

	SDL_Renderer*& GetRenderer();
};

