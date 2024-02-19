#include "Instagram.h"
#include "Messager.h"
#include <iostream>


void Instagram::sendMessage(std::string message) {
    std::cout << "User: " << user << std::endl
              << "Mensaje: " << message << std::endl
              << "Mensaje enviado mediante Instagram" << std::endl;
}

void Instagram::setUser(std::string user) {
    this->user = user;
}

std::string Instagram::getUser() const {
    return user;
}