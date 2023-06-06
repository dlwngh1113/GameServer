#pragma once

class Handler
{
public:
	Handler();
	virtual ~Handler();

protected:
	unsigned char* m_packet{ nullptr };
	short m_snPacketSize{ 0 };

public:
	void Init(unsigned char* packet, short snPacketSize);
	virtual void Handle() = 0;
	virtual Handler* Create() = 0;
};

