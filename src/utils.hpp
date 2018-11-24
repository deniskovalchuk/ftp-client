/**
 * utils.hpp
 *
 * Copyright (c) 2018, Denis Kovalchuk <deniskovjob@gmail.com>
 *
 * This code is licensed under a MIT-style license.
 */

#ifndef FTP_CLIENT_UTILS_HPP
#define FTP_CLIENT_UTILS_HPP

#include <string>

using std::string;

namespace ftp
{
namespace utils
{

string read_line(const string & greeting);

} // namespace utils
} // namespace ftp
#endif //FTP_CLIENT_UTILS_HPP
