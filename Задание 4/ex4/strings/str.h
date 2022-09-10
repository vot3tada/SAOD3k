#pragma once
class str
{
	char* m_pszText;
	public:
		operator const char* ()const
		{
			return m_pszText;
		}
		str() 	//Конструктор “по умолчанию” (default)*
		{
			m_pszText = new char[1]{ 0 };
		}
		str(const char* p)
		{
			if (p) {
				m_pszText = new char[strlen(p) + 1];
				strcpy_s(m_pszText, strlen(p) + 1, p);
			}
			else
				m_pszText = new char[1]{ 0 };
		}
		~str() 
		{ 
			delete[]m_pszText;
		}
		inline str(const str& s) //Константная ссылка на объект
		{
			m_pszText = new char[strlen(s.m_pszText) + 1];
			strcpy_s(m_pszText,
				strlen(s.m_pszText) + 1,
				s.m_pszText);
		}
		inline const str& operator = (const str& s) //Константная ссылка на объект
		{
			if (&s == this) return *this;
			delete[] m_pszText;	 //Освобождаем текущие данные					//Дальше просто копирование
			m_pszText = new char[strlen(s.m_pszText) + 1];
			strcpy_s(m_pszText,
				strlen(s.m_pszText) + 1,
				s.m_pszText);
			return *this;
		}
		inline str& operator += (const char* sz)
		{
			char* oldstr = new char[strlen(m_pszText)];
			for (char* p1 = oldstr, *p2 = m_pszText; *p1++ = *p2++;);
			delete[] m_pszText;
			m_pszText = new char[strlen(sz) + strlen(oldstr) + 1];
			strcpy_s(m_pszText,
				strlen(oldstr) + 1,
				oldstr);
			strcpy_s(m_pszText + strlen(sz),
				strlen(sz) + 1,
				sz);
			return *this;
		}
		inline str operator +(const char* sz) const
		{
			char* newstr = new char[strlen(m_pszText) + strlen(sz) + 1];
			strcpy_s(newstr,
				strlen(m_pszText) + 1,
				m_pszText);
			strcpy_s(newstr + strlen(m_pszText),
				strlen(sz) + 1,
				sz);
			return str(newstr);
		}
};

