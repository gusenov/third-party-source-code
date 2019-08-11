// Copyright 2007 Edd Dawson.
// Distributed under the Boost Software License, Version 1.0.
// See accompanying file BOOST_LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt

#include <iostream>
#include <istream>
#include <string>

#include "char_array_buffer.hpp"

int main()
{
	const char text[] = "This is the contents of an array!";
	char_array_buffer buff(text); // -1 for \0
	std::istream in(&buff);

	std::string s;
	while (in >> s)
		std::cout << "echo: " << s << '\n';
		
	in.clear();
	for (unsigned i = 0; i != 3; ++i)
		in.unget();
		
	if (in >> s)
		std::cout << "final: " << s << '\n';
		
	return 0;
}
