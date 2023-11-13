/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TcpServer.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogmart <diogmart@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 12:27:31 by diogmart          #+#    #+#             */
/*   Updated: 2023/11/13 12:15:00 by diogmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "TcpServer.hpp"

TcpServer::TcpServer(const std::string& ip_address, int port) : m_ip_address(ip_address), m_port(port) {
    setupServer();
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

    return (0);
}

void TcpServer::closeServer(void) {
    close(this->m_socket);
    exit(0);
}
