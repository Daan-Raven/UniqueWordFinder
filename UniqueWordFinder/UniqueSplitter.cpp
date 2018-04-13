#include "UniqueSplitter.h"
#include <sstream>
#include <conio.h>

wstring ReadWordsString() {
	cdbg << L"������� ������� ReadWordsString()." << endl;
	wstring str;
	const wstring readMsg = L"������� ��������� ���� ����� ������� (��� ��������): ";
	wcout << readMsg;
	wchar_t ch;
	// ���� �� ������� ����� � ���� �� ���� ������ - ���������� ����.

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
				wcout << L"\n�� �� ����� �����. ���������� ���...\n";
			else
				wcout << L"\n�� ����� ������������ ������. ���������� ���...\n";
			wcout << readMsg << str;
		}
	}
	wcout << endl;

	str.push_back(L'.');
	return str;
}

UniqueSplitter::UniqueSplitter(const std::wstring& str) : mString(str) {
	cdbg << L"������ ����������� UniqueSplitter::UniqueSplitter(\"" << str << L"\")." << endl;
}

vector<wstring> UniqueSplitter::GetUniqueWords() const {
	cdbg << L"������ ����� UniqueSplitter::GetUniqueWords()." << endl;

	vector<wstring> words;

	// �������� ��������, ����������� �� ������ ������
	auto current (mString.begin());
	// ���� ����� ����� ����� �� STL C++17 Book - Chapter 06 - split.cpp
	while (current != mString.end()) {
		// �������� ��������, ����������� �� ������� �� current ���������
		auto sliceEnd(find(current, mString.end(), L','));
		// ������� ������ �� current �� sliceEnd
		auto str(wstring(current, sliceEnd));
		// ���� ������� �� ����� - ������ ��� ��������� �����
		if (sliceEnd == mString.end())
			// ����� ������� ����� � �����
			str = str.substr(0, str.length() - 1);

		// ���������, ���� �� ��� ��� ����� � �������
		if (find(words.begin(), words.end(), str) == words.end())
			// ���� ��� - ������� � ������
			words.push_back(str);
		
		// ���� ��� ��������� ����� - ������� �� �����
		if (sliceEnd == mString.end())
			break;
		current = next(sliceEnd);
	}

	return words;
}