#include "UniqueSplitter.h"
#include "WideException.h"
#include <sstream>
#include <conio.h>

const int MAX_WORDS = 30;
const int MAX_LETTERS = 5;

wstring ReadWordsString() {
	cdbg << L"Вызвана функция ReadWordsString()." << endl;
	wstring wordsString; // строка слов
	auto readMsg = L"Введите несколько слов через запятую (без пробелов): ";
	wcout << readMsg;
	wchar_t ch; // считываемый символ
	unsigned letterCount = 0, wordCount = 0; // счетчики количества букв и слов
	// Пока не введена точка и хотя бы один символ - продолжаем ввод.
	while ((ch = _getwche()) != L'.' || wordCount == 0 || letterCount == 0) {
		// введенный символ - латинская заглавная буква и количество букв меньше максимально допустимого
		if (ch >= L'A' && ch <= L'Z' && letterCount < MAX_LETTERS) {
			wordsString.push_back(ch);
			letterCount++;
		}
		// введенный символ - запятая, введен хотя бы один символ и одно слово, количество меньше
		// максимально допустимого и с условием на то, что это не последнее слово 
		else if (ch == L',' && letterCount != 0 && wordCount < MAX_WORDS - 1) {
			wordsString.push_back(ch);
			letterCount = 0;
			wordCount++;
		}
		// введенный символ - возврат каретки (backspace)
		else if (ch == 0x8) {
			// если нет ни одного символа - переводим каретку обратно вперед
			if (letterCount == 0 && wordCount == 0) {
				wcout << L' ';
			}
			else {
				wordsString.pop_back();
				wcout << L" \b";
				// введен хотя бы один символ
				if (letterCount != 0) {
					letterCount--;
				}
				// введено хотя бы одно слово
				else if (wordCount != 0) {
					wordCount--;
					letterCount = wordsString.length() - wordsString.find_last_of(L",") - 1;
				}
			}
		}
		// блок условий для вывода сообщения об ошибке и отображения введенной строки до этой ошибки
		else {
			wcout << endl;
			if (ch >= L'A' && ch <= L'Z' && wordCount < MAX_WORDS - 1) {
				wcout << L"Превышен лимит количества букв! Перейдите к вводу следующего слова с помощью ',' или завершите ввод с помощью '.'.";
			}
			else if (ch >= L'A' && ch <= L'Z') {
				wcout << L"Превышен лимит количества букв и слов! Завершите ввод с помощью '.'.";
			}
			else if (ch == L',' && wordCount == MAX_WORDS - 1 && letterCount != 0) {
				wcout << L"Превышен лимит количества слов! Завершите ввод с помощью '.'.";
			}
			else if (ch = L',' && letterCount == 0) {
				wcout << L"Не введено ни одной буквы для текущего слова! Введите хотя бы одну букву.";
			}
			else {
				wcout << L"Введен недопустимый символ! Разрешены заглавные буквы латинского алфавита, запятая и точка.";
			}
			wcout << endl << readMsg << wordsString;
		}
	}
	wcout << endl;

	wordsString.push_back(L'.');
	return wordsString;
}

UniqueSplitter::UniqueSplitter(const std::wstring& str) : mString(str) {
	cdbg << L"Вызван конструктор UniqueSplitter::UniqueSplitter(\"" << str << L"\")." << endl;
}


template <typename T>
static void UniqueAdd(vector<T>& array, const T& value) {
	cdbg << L"Вызвана функция UniqueAdd(array, \"" << value << "\")." << endl;
	if (find(array.begin(), array.end(), value) == array.end())
		array.push_back(value);
}

vector<wstring_view> UniqueSplitter::GetUniqueWords() const {
	cdbg << L"Вызван метод UniqueSplitter::GetUniqueWords()." << endl;

	vector<wstring_view> words;

	size_t found;
	wstring_view view(mString.c_str(), mString.length());
	for (auto it = view.begin(); it != view.end(); it++) {
		if ((*it < L'A' || *it > L'Z') && *it != L',' && *it != L'.')
			throw WideException(L"Обнаружен недопустимый символ на позиции " + to_wstring(view.find(*it)) + L"!");
	}

	while ((found = view.find(L",")) != wstring::npos) {
		UniqueAdd(words, view.substr(0, found));
		view = view.substr(found + 1);
	}
	UniqueAdd(words, view.substr(0, view.length() - 1));

	return words;
}
