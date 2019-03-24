#define _CRT_SECURE_NO_WARNINGS

#include <string.h>
#include <iostream>

class String
{
public:
	String(const char* str = NULL);
	String(const String& other);

	~String(void);
	String& operator = (const String &other);

	friend std::ostream& operator << (std::ostream &out, const String &s1);

private:
	char* m_date;
};

String::String(const char* str)
{
	if (str == NULL)
	{
		m_date = new char[1];
		*m_date = '\0';
	}
	else
	{
		int length = strlen(str);
		m_date = new char[length + 1];
		strcpy(m_date, str);
	}
}

String::~String(void)
{
	delete[] m_date;
}

String::String(const String& other)
{
	int length = strlen(other.m_date);
	m_date = new char[length + 1];
	strcpy(m_date, other.m_date);
}
// ¸³Öµº¯Êý
String& String::operator = (const String & other)
{
	if (this == &other)
		return *this;
	delete[] m_date;
	int length = strlen(other.m_date);
	m_date = new char[length + 1];
	strcpy(m_date, other.m_date);
	return *this;
}
 std::ostream& operator << (std::ostream &out, const String &s1)
{
	out << s1.m_date;
	return out;
}
int main()
{
	char * str = "ancvcv";
	String a(str);

	std::cout << a;

	system("pause");
	return 0;

}