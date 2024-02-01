#pragma once

#ifdef JCORE_EXPORTS
#define JCORE_API __declspec(dllexport)
#else
#define JCORE_API __declspec(dllimport)
#endif

namespace JCore
{
	class JCORE_API IPeer
	{
	public:
		virtual void ProcessIO(DWORD ioSize) = 0;
		virtual void SendPacket(unsigned char* data, unsigned short snSize) = 0;
	};
}
