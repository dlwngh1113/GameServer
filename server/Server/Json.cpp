#include "stdafx.h"
#include "Json.h"

Json::Json(const char* fileName)
{
	ifstream in(fileName, ios::binary);
	if (!in)
		cerr << "[Error]" << fileName << endl;

    string data;
    in >> data;
    in.close();

    // JSON 문자열을 파싱하여 value 객체로 읽어들임
    m_value = boost::json::parse(data);

    // value 객체에서 object 객체로 변환하여 필요한 데이터에 접근
    boost::json::object& obj = m_value.as_object();

    // 필요한 데이v터에 접근하여 출력
    std::cout << "Name: " << obj["name"].as_string() << std::endl;
    std::cout << "Age: " << obj["age"].as_int64() << std::endl;
    std::cout << "City: " << obj["city"].as_string() << std::endl;
    for (auto elem : obj["h"].as_array())
    {

    }
}
