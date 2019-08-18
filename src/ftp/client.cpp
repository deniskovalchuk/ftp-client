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

#include <boost/lexical_cast.hpp>
#include "client.hpp"
#include "ftp_exception.hpp"

namespace ftp
{

using std::string;
using std::vector;
using std::make_unique;
using std::optional;
using std::ifstream;
using std::ofstream;
using std::unique_ptr;
using std::ios_base;

void client::open(const string & hostname, uint16_t port)
{
    reply_t reply;

    control_connection_.open(hostname, port);
    reply = control_connection_.recv();

    notify_of_reply(reply);
}

bool client::is_open() const
{
    return control_connection_.is_open();
}

void client::user(const string & username, const string & password)
{
    reply_t reply;

    control_connection_.send("USER " + username);
    reply = control_connection_.recv();

    notify_of_reply(reply);

    if (reply.code == 331)
    {
        // 331 User name okay, need password.
        control_connection_.send("PASS " + password);
        notify_of_reply(control_connection_.recv());
    }
    else if (reply.code == 332)
    {
        // 332 Need account for login.
        // Sorry, we don't support ACCT command.
    }
}

void client::cwd(const string & remote_directory)
{
    reply_t reply;

    control_connection_.send("CWD " + remote_directory);
    reply = control_connection_.recv();

    notify_of_reply(reply);
}

void client::list(const optional<string> & remote_directory)
{
    string command;

    if (remote_directory)
    {
        command = "LIST " + remote_directory.value();
    }
    else
    {
        command = "LIST";
    }

    unique_ptr<data_connection> data_connection = create_data_connection();

    if (!data_connection)
    {
        return;
    }

    reply_t reply;

    control_connection_.send(command);
    reply = control_connection_.recv();

    notify_of_reply(reply);

    if (reply.code >= 400)
    {
        return;
    }

    notify_of_reply(data_connection->recv());
    // Don't keep the data connection.
    data_connection.reset();

    reply = control_connection_.recv();

    notify_of_reply(reply);
}

void client::stor(const string & local_file, const string & remote_file)
{
    ifstream file(local_file, ios_base::binary);

    if (!file)
    {
        notify_of_error(
                (boost::format("Cannot open file: '%1%'.") % local_file).str());
        return;
    }

    unique_ptr<data_connection> data_connection = create_data_connection();

    if (!data_connection)
    {
        return;
    }

    reply_t reply;

    control_connection_.send("STOR " + remote_file);
    reply = control_connection_.recv();

    notify_of_reply(reply);

    if (reply.code >= 400)
    {
        return;
    }

    data_connection->send_file(file);
    // Don't keep the data connection.
    data_connection.reset();

    reply = control_connection_.recv();

    notify_of_reply(reply);
}

void client::retr(const string & remote_file, const string & local_file)
{
    ofstream file(local_file, ios_base::binary);

    if (!file)
    {
        notify_of_error(
            (boost::format("Cannot create file: '%1%'.") % local_file).str());
        return;
    }

    unique_ptr<data_connection> data_connection = create_data_connection();

    if (!data_connection)
    {
        return;
    }

    reply_t reply;

    control_connection_.send("RETR " + remote_file);
    reply = control_connection_.recv();

    notify_of_reply(reply);

    if (reply.code >= 400)
    {
        return;
    }

    data_connection->recv_file(file);
    // Don't keep the data connection.
    data_connection.reset();

    reply = control_connection_.recv();

    notify_of_reply(reply);
}

void client::pwd()
{
    reply_t reply;

    control_connection_.send("PWD");
    reply = control_connection_.recv();

    notify_of_reply(reply);
}

void client::mkd(const string & directory_name)
{
    reply_t reply;

    control_connection_.send("MKD " + directory_name);
    reply = control_connection_.recv();

    notify_of_reply(reply);
}

void client::type_i()
{
    reply_t reply;

    control_connection_.send("TYPE I");
    reply = control_connection_.recv();

    notify_of_reply(reply);
}

void client::size(const string & remote_file)
{
    reply_t reply;

    control_connection_.send("SIZE " + remote_file);
    reply = control_connection_.recv();

    notify_of_reply(reply);
}

void client::stat(const optional<string> & remote_file)
{
    string command;

    if (remote_file)
    {
        command = "STAT " + remote_file.value();
    }
    else
    {
        command = "STAT";
    }

    reply_t reply;

    control_connection_.send(command);
    reply = control_connection_.recv();

    notify_of_reply(reply);
}

void client::syst()
{
    reply_t reply;

    control_connection_.send("SYST");
    reply = control_connection_.recv();

    notify_of_reply(reply);
}

void client::noop()
{
    reply_t reply;

    control_connection_.send("NOOP");
    reply = control_connection_.recv();

    notify_of_reply(reply);
}

void client::quit()
{
    reply_t reply;

    control_connection_.send("QUIT");
    reply = control_connection_.recv();

    notify_of_reply(reply);

    control_connection_.close();
}

unique_ptr<data_connection> client::create_data_connection()
{
    reply_t reply;

    control_connection_.send("EPSV");
    reply = control_connection_.recv();

    notify_of_reply(reply);

    if (reply.code >= 400)
    {
        return nullptr;
    }

    uint16_t port = parse_epsv_port(reply.status_line);

    unique_ptr<data_connection> connection = make_unique<data_connection>();

    connection->open(control_connection_.ip(), port);

    return connection;
}

/**
 * The text returned in response to the EPSV command MUST be:
 *
 *     <text indicating server is entering extended passive mode> \
 *       (<d><d><d><tcp-port><d>)
 *
 * The first two fields contained in the parenthesis MUST be blank.  The
 * third field MUST be the string representation of the TCP port number
 * on which the server is listening for a data connection.  The network
 * protocol used by the data connection will be the same network
 * protocol used by the control connection.  In addition, the network
 * address used to establish the data connection will be the same
 * network address used for the control connection.  An example response
 * string follows:
 *
 *     Entering Extended Passive Mode (|||6446|)
 *
 * RFC 2428: https://tools.ietf.org/html/rfc2428
 */
uint16_t client::parse_epsv_port(const string & reply)
{
    uint16_t port;
    size_t begin;
    size_t end;

    begin = reply.find('|');
    if (begin == string::npos)
    {
        throw ftp_exception("Invalid server reply: %1%", reply);
    }

    // Skip '|||' characters.
    begin = begin + 3;

    end = reply.rfind('|');
    if (end == string::npos)
    {
        throw ftp_exception("Invalid server reply: %1%", reply);
    }

    string port_str = reply.substr(begin, end - begin);
    if (!boost::conversion::try_lexical_convert(port_str, port))
    {
        throw ftp_exception("Invalid server reply: %1%", reply);
    }

    return port;
}

void client::subscribe(event_observer *observer)
{
    observers_.push_back(observer);
}

void client::unsubscribe(event_observer *observer)
{
    observers_.remove(observer);
}

void client::notify_of_reply(const string & reply)
{
    for (const auto & observer : observers_)
        observer->on_reply(reply);
}

void client::notify_of_reply(const reply_t & reply)
{
    for (const auto & observer : observers_)
        observer->on_reply(reply.status_line);
}

void client::notify_of_error(const string & error)
{
    for (const auto & observer : observers_)
        observer->on_error(error);
}

} // namespace ftp
