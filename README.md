# File Transfer Protocol (FTP)

The File Transfer Protocol (FTP) is a standart network protocol used for the transfer of computer files between a client and server on a computer network.
FTP is built on a client-server model architecture and uses separate control and data connections between the client and the server. 

<h2>Communication and data transfer</h2>

FTP may run in active or passive mode, which determines how the data connection is established. In both cases, the client creates a TCP control connection from a random port to the FTP server command port 21.

* In active mode, the client starts listening for incoming data connections from the server on port N. It sends the FTP command "PORT N" to inform the server on which port it is listening. The server then initiates a data channel to the client.

* In situations where the client is behind a firewall and unable to accept incoming TCP connections, passive mode may be used. In this mode, the client uses the control connection to send the FTP command "PASV" to the server and then receives a server IP address and server port numbuer from server, which the client then uses to open a data connection.

<img src="https://gist.githubusercontent.com/deniskovalchuk/119c6b0134389b76129f7eda3ae602ff/raw/9f7aac03364943653bfe89c2901d00ae54648c30/ftp1.jpg">

<h2>Available commands</h2>
<ol>
  <li>open hostname [ port ] - Open new connection.</li>
  <li>user username - Send new user information.</li>
  <li>cd remote-directory - Change remote working directory.</li>
  <li>ls [ remote-directory ] - Print list of files in the remote directory.</li>
  <li>get remote-file [ local-file ] - Retrieve a copy of the file.</li>
  <li>pwd - Print the current working directory name.</li>
  <li>mkdir directory-name - Make a directory on the remote machine.</li>
  <li>ascii - Set ascii transfer type.</li>
  <li>binary - Set binary transfer type.</li>
  <li>size remote-file - Show size of remote file.</li>
  <li>syst - Show remote system type.</li>
  <li>close - Close current connection.</li>
  <li>help - Print list of FTP commands.</li>
  <li>exit - Exit program.</li>
</ol>

<h2>Requirements</h2>

* Compiler support for C++11/14
* Makefile
* <a href="https://www.boost.org/doc/libs/1_66_0/doc/html/boost_asio.html" target="_blank">Boost.Asio</a>
* <a href="https://www.boost.org/doc/libs/1_65_1/libs/filesystem/doc/index.htm" target="_blank">Boost.Filesystem</a>

<h2>References</h2>

* File Transfer Protocol [Электронный ресурс]. – Режим доступа: https://en.wikipedia.org/wiki/File_Transfer_Protocol
* <a href="https://github.com/deniskovalchuk/file-transfer-protocol/blob/master/RFC959.txt">RFC 959</a> File Transfer Protocol (FTP) Network Working Group J. Postel, J. Reynolds ISI October 1985
