#include "pch.h"
#include "PacketSender.h"
#include "NetworkManager.h"

PacketSender PacketSender::s_instance;

void PacketSender::Send(ClientCommon::Packet* packet)
{
	unsigned char* data = reinterpret_cast<unsigned char*>(packet);
	Send(data, packet->header.size);
}

void PacketSender::Send(unsigned char* packet, short snSize)
{
	NetworkManager::GetInstance().SendPacket(packet, snSize);
}
