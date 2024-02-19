#include "Whatsapp.h"
#include "Messager.h"
#include <iostream>

void Whatsapp::sendMessage(std::string message) {
    std::cout << "User: " << user << std::endl
              << "Mensaje: " << message << std::endl
              << "Mensaje enviado mediante Whatsapp" << std::endl;
}

void Whatsapp::setUser(std::string user) {
    this->user = user;
}

std::string Whatsapp::getUser() const {
    return user;
}
