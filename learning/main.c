/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfaustin <kfaustin@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 12:08:38 by kfaustin          #+#    #+#             */
/*   Updated: 2023/11/02 15:25:18 by kfaustin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

#include <sys/socket.h>
#include <netinet/in.h>

//General
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/*
 *  1 - Create the socket
    2 - Identify the socket
    3 - On the server, wait for an incoming connection
    4 - Send and receive messages
    5 - Close the socket
 */

void	write_fd_msg_exit(int fd, char* msg) {
	write(fd, msg, strlen(msg));
	exit (1);
}

int main(int argc, char **argv) {
	int	server_fd;
	int	new_socket;
	/*
	 * (domain, or address family): communication domain in which the socket should be created.
	 * 	Some of address families are AF_INET (IP), AF_INET6 (IPv6), AF_UNIX (local channel, similar to pipes),
	 * 	AF_ISO (ISO protocols), and AF_NS (Xerox Network Systems protocols).
	 *
	 * (type): type of service. This is selected according to the properties required by the application: SOCK_STREAM
	 * 	(virtual circuit service), SOCK_DGRAM (datagram service), SOCK_RAW (direct IP service).
	 *
	 * (protocol): indicate a specific protocol to use in supporting the sockets operation. This is useful in cases
	 * 	where some families may have more than one protocol to support a given type of service. The return value is a
	 * 	file descriptor (a small integer).
	 *
	 *	For TCP/IP sockets, we want to specify the IP address family (AF_INET) and virtual circuit service (SOCK_STREAM).
	 * 	Since there’s only one form of virtual circuit service, there are no variations of the protocol, so the last argument, protocol, is zero.
	 */
	if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		write_fd_msg_exit(STDERR_FILENO, "Cannot create socket\n")
	printf("Socket: %d\n", server_fd);
	/*struct sockaddr_in
	{
		__uint8_t         sin_len; //Differ based on the type of transport used
		sa_family_t       sin_family; //The address family we used when we set up the socket. In our case, it’s AF_INET.
		in_port_t         sin_port; //The port number (the transport address). You can explicitly assign a transport address (port) or allow the operating system to assign one. If you’re a client and won’t be receiving incoming connections, you’ll usually just let the operating system pick any available port number by specifying port 0. If you’re a server, you’ll generally pick a specific number since clients will need to know a port number to connect to.
		struct in_addr    sin_addr; //The address for this socket. This is just your machine’s IP address. With IP, your machine will have one IP address for each network interface. For example, if your machine has both Wi-Fi and ethernet connections, that machine will have two addresses, one for each interface. Most of the time, we don’t care to specify a specific interface and can let the operating system use whatever it wants. The special address for this is 0.0.0.0, defined by the symbolic constant INADDR_ANY.
		char              sin_zero[8];
	};*/
	struct sockaddr_in	address; //Transport address
	// Macro defined PORT 8080
	// int bind(int socket, const struct sockaddr *address, socklen_t address_len);
	memset(&address, 0, sizeof(address));
	address.sin_family = AF_INET;
	address.sin_port = htons(PORT); // htons converts a short integer (e.g. port) to a network representation
	address.sin_addr.s_addr = htonl(INADDR_ANY); // htonl converts a long integer (e.g. address) to a network representation
	// prototype> int bind(int socket, const struct sockaddr *address, socklen_t address_len);
	if (bind(server_fd, (struct sockaddr *)(&address), sizeof(address)) < 0)
		write_fd_msg_exit(STDERR_FILENO, "bind failed\n");
	// prototype> int listen(int socket, int backlog);
	// Before a client can connect to a server, the server should have a socket that is prepared to accept the connections. The listen system call tells a socket that it should be capable of accepting incoming connections
	// backlog, defines the maximum number of pending connections that can be queued up before connections are refused.
	if (listen(server_fd, MAX_CONNECT) < 0)
		write_fd_msg_exit(STDERR_FILENO, "In listen\n");
	// prototype> int accept(int socket, struct sockaddr *restrict address, socklen_t *restrict address_len);
	// The accept system call grabs the first connection request on the queue of pending connections (set up in listen) and creates a new socket for that connection.
	// The original socket that was set up for listening is used only for accepting connections, not for exchanging data. By default, socket operations are synchronous, or blocking, and accept will block until a connection is present on the queue.
	// The first parameter, socket, is the socket that was set for accepting connections with listen.
	// The second parameter, address, is the address structure that gets filed in with the address of the client that is doing the connect. This allows us to examine the address and port number of the connecting socket if we want to.
	// The third parameter is filled in with the length of the address structure.
	socklen_t	addrlen;
	addrlen = sizeof(struct sockaddr);
	if ((new_socket = accept(server_fd, (struct sockaddr *)(&address), (socklen_t *)(&addrlen))) < 0)
		write_fd_msg_exit(STDERR_FILENO, "In accept");
	return (0);
}

