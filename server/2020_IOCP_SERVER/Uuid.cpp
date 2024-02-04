#include "stdafx.h"
#include "Uuid.h"

namespace Core
{
	Uuid Uuid::s_instance;

	Uuid::Uuid()
	{
	}

	Uuid::~Uuid()
	{
	}

	boost::uuids::uuid Uuid::New()
	{
		return s_instance.m_generator();
	}

	boost::uuids::uuid Uuid::Empty()
	{
		return boost::uuids::uuid();
	}
}