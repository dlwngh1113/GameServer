#include "stdafx.h"
#include "Logger.h"

Logger Logger::s_instance;

Logger::Logger()
{
	boost::log::add_file_log("log.txt");
	boost::log::add_common_attributes();
}

void Logger::Log(const char* message)
{
	boost::log::record record = m_logger.open_record();
	if (record)
	{
		boost::log::record_ostream os(record);
		os << message;
		os.flush();
		m_logger.push_record(move(record));
	}
}

void Logger::Log(const string& message)
{
	Log(message.c_str());
}