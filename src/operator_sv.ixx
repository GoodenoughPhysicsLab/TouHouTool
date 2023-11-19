export module operator_sv;

import <string_view>;

export ::std::string_view operator""_sv(const char* str, ::std::size_t)
{
	return ::std::string_view(str);
}