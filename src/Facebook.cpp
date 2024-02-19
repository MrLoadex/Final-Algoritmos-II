#include "Facebook.h"
#include "Messager.h"
#include <iostream>


void Facebook::sendMessage(std::string message) {
    std::cout << "User: " << user << std::endl
              << "Mensaje: " << message << std::endl
              << "Mensaje enviado mediante Facebook" << std::endl;
}

void Facebook::setUser(std::string user) {
    this->user = user;
}

std::string Facebook::getUser() const {
    return user;
}
