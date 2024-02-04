#pragma once

namespace Core
{
	class Uuid
	{
	public:
		Uuid();
		~Uuid();

		// Static member variables
	private:
		static boost::uuids::random_generator s_generator;

		// Stataic member functions
	public:
		static boost::uuids::uuid New();
		static boost::uuids::uuid Empty();
	};
}
