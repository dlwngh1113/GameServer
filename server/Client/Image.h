#pragma once
#include "Asset.h"

namespace ClientFramework
{
	class Image : public Asset
	{
	private:
		SDL_Texture* m_texture;

	public:
		SDL_Texture* texture() { return m_texture; }

	protected:
		virtual void OnSetFilename() override;

	public:
		virtual void Load() override;
	};
}
