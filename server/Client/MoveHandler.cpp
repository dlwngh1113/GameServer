#include "pch.h"
#include "MoveHandler.h"
#include "Framework.h"
#include "Scene.h"
#include "MyPlayer.h"
#include "OtherPlayer.h"

MoveHandler::MoveHandler()
{
}

MoveHandler::~MoveHandler()
{
}

void MoveHandler::Handle()
{
    ClientCommon::UserMoveEvent* packet = reinterpret_cast<ClientCommon::UserMoveEvent*>(m_packet);

    Scene* scene = Framework::GetInstance().GetScene();
    if (scene == nullptr)
    {
        std::cout << "현재 씬이 존재하지 않습니다.\n";
        return;
    }

    MyPlayer* myPlayer = scene->GetPlayer();
    if (myPlayer->id() == packet->id)
    {
        myPlayer->Move(packet->x, packet->y);
    }
    else
    {
        OtherPlayer* otherPlayer = scene->GetOtherPlayer(packet->id);
        otherPlayer->Move(packet->x, packet->y);
    }
}

Handler* MoveHandler::Create()
{
    return new MoveHandler;
}
