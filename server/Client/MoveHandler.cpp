#include "pch.h"
#include "MoveHandler.h"
#include "Framework.h"

MoveHandler::MoveHandler()
{
}

MoveHandler::~MoveHandler()
{
}

void MoveHandler::Handle()
{
    Scene* scene = Framework::GetInstance().GetScene();
    if (scene == nullptr)
    {
        std::cout << "현재 씬이 존재하지 않습니다.\n";
        return;
    }


}

Handler* MoveHandler::Create()
{
    return new MoveHandler;
}
