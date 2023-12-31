/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TcpServer.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogmart <diogmart@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 12:27:31 by diogmart          #+#    #+#             */
/*   Updated: 2023/11/14 14:16:04 by diogmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "TcpServer.hpp"

TcpServer::TcpServer(std::string ip_address, int port) : m_ip_address(ip_address), m_port(port),
                                                         m_sockaddr(), m_sockaddr_len(sizeof(m_sockaddr))
{
    m_sockaddr.sin_family = AF_INET;
    m_sockaddr.sin_port = htons(m_port);
    m_sockaddr.sin_addr.s_addr = inet_addr(m_ip_address.c_str());

    if (setupServer() != 0)
        exitWithError("couldn't start server.");
}

TcpServer::~TcpServer() {
    closeServer();
}

int TcpServer::setupServer(void) {
    
    this->m_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (this->m_socket < 0) {
        exitWithError("couldn't create socket.");
        return (1);
    }

    if (bind(m_socket, (sockaddr *)&m_sockaddr, m_sockaddr_len) < 0) {
        exitWithError("couldn't bind socket.");
        return (1);
    }

    return (0);
}

void TcpServer::closeServer(void) {
    close(this->m_socket);
    exit(0);
}

void TcpServer::startListen(void) {
    
    if (listen(m_socket, 42) < 0) // the max number of clients is just a placeholder
        exitWithError("socket listen failed.");

    // look for connection and accept them
}

void TcpServer::acceptConnection(void) {
    // We need to accept the connection, store the new socket fd in a variable
    // and the new socket address in another struct ?
}

std::string TcpServer::buildResponse(void) {
    // The response should start with "HTTP/1.1 200 OK" if the resquest is successful.
    // Then there should be some more stuff, it could be a html file or something else

/*
    Basically, responses consist of the following elements:

    -The version of the HTTP protocol they follow.
    -A status code, indicating if the request was successful or not, and why.
    -A status message, a non-authoritative short description of the status code.
    -HTTP headers, like those for requests.
    -Optionally, a body containing the fetched resource.
*/
}

void TcpServer::sendResponse(void) {
    // We should use the send() function instead of write() as it gives us more
    // option on how to handle the content we send as well as being particularly 
    // useful for working with network sockets, such as those used in HTTP server development.
}
