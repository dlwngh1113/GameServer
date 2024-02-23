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
    // JSON �����͸� ���ڿ��� �ʱ�ȭ
    std::string json_data = R"(
        {
            "name": "John",
            "age": 30,
            "city": "New York"
        },
        {
            "name": "Kon",
            "friends":
            [
                "kate",
                "juho"
            ],
            "age": 3,
            "city": "New York"
        }
    )";

    // JSON ���ڿ��� �Ľ��Ͽ� value ��ü�� �о����
    boost::json::value jv = boost::json::parse(json_data);
     
    // value ��ü���� object ��ü�� ��ȯ�Ͽ� �ʿ��� �����Ϳ� ����
    boost::json::object& obj = jv.as_object();

    // �ʿ��� ����v�Ϳ� �����Ͽ� ���
    std::cout << "Name: " << obj["name"].as_string() << std::endl;
    std::cout << "Age: " << obj["age"].as_int64() << std::endl;
    std::cout << "City: " << obj["city"].as_string() << std::endl;
}
