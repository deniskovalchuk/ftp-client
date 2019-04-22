/*
 * MIT License
 *
 * Copyright (c) 2018 Denis Kovalchuk
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

#include "resources.hpp"

namespace ftp
{
namespace command
{

using std::string;

namespace local
{
    const string open = "open";
    const string user = "user";
    const string cd = "cd";
    const string ls = "ls";
    const string get = "get";
    const string pwd = "pwd";
    const string mkdir = "mkdir";
    const string syst = "syst";
    const string ascii = "ascii";
    const string binary = "binary";
    const string size = "size";
    const string noop = "noop";
    const string close = "close";
    const string help = "help";
    const string exit = "exit";
} // namespace local

namespace remote
{
    const string user = "USER";
    const string password = "PASS";
    const string cd = "CWD";
    const string ls = "LIST";
    const string get = "RETR";
    const string pwd = "PWD";
    const string mkdir = "MKD";
    const string pasv = "PASV";
    const string syst = "SYST";
    const string ascii = "TYPE A";
    const string binary = "TYPE I";
    const string size = "SIZE";
    const string noop = "NOOP";
    const string close = "QUIT";
} // namespace remote
} // namespace command
} // namespace ftp
