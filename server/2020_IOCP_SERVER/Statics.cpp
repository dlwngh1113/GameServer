#include "stdafx.h"
#include "Statics.h"

ObjectPool<OVER_EX> Statics::overlappedPool{ ClientCommon::MAX_USER };