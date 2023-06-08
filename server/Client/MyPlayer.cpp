#include "pch.h"
#include "MyPlayer.h"
#include "PacketSender.h"

MyPlayer::MyPlayer(int nx, int ny, int nWidth, int nHeight) : Player(nx, ny, nWidth, nHeight)
{
}

MyPlayer::~MyPlayer()
{
}

void MyPlayer::Move(SDL_Keycode code)
{
	PacketSender::GetInstance().SendMove(code - 79);
}
