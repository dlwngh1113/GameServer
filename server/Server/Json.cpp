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

    // JSON ���ڿ��� �Ľ��Ͽ� value ��ü�� �о����
    m_value = boost::json::parse(data);

    // value ��ü���� object ��ü�� ��ȯ�Ͽ� �ʿ��� �����Ϳ� ����
    boost::json::object& obj = m_value.as_object();

    // �ʿ��� ����v�Ϳ� �����Ͽ� ���
    std::cout << "Name: " << obj["name"].as_string() << std::endl;
    std::cout << "Age: " << obj["age"].as_int64() << std::endl;
    std::cout << "City: " << obj["city"].as_string() << std::endl;
    for (auto elem : obj["h"].as_array())
    {

    }
}
