/*
 * libOG, 2020
 *
 * Name: Socket.cc
 *
*/

#include "og/core/System.hpp"
#include "og/net/Internal.hpp"
#include "og/net/Socket.hpp"

using namespace og::net;

Socket::Socket(int domain, int type, int protocol)
	: m_handle(intl::bad_socket)
	, m_domain(domain)
	, m_type(type)
	, m_protocol(protocol)
{
	open();
}

Socket::~Socket()
{
	close();
}

int Socket::bind(const SocketAddr& address)
{
	return intl::bind(m_handle, address);
}

// https://docs.rs/crate/mio/0.7.5/source/src/sys/unix/net.rs
int Socket::open()
{
	SocketHandle new_h;

	new_h = intl::open(m_domain, m_type, m_protocol);
	if (new_h == intl::bad_socket)
		return -errno;

	if (m_handle != intl::bad_socket)
		close();

	m_handle = new_h;
	return 0;
}

int Socket::close()
{
	return intl::close(m_handle);
}
