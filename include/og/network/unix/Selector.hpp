/*
 * libOG, 2020
 *
 * Name: Selector.hpp
 *
*/

#pragma once

#include "og/network/IBaseSelector.hpp"

namespace og {

//! \brief The epoll specialized version of the selector
//!
class Selector : public IBaseSelector {
public:

	//! \brief Default constructor
	//!
	Selector();

	//! \brief Destructor
	//!
	~Selector();

	//! \brief Add a new socket to the poll list
	//!
	//! \param handle The raw socket handle to register
	//!
	//! \param token Token to retrieve the events of the socket
	//!        handle descriptor
	//!
	//! \param concern The readiness that should be monitored
	//!
	//! \return zero if the socket handle was registered ;
	//!         -1 if an occured. Errno is set accordingly if a
	//!         system error occured
	//!
	int add(SocketHandle socket, Token token, Concern concern);

	//! \brief Remove a socket from the poll list
	//!
	//! \param The raw socket handle to deregister
	//!
	//! \return zero if the socket handle was deregistered ;
	//!         -1 if an error occured
	//!
	int remove(SocketHandle handle);
	
	//! \brief Poll pending events
	//!
	//! \param events The events container
	//!
	//! \param timeout The number of milliseconds to block for
	//!                waiting for events.
	//!
	//! \return The number of file descriptors ready for I/O ; zero if
	//!         no file descriptors became ready during before timeout ; 
	//!         -1 if an error occured. Errno is set accordingly if a
	//!         system error occured
	//!         
	int select(Events& events, int64_t timeout);

private:

	int m_poll_fd; //!< The epoll file descriptor

}; // class Selector

} // namespace og
