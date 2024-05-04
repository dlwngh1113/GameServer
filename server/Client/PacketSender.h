#pragma once

class PacketSender
{
	static PacketSender s_instance;

private:
	static void Send(unsigned char* packet, short snSize);

public:
	static PacketSender& instance() { return s_instance; }
};

