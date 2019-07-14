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

#include "data_connection.hpp"
#include "ftp_exception.hpp"
#include <boost/asio/read.hpp>

namespace ftp
{

using std::string;
using std::ofstream;
using std::array;

data_connection::data_connection()
    : io_context_(),
      socket_(io_context_)
{
}

void data_connection::open(const string & ip, uint16_t port)
{
    boost::asio::ip::address address;
    boost::system::error_code ec;

    address = boost::asio::ip::address::from_string(ip, ec);

    if (ec)
    {
        throw ftp_exception("Cannot get ip address: %1%", ec.message());
    }

    boost::asio::ip::tcp::endpoint remote_endpoint(address, port);
    socket_.connect(remote_endpoint, ec);

    if (ec)
    {
        boost::system::error_code ignored;

        /*
         * If the connect fails, and the socket was automatically opened,
         * the socket is not returned to the closed state.
         *
         * https://www.boost.org/doc/libs/1_70_0/doc/html/boost_asio/reference/basic_stream_socket/connect/overload2.html
         */
        socket_.close(ignored);

        throw ftp_exception("Cannot open connection: %1%", ec.message());
    }
}

string data_connection::recv()
{
    boost::system::error_code ec;
    string reply;

    boost::asio::read(socket_, boost::asio::dynamic_buffer(reply), ec);

    if (ec == boost::asio::error::eof)
    {
        // Ignore eof.
    }
    else if (ec)
    {
        throw ftp_exception("Cannot receive reply: %1%", ec.message());
    }

    return reply;
}

void data_connection::recv_file(ofstream & file)
{
    boost::system::error_code ec;
    array<char, 4096> buffer = {};
    size_t len;

    for (;;)
    {
        len = socket_.read_some(boost::asio::buffer(buffer), ec);

        if (ec == boost::asio::error::eof)
        {
            break;
        }
        else if (ec)
        {
            throw ftp_exception("Cannot receive file: %1%", ec.message());
        }

        file.write(buffer.data(), len);
    }
}

} // namespace ftp
