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

	struct uuid_hash
	{
		size_t operator()(const boost::uuids::uuid& other) const
		{
			return boost::uuids::hash_value(other);
		}
	};

	struct uuid_equal
	{
		bool operator()(const boost::uuids::uuid& param1, const boost::uuids::uuid& param2) const
		{
			return param1 == param2;
		}
	};
}
