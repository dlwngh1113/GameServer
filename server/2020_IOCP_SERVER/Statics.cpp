#include "stdafx.h"
#include "Statics.h"

ThreadPool Statics::s_threadPool{ MAX_THREAD_COUNT };
ObjectPool<OVER_EX> Statics::s_overlappedPool{ MAX_USER };