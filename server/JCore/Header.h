#pragma once

namespace JCore
{
	struct JCORE_API Header
	{
		short type;
		short size;
	};

	struct JCORE_API Packet
	{
		Header header;
	};
}
