/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diogmart <diogmart@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 14:27:49 by diogmart          #+#    #+#             */
/*   Updated: 2023/11/07 12:13:46 by diogmart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "webserv.hpp"

int main(int argc, char **argv) {
    
    if (argc != 2) {
        std::cout << "Error: wrong number of arguments.\nTry: \"./webserv [configuration file]\"" << std::endl;
        return (1);
    }
    (void)argv;
    
}
