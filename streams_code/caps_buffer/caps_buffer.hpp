// Copyright 2007 Edd Dawson.
// Distributed under the Boost Software License, Version 1.0.
// See accompanying file BOOST_LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt

#ifndef CAPS_BUFFER_HPP_1819_13042007_
#define CAPS_BUFFER_HPP_1819_13042007_

#include <streambuf>
#include <iosfwd>
#include <cstdlib>
#include <vector>

class caps_buffer : public std::streambuf
{
    public:
        explicit caps_buffer(std::ostream &sink, std::size_t buff_sz = 256);

    protected:
        bool do_caps_and_flush();

    private:
        int_type overflow(int_type ch);
        int sync();

        // copy ctor and assignment not implemented;
        // copying not allowed
        caps_buffer(const caps_buffer &);
        caps_buffer &operator= (const caps_buffer &);

    private:
        bool cap_next_;
        std::ostream &sink_;
        std::vector<char> buffer_;
};

#endif
