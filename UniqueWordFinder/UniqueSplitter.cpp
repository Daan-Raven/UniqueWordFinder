#include "UniqueSplitter.h"
#include "WideException.h"
#include <sstream>
#include <conio.h>

const int MAX_WORDS = 30;
const int MAX_LETTERS = 5;

wstring ReadWordsString() {
	cdbg << L"������� ������� ReadWordsString()." << endl;
	wstring wordsString; // ������ ����
	auto readMsg = L"������� ��������� ���� ����� ������� (��� ��������): ";
	wcout << readMsg;
	wchar_t ch; // ����������� ������
	unsigned letterCount = 0, wordCount = 0; // �������� ���������� ���� � ����
	// ���� �� ������� ����� � ���� �� ���� ������ - ���������� ����.
	while ((ch = _getwche()) != L'.' || wordCount == 0 || letterCount == 0) {
		// ��������� ������ - ��������� ��������� ����� � ���������� ���� ������ ����������� �����������
		if (ch >= L'A' && ch <= L'Z' && letterCount < MAX_LETTERS) {
			wordsString.push_back(ch);
			letterCount++;
		}
		// ��������� ������ - �������, ������ ���� �� ���� ������ � ���� �����, ���������� ������
		// ����������� ����������� � � �������� �� ��, ��� ��� �� ��������� ����� 
		else if (ch == L',' && letterCount != 0 && wordCount < MAX_WORDS - 1) {
			wordsString.push_back(ch);
			letterCount = 0;
			wordCount++;
		}
		// ��������� ������ - ������� ������� (backspace)
		else if (ch == 0x8) {
			// ���� ��� �� ������ ������� - ��������� ������� ������� ������
			if (letterCount == 0 && wordCount == 0) {
				wcout << L' ';
			}
			else {
				wordsString.pop_back();
				wcout << L" \b";
				// ������ ���� �� ���� ������
				if (letterCount != 0) {
					letterCount--;
				}
				// ������� ���� �� ���� �����
				else if (wordCount != 0) {
					wordCount--;
					letterCount = wordsString.length() - wordsString.find_last_of(L",") - 1;
				}
			}
		}
		// ���� ������� ��� ������ ��������� �� ������ � ����������� ��������� ������ �� ���� ������
		else {
			wcout << endl;
			if (ch >= L'A' && ch <= L'Z' && wordCount < MAX_WORDS - 1) {
				wcout << L"�������� ����� ���������� ����! ��������� � ����� ���������� ����� � ������� ',' ��� ��������� ���� � ������� '.'.";
			}
			else if (ch >= L'A' && ch <= L'Z') {
				wcout << L"�������� ����� ���������� ���� � ����! ��������� ���� � ������� '.'.";
			}
			else if (ch == L',' && wordCount == MAX_WORDS - 1 && letterCount != 0) {
				wcout << L"�������� ����� ���������� ����! ��������� ���� � ������� '.'.";
			}
			else if (ch = L',' && letterCount == 0) {
				wcout << L"�� ������� �� ����� ����� ��� �������� �����! ������� ���� �� ���� �����.";
			}
			else {
				wcout << L"������ ������������ ������! ��������� ��������� ����� ���������� ��������, ������� � �����.";
			}
			wcout << endl << readMsg << wordsString;
		}
	}
	wcout << endl;

	wordsString.push_back(L'.');
	return wordsString;
}

UniqueSplitter::UniqueSplitter(const std::wstring& str) : mString(str) {
	cdbg << L"������ ����������� UniqueSplitter::UniqueSplitter(\"" << str << L"\")." << endl;
}


template <typename T>
static void UniqueAdd(vector<T>& array, const T& value) {
	cdbg << L"������� ������� UniqueAdd(array, \"" << value << "\")." << endl;
	if (find(array.begin(), array.end(), value) == array.end())
		array.push_back(value);
}

vector<wstring_view> UniqueSplitter::GetUniqueWords() const {
	cdbg << L"������ ����� UniqueSplitter::GetUniqueWords()." << endl;

	vector<wstring_view> words;

	size_t found;
	wstring_view view(mString.c_str(), mString.length());
	for (auto it = view.begin(); it != view.end(); it++) {
		if ((*it < L'A' || *it > L'Z') && *it != L',' && *it != L'.')
			throw WideException(L"��������� ������������ ������ �� ������� " + to_wstring(view.find(*it)) + L"!");
	}

	while ((found = view.find(L",")) != wstring::npos) {
		UniqueAdd(words, view.substr(0, found));
		view = view.substr(found + 1);
	}
	UniqueAdd(words, view.substr(0, view.length() - 1));

	return words;
}
