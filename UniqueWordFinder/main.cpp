#include <cstdio>
#include <fcntl.h>
#include <io.h>
#include "UniqueSplitter.h"

int main() {
	_setmode(_fileno(stdout), _O_U16TEXT);
	_setmode(_fileno(stdin), _O_U16TEXT);
	// TODO: Вывести условия задачи и инструкцию.
	for (int i = 1; ; i++) {
		cdbg << L"Тест №" << i << endl;
		auto str = ::ReadWordsString();
		UniqueSplitter uniqueSplitter(str);

		auto words (uniqueSplitter.GetUniqueWords());
		wcout << L"Количество уникальных слов: " << words.size() << endl <<
			L"Список слов: " << endl;
		for (auto i = words.begin(); i != words.end(); i++) {
			wcout << *i << endl;
		}

		wcout << endl << L"-----------------------------------------------" << endl;
	}
	
	return 0;
}