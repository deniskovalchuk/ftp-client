/**
 * control_connection.cpp
 *
 * Copyright (c) 2018, Denis Kovalchuk <deniskovjob@gmail.com>
 *
 * This code is licensed under a MIT-style license.
 */

#include <boost/asio/connect.hpp>
#include <boost/asio/read.hpp>
#include <boost/asio/read_until.hpp>
#include <boost/asio/write.hpp>
#include "control_connection.hpp"

using std::istream;

namespace ftp
{

control_connection::control_connection(const string & hostname,
                                       const string & port)
        : socket_(io_context_),
          resolver_(io_context_)
{
    asio::connect(socket_, resolver_.resolve(hostname, port));
}

control_connection::~control_connection()
{
    socket_.close();
}

/**
 * RFC 959: https://tools.ietf.org/html/rfc959
 *
 * An FTP reply consists of a three digit number (transmitted as
 * three alphanumeric characters) followed by some text.
 */
string control_connection::get_reply_code(const string & line)
{
    if (line.size() < 3)
    {
        return string();
    }

    return line.substr(0, 3);
}

/**
 * RFC 959: https://tools.ietf.org/html/rfc959
 *
 * Thus the format for multi-line replies is that the first line
 * will begin with the exact required reply code, followed
 * immediately by a Hyphen, "-" (also known as Minus), followed by
 * text.
 */
bool control_connection::is_multiline_reply(const string & line) const
{
    if (line.size() < 4)
    {
        return false;
    }

    return line[3] == '-';
}

string control_connection::read()
{
    string line = read_line();

    if (!is_multiline_reply(line))
    {
        return line;
    }

    string reply = line;
    string reply_code = get_reply_code(line);

    while (true)
    {
        line = read_line();
        reply += line;

        /**
         * RFC 959: https://tools.ietf.org/html/rfc959
         *
         * The last line will begin with the same code, followed
         * immediately by Space <SP>, optionally some text, and the Telnet
         * end-of-line code.
         */
        string current_reply_code = get_reply_code(line);
        if (current_reply_code == reply_code && line.size() > 3 && line[3] == ' ')
        {
            break;
        }
    }

    return reply;
}

string control_connection::read_line()
{
    asio::read_until(socket_, read_buf_, '\n');
    istream is(&read_buf_);

    string line;
    getline(is, line);

    return line + "\n";
}

void control_connection::write(const string & command)
{
    asio::write(socket_, asio::buffer(command + "\r\n"));
}

} // namespace ftp