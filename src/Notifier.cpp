#include "Notifier.h"
#include <iostream>

std::shared_ptr<Customer> Notifier::getCustomer(std::shared_ptr<Reservation> reservation) {
    return reservation->getCustomer();
}

std::shared_ptr<Messager> Notifier::getPreferredMessager(std::shared_ptr<Customer> customer) {
    return customer->getPreferredMessager();
}

void Notifier::notify(std::shared_ptr<Reservation> reservation) {
    std::shared_ptr<Customer> customer = getCustomer(reservation);
    std::shared_ptr<Messager> messager = getPreferredMessager(customer);
    messager->sendMessage("Alquiler finalizado");
}
