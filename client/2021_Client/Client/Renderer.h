#pragma once

class Renderer
{
	SDL_Renderer* m_renderer;
public:
	Renderer();
	virtual ~Renderer();

	SDL_Renderer*& GetRenderer();
};
