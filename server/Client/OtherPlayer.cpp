#include "pch.h"
#include "OtherPlayer.h"

OtherPlayer::OtherPlayer()
{
}

OtherPlayer::~OtherPlayer()
{
}

void OtherPlayer::Init(int nId)
{
	m_nId = nId;
}

OtherPlayer* OtherPlayer::Create(int nId)
{
	OtherPlayer* inst = new OtherPlayer;
	inst->Init(nId);
	return inst;
}
