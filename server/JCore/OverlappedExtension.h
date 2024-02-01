#pragma once

#ifdef JCORE_EXPORTS
#define JCORE_API __declspec(dllexport)
#else
#define JCORE_API __declspec(dllimport)
#endif

namespace JCore
{
	struct JCORE_API OverlappedExtension
	{
		WSAOVERLAPPED wsaOver;
		char	opMode;
		WSABUF	wsaBuf;
		unsigned char iocpBuf[BUF_SIZE];
		int		objectId;
	};
}
