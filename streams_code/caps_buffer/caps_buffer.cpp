// Copyright 2007 Edd Dawson.
// Distributed under the Boost Software License, Version 1.0.
// See accompanying file BOOST_LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt

#include "caps_buffer.hpp"

#include <cctype>
#include <ostream>
#include <functional>
#include <cassert>

caps_buffer::caps_buffer(std::ostream &sink, std::size_t buff_sz) :
    cap_next_(true),
    sink_(sink),
    buffer_(buff_sz + 1)
{
    sink_.clear();
    char *base = &buffer_.front();
    setp(base, base + buffer_.size() - 1);
}

caps_buffer::int_type caps_buffer::overflow(int_type ch)
{
    if (sink_ && ch != traits_type::eof())
    {
        assert(std::less_equal<char *>()(pptr(), epptr()));
        *pptr() = char(ch);
        pbump(1);
        if (do_caps_and_flush())
            return ch;
    }

    return traits_type::eof();
}

int caps_buffer::sync()
{
    return do_caps_and_flush() ? 0 : -1;
}

bool caps_buffer::do_caps_and_flush()
{
    for (char *p = pbase(), *e = pptr(); p != e; ++p)
    {
        if (*p == '.')
            cap_next_ = true;
        else if (std::isalpha(*p))
        {
            if (cap_next_)
                *p = char(std::toupper(*p));

            cap_next_ = false;
        }
    }
    std::ptrdiff_t n = pptr() - pbase();
    pbump(-n);

    return sink_.write(pbase(), n);
}
