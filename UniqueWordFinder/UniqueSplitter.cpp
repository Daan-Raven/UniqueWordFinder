#include "UniqueSplitter.h"
#include <sstream>
#include <conio.h>

wstring ReadWordsString() {
	cdbg << L"Вызвана функция ReadWordsString()." << endl;
	wstring str;
	const wstring readMsg = L"Введите несколько слов через запятую (без пробелов): ";
	wcout << readMsg;
	wchar_t ch;
	// Пока не введена точка и хотя бы один символ - продолжаем ввод.

	while ((ch = _getwche()) != L'.' || str.empty() || str.at(str.length() - 1) == L',') {
		if ((ch >= L'A' && ch <= L'Z') || ((ch == L'.'|| ch == L',') && str.length() != 0 && str.at(str.length()-1) != L','))
			str.push_back(ch);
		else if (ch == 0x8 && str.length() != 0) {
			str.pop_back();
			wcout << L" \b";
		}
		else if (ch == 0x8)
			wcout << L' ';
		else
		{
			if (ch == L'.')
				wcout << L"\nВы не ввели слово. Попробуйте еще...\n";
			else
				wcout << L"\nВы ввели недопустимый символ. Попробуйте еще...\n";
			wcout << readMsg << str;
		}
	}
	wcout << endl;

	str.push_back(L'.');
	return str;
}

UniqueSplitter::UniqueSplitter(const std::wstring& str) : mString(str) {
	cdbg << L"Вызван конструктор UniqueSplitter::UniqueSplitter(\"" << str << L"\")." << endl;
}

vector<wstring> UniqueSplitter::GetUniqueWords() const {
	cdbg << L"Вызван метод UniqueSplitter::GetUniqueWords()." << endl;

	vector<wstring> words;

	// Получаем итератор, указывающий на начало строки
	auto current (mString.begin());
	// Идея этого цикла взята из STL C++17 Book - Chapter 06 - split.cpp
	while (current != mString.end()) {
		// Получаем итератор, указывающий на запятую от current итератора
		auto sliceEnd(find(current, mString.end(), L','));
		// Создаем строку от current до sliceEnd
		auto str(wstring(current, sliceEnd));
		// Если запятую не нашли - значит это последнее слово
		if (sliceEnd == mString.end())
			// тогда убираем точку в конце
			str = str.substr(0, str.length() - 1);

		// Проверяем, есть ли уже это слово в векторе
		if (find(words.begin(), words.end(), str) == words.end())
			// если нет - заносим в вектор
			words.push_back(str);
		
		// Если это последнее слово - выходим из цикла
		if (sliceEnd == mString.end())
			break;
		current = next(sliceEnd);
	}

	return words;
}