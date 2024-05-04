#pragma once
#include "UIBase.h"

namespace ClientFramework
{
    class Label : public UIBase
    {
    protected:
        SDL_Surface* m_surface;
        TTF_Font* m_font;
        SDL_Texture* m_texture;
        SDL_Color m_color;

    public:
        explicit Label();
        virtual ~Label();

    public:
        virtual void Initialize() override;
        void Render(SDL_Renderer* renderer);
    };
}
