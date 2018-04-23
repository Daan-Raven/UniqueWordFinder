#ifndef WIDEEXCEPTION_HEADER_PROTECTION
#define WIDEEXCEPTION_HEADER_PROTECTION
#include <string>
#include <cstdarg>
using namespace std;
class WideException {
public:
	WideException(const wstring& message) : mMessage(message) { }
	const wstring GetMessage() const noexcept { return mMessage; }
private:
	wstring mMessage;
};
#endif // WIDEEXCEPTION_HEADER_PROTECTION