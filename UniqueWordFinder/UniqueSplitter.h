#ifndef UNIQUE_SPLITTER_HEADER_PROTECTION
#define UNIQUE_SPLITTER_HEADER_PROTECTION

#include <iostream>
#include <string>
#include <string_view>
#include <vector>

using namespace std;

#ifdef _DEBUG
#define cdbg wcout
#else
#define cdbg 0 && wcout
#endif

// Функция чтения из консоли
wstring ReadWordsString();

class UniqueSplitter
{
public:
	// Конструктор, задающий строку для разбора
	UniqueSplitter(const wstring& str);
	// Метод получения уникальных слов из строки
	vector<wstring_view> GetUniqueWords() const;
private:
	wstring mString; // строка
};

#endif // UNIQUE_SPLITTER_HEADER_PROTECTION