/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TcpServer.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogmart <diogmart@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 12:27:31 by diogmart          #+#    #+#             */
/*   Updated: 2023/11/13 15:42:30 by diogmart         ###   ########.fr       */
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
