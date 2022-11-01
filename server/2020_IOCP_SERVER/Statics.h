#include"ObjectPool.h"

class Statics
{
public:
	ObjectPool<OVER_EX> overlappedPool{ MAX_USER / 2 };
};