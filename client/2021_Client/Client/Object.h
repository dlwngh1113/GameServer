#pragma once

class Object
{
protected:
public:
	Object() = default;
	Object(SDL_Rect* position);
	virtual ~Object();
};