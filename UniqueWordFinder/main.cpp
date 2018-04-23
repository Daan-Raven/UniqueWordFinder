#include <cstdio>
#include <fcntl.h>
#include <io.h>
#include "UniqueSplitter.h"
#include "WideException.h"

const wchar_t* gHeader = L"������������ ������ �6: ��������-��������������� ��������� ���������� ������ � �����. ����������� ����� string.";
const wchar_t* gAuthor = L"�������� ������� ������ 611��� ���� ������.";
const wchar_t* gDescription = L"���� ������������������, ���������� �� 1 �� 30 ����, � ������ �� ������� �� 1 �� 5 ��������� (�������) ��������� ����; ����� ��������� ������� - �������, ����� ���������� ����� - �����. ������ �� ������� ��� �����, ������� ����������� � ������������������ �� ������ ����.";

int main() {
	_setmode(_fileno(stdout), _O_U16TEXT);
	_setmode(_fileno(stdin), _O_U16TEXT);
	wcout << gHeader << endl << gAuthor << endl << gDescription << endl;
	for (int i = 1; ; i++) {
		wcout << endl << L"-----------------------------------------------" << endl;
		cdbg << L"���� �" << i << endl;
		auto str = ::ReadWordsString();
		UniqueSplitter uniqueSplitter(str);

		try {
			auto words(uniqueSplitter.GetUniqueWords());
			wcout << L"���������� ���������� ����: " << words.size() << endl <<
				L"������ ����: " << endl;
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