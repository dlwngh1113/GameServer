#include "pch.h"
#include "PacketSender.h"
#include "NetworkManager.h"

PacketSender PacketSender::s_instance;

void PacketSender::Send(char* packet, short snSize)
{
	NetworkManager::instance().SendPacket(packet, snSize);
}
