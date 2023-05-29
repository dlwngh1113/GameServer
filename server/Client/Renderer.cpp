#include "pch.h"
#include "Renderer.h"

Renderer Renderer::s_instance;

Renderer::Renderer()
{
}

Renderer::~Renderer()
{
    SDL_DestroyRenderer(m_renderer);
}

SDL_Renderer*& Renderer::GetRenderer()
{
    return m_renderer;
}
