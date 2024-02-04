#pragma once

namespace JCore
{
	class Uuid
	{
	private:
		boost::uuids::random_generator m_generator;

	public:
		Uuid();
		~Uuid();

	private:
		static Uuid s_instance;
	public:
		static boost::uuids::uuid New();
		static boost::uuids::uuid Empty();
	};
}
