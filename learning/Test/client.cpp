/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogmart <diogmart@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 12:33:42 by diogmart          #+#    #+#             */
/*   Updated: 2023/11/08 14:18:55 by diogmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.hpp"
#include <netdb.h>

using namespace std;

int main()
{
    int client, server;
    int portNum = 1500; // the server and clients ip are the same
    bool isExit = false;
    int bufsize = 1024;
    char buffer[bufsize];
    char *ip = "127.0.0.1";

    struct sockaddr_in server_addr;

    // init socket

    client = socket(AF_INET, SOCK_STREAM, 0);

    if (client < 0)
    {
        cout << "Error: couldn't establish a connection." << endl;
        exit(1);
    }

    cout << "Client socket created!" << endl;

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(portNum);

    // connecting socket server

    if (connect(client, (struct sockaddr*)&server_addr, sizeof(server_addr)) == 0)
    {
        cout << "Connecting to server..." << endl;
    }

    recv(client, buffer, bufsize, 0);
    cout << "Connection confirmed!" << endl;

    cout << "Enter # to end the connection" << endl;

    do {
        cout << "Client: ";
        do {
            cin >> buffer;
            send(client, buffer, bufsize, 0);
            if (*buffer == '#')
            {
                send(client, buffer, bufsize, 0);
                *buffer = '*';
                isExit = true;
            }
        } while (*buffer != '*');

        cout << "Server: ";
        do {
            recv(client, buffer, bufsize, 0);
            cout << buffer << " ";
            if (*buffer == '#')
            {
                *buffer = '*';
                isExit = true;
            }
        } while (*buffer != '*');

        cout << endl;
    } while (!isExit);

    cout << "Connection terminated!" << endl;
    cout <<"Goodbye!" << endl;

    close(client);
    return (0);
}