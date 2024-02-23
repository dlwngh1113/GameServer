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
    // JSON 데이터를 문자열로 초기화
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

    // JSON 문자열을 파싱하여 value 객체로 읽어들임
    boost::json::value jv = boost::json::parse(json_data);
     
    // value 객체에서 object 객체로 변환하여 필요한 데이터에 접근
    boost::json::object& obj = jv.as_object();

    // 필요한 데이v터에 접근하여 출력
    std::cout << "Name: " << obj["name"].as_string() << std::endl;
    std::cout << "Age: " << obj["age"].as_int64() << std::endl;
    std::cout << "City: " << obj["city"].as_string() << std::endl;
}
