#include "UniqueSplitter.h"

UniqueSplitter::UniqueSplitter(const std::wstring& str) : mString(str)
{
}

vector<wstring> UniqueSplitter::GetUniqueWords() const
{
	vector<wstring> words;

	auto current (mString.begin());

	while (current != mString.end()) {
		auto sliceEnd(find(current, mString.end(), L','));
		auto str(wstring(current, sliceEnd));
		if (sliceEnd == mString.end())
			str = str.substr(0, str.size() - 1);

		if (find(words.begin(), words.end(), str) == words.end())
			words.push_back(str);
		
		if (sliceEnd == mString.end())
			break;
		current = next(sliceEnd);
	}

	cdbg << words.size() << mString << endl;

	return words;
}
