/**
 * user_interface.cpp
 *
 * Copyright (c) 2018, Denis Kovalchuk <deniskovjob@gmail.com>
 *
 * This code is licensed under a MIT-style license.
 */

#include "user_interface.hpp"
#include "resources.hpp"
#include "local_exception.hpp"
#include "tools.hpp"
#include <iostream>
#include <vector>

namespace ftp
{

using std::string;
using std::vector;
using std::cout;
using std::endl;

void user_interface::run()
{
    while (true)
    {
        string user_input = tools::read_line("ftp> ");

        string command = tools::get_command(user_input);
        vector<string> arguments = tools::get_arguments(user_input);

        try
        {
            ftp_client_.execute_command(command, arguments);

            if (command == command::local::exit)
            {
                return;
            }
        }
        catch (const local_exception & ex)
        {
            cout << ex.what() << endl;
        }
    }
}

} // namespace ftp
