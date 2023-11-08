/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogmart <diogmart@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 12:33:33 by diogmart          #+#    #+#             */
/*   Updated: 2023/11/08 14:20:19 by diogmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.hpp"

using namespace std;

int main()
{
    int client, server;
    int portNum = 1500;
    bool isExit = false;
    int bufsize = 1024;
    char buffer[bufsize];

    struct sockaddr_in server_addr;
    socklen_t size;

    // init socket

    client = socket(AF_INET, SOCK_STREAM, 0);
    if (client < 0) {
        cout << "Error: couldn't establish a connection." << endl;
        exit(1);
    }

    cout << "Server socket connection created!" << endl;

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htons(INADDR_ANY); // explanation below
    server_addr.sin_port = htons(portNum); // explanation below
/* 
HTONS FUNCTION:

    The htons() function is a commonly used function in network programming and is often found in C and C++ programming.
    It stands for "host to network short" and is used to convert a 16-bit unsigned short integer from the host byte order
    (the byte order used by the machine on which the code is running) to network byte order (big-endian).
    This conversion is necessary when working with networking protocols and data transmission between different systems
    because different systems may use different byte orders for representing multi-byte data types.
    
    The "host byte order" refers to the byte order used by the computer's CPU. On x86 and x86-64 architectures,
    the host byte order is little-endian, while many network protocols (like TCP/IP) use big-endian byte order for data transmission.
    
    By using htons(), you ensure that data sent over the network is in the expected byte order,
    which helps with interoperability between different systems. It's typically used before sending a 16-bit integer value over
    a network connection to make sure the value is in network byte order.
    
    Conversely, you have a corresponding function ntohs() (network to host short) for converting a 16-bit integer
    from network byte order to the host byte order when you receive data from the network.
*/

    // bind socket
    
    if (bind(client, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0)
    {
        cout << "Error: couldn't bind socket." << endl;
        exit(1);
    }

    size = sizeof(server_addr);
    cout << "Looking for clients..." << endl;

    // listen

    listen(client, 1);

    // accept client

    server = accept(client, (struct sockaddr*)&server_addr, &size);
    if (server < 0)
    {
        cout << "Error: couldn't accept client." << endl;
        exit(1);
    }
    
    while (server > 0)
    {
        strcpy(buffer, "Server connected!\n");
        send(server, buffer, bufsize, 0);

        cout << "Connected with client!" << endl;
        cout << "Enter # to end the connection" << endl;

        cout << "Client: ";
        do {
            recv(server, buffer, bufsize, 0);
            cout << buffer << " ";
            if (*buffer == '#')
            {
                *buffer = '*';
                isExit = true;
            }
        } while (*buffer != '*');

        do {
            cout << "\nServer: ";
            do {
                cin >> buffer;
                send(server, buffer, bufsize, 0);
                if (*buffer == '#')
                {
                    send(server, buffer, bufsize, 0);
                    *buffer = '*';
                    isExit = true;
                }
            } while (*buffer != '*');

            cout << "Client: ";
            do {
                recv(server, buffer, bufsize, 0);
                cout << buffer << " ";
                if (*buffer == '#')
                {
                    *buffer = '*';
                    isExit = true;
                }
            } while (*buffer != '*');
        } while (!isExit);

        cout << "Connection terminated!" << endl;
        cout <<"Goodbye!" << endl;
        isExit = false;
        exit(1);
    }
    close(client);
    return (0);
}