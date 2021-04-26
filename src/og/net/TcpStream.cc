/*
 * libOG, 2020
 *
 * Name: TcpStream.cxx
 *
*/

#include "og/net/Error.hpp"
#include "og/net/Internal.hpp"
#include "og/net/TcpStream.hpp"

using namespace og::net;

TcpStream::TcpStream() :
	Socket(AF_INET, SOCK_STREAM)
{
}

TcpStream::TcpStream(SocketFd socket) :
	Socket(socket)
{
}

int TcpStream::connect(const SocketAddr& address)
{
	int res = intl::connect(m_socket, address);

	if (res != -1)
		return og::net::Status::e_success;

	if (errno == EINPROGRESS)
		return og::net::Status::e_in_progress;

	return -errno;
}

int TcpStream::send(core::RawBufferConst data)
{
	ssize_t res = intl::send(m_socket, data);

	if (res != -1)
		return og::net::Status::e_success;

	if (errno == EWOULDBLOCK || errno == EAGAIN)
		return og::net::Status::e_would_block;

	return -errno;
}

int TcpStream::send(core::RawBufferConst data, std::size_t& sent)
{
	ssize_t res = intl::send(m_socket, data);

	if (res != -1)
	{
		sent = static_cast<std::size_t>(res);
		return og::net::Status::e_success;
	}
	
	sent = 0;
	if (errno == EWOULDBLOCK || errno == EAGAIN)
		return og::net::Status::e_would_block;

	return -errno;
}

int TcpStream::recv(core::RawBuffer& data)
{
	/* Provided buffer and length should be bigger
	 * than zero.
	*/
	ssize_t res = intl::recv(m_socket, data);

	if (res > 0)
		return og::net::Status::e_success;

	if (res == 0)
		return og::net::Status::e_closed;

	if (errno == EWOULDBLOCK || errno == EAGAIN)
		return og::net::Status::e_would_block;

	return -errno;
}

int TcpStream::recv(core::RawBuffer& data, size_t& received)
{
	ssize_t res = intl::recv(m_socket, data);

	if (res > 0)
	{
		received = static_cast<std::size_t>(res);
		return og::net::Status::e_success;
	}

	received = 0;
	if (res == 0)
		return og::net::Status::e_closed;

	if (errno == EWOULDBLOCK || errno == EAGAIN)
		return og::net::Status::e_would_block;

	return -errno;
}
