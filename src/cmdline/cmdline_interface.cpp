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

#include "cmdline_interface.hpp"
#include "command.hpp"
#include "cmdline_exception.hpp"
#include "command_parser.hpp"
#include "ftp/ftp_exception.hpp"
#include "utils/utils.hpp"
#include <iostream>

using std::string;
using std::cout;
using std::endl;

using ftp::ftp_exception;

void cmdline_interface::run()
{
    for (;;)
    {
        try
        {
            string line = utils::read_line("ftp> ");

            if (line.empty())
            {
                continue;
            }

            auto [command, args] = parse_command(line);

            command_handler_.handle(command, args);

            if (command == command::exit)
            {
                break;
            }
        }
        catch (const cmdline_exception & ex)
        {
            cout << ex.what() << endl;
        }
        catch (const ftp_exception & ex)
        {
            cout << ex.what() << endl;
        }
    }
}
