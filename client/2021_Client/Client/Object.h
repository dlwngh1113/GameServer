#pragma once

class Object
{
protected:
	SDL_Rect m_position{ NULL };

public:
	Object();
	virtual ~Object();

	virtual void Update(float flElapsedTime) = 0;
	virtual void Render() = 0;
};