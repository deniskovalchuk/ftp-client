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

#ifndef FTP_CLIENT_COMMANDS_HPP
#define FTP_CLIENT_COMMANDS_HPP

#include <string>

namespace command
{
    inline const char * const open = "open";
    inline const char * const user = "user";
    inline const char * const cd = "cd";
    inline const char * const ls = "ls";
    inline const char * const get = "get";
    inline const char * const pwd = "pwd";
    inline const char * const mkdir = "mkdir";
    inline const char * const stat = "stat";
    inline const char * const syst = "syst";
    inline const char * const binary = "binary";
    inline const char * const size = "size";
    inline const char * const noop = "noop";
    inline const char * const close = "close";
    inline const char * const help = "help";
    inline const char * const exit = "exit";
} // namespace commands
#endif //FTP_CLIENT_COMMANDS_HPP
