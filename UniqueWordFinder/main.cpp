#include <cstdio>
#include <fcntl.h>
#include <io.h>
#include "UniqueSplitter.h"
#include "WideException.h"

const wchar_t* gHeader = L"Лабораторная работа №6: Объектно-ориентированная обработка символьных данных и строк. Стандартный класс string.";
const wchar_t* gAuthor = L"Выполнил студент группы 611пст Заец Богдан.";
const wchar_t* gDescription = L"Дана последовательность, содержащая от 1 до 30 слов, в каждом из которых от 1 до 5 прописных (больших) латинских букв; между соседними словами - запятая, после последнего слова - точка. Выдать на дисплей все слова, которые встречаются в последовательности по одному разу.";

int main() {
	_setmode(_fileno(stdout), _O_U16TEXT);
	_setmode(_fileno(stdin), _O_U16TEXT);
	wcout << gHeader << endl << gAuthor << endl << gDescription << endl;
	for (int i = 1; ; i++) {
		wcout << endl << L"-----------------------------------------------" << endl;
		cdbg << L"Тест №" << i << endl;
		auto str = ::ReadWordsString();
		UniqueSplitter uniqueSplitter(str);

		try {
			auto words(uniqueSplitter.GetUniqueWords());
			wcout << L"Количество уникальных слов: " << words.size() << endl <<
				L"Список слов: " << endl;
			for (auto i = words.begin(); i != words.end(); i++) {
				wcout << *i << endl;
			}
		}
		catch (const WideException& exception) {
			wcout << exception.GetMessage() << endl;
		}
	}
	
	return 0;
}