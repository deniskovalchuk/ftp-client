/**
 * command_handler.cpp
 *
 * Copyright (c) 2018, Denis Kovalchuk <deniskovjob@gmail.com>
 *
 * This code is licensed under a MIT-style license.
 */

#ifndef FTP_CLIENT_COMMAND_HANDLER_HPP
#define FTP_CLIENT_COMMAND_HANDLER_HPP

#include <string>
#include <vector>
#include "control_connection.hpp"
#include "user_command.hpp"

using std::string;
using std::vector;
using std::unique_ptr;

namespace ftp
{

class command_handler
{
public:
    void execute(const user_command & user_command);

private:
    bool is_remote_command(const user_command & command) const;

    void open(const vector<string> & parameters);

    void close();

    void help();

    void exit();

    unique_ptr<control_connection> control_connection_;
};

} // namespace ftp
#endif //FTP_CLIENT_COMMAND_HANDLER_HPP
