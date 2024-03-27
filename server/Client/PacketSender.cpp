#include "pch.h"
#include "PacketSender.h"
#include "NetworkManager.h"

PacketSender PacketSender::s_instance;

void PacketSender::Send(unsigned char* packet, short snSize)
{
	NetworkManager::GetInstance().SendPacket(packet, snSize);
}
