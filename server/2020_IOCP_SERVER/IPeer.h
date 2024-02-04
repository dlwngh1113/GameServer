#pragma once

namespace JCore
{
	class IPeer
	{
		virtual void ProcessPacket(unsigned char* data, unsigned short snSize) = 0;
	public:
		virtual void ProcessIO(short ioSize) = 0;
		virtual void SendPacket(unsigned char* data, unsigned short snSize) = 0;
	};
}