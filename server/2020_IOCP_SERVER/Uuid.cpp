#include "stdafx.h"
#include "Uuid.h"

namespace Core
{
	boost::uuids::random_generator Uuid::s_generator;

	Uuid::Uuid()
	{
	}

	Uuid::~Uuid()
	{
	}

	boost::uuids::uuid Uuid::New()
	{
		return s_generator();
	}

	boost::uuids::uuid Uuid::Empty()
	{
		return boost::uuids::uuid();
	}
}