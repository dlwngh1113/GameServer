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
        std::cout << "���� ���� �������� �ʽ��ϴ�.\n";
        return;
    }


}

Handler* MoveHandler::Create()
{
    return new MoveHandler;
}
