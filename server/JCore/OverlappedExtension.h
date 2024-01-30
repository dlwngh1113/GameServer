#pragma once
#include <WS2tcpip.h>

namespace JCore
{
	struct OverlappedExtension
	{
		WSAOVERLAPPED wsaOver;
		char	opMode;
		WSABUF	wsaBuf;
		unsigned char iocpBuf[BUF_SIZE];
		int		objectId;
	};
}
