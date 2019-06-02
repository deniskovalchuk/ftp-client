/*
 * MIT License
 *
 * Copyright (c) 2019 Denis Kovalchuk
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include <ncurses.h>
#include "ncurses_exception.hpp"

#ifndef FTP_CLIENT_NCURSES_INITIALIZER_HPP
#define FTP_CLIENT_NCURSES_INITIALIZER_HPP

namespace ncurses
{

class ncurses_initializer
{
public:
    ncurses_initializer()
    {
        if (!initscr())
            throw ncurses_exception("ncurses: cannot initialize library.");
    }

    ncurses_initializer(const ncurses_initializer &) = delete;

    ncurses_initializer & operator=(const ncurses_initializer) = delete;

    ~ncurses_initializer()
    {
        endwin();
    }
};

} // namespace ncurses
#endif //FTP_CLIENT_NCURSES_INITIALIZER_HPP
