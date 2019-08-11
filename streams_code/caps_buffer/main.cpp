// Copyright 2007 Edd Dawson.
// Distributed under the Boost Software License, Version 1.0.
// See accompanying file BOOST_LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt

#include <iostream>
#include <iomanip>

#include "caps_buffer.hpp"

int main()
{
	caps_buffer buff(std::cout);
	std::ostream out(&buff);

	out << 	"this is a test. "
			"we should see all sentences beginning with an initial capital letter. "
			"the end.";
	out << std::flush;

	return 0;
}
