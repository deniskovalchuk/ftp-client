/**
 * resources.cpp
 *
 * Copyright (c) 2018, Denis Kovalchuk <deniskovjob@gmail.com>
 *
 * This code is licensed under a MIT-style license.
 */

#include "resources.hpp"

namespace ftp
{
namespace user_request
{
    const char * open = "open";
    const char * close = "close";
    const char * exit = "exit";
} // namespace user_request

namespace ftp_request
{
    const char * close = "QUIT";
} // namespace ftp_request

namespace error
{
    const char * invalid_request =
        "Invalid request. Use 'help' to display list of FTP commands.";
    const char * not_connected = "Not connected.";
} // namespace error

namespace usage
{
    const char * open = "Usage: open <hostname> <port>";
} // namespace usage
} // namespace ftp
