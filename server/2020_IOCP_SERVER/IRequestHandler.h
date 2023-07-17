#pragma once

class Peer;

class IRequestHandler
{
public:
	virtual void Handle() = 0;
	virtual void Initialize(Peer* peer, ClientCommon::BasePacket*) = 0;
};

