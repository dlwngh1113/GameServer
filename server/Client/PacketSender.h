#pragma once

struct BasePacket;

class PacketSender
{
	static PacketSender s_instance;

private:
	static void Send(ClientCommon::BasePacket* packet);
	static void Send(unsigned char* packet, short snSize);

public:
	static void SendLogin(const char* sName);

	static PacketSender& GetInstance()
	{
		return s_instance;
	}
};

