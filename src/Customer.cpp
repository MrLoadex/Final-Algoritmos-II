#include "Customer.h"

Customer::Customer(int customerId, const std::string customerApellido)
    : id(customerId), apellido(customerApellido), preferredMessager(nullptr) {}

int Customer::getId() const {
    return id;
}

void Customer::setId(int newId) {
    id = newId;
}

std::string Customer::getApellido() const {
    return apellido;
}

void Customer::setApellido(const std::string newApellido) {
    apellido = newApellido;
}

std::shared_ptr<Messager> Customer::getPreferredMessager() const {
    return preferredMessager;
}

void Customer::setPreferredMessager(std::shared_ptr<Messager> messager) {
    preferredMessager = messager;
}

void Customer::setUserMessager(std::string customerUser) {
    preferredMessager->setUser(customerUser);
}
