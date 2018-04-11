#ifdef WIN32
#include <cstdio>
#include <fcntl.h>
#include <io.h>
#else
#include <locale>
#endif // !WIN32
#include "UniqueSplitter.h"

int main() {
#ifdef WIN32
	_setmode(_fileno(stdout), _O_U16TEXT);
	_setmode(_fileno(stdin), _O_U16TEXT);
#else
	locale currentLocale;
	setlocale(LC_ALL, "");
#endif // !WIN32
	for (int i = 1; ; i++) {
		cdbg << L"Òåñò ¹" << i << endl;
		UniqueSplitter uniqueSplitter(L"ÊÓÐÈÖÀ,ÏÅÒÓÕ,ÎËÅÍÜ,ÈÍÄÞÊ,ÏÅÒÓÕ,ÎËÅÍÜ.");
		
		auto words = uniqueSplitter.GetUniqueWords();
		wcout << L"Word count: " << words.size() << endl;
		for (auto i = words.begin(); i != words.end(); i++) {
			wcout << *i << endl;
		}

		wcout << endl << "-----------------------------------------------" << endl;
		wcin.get();
	}
#ifndef WIN32
	setlocale(LC_ALL, currentLocale.name().c_str());
#endif // !WIN32
}