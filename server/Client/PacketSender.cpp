#include "pch.h"
#include "PacketSender.h"
#include "NetworkManager.h"

PacketSender PacketSender::s_instance;

void PacketSender::Send(ClientCommon::BasePacket* packet)
{
	unsigned char* data = reinterpret_cast<unsigned char*>(packet);
	Send(data, packet->header.size);
}

void PacketSender::Send(unsigned char* packet, short snSize)
{
	NetworkManager::GetInstance().SendPacket(packet, snSize);
}

void PacketSender::SendLogin(const char* sName)
{
	ClientCommon::LoginRequest packet;
	packet.header.size = sizeof(packet);
	packet.header.type = static_cast<short>(ClientCommand::Login);
	strcpy_s(packet.name, sName);

	Send(&packet);
}
