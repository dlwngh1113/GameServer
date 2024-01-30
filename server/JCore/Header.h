#pragma once

namespace JCore
{
	struct Header
	{
		short type;
		short size;
	};

	struct Packet
	{
		Header header;
	};
}
