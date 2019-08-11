// Copyright 2007 Edd Dawson.
// Distributed under the Boost Software License, Version 1.0.
// See accompanying file BOOST_LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt

#include <istream>
#include <iostream>
#include <string>

#if defined(__BORLANDC__)
	#include <stdio.h>
#else
	#include <cstdio>
#endif

#include "file_buffer.hpp"

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		std::cerr << "Please put the name of a file on the command line\n";
		return 1;
	}
	
	FILE *fptr = std::fopen(argv[1], "r");
	if (!fptr)
	{
		std::cerr << "Failed to open " << argv[1] << '\n';
		return 2;
	}

	std::istream in(new FILE_buffer(fptr, 1));

	std::string s;
	while (in >> s)
		std::cout << "echo: " << s << std::endl;

	std::fclose(fptr);

	return 0;
}
