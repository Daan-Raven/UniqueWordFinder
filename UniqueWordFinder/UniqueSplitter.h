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

// ������� ������ �� �������
wstring ReadWordsString();

class UniqueSplitter
{
public:
	// �����������, �������� ������ ��� �������
	UniqueSplitter(const wstring& str);
	// ����� ��������� ���������� ���� �� ������
	vector<wstring_view> GetUniqueWords() const;
private:
	wstring mString; // ������
};

#endif // UNIQUE_SPLITTER_HEADER_PROTECTION