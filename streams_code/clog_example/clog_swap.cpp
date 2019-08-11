// Copyright 2007 Edd Dawson.
// Distributed under the Boost Software License, Version 1.0.
// See accompanying file BOOST_LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt

#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>

int main()
{
	std::ostringstream oss;

	// Make clog use the buffer from oss
	std::streambuf *former_buff = std::clog.rdbuf(oss.rdbuf());

	std::clog << "This will appear in oss!" << std::flush;

	std::cout << oss.str() << '\n';

	// Give clog back its previous buffer
	std::clog.rdbuf(former_buff);

	return 0;
}
