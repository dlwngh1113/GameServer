#pragma once

struct BasePacket;

class PacketSender
{
	static PacketSender s_instance;

private:
	static void Send(ClientCommon::Packet* packet);
	static void Send(unsigned char* packet, short snSize);

public:
	static PacketSender& GetInstance() { return s_instance; }
};

