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
#include "../ftp_exception.hpp"
#include <boost/asio/read.hpp>
#include <boost/asio/write.hpp>

namespace ftp::detail
{

using std::string;
using std::ifstream;
using std::ofstream;
using std::array;

data_connection::data_connection()
    : io_context_(),
      socket_(io_context_)
{
}

void data_connection::open(const string & ip, uint16_t port)
{
    boost::system::error_code ec;

    boost::asio::ip::address address = boost::asio::ip::address::from_string(ip, ec);

    if (ec)
    {
        throw ftp_exception(ec, "Cannot get ip address");
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

        throw ftp_exception(ec, "Cannot open connection");
    }
}

bool data_connection::is_open() const
{
    return socket_.is_open();
}

void data_connection::close()
{
    boost::system::error_code ec;

    socket_.close(ec);

    if (ec)
    {
        throw ftp_exception(ec, "Cannot close connection");
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
        throw ftp_exception(ec, "Cannot receive reply");
    }

    return reply;
}

void data_connection::send_file(ifstream & file)
{
    boost::system::error_code ec;

    for (;;)
    {
        file.read(buffer_.data(), buffer_.size());

        if (file.fail() && !file.eof())
        {
            throw ftp_exception("Cannot send file.");
        }

        boost::asio::write(socket_, boost::asio::buffer(buffer_, file.gcount()), ec);

        if (ec)
        {
            throw ftp_exception(ec, "Cannot send file");
        }

        if (file.eof())
        {
            break;
        }
    }
}

void data_connection::recv_file(ofstream & file)
{
    boost::system::error_code ec;

    for (;;)
    {
        size_t len = socket_.read_some(boost::asio::buffer(buffer_), ec);

        if (ec == boost::asio::error::eof)
        {
            break;
        }
        else if (ec)
        {
            throw ftp_exception(ec, "Cannot receive file");
        }

        file.write(buffer_.data(), len);
    }
}

} // namespace ftp::detail
