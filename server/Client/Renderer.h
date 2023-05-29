#pragma once

class Renderer
{
	static Renderer s_instance;
	SDL_Renderer* m_renderer;
public:
	Renderer();
	virtual ~Renderer();

	SDL_Renderer*& GetRenderer();

	static Renderer& GetInstance()
	{
		return s_instance;
	}
};
