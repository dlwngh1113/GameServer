#include "stdafx.h"
#include "JsonUtil.h"

JsonUtil JsonUtil::s_instance;

boost::json::value JsonUtil::Parse(const char* fileName)
{
    ifstream in(fileName, ios_base::app | ios_base::binary);
    boost::json::stream_parser p;
    boost::json::error_code ec;
    do
    {
        char buf[4096];
        auto& nread = in.read(buf, sizeof(buf));
        p.write(buf, nread.gcount(), ec);
    } while (!in.eof());
    if (ec)
        return nullptr;
    p.finish(ec);
    if (ec)
        return nullptr;

    return p.release();
}

void JsonUtil::Test()
{
    boost::json::value val = Parse("hello.json");
    if (val != nullptr)
    {
    }
}
